
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
zW+aGFhYN3dBAwtcpnCf8qmw+QMsuRxYBpcll4Oo7GmC369EPPC15b/qCH868T6D8Ovz8n44fO1Jn2fJvJsU4zMahI7MEu0726rHnDK4rHo0Eh8HW7KebrXPXIKbJ+rbIO5nWfgthN9M9T2U8FstuHKrnDaCW2DBNVtwhxHc4YKHEgvnSMKpJR6OIpyjBc5Uuv9dP93nJnA+K5HmMZeWU3s8rmZGdRrIxrJnStc+Bf0ojs8MrBrFdUaSHvwIvDeIJIPpSNgL2x5NE1lvOp5TxjkiXR15hm6DsiROevJEShW8BPf1pXVGYsBKty+9vSfhS8vEourDZQDtL0+diRftUeMuH+3oCZGwL683mooaziWdjinZZKAGzt7n4zORGL9TXWTapTfYnYnwuy8wrJKA6i8LmCcaI2MvEWcdi/iaLL/HC5aJMWUB/dyRHtqxaJjqUo4xXU80lgIhuWmqPBjkYpp859QTTC3m+QQT682ieeOQ4KnyG/Q5GLeTvxoo4vY0xe0RSEd/gjCcb/xJZxnF/uhDVKzrpxG1YEqylLNYwmA5fpieMhOHD8C4XV3WeKNEx+FxAZvmy4almP148hPThZ8YSP6ceUopnpBH6ddhLsL4eR6PuDh+3jTOUq4r1iP7eOkEjjFKvD5dlbPc8uknaVikL3k+hXm2yj+1zIw5xmYZcySsMQbO0yrdFHo5nPSwlsYcK8rknJT6zo2YzzaPeeZW+TD9eJjRTApi5uvvG9tg9onQ3AQuj+rO7YOyOku09Wl0z3OgK+F5FVww/kcZEj5a7dllOcaxfdRZlXOuKHO1t6/Gss6z2vV8eOa+bbXVH65RsVv2+ddoHMpGHvStW/5FOep5MVx2PS/RZZeeIWKNyzQ+wl3u6rvhUaXJeZMr4ZnLugp1XOmieacL91jW1Vxv834Gyz5TlL22zKvb67B9mJbR7fVkC4usum5gW0BcxFEwWP718N+li/Lw072BcFabenN78LPblgCDNoPjfGrLW9wymG+/f7tN+iwFr2DwUrjeeYbbiZ8xpvx8MaV6L8ma6SbIccedQtY/FDHlXZae3l0Gl6WnPyKZ31OW771rYnEotR/zgA+y/PtE+feL8n9slf9AGVxW+Q9S+T8h2Gm55aAOTYup1+XMiC9V+hk/voodGNVNkDb+iBWTPmrZ7U+J18f8Y0e/rKKdEEp52s6XIct+3JSN9yzPJy2eniKenqA4+efE09N5xyaR3kQgFE10makgk2LGJr8Q5T5L9BZiX8PxcigeU4ssAibWasZYCwc50XRXjxsXlkLMHAqYfuiXZarf0SXi+2Xqe56TfQ/JTmFSScyuL4NlNyt3e8OrlMZZRwRa6lrr3P7FlyHb4NdG1njPsviN1Qa/pTZ4ntrgBWqDFwmuNlcb4Ln1zAo/m3HtS4Q/o682lFrlT8b63OiJX3t5nYlpM2wfbDdvmyFPus02YZuFIzItje2k2PbHHeNUOra5gZ2AaR3JCOnL74HmFKEHU2ktyctCD1qchF63ExDiEkn55z2XqibujscXZxKMK5Jke79iteurlr3/kdr1NYLbI2d5siDTnn8y9PGe9enPVrlvUrlvkD69ReW+bcE9b/H3F4J7V5TziCjnPeGL/2b54vfL4LJ88QdE70PWwz58KZhh0m0fX7KR82arHlusenxE5X7Mc6F9+dVwFpcaFvNDeflnV9Ib6Y4nDClfsuH/c6LX2idfwVjYRzh3PvP7jwLqrY/lZpoyzdD5Z0H1xjOi/fXGZG+9vyJ6ax3/fIsZ1xt7/wyfVU318xf47FYY/cyXLgyUBeIwEtc4/9I0sWbsW74mOsgi0dFzyvG0ciNq3mCIeiFTXti8QQc=
*/