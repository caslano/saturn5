
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
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
*/