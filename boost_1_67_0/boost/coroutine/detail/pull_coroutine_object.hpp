
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