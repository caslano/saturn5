
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_CONTINUATION_H
#define BOOST_CONTEXT_CONTINUATION_H

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

namespace boost {
namespace context {
namespace detail {

// tampoline function
// entered if the execution context
// is resumed for the first time
template< typename Record >
static void entry_func( void * data) noexcept {
    Record * record = static_cast< Record * >( data);
    BOOST_ASSERT( nullptr != record);
    // start execution of toplevel context-function
    record->run();
}

struct BOOST_CONTEXT_DECL activation_record {
    ucontext_t                                                  uctx{};
    stack_context                                               sctx{};
    bool                                                        main_ctx{ true };
	activation_record                                       *	from{ nullptr };
    std::function< activation_record*(activation_record*&) >    ontop{};
    bool                                                        terminated{ false };
    bool                                                        force_unwind{ false };
#if defined(BOOST_USE_ASAN)
    void                                                    *   fake_stack{ nullptr };
    void                                                    *   stack_bottom{ nullptr };
    std::size_t                                                 stack_size{ 0 };
#endif

    static activation_record *& current() noexcept;

    // used for toplevel-context
    // (e.g. main context, thread-entry context)
    activation_record() {
        if ( BOOST_UNLIKELY( 0 != ::getcontext( & uctx) ) ) {
            throw std::system_error(
                    std::error_code( errno, std::system_category() ),
                    "getcontext() failed");
        }
    }

    activation_record( stack_context sctx_) noexcept :
        sctx( sctx_ ),
        main_ctx( false ) {
    } 

    virtual ~activation_record() {
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
        // adjust segmented stack properties
        __splitstack_getcontext( from->sctx.segments_ctx);
        __splitstack_setcontext( sctx.segments_ctx);
#endif
#if defined(BOOST_USE_ASAN)
        __sanitizer_start_switch_fiber( & from->fake_stack, stack_bottom, stack_size);
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

struct BOOST_CONTEXT_DECL activation_record_initializer {
    activation_record_initializer() noexcept;
    ~activation_record_initializer();
};

struct forced_unwind {
    activation_record   *   from{ nullptr };
#ifndef BOOST_ASSERT_IS_VOID
    bool                    caught{ false };
#endif

    forced_unwind( activation_record * from_) noexcept :
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
        activation_record{ sctx },
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
    record->uctx.uc_stack.ss_sp = stack_bottom;
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx, ( void (*)() ) & entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
    return record;
}

template< typename Ctx, typename StackAlloc, typename Fn >
static activation_record * create_context2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    typedef capture_record< Ctx, StackAlloc, Fn >  capture_t; 

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
    record->uctx.uc_stack.ss_sp = stack_bottom;
    // 64byte gap between control structure and stack top
    record->uctx.uc_stack.ss_size = reinterpret_cast< uintptr_t >( storage) -
            reinterpret_cast< uintptr_t >( stack_bottom) - static_cast< uintptr_t >( 64);
    record->uctx.uc_link = nullptr;
    ::makecontext( & record->uctx,  ( void (*)() ) & entry_func< capture_t >, 1, record);
#if defined(BOOST_USE_ASAN)
    record->stack_bottom = record->uctx.uc_stack.ss_sp;
    record->stack_size = record->uctx.uc_stack.ss_size;
#endif
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
#if defined(BOOST_USE_SEGMENTED_STACKS)
			segmented_stack(),
#else
			fixedsize_stack(),
#endif
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

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_CONTINUATION_H

/* continuation_ucontext.hpp
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
*/