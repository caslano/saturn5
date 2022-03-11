
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIBER_H
#define BOOST_CONTEXT_FIBER_H

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
static VOID WINAPI fiber_entry_func( LPVOID data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL fiber_activation_record {
    LPVOID                                                      fiber{ nullptr };
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
    fiber_activation_record                                       *   from{ nullptr };
    std::function< fiber_activation_record*(fiber_activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };

    static fiber_activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    fiber_activation_record() noexcept {
#if ( _WIN32_WINNT > 0x0600)
        if ( ::IsThreadAFiber() ) {
            fiber = ::GetCurrentFiber();
        } else {
            fiber = ::ConvertThreadToFiber( nullptr);
        }
#else
        fiber = ::ConvertThreadToFiber( nullptr);
        if ( BOOST_UNLIKELY( nullptr == fiber) ) {
            BOOST_ASSERT( ERROR_ALREADY_FIBER == ::GetLastError());
            fiber = ::GetCurrentFiber(); 
            BOOST_ASSERT( nullptr != fiber);
            BOOST_ASSERT( reinterpret_cast< LPVOID >( 0x1E00) != fiber);
        }
#endif
    }

    fiber_activation_record( stack_context sctx_) noexcept :
        sctx{ sctx_ },
        main_ctx{ false } {
    } 

    virtual ~fiber_activation_record() {
        if ( BOOST_UNLIKELY( main_ctx) ) {
            ::ConvertFiberToThread();
        } else {
            ::DeleteFiber( fiber);
        }
    }

    fiber_activation_record( fiber_activation_record const&) = delete;
    fiber_activation_record & operator=( fiber_activation_record const&) = delete;

    bool is_main_context() const noexcept {
        return main_ctx;
    }

    fiber_activation_record * resume() {
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
    fiber_activation_record * resume_with( Fn && fn) {
        from = current();
        // store `this` in static, thread local pointer
        // `this` will become the active (running) context
        // returned by fiber::current()
        current() = this;
#if defined(BOOST_NO_CXX14_GENERIC_LAMBDAS)
        current()->ontop = std::bind(
                [](typename std::decay< Fn >::type & fn, fiber_activation_record *& ptr){
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
        current()->ontop = [fn=std::forward<Fn>(fn)](fiber_activation_record *& ptr){
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

struct BOOST_CONTEXT_DECL fiber_activation_record_initializer {
    fiber_activation_record_initializer() noexcept;
    ~fiber_activation_record_initializer();
};

struct forced_unwind {
    fiber_activation_record  *  from{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool                        caught{ false };
#endif

    explicit forced_unwind( fiber_activation_record * from_) :
        from{ from_ } {
    }

#ifndef BOOST_ASSERT_IS_VOID
    ~forced_unwind() {
        BOOST_ASSERT( caught);
    }
#endif
};

template< typename Ctx, typename StackAlloc, typename Fn >
class fiber_capture_record : public fiber_activation_record {
private:
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( fiber_capture_record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx;
        // deallocate activation record
        p->~fiber_capture_record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    fiber_capture_record( stack_context sctx, StackAlloc && salloc, Fn && fn) noexcept :
        fiber_activation_record( sctx),
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
        std::move( c).resume();
        BOOST_ASSERT_MSG( false, "fiber already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber1( StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t;

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
    record->fiber = ::CreateFiber( sctx.size, & detail::fiber_entry_func< capture_t >, record);
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    BOOST_ASSERT( ( sizeof( capture_t) ) < palloc.size);
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // create user-context
    record->fiber = ::CreateFiber( palloc.sctx.size, & detail::fiber_entry_func< capture_t >, record);
    return record;
}

}

class BOOST_CONTEXT_DECL fiber {
private:
    friend struct detail::fiber_activation_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::fiber_capture_record;

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::fiber_activation_record * detail::create_fiber1( StackAlloc &&, Fn &&);

    template< typename Ctx, typename StackAlloc, typename Fn >
    friend detail::fiber_activation_record * detail::create_fiber2( preallocated, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::fiber_activation_record   *   ptr_{ nullptr };

    fiber( detail::fiber_activation_record * ptr) noexcept :
        ptr_{ ptr } {
    }

public:
    fiber() = default;

    template< typename Fn, typename = detail::disable_overload< fiber, Fn > >
    fiber( Fn && fn) :
        fiber{ std::allocator_arg,
               fixedsize_stack(),
               std::forward< Fn >( fn) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber1< fiber >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {;
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber2< fiber >(
                palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
    }

    ~fiber() {
        if ( BOOST_UNLIKELY( nullptr != ptr_) && ! ptr_->main_ctx) {
            if ( BOOST_LIKELY( ! ptr_->terminated) ) {
                ptr_->force_unwind = true;
                ptr_->resume();
                BOOST_ASSERT( ptr_->terminated);
            }
            ptr_->deallocate();
        }
    }

    fiber( fiber const&) = delete;
    fiber & operator=( fiber const&) = delete;

    fiber( fiber && other) noexcept {
        swap( other);
    }

    fiber & operator=( fiber && other) noexcept {
        if ( BOOST_LIKELY( this != & other) ) {
            fiber tmp = std::move( other);
            swap( tmp);
        }
        return * this;
    }

    fiber resume() && {
        BOOST_ASSERT( nullptr != ptr_);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::fiber_activation_record * ptr = detail::exchange( ptr_, nullptr)->resume();
#else
        detail::fiber_activation_record * ptr = std::exchange( ptr_, nullptr)->resume();
#endif
        if ( BOOST_UNLIKELY( detail::fiber_activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::fiber_activation_record::current()->ontop) ) {
            ptr = detail::fiber_activation_record::current()->ontop( ptr);
            detail::fiber_activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    template< typename Fn >
    fiber resume_with( Fn && fn) && {
        BOOST_ASSERT( nullptr != ptr_);
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        detail::fiber_activation_record * ptr =
            detail::exchange( ptr_, nullptr)->resume_with< fiber >( std::forward< Fn >( fn) );
#else
        detail::fiber_activation_record * ptr =
            std::exchange( ptr_, nullptr)->resume_with< fiber >( std::forward< Fn >( fn) );
#endif
        if ( BOOST_UNLIKELY( detail::fiber_activation_record::current()->force_unwind) ) {
            throw detail::forced_unwind{ ptr};
        } else if ( BOOST_UNLIKELY( nullptr != detail::fiber_activation_record::current()->ontop) ) {
            ptr = detail::fiber_activation_record::current()->ontop( ptr);
            detail::fiber_activation_record::current()->ontop = nullptr;
        }
        return { ptr };
    }

    explicit operator bool() const noexcept {
        return nullptr != ptr_ && ! ptr_->terminated;
    }

    bool operator!() const noexcept {
        return nullptr == ptr_ || ptr_->terminated;
    }

    bool operator<( fiber const& other) const noexcept {
        return ptr_ < other.ptr_;
    }

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( fiber & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

inline
void swap( fiber & l, fiber & r) noexcept {
    l.swap( r);
}

typedef fiber fiber_context;

}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIBER_H

/* fiber_winfib.hpp
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
*/