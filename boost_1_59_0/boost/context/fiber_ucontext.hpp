
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIBER_H
#define BOOST_CONTEXT_FIBER_H

#include <boost/predef.h>
#if BOOST_OS_MACOS
#define _XOPEN_SOURCE 600
#endif

extern "C" {
#include <ucontext.h>
}

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
#include <boost/predef.h>

#include <boost/context/detail/disable_overload.hpp>
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
#include <boost/context/detail/exchange.hpp>
#endif
#include <boost/context/detail/externc.hpp>
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/fixedsize_stack.hpp>
#include <boost/context/flags.hpp>
#include <boost/context/preallocated.hpp>
#if defined(BOOST_USE_SEGMENTED_STACKS)
#include <boost/context/segmented_stack.hpp>
#endif
#include <boost/context/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#ifdef BOOST_USE_TSAN
#include <sanitizer/tsan_interface.h>
#endif

namespace boost {
namespace context {
namespace detail {

// tampoline function
// entered if the execution context
// is resumed for the first time
template< typename Record >
static void fiber_entry_func( void * data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL fiber_activation_record {
    ucontext_t                                                  uctx{};
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
	fiber_activation_record                                       *	from{ nullptr };
    std::function< fiber_activation_record*(fiber_activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };
#if defined(BOOST_USE_ASAN)
    void                                                    *   fake_stack{ nullptr };
    void                                                    *   stack_bottom{ nullptr };
    std::size_t                                                 stack_size{ 0 };
#endif

#if defined(BOOST_USE_TSAN)
    void * tsan_fiber{ nullptr };
    bool destroy_tsan_fiber{ true };
#endif

    static fiber_activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    fiber_activation_record() {
        if ( BOOST_UNLIKELY( 0 != ::getcontext( & uctx) ) ) {
            throw std::system_error(
                    std::error_code( errno, std::system_category() ),
                    "getcontext() failed");
        }

#if defined(BOOST_USE_TSAN)
        tsan_fiber = __tsan_get_current_fiber();
        destroy_tsan_fiber = false;
#endif
    }

    fiber_activation_record( stack_context sctx_) noexcept :
        sctx( sctx_ ),
        main_ctx( false ) {
    } 

    virtual ~fiber_activation_record() {
#if defined(BOOST_USE_TSAN)
        if (destroy_tsan_fiber)
            __tsan_destroy_fiber(tsan_fiber);
#endif
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
        // adjust segmented stack properties
        __splitstack_getcontext( from->sctx.segments_ctx);
        __splitstack_setcontext( sctx.segments_ctx);
#endif
#if defined(BOOST_USE_ASAN)
        if ( terminated) {
            __sanitizer_start_switch_fiber( nullptr, stack_bottom, stack_size);
        } else {
            __sanitizer_start_switch_fiber( & from->fake_stack, stack_bottom, stack_size);
        }
#endif
#if defined (BOOST_USE_TSAN)
        __tsan_switch_to_fiber(tsan_fiber, 0);
#endif
        // context switch from parent context to `this`-context
        ::swapcontext( & from->uctx, & uctx);
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( current()->fake_stack,
                                         (const void **) & current()->from->stack_bottom,
                                         & current()->from->stack_size);
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( current()->from, nullptr);
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
        // adjust segmented stack properties
        __splitstack_getcontext( from->sctx.segments_ctx);
        __splitstack_setcontext( sctx.segments_ctx);
#endif
#if defined(BOOST_USE_ASAN)
        __sanitizer_start_switch_fiber( & from->fake_stack, stack_bottom, stack_size);
#endif
#if defined (BOOST_USE_TSAN)
        __tsan_switch_to_fiber(tsan_fiber, 0);
#endif
        // context switch from parent context to `this`-context
        ::swapcontext( & from->uctx, & uctx);
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( current()->fake_stack,
                                         (const void **) & current()->from->stack_bottom,
                                         & current()->from->stack_size);
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( current()->from, nullptr);
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

    forced_unwind( fiber_activation_record * from_) noexcept :
        from{ from_ } {
    }
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
        fiber_activation_record{ sctx },
        salloc_{ std::forward< StackAlloc >( salloc) },
        fn_( std::forward< Fn >( fn) ) {
    }

    void deallocate() noexcept override final {
        BOOST_ASSERT( main_ctx || ( ! main_ctx && terminated) );
        destroy( this);
    }

    void run() {
#if defined(BOOST_USE_ASAN)
        __sanitizer_finish_switch_fiber( fake_stack,
                                         (const void **) & from->stack_bottom,
                                         & from->stack_size);
#endif
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
        std::move( c).resume();
        BOOST_ASSERT_MSG( false, "fiber already terminated");
    }
};

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber1( StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t;

    auto sctx = salloc.allocate();
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // stack bottom
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sctx.size) );
    // create user-context
    if ( BOOST_UNLIKELY( 0 != ::getcontext( & record->uctx) ) ) {
        record->~capture_t();
        salloc.deallocate( sctx);
        throw std::system_error(
                std::error_code( errno, std::system_category() ),
                "getcontext() failed");
    }
#if BOOST_OS_BSD_FREE
    // because FreeBSD defines stack_t::ss_sp as char *
    record->uctx.uc_stack.ss_sp = static_cast< char * >( stack_bottom);
#else
    record->uctx.uc_stack.ss_sp = stack_bottom;
#endif
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx, ( void (*)() ) & fiber_entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
#if defined (BOOST_USE_TSAN)
    record->tsan_fiber = __tsan_create_fiber(0);
#endif
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static fiber_activation_record * create_fiber2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef fiber_capture_record< Ctx, StackAlloc, Fn >  capture_t; 

    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( capture_t) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    capture_t * record = new ( storage) capture_t{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // stack bottom
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( palloc.sctx.sp) - static_cast< uintptr_t >( palloc.sctx.size) );
    // create user-context
    if ( BOOST_UNLIKELY( 0 != ::getcontext( & record->uctx) ) ) {
        record->~capture_t();
        salloc.deallocate( palloc.sctx);
        throw std::system_error(
                std::error_code( errno, std::system_category() ),
                "getcontext() failed");
    }
#if BOOST_OS_BSD_FREE
    // because FreeBSD defines stack_t::ss_sp as char *
    record->uctx.uc_stack.ss_sp = static_cast< char * >( stack_bottom);
#else
    record->uctx.uc_stack.ss_sp = stack_bottom;
#endif
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx,  ( void (*)() ) & fiber_entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
#if defined (BOOST_USE_TSAN)
    record->tsan_fiber = __tsan_create_fiber(0);
#endif
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
        fiber{
                std::allocator_arg,
#if defined(BOOST_USE_SEGMENTED_STACKS)
                segmented_stack(),
#else
                fixedsize_stack(),
#endif
                std::forward< Fn >( fn) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) :
        ptr_{ detail::create_fiber1< fiber >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
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

    #if !defined(BOOST_EMBTC)

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

    #else

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other);

    #endif

    void swap( fiber & other) noexcept {
        std::swap( ptr_, other.ptr_);
    }
};

#if defined(BOOST_EMBTC)

    template< typename charT, class traitsT >
    inline std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.ptr_) {
            return os << other.ptr_;
        } else {
            return os << "{not-a-context}";
        }
    }

#endif

inline
void swap( fiber & l, fiber & r) noexcept {
    l.swap( r);
}

typedef fiber fiber_context;

}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_FIBER_H

/* fiber_ucontext.hpp
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
*/