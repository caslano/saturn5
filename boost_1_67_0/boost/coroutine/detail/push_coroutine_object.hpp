
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