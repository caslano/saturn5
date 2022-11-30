
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

    #if !defined(BOOST_EMBTC)
    
    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.fctx_) {
            return os << other.fctx_;
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
        std::swap( fctx_, other.fctx_);
    }
};

#if defined(BOOST_EMBTC)

    template< typename charT, class traitsT >
    inline std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, fiber const& other) {
        if ( nullptr != other.fctx_) {
            return os << other.fctx_;
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