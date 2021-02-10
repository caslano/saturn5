
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
wyKzSaVb19ZrCFR7HY4D37BrTkrXFZMSHSWu8SxAGlgN2aC+5zmtYgeldpGV7hJ/aFjhGs0C2Za3hcgyqNX20K1bU1odmjbLoMaild5jfSwybISUZKTYAKHW7TVaGAY8E5aMRUAftABXjciY2wXCC3WjJYaS1/8K7Xh85Ngcj08GYO3Gh5uy10i70RUYVrpVjevOkjN0LGpQM2UKXtfcJqfQ4OwmnBFNuwvp5ahehsZEucVffEsM8h6PDzMNcqrlPUvty3nJnsSIIjGaR3Eymi8Tz1JkjiwqB657jqKqeC4Y9HFPrIBmMB5yg91c2piOWdck1qt1E97CKcIObLfbcb/jioHmEpyx1pIoOUSkFO/kAE42LZnUO5BVMbEKD1Ort3QRJsvFLDxLnc5Xxbyj2enP30r9Q7CcJh6OLUzBnSpsLzoyzma+iJLoNJrGnlOxXQr/CD7Op6Hnq8LrGsxNhbdftJ9QoumjoUTRt4sD+scjemxTsHiN3//pVrvw1KW4Dam3O3T4HcMg5H6mq1Fv8Az3vSY/mjoXBN6jieMCgqk6jtYAfJ3NW/rfTHZ7wb8lB7Zq+0Orq+Gm1jgxKzoYwfCz99nzC+ESF3wCp+D9ZDpJrrzAjZZbzHsH0lWkC0Wfguky9BauWGZLJbqw
*/