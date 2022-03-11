
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_CONTINUATION_H
#define BOOST_CONTEXT_CONTINUATION_H

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
transfer_t context_unwind( transfer_t t) {
    throw forced_unwind( t.fctx);
    return { nullptr, nullptr };
}

template< typename Rec >
transfer_t context_exit( transfer_t t) noexcept {
    Rec * rec = static_cast< Rec * >( t.data);
    // destroy context stack
    rec->deallocate();
    return { nullptr, nullptr };
}

template< typename Rec >
void context_entry( transfer_t t) noexcept {
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
    ontop_fcontext( t.fctx, rec, context_exit< Rec >);
    BOOST_ASSERT_MSG( false, "context already terminated");
}

template< typename Ctx, typename Fn >
transfer_t context_ontop( transfer_t t) {
    auto p = static_cast< std::tuple< Fn > * >( t.data);
    BOOST_ASSERT( nullptr != p);
    typename std::decay< Fn >::type fn = std::get< 0 >( * p);
    t.data = nullptr;
    Ctx c{ t.fctx };
    // execute function, pass continuation via reference
    c = fn( std::move( c) );
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
    return { exchange( c.fctx_, nullptr), nullptr };
#else
    return { std::exchange( c.fctx_, nullptr), nullptr };
#endif
}

template< typename Ctx, typename StackAlloc, typename Fn >
class record {
private:
    stack_context                                       sctx_;
    typename std::decay< StackAlloc >::type             salloc_;
    typename std::decay< Fn >::type                     fn_;

    static void destroy( record * p) noexcept {
        typename std::decay< StackAlloc >::type salloc = std::move( p->salloc_);
        stack_context sctx = p->sctx_;
        // deallocate record
        p->~record();
        // destroy stack with stack allocator
        salloc.deallocate( sctx);
    }

public:
    record( stack_context sctx, StackAlloc && salloc,
            Fn && fn) noexcept :
        sctx_( sctx),
        salloc_( std::forward< StackAlloc >( salloc)),
        fn_( std::forward< Fn >( fn) ) {
    }

    record( record const&) = delete;
    record & operator=( record const&) = delete;

    void deallocate() noexcept {
        destroy( this);
    }

    fcontext_t run( fcontext_t fctx) {
        Ctx c{ fctx };
        // invoke context-function
#if defined(BOOST_NO_CXX17_STD_INVOKE)
        c = boost::context::detail::invoke( fn_, std::move( c) );
#else
        c = std::invoke( fn_, std::move( c) );
#endif
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
        return exchange( c.fctx_, nullptr);
#else
        return std::exchange( c.fctx_, nullptr);
#endif
    }
};

template< typename Record, typename StackAlloc, typename Fn >
fcontext_t create_context1( StackAlloc && salloc, Fn && fn) {
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
    const fcontext_t fctx = make_fcontext( stack_top, size, & context_entry< Record >);
    BOOST_ASSERT( nullptr != fctx);
    // transfer control structure to context-stack
    return jump_fcontext( fctx, record).fctx;
}

template< typename Record, typename StackAlloc, typename Fn >
fcontext_t create_context2( preallocated palloc, StackAlloc && salloc, Fn && fn) {
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
    const fcontext_t fctx = make_fcontext( stack_top, size, & context_entry< Record >);
    BOOST_ASSERT( nullptr != fctx);
    // transfer control structure to context-stack
    return jump_fcontext( fctx, record).fctx;
}

}

class continuation {
private:
    template< typename Ctx, typename StackAlloc, typename Fn >
    friend class detail::record;

    template< typename Ctx, typename Fn >
    friend detail::transfer_t
    detail::context_ontop( detail::transfer_t);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, StackAlloc &&, Fn &&);

    template< typename StackAlloc, typename Fn >
    friend continuation
    callcc( std::allocator_arg_t, preallocated, StackAlloc &&, Fn &&);

    detail::fcontext_t  fctx_{ nullptr };

    continuation( detail::fcontext_t fctx) noexcept :
        fctx_{ fctx } {
    }

public:
    continuation() noexcept = default;

    ~continuation() {
        if ( BOOST_UNLIKELY( nullptr != fctx_) ) {
            detail::ontop_fcontext(
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    detail::exchange( fctx_, nullptr),
#else
                    std::exchange( fctx_, nullptr),
#endif
                   nullptr,
                   detail::context_unwind);
        }
    }

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

    continuation( continuation const& other) noexcept = delete;
    continuation & operator=( continuation const& other) noexcept = delete;

    continuation resume() & {
        return std::move( * this).resume();
    }

    continuation resume() && {
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
    continuation resume_with( Fn && fn) & {
        return std::move( * this).resume_with( std::forward< Fn >( fn) );
    }

    template< typename Fn >
    continuation resume_with( Fn && fn) && {
        BOOST_ASSERT( nullptr != fctx_);
        auto p = std::make_tuple( std::forward< Fn >( fn) );
        return { detail::ontop_fcontext(
#if defined(BOOST_NO_CXX14_STD_EXCHANGE)
                    detail::exchange( fctx_, nullptr),
#else
                    std::exchange( fctx_, nullptr),
#endif
                    & p,
                    detail::context_ontop< continuation, Fn >).fctx };
    }

    explicit operator bool() const noexcept {
        return nullptr != fctx_;
    }

    bool operator!() const noexcept {
        return nullptr == fctx_;
    }

    bool operator<( continuation const& other) const noexcept {
        return fctx_ < other.fctx_;
    }

    template< typename charT, class traitsT >
    friend std::basic_ostream< charT, traitsT > &
    operator<<( std::basic_ostream< charT, traitsT > & os, continuation const& other) {
        if ( nullptr != other.fctx_) {
            return os << other.fctx_;
        } else {
            return os << "{not-a-context}";
        }
    }

    void swap( continuation & other) noexcept {
        std::swap( fctx_, other.fctx_);
    }
};

template<
    typename Fn,
    typename = detail::disable_overload< continuation, Fn >
>
continuation
callcc( Fn && fn) {
    return callcc(
            std::allocator_arg, fixedsize_stack(),
            std::forward< Fn >( fn) );
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, StackAlloc && salloc, Fn && fn) {
    using Record = detail::record< continuation, StackAlloc, Fn >;
    return continuation{
                detail::create_context1< Record >(
                        std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, preallocated palloc, StackAlloc && salloc, Fn && fn) {
    using Record = detail::record< continuation, StackAlloc, Fn >;
    return continuation{
                detail::create_context2< Record >(
                        palloc, std::forward< StackAlloc >( salloc), std::forward< Fn >( fn) ) }.resume();
}

#if defined(BOOST_USE_SEGMENTED_STACKS)
template< typename Fn >
continuation
callcc( std::allocator_arg_t, segmented_stack, Fn &&);

template< typename StackAlloc, typename Fn >
continuation
callcc( std::allocator_arg_t, preallocated, segmented_stack, Fn &&);
#endif

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

/* continuation_fcontext.hpp
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
*/