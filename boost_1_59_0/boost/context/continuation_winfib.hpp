
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

    explicit forced_unwind( activation_record * from_) :
        from{ from_ } {
    }
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
    
    #if !defined(BOOST_EMBTC)
    
    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    #else
    
    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other);

    #endif

    void swap( continuation & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

#if defined(BOOST_EMBTC)

    template< typename charT, class traitsT >
    inline std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

#endif
    
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