
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_OBJECT_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_OBJECT_H

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
#include <boost/coroutine/detail/push_coroutine_impl.hpp>
#include <boost/coroutine/detail/trampoline_push.hpp>
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

struct push_coroutine_context
{
    coroutine_context   caller;
    coroutine_context   callee;

    template< typename Coro >
    push_coroutine_context( preallocated const& palloc, Coro *) :
        caller(),
        callee( trampoline_push< Coro >, palloc)
    {}
};

struct push_coroutine_context_void
{
    coroutine_context   caller;
    coroutine_context   callee;

    template< typename Coro >
    push_coroutine_context_void( preallocated const& palloc, Coro *) :
        caller(),
        callee( trampoline_push_void< Coro >, palloc)
    {}
};

template< typename PullCoro, typename R, typename Fn, typename StackAllocator >
class push_coroutine_object : private push_coroutine_context,
                              public push_coroutine_impl< R >
{
private:
    typedef push_coroutine_context                                      ctx_t;
    typedef push_coroutine_impl< R >                                    base_t;
    typedef push_coroutine_object< PullCoro, R, Fn, StackAllocator >    obj_t;

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
    push_coroutine_object( Fn fn, attributes const& attrs,
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

    push_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
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

    void run( R * result)
    {
        BOOST_ASSERT( ! base_t::unwind_requested() );

        base_t::flags_ |= flag_started;
        base_t::flags_ |= flag_running;

        // create push_coroutine
        typename PullCoro::synth_type b( & this->callee, & this->caller, false, result);
        PullCoro pull_coro( synthesized_t::syntesized, b);
        try
        { fn_( pull_coro); }
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

template< typename PullCoro, typename R, typename Fn, typename StackAllocator >
class push_coroutine_object< PullCoro, R &, Fn, StackAllocator > : private push_coroutine_context,
                                                                   public push_coroutine_impl< R & >
{
private:
    typedef push_coroutine_context                                          ctx_t;
    typedef push_coroutine_impl< R & >                                      base_t;
    typedef push_coroutine_object< PullCoro, R &, Fn, StackAllocator >      obj_t;

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
    push_coroutine_object( Fn fn, attributes const& attrs,
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

    push_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
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

    void run( R * result)
    {
        BOOST_ASSERT( ! base_t::unwind_requested() );

        base_t::flags_ |= flag_started;
        base_t::flags_ |= flag_running;

        // create push_coroutine
        typename PullCoro::synth_type b( & this->callee, & this->caller, false, result);
        PullCoro push_coro( synthesized_t::syntesized, b);
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

template< typename PullCoro, typename Fn, typename StackAllocator >
class push_coroutine_object< PullCoro, void, Fn, StackAllocator > : private push_coroutine_context_void,
                                                                    public push_coroutine_impl< void >
{
private:
    typedef push_coroutine_context_void                                     ctx_t;
    typedef push_coroutine_impl< void >                                     base_t;
    typedef push_coroutine_object< PullCoro, void, Fn, StackAllocator >     obj_t;

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
    push_coroutine_object( Fn fn, attributes const& attrs,
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

    push_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
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
        typename PullCoro::synth_type b( & this->callee, & this->caller, false);
        PullCoro push_coro( synthesized_t::syntesized, b);
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

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_OBJECT_H

/* push_coroutine_object.hpp
b+OicWAjOpd+Sn/SM5rBQRq1EP118ylxgFfG+fuktcSosdY5xUM9NY75N7BXc5hrzJW1GlqM1lXrpfXVWhwQL/LVYfyqFz+ZZU5mp8uNm+MJcT/JPBaw32i1vmeb15vT3YcWGrHfvSfQejfSgOawsbl9XbzP0ZcV273DQCu8kWJP0WLaxDjjOgV+Dp/xVZfZ7AwLrt7CTvbV1KpgjNPZh09H94UlkXi8EF2jH/mn+Z0fph7End2CfVLWpdxr6svWOz9W/4GNteSJTZLl6/RRURf/obK5YO8deKhKU3n0iAjrStYj1fFfe42fH1Q3ex7uzKSRpsPHyvp6r5oSe8zV7tDmafO1hdpi7X5tmfamtlF7W3tH26G9p+3WPtT2aQe0Q9oGbZO2Rdum7TzPOYVow6Jace1CrYxWVqugVdQqaVW0Gtps/jnBnFczlp/kP2PkoKn8IpL93hRr3x0L05bylSvNMX7OvDHIQcMGY44O4/iq4uRP5kLN5zH58Em1pk4pbFzKfq8u9MClfJrPzOQDH8G2lAQ1sU3yAH5c1rzc1CB0WgMV/JrGnM9WI/l2pNz+uLqDfOkp+mLrfXz793IJ3F5LvXsXXpz0GK1CT60yp+3o//R57EDzPEg7jlC/EIv2BJtTeWMpNaSwPk4PyR/g8DJcOIh+eO5RNulGX8ClrxtYn40y/+vUCurAH/x2/x9ofjl/swQcgLfWjM/ZI16A7sgKyw/ZoR+eK9oZph+heVqaF8+79S2xI7/b9Vta/inj+oCdfkeXFDRPwd44dr/vcTxXSlxNknPJh0Z8Yixl9U3du/N78HiauHDe93fD4li8VdT81BUzS2iwOGsBK8zVJPpQH+esUY/rbZ95ebUhY6vRQf2xF5xYE6kmysZxETSNfXrR3n+7FuZuxV20wMpH+eowPtOfPhoonq0F7d8GL8zz8Pl8E250jROP4yJOY0mno3x8Is5YT8sfoR/x476rxfa37EprjqT9ZnwJo07QeHR8OXXOzTCzgngIOW/WCJp/lhii1+fJzQrQxdWjQ+qR6gOV1Vlw/z24Nj/NHlMXhondu8vSaXTkzOJ8YRdsWmtPotriCX4Z6X7rT8oPs/hzdzZ9ns5ZZR/NjXDsU5qiK757233pjGR2O8V/espdCrFP4Xj5uJy+ySK4p5aW9g5M7yLG6Z+x8rEWy/BuJ1y/l58cgOnWAMvwkZa92ax4pNyHv8l18qaxcWP2gyEJOHIRvb+psFjW7lD/XPASf2oh/t4WO1XhKp/o2RqnGt8LFWmRC3B/V/Eqdu5oT1PDzaWw8KH89IQ+zqbxEvrQrWy8yz33abu1i0u5p1ZYy6RRG3bnhxNooxTYOEoMmfMFcp4tMLxHHfd+R12Cjh0hjpLDkZJ2fqZGcc+fPAPGl0wK47GwNVOaN1Mduoy5Poor5Zc95tCoyWJjgJzjWv31zHgtSdt0Jx+QL2V1VcfpKq4/sM+rmbrYdGvQa8X+Kj7nszK1aJj3+Vp9On6kWKvBj9aw4atsdYe9vv4uSQf8vrwcqy+cZKfP9PkeXFySVji5Sy65US4Zjji9j6mU2mLlWeLiYjxaXQ3WfKVaBz4Zjx9eN7fy3owJ/I/Gm5qCJ96G1zvgCnxPjGWLH+QKe+R1FcThV3iD7uvcnp4TV63oq45BjsA+lcR+DJ4eJW7KPkAXV9UP915+mN2dtwrujX1NHrqG3flSrXxs+RCekxd8kSk+zUFrNq1Ny620Vn7H/ebdMz/oTQPTRRHG9NATbGW9OmUSjXwo0hoxnQNvvtztnNn6614zW+A4fPWH2e5HJ10n56x2ijYxz5lL2GyFfB6XFWlKg6rFrBVzy0uJF+3W4Kf5rCw=
*/