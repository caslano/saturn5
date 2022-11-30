
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
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
*/