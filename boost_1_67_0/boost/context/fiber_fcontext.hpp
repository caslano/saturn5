
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_FIBER_H
#define BOOST_CONTEXT_FIBER_H

#include <boost/context/detail/config.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <functional>
#include <memory>
#include <ostream>
#include <tuple>
#include <utility>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/intrusive_ptr.hpp>

#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
#include <boost/context/detail/exchange.hpp>
#endif
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/detail/disable_overload.hpp>
#include <boost/context/detail/exception.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/context/detail/tuple.hpp>
#include <boost/context/fixedsize_stack.hpp>
#include <boost/context/flags.hpp>
#include <boost/context/preallocated.hpp>
#include <boost/context/segmented_stack.hpp>
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

inline
transfer_t fiber_unwind( transfer_t t) {
    throw forced_unwind( t.fctx);
    return { nullptr, nullptr };
}

template< typename Rec >
transfer_t fiber_exit( transfer_t t) noexcept {
    Rec * rec = static_cast< Rec * >( t.data);
    // destroy context stack
    rec->deallocate();
    return { nullptr, nullptr };
}

template< typename Rec >
void fiber_entry( transfer_t t) noexcept {
    // transfer control structure to the context-stack
    Rec * rec = static_cast< Rec * >( t.data);
    BOOST_ASSERT( nullptr != t.fctx);
    BOOST_ASSERT( nullptr != rec);
    try {
        // jump back to `create_context()`
        t = jump_fcontext( t.fctx, nullptr);
        // start executing
        t.fctx = rec->run( t.fctx);
    } catch ( forced_unwind const& ex) {
        t = { ex.fctx, nullptr };
#ifndef BOOST_ASSERT_IS_VOID
        const_cast< forced_unwind & >( ex).caught = true;
#endif
    }
    BOOST_ASSERT( nullptr != t.fctx);
    // destroy context-stack of `this`context on next context
    ontop_fcontext( t.fctx, rec, fiber_exit< Rec >);
    BOOST_ASSERT_MSG( false, "context already terminated");
}

template< typename Ctx, typename Fn >
transfer_t fiber_ontop( transfer_t t) {
    BOOST_ASSERT( nullptr != t.data);
    auto p = *static_cast< Fn * >( t.data);
    t.data = nullptr;
    // execute function, pass fiber via reference
    Ctx c = p( Ctx{ t.fctx } );
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
    return { exchange( c.fctx_, nullptr), nullptr };
#else
    return { std::exchange( c.fctx_, nullptr), nullptr };
#endif
}

template< typename Ctx, typename StackAlloc, typename Fn >
class fiber_record {
private:
    stack_context                                       sctx_;
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( fiber_record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx_;
        // deallocate fiber_record
        p->~fiber_record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    fiber_record( stack_context sctx, StackAlloc && salloc,
            Fn && fn) noexcept :
        sctx_( sctx),
        salloc_( std::forward< StackAlloc >( salloc)),
        fn_( std::forward< Fn >( fn) ) {
    }

    fiber_record( fiber_record const&) = delete;
    fiber_record & operator=( fiber_record const&) = delete;

    void deallocate() noexcept {
        destroy( this);
    }

    fcontext_t run( fcontext_t fctx) {
        // invoke context-function
#if defined(BOOST_NO_CXX17_STD_INVOKE)
        Ctx c = boost::context::detail::invoke( fn_, Ctx{ fctx } );
#else
        Ctx c = std::invoke( fn_, Ctx{ fctx } );
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( c.fctx_, nullptr);
#else
        return std::exchange( c.fctx_, nullptr);
#endif
    }
};

template< typename Record, typename StackAlloc, typename Fn >
fcontext_t create_fiber1( StackAlloc && salloc, Fn && fn) {
    auto sctx = salloc.allocate();
    // reserve space for control structure
	void * storage = reinterpret_cast< void * >(
			( reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sizeof( Record) ) )
            & ~static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context stack
    Record * record = new ( storage) Record{
            sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // 64byte gab between control structure and stack top
    // should be 16byte aligned
    void * stack_top = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( storage) - static_cast< uintptr_t >( 64) );
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( sctx.sp) - static_cast< uintptr_t >( sctx.size) );
    // create fast-context
    const std::size_t size = reinterpret_cast< uintptr_t >( stack_top) - reinterpret_cast< uintptr_t >( stack_bottom);
    const fcontext_t fctx = make_fcontext( stack_top, size, & fiber_entry< Record >);
    BOOST_ASSERT( nullptr != fctx);
    // transfer control structure to context-stack
    return jump_fcontext( fctx, record).fctx;
}

template< typename Record, typename StackAlloc, typename Fn >
fcontext_t create_fiber2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
    // reserve space for control structure
    void * storage = reinterpret_cast< void * >(
            ( reinterpret_cast< uintptr_t >( palloc.sp) - static_cast< uintptr_t >( sizeof( Record) ) )
            & ~ static_cast< uintptr_t >( 0xff) );
    // placment new for control structure on context-stack
    Record * record = new ( storage) Record{
            palloc.sctx, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) };
    // 64byte gab between control structure and stack top
    void * stack_top = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( storage) - static_cast< uintptr_t >( 64) );
    void * stack_bottom = reinterpret_cast< void * >(
            reinterpret_cast< uintptr_t >( palloc.sctx.sp) - static_cast< uintptr_t >( palloc.sctx.size) );
    // create fast-context
    const std::size_t size = reinterpret_cast< uintptr_t >( stack_top) - reinterpret_cast< uintptr_t >( stack_bottom);
    const fcontext_t fctx = make_fcontext( stack_top, size, & fiber_entry< Record >);
    BOOST_ASSERT( nullptr != fctx);
    // transfer control structure to context-stack
    return jump_fcontext( fctx, record).fctx;
}

}

class fiber {
private:
    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::fiber_record;

    template< typename Ctx, typename Fn >
    friend detail::transfer_t
    detail::fiber_ontop( detail::transfer_t);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend fiber
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::fcontext_t  fctx_{ nullptr };

    fiber( detail::fcontext_t fctx) noexcept :
        fctx_{ fctx } {
    }

public:
    fiber() noexcept = default;

    template< typename Fn, typename = detail::disable_overload< fiber, Fn > >
    fiber( Fn && fn) :
        fiber{ std::allocator_arg, fixedsize_stack(), std::forward< Fn >( fn) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) :
        fctx_{ detail::create_fiber1< detail::fiber_record< fiber, StackAlloc, Fn > >(
                std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
    }

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) :
        fctx_{ detail::create_fiber2< detail::fiber_record< fiber, StackAlloc, Fn > >(
                palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) } {
    }

#if defined(BOOST_USE_SEGMENTED_STACKS)
    template< typename Fn >
    fiber( std::allocator_arg_t, segmented_stack, Fn &&);

    template< typename StackAlloc, typename Fn >
    fiber( std::allocator_arg_t, preallocated, segmented_stack, Fn &&);
#endif

    ~fiber() {
        if ( BOOST_UNLIKELY( nullptr != fctx_) ) {
            detail::ontop_fcontext(
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    detail::exchange( fctx_, nullptr),
#else
                    std::exchange( fctx_, nullptr),
#endif
                   nullptr,
                   detail::fiber_unwind);
        }
    }

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

    fiber( fiber const& other) noexcept = delete;
    fiber & operator=( fiber const& other) noexcept = delete;

    fiber resume() && {
        BOOST_ASSERT( nullptr != fctx_);
        return { detail::jump_fcontext(
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    detail::exchange( fctx_, nullptr),
#else
                    std::exchange( fctx_, nullptr),
#endif
                    nullptr).fctx };
    }

    template< typename Fn >
    fiber resume_with( Fn && fn) && {
        BOOST_ASSERT( nullptr != fctx_);
        auto p = std::forward< Fn >( fn);
        return { detail::ontop_fcontext(
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    detail::exchange( fctx_, nullptr),
#else
                    std::exchange( fctx_, nullptr),
#endif
                    & p,
                    detail::fiber_ontop< fiber, decltype(p) >).fctx };
    }

    explicit operator bool() const noexcept {
        return nullptr != fctx_;
    }

    bool operator!() const noexcept {
        return nullptr == fctx_;
    }

    bool operator<( fiber const& other) const noexcept {
        return fctx_ < other.fctx_;
    }

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.fctx_) {
            return os << other.fctx_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( fiber & other) noexcept {
        std::swap( fctx_, other.fctx_);
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

/* fiber_fcontext.hpp
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
*/