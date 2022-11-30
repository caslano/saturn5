
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

    forced_unwind( activation_record * from_) noexcept :
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