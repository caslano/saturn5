
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