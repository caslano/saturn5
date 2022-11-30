
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