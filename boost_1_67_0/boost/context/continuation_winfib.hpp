
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_CONTINUATION_H
#define BOOST_CONTEXT_CONTINUATION_H

#include <windows.h>

#include <boost/context/detail/config.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <memory>
#include <ostream>
#include <system_error>
#include <tuple>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/context/detail/disable_overload.hpp>
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
#include <boost/context/detail/exchange.hpp>
#endif
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/fixedsize_stack.hpp>
#include <boost/context/flags.hpp>
#include <boost/context/preallocated.hpp>
#include <boost/context/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4702)
#endif

namespace boost {
namespace context {
namespace detail {

// tampoline function
// entered if the execution context
// is resumed for the first time
template< typename Record >
static VOID WINAPI entry_func( LPVOID data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL activation_record {
    LPVOID                                                      fiber{ nullptr };
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
    activation_record                                       *   from{ nullptr };
    std::function< activation_record*(activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };

    static activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    activation_record() noexcept {
#if ( _WIN32_WINNT > 0x0600)
        if ( ::IsThreadAFiber() ) {
            fiber = ::GetCurrentFiber();
        } else {
            fiber = ::ConvertThreadToFiber( nullptr);
        }
#else
        fiber = ::ConvertThreadToFiber( nullptr);
        if ( BOOST_UNLIKELY( nullptr == fiber) ) {
            DWORD err = ::GetLastError();
            BOOST_ASSERT( ERROR_ALREADY_FIBER == err);
            fiber = ::GetCurrentFiber(); 
            BOOST_ASSERT( nullptr != fiber);
            BOOST_ASSERT( reinterpret_cast< LPVOID >( 0x1E00) != fiber);
        }
#endif
    }

    activation_record( stack_context sctx_) noexcept :
        sctx{ sctx_ },
        main_ctx{ false } {
    } 

    virtual ~activation_record() {
        if ( BOOST_UNLIKELY( main_ctx) ) {
            ::ConvertFiberToThread();
        } else {
            ::DeleteFiber( fiber);
        }
    }

    activation_record( activation_record const&) = delete;
    activation_record & operator=( activation_record const&) = delete;

    bool is_main_context() const noexcept {
        return main_ctx;
    }

    activation_record * resume() {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        current() = this;
        // context switch from parent context to `this`-context
        // context switch
        ::SwitchToFiber( fiber);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return detail::exchange( current()->from, nullptr);
#else
        return std::exchange( current()->from, nullptr);
#endif
    }

    template< typename Ctx, typename Fn >
    activation_record * resume_with( Fn && fn) {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        // returned by continuation::current()
        current() = this;
#if defined(BOOST_NO_CXX14_GENERIC_LAMBDAS)
        current()->ontop = std::bind(
                [](typename std::decay< Fn >::type & fn, activation_record *& ptr){
                    Ctx c{ ptr };
                    c = fn( std::move( c) );
                    if ( ! c) {
                        ptr = nullptr;
                    }
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    return exchange( c.ptr_, nullptr);
#else
                    return std::exchange( c.ptr_, nullptr);
#endif
                },
                std::forward< Fn >( fn),
                std::placeholders::_1);
#else
        current()->ontop = [fn=std::forward<Fn>(fn)](activation_record *& ptr){
            Ctx c{ ptr };
            c = fn( std::move( c) );
            if ( ! c) {
                ptr = nullptr;
            }
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
            return exchange( c.ptr_, nullptr);
#else
            return std::exchange( c.ptr_, nullptr);
#endif
        };
#endif
        // context switch
        ::SwitchToFiber( fiber);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return detail::exchange( current()->from, nullptr);
#else
        return std::exchange( current()->from, nullptr);
#endif
    }

    virtual void deallocate() noexcept {
    }
};

struct BOOST_CONTEXT_DECL activation_record_initializer {
    activation_record_initializer() noexcept;
    ~activation_record_initializer();
};

struct forced_unwind {
    activation_record   *   from{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool                    caught{ false };
#endif

    explicit forced_unwind( activation_record * from_) :
        from{ from_ } {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

template< typename Ctx, typename StackAlloc, typename Fn >
class capture_record : public activation_record {
private:
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( capture_record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx;
        // deallocate activation record
        p->~capture_record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    capture_record( stack_context sctx, StackAlloc && salloc, Fn && fn) noexcept :
        activation_record( sctx),
        salloc_( std::forward< StackAlloc >( salloc)),
        fn_( std::forward< Fn >( fn) ) {
    }

    void deallocate() noexcept override final {
        BOOST_ASSERT( main_ctx || ( ! main_ctx && terminated) );
        destroy( this);
    }

    void run() {
        Ctx c{ from };
        try {
            // invoke context-function
#if defined(BOOST_NO_CXX17_STD_INVOKE)
            c = boost::context::detail::invoke( fn_, std::move( c) );
#else
            c = std::invoke( fn_, std::move( c) );
#endif  
        } catch ( forced_unwind const& ex) {
            c = Ctx{ ex.from };
#ifndef BOOST_ASSERT_IS_VOID
            const_cast< forced_unwind & >( ex).caught = true;
#endif
        }
        // this context has finished its task
        from = nullptr;
        ontop = nullptr;
        terminated = true;
        force_unwind = false;
        c.resume();
        BOOST_ASSERT_MSG( false, "continuation already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static activation_record * create_context1( StackAlloc && salloc, Fn && fn) {
    typedef capture_record< Ctx, StackAlloc, Fn >  capture_t;

    auto sctx = salloc.allocate();
    BOOST_ASSERT( ( sizeof( capture_t) ) < sctx.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( sctx.size, & detail::entry_func< capture_t >, record);
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static activation_record * create_context2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    BOOST_ASSERT( ( sizeof( capture_t) ) < palloc.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( palloc.sctx.size, & detail::entry_func< capture_t >, record);
    return record;
}

}

class BOOST_CONTEXT_DECL continuation {
private:
    friend struct detail::activation_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::capture_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::activation_record * detail::create_context1( StackAlloc &&, Fn &&);

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::activation_record * detail::create_context2( preallocated, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::activation_record   *   ptr_{ nullptr };

    continuation( detail::activation_record * ptr) noexcept :
        ptr_{ ptr } {
    }

public:
    continuation() = default;

    ~continuation() {
        if ( BOOST_UNLIKELY( nullptr != ptr_) && ! ptr_->main_ctx) {
            if ( BOOST_LIKELY( ! ptr_->terminated) ) {
                ptr_->force_unwind = true;
                ptr_->resume();
                BOOST_ASSERT( ptr_->terminated);
            }
            ptr_->deallocate();
        }
    }

    continuation( continuation const&) = delete;
    continuation & operator=( continuation const&) = delete;

    continuation( continuation && other) noexcept {
        swap( other);
    }

    continuation & operator=( continuation && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            continuation tmp = std::move( other);
            swap( tmp);
        }
        return * this;
    }

    continuation resume() & {
        return std::move( * this).resume();
    }

    continuation resume() && {
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::activation_record * ptr = detail::exchange( ptr_, nullptr)->resume();
#else
        detail::activation_record * ptr = std::exchange( ptr_, nullptr)->resume();
#endif
        if ( BOOST_UNLIKELY( detail::activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::activation_record::current()->ontop) ) {
            ptr = detail::activation_record::current()->ontop( ptr);
            detail::activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) & {
        return std::move( * this).resume_with( std::forward< Fn >( fn) );
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) && {
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::activation_record * ptr =
            detail::exchange( ptr_, nullptr)->resume_with< continuation >( std::forward< Fn >( fn) );
#else
        detail::activation_record * ptr =
            std::exchange( ptr_, nullptr)->resume_with< continuation >( std::forward< Fn >( fn) );
#endif
        if ( BOOST_UNLIKELY( detail::activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::activation_record::current()->ontop) ) {
            ptr = detail::activation_record::current()->ontop( ptr);
            detail::activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    explicit operator bool() const noexcept {
        return nullptr != ptr_ && ! ptr_->terminated;
    }

    bool operator!() const noexcept {
        return nullptr == ptr_ || ptr_->terminated;
    }

    bool operator<( continuation const& other) const noexcept {
        return ptr_ < other.ptr_;
    }

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( continuation & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

template<
    typename Fn,
    typename = detail::disable_overload< continuation, Fn >
>
continuation
callcc( Fn && fn) {
    return callcc(
            std::allocator_arg,
            fixedsize_stack(),
            std::forward< Fn >( fn) );
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) {
    return continuation{
        detail::create_context1< continuation >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) {
    return continuation{
        detail::create_context2< continuation >(
                palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

inline
void swap( continuation & l, continuation & r) noexcept {
    l.swap( r);
}

}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_CONTINUATION_H

/* continuation_winfib.hpp
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
*/