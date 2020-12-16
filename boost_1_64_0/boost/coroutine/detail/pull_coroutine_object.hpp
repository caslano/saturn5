
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PULL_COROUTINE_OBJECT_H
#define BOOST_COROUTINES_DETAIL_PULL_COROUTINE_OBJECT_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/move/move.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/detail/pull_coroutine_impl.hpp>
#include <boost/coroutine/detail/trampoline_pull.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/flags.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4355)
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct pull_coroutine_context
{
    coroutine_context   caller;
    coroutine_context   callee;

    template< typename Coro >
    pull_coroutine_context( preallocated const& palloc, Coro *) :
        caller(),
        callee( trampoline_pull< Coro >, palloc)
    {}
};

template< typename PushCoro, typename R, typename Fn, typename StackAllocator >
class pull_coroutine_object : private pull_coroutine_context,
                              public pull_coroutine_impl< R >
{
private:
    typedef pull_coroutine_context                                      ctx_t;
    typedef pull_coroutine_impl< R >                                    base_t;
    typedef pull_coroutine_object< PushCoro, R, Fn, StackAllocator >    obj_t;

    Fn                  fn_;
    stack_context       stack_ctx_;
    StackAllocator      stack_alloc_;

    static void deallocate_( obj_t * obj)
    {
        stack_context stack_ctx( obj->stack_ctx_);
        StackAllocator stack_alloc( obj->stack_alloc_);
        obj->unwind_stack();
        obj->~obj_t();
        stack_alloc.deallocate( stack_ctx);
    }

public:
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    pull_coroutine_object( Fn fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    pull_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run()
    {
        BOOST_ASSERT( ! base_t::unwind_requested() );

        base_t::flags_ |= flag_started;
        base_t::flags_ |= flag_running;

        // create push_coroutine
        typename PushCoro::synth_type b( & this->callee, & this->caller, false);
        PushCoro push_coro( synthesized_t::syntesized, b);
        try
        { fn_( push_coro); }
        catch ( forced_unwind const&)
        {}
#if defined( BOOST_CONTEXT_HAS_CXXABI_H )
        catch ( abi::__forced_unwind const&)
        { throw; }
#endif
        catch (...)
        { base_t::except_ = current_exception(); }

        base_t::flags_ |= flag_complete;
        base_t::flags_ &= ~flag_running;
        typename base_t::param_type to;
        this->callee.jump(
            this->caller,
            & to);
        BOOST_ASSERT_MSG( false, "pull_coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

template< typename PushCoro, typename R, typename Fn, typename StackAllocator >
class pull_coroutine_object< PushCoro, R &, Fn, StackAllocator > : private pull_coroutine_context,
                                                                   public pull_coroutine_impl< R & >
{
private:
    typedef pull_coroutine_context                                      ctx_t;
    typedef pull_coroutine_impl< R & >                                  base_t;
    typedef pull_coroutine_object< PushCoro, R &, Fn, StackAllocator >  obj_t;

    Fn                  fn_;
    stack_context       stack_ctx_;
    StackAllocator      stack_alloc_;

    static void deallocate_( obj_t * obj)
    {
        stack_context stack_ctx( obj->stack_ctx_);
        StackAllocator stack_alloc( obj->stack_alloc_);
        obj->unwind_stack();
        obj->~obj_t();
        stack_alloc.deallocate( stack_ctx);
    }

public:
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    pull_coroutine_object( Fn fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    pull_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run()
    {
        BOOST_ASSERT( ! base_t::unwind_requested() );

        base_t::flags_ |= flag_started;
        base_t::flags_ |= flag_running;

        // create push_coroutine
        typename PushCoro::synth_type b( & this->callee, & this->caller, false);
        PushCoro push_coro( synthesized_t::syntesized, b);
        try
        { fn_( push_coro); }
        catch ( forced_unwind const&)
        {}
#if defined( BOOST_CONTEXT_HAS_CXXABI_H )
        catch ( abi::__forced_unwind const&)
        { throw; }
#endif
        catch (...)
        { base_t::except_ = current_exception(); }

        base_t::flags_ |= flag_complete;
        base_t::flags_ &= ~flag_running;
        typename base_t::param_type to;
        this->callee.jump(
            this->caller,
            & to);
        BOOST_ASSERT_MSG( false, "pull_coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

template< typename PushCoro, typename Fn, typename StackAllocator >
class pull_coroutine_object< PushCoro, void, Fn, StackAllocator > : private pull_coroutine_context,
                                                                    public pull_coroutine_impl< void >
{
private:
    typedef pull_coroutine_context                                      ctx_t;
    typedef pull_coroutine_impl< void >                                 base_t;
    typedef pull_coroutine_object< PushCoro, void, Fn, StackAllocator > obj_t;

    Fn                  fn_;
    stack_context       stack_ctx_;
    StackAllocator      stack_alloc_;

    static void deallocate_( obj_t * obj)
    {
        stack_context stack_ctx( obj->stack_ctx_);
        StackAllocator stack_alloc( obj->stack_alloc_);
        obj->unwind_stack();
        obj->~obj_t();
        stack_alloc.deallocate( stack_ctx);
    }

public:
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
    pull_coroutine_object( Fn fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    pull_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                           preallocated const& palloc,
                           StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        ctx_t( palloc, this),
        base_t( & this->caller,
                & this->callee,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run()
    {
        BOOST_ASSERT( ! base_t::unwind_requested() );

        base_t::flags_ |= flag_started;
        base_t::flags_ |= flag_running;

        // create push_coroutine
        typename PushCoro::synth_type b( & this->callee, & this->caller, false);
        PushCoro push_coro( synthesized_t::syntesized, b);
        try
        { fn_( push_coro); }
        catch ( forced_unwind const&)
        {}
#if defined( BOOST_CONTEXT_HAS_CXXABI_H )
        catch ( abi::__forced_unwind const&)
        { throw; }
#endif
        catch (...)
        { base_t::except_ = current_exception(); }

        base_t::flags_ |= flag_complete;
        base_t::flags_ &= ~flag_running;
        typename base_t::param_type to;
        this->callee.jump(
            this->caller,
            & to);
        BOOST_ASSERT_MSG( false, "pull_coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PULL_COROUTINE_OBJECT_H

/* pull_coroutine_object.hpp
Xj3fRMy9Bns9BB6wpom0n4Mf+HI79uUgNu49cCi6sxK/dwYejl2FPVbI9ePTkj9GpkYybh96v5jx/UaONg18swe/SjtNsI+/00YpOvYoWFL/bv3sSeQOX4HHHfApTbG/pdgUYr+Bx9hPwo+o2N4Jc9CZ16kLNh64Fd+NX685n7ETQ7SYhswTK8TfRhywlniVta97C/K2Fnu+GiwLFt6NDXXg/5cxhlfAm8PhcfOu5HGZ1x5yec8vBxe8ydiz8Q2D8ffY2Hcmwe9hrA33zKXMp8yjLKYspDxCWdmKOpS9lI8pn1P2UTZTPqTsoeynXNoa+0FpRrmachmlIaUxpSVlBGW4nqukjKLkUca0ps1M8Af8euNR1gabMwqZGFGT9SAX+Sr+8i34czW5jKiVCnleRfTwwVONsfek/w7oK3F3Zn10gYOhr0zFpsP3mz4GazlZkzLWCEyof91gNnsUny4GXxZybTb2E96GJSDnHvDp5/AP3ammsD+HXrpGEKOlE2eNxIfmkLdAzjfOBVuNYU8S3XqH+PZwJLHMGuQijb1MYsukVLBYL3QGf5ThwO+kITvraKsL+aAPwUjI8qNVWY9NrHVjcCPlBPHDm6tYP2Lk1B1gOHJhvW/HzmCTWrelLvuLnlJyM+zPZSazP9IB+Yb2K7K/iPxDyQD09wAxQRPOT7+qiQ0NwTrshS39FVv7qiJqoi/L8W+TsKOu22hnBbq+Bfu7CXtKvvPsp5qYcCvy1hoMgpwtrA6PmfNHv9H2I4wLu7md9eiJbl7CuJLX4B/vxSfAx1HY/ergyCuJKX1T6G8BMSZj2TQMvxYH3iS3M7EP9oa8cmPavJ56jdGls8ORW/TwfXD5vk+IWYlnF2wjvscvr9kBb7Ctr8Lja7LBnNPJ6aEXxeQASu2s+0bW5zd+sZv1v2EdZiIH89irJb7PxnZ1Je/7+3H0mjxGjI4l7wzYPR8PyM8uwQ7NRzaJsy5rDK6vjYxSGlNuhe+R8KVxMX4dO/ENe033XIO9oo+90cRm+p5KLU2s607+GmyuxGM/d7DOHnjyPngDPWx2CfXJeWWNU9gfBmuT+HEiD4ewack/8Df5jaLTyEB7ymvIBDpdii36mPvbdAbzqPAdOOo8gt27hrgEviU9hj4V4hNZ05wHdT/OHhZr3Hcr88bu3zcRmb4Vul3x54Dua6by3ir+ZqyzRhK30scLsexXvoKc+pC3K1gfcryDj5OLQVeO/5mY71Zsygt0jI17E1wa8xxyiJx/X0TsVhfflY1Pwu/e15e+P8Nm6Wd8UomVbkbu2Gcvo77+7eCIXrQDLmlH3w8tZO+VPNsPhxnbUOzgDMaJPN0PZmhBXr5gNXHkXYz/BPZrBnz5hPwpspJRBWzTAF4gS9+8g/3ogDxHEQfGg1/pY52eh8cWXP4T9o2cU0/076eqqtCfOb19PjmV8ezvX6+IH8kfF4aTl/4VrP0z9aci5+vxV62wKfuQyTrELlnsicURS32NnpPTGHAL+J85bWC/fAJ6uQB9ur2A+tjtBzG+YZ+hY8QprRX4yJgTn8EuILs5uq1GTpfUUEUkMj6TODQOnp1kHcdMRX4uYS0Z71F4su1HMPDDnHO6V2B72QcBX/QiZ5WCvYt6hjzsM2DDDeBE4sje9clNo/t99JgQ/NjkbnTIwfWfkNuOyKAD/ThELMC8l3xEbIXvPYK/PYlsbrqd/NFtinh9ArmXndgMcOL3xM8zN7K3NILY+5QmjqLL304BS59hHU4iC+DQntOxR2Bkexv2ytaTi0QvezH++17E/vVBTi9HtskbnkXfW1Qh/1gHflA6EWv9Gd+eRry3C0w3tAq2C30ugT+/3QROxB5/h78=
*/