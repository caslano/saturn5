
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_OBJECT_H
#define BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_OBJECT_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_impl.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct stack_context;

namespace detail {

template< typename R, typename Fn, typename StackAllocator >
class symmetric_coroutine_object : public symmetric_coroutine_impl< R >
{
private:
    typedef symmetric_coroutine_impl< R >                       impl_t;
    typedef symmetric_coroutine_object< R, Fn, StackAllocator > obj_t;

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
    symmetric_coroutine_object( Fn fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    symmetric_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run( R * r) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! impl_t::unwind_requested() );

        impl_t::flags_ |= flag_started;
        impl_t::flags_ |= flag_running;
        try
        {
            symmetric_coroutine_yield< R > yc( this, r);
            fn_( yc);
        }
        catch ( forced_unwind const&)
        {}
        catch (...)
        { std::terminate(); }

        impl_t::flags_ |= flag_complete;
        impl_t::flags_ &= ~flag_running;
        typename impl_t::param_type to;
        impl_t::callee_.jump(
            impl_t::caller_, 
            & to);
        BOOST_ASSERT_MSG( false, "coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

template< typename R, typename Fn, typename StackAllocator >
class symmetric_coroutine_object< R &, Fn, StackAllocator > : public symmetric_coroutine_impl< R & >
{
private:
    typedef symmetric_coroutine_impl< R & >                         impl_t;
    typedef symmetric_coroutine_object< R &, Fn, StackAllocator >   obj_t;

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
    symmetric_coroutine_object( Fn fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    symmetric_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run( R * r) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! impl_t::unwind_requested() );

        impl_t::flags_ |= flag_started;
        impl_t::flags_ |= flag_running;
        try
        {
            symmetric_coroutine_yield< R & > yc( this, r);
            fn_( yc);
        }
        catch ( forced_unwind const&)
        {}
        catch (...)
        { std::terminate(); }

        impl_t::flags_ |= flag_complete;
        impl_t::flags_ &= ~flag_running;
        typename impl_t::param_type to;
        impl_t::callee_.jump(
            impl_t::caller_, 
            & to);
        BOOST_ASSERT_MSG( false, "coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

template< typename Fn, typename StackAllocator >
class symmetric_coroutine_object< void, Fn, StackAllocator > : public symmetric_coroutine_impl< void >
{
private:
    typedef symmetric_coroutine_impl< void >                        impl_t;
    typedef symmetric_coroutine_object< void, Fn, StackAllocator >  obj_t;

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
    symmetric_coroutine_object( Fn fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
        fn_( fn),
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}
#endif

    symmetric_coroutine_object( BOOST_RV_REF( Fn) fn, attributes const& attrs,
                                preallocated const& palloc,
                                StackAllocator const& stack_alloc) BOOST_NOEXCEPT :
        impl_t( palloc,
                stack_unwind == attrs.do_unwind),
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
        fn_( fn),
#else
        fn_( boost::forward< Fn >( fn) ),
#endif
        stack_ctx_( palloc.sctx),
        stack_alloc_( stack_alloc)
    {}

    void run() BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! impl_t::unwind_requested() );

        impl_t::flags_ |= flag_started;
        impl_t::flags_ |= flag_running;
        try
        {
            symmetric_coroutine_yield< void > yc( this);
            fn_( yc);
        }
        catch ( forced_unwind const&)
        {}
        catch (...)
        { std::terminate(); }

        impl_t::flags_ |= flag_complete;
        impl_t::flags_ &= ~flag_running;
        typename impl_t::param_type to;
        impl_t::callee_.jump(
            impl_t::caller_, 
            & to);
        BOOST_ASSERT_MSG( false, "coroutine is complete");
    }

    void destroy()
    { deallocate_( this); }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_OBJECT_H

/* symmetric_coroutine_object.hpp
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
*/