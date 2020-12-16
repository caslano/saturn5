
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
oX0Wm0MxvUAM7ZeHtLrZ3H3F1/npNVM9Sx74Pu12YpprprLFMjEVvFdI47/aG3/gi5OlYeMG9cub5eAw4toYXDbaXpyu9AC822kNqzb9/15NtbUf+OlWeA+D4+xPOaj/I97GQWIoT6Z3OuiG7533ChvXERer2+j/Orl6G1qjjvngs52G04JtxPXvabwImqIxjr1c3ais9Qhc+UexXCRLvSANX7tuoZiMa87ug8RuI3/TZveLu4oJ8DdafuFYvUDPj1Uvk8+9QYNVE4vb+WvPQrgVx/bAxa94doVNNJbcMA+7PgdPk6u630nxKfa+hydJY+VkNFvMCnpsljrFIjFPM9wZ1BFvjbSvU4zmpYk7uoc8KF2MPi42x76nTo6/Vn1He1WGa4+Zy5fxKhxLXIx7U9TqGkVYz5IXiLM5B8V3ITH0BxiWX01ArLxRjo1h7jOvBPuS1SFrsr34GUczNV9ID9LJeYJ9BzT2CLH8MJ2YbE9z5kw8+Rtc/BPdWcHcPQrP+emefDBU/Zw+oeXNr1ir/Qqe8/vrNGorNivwU873clfRDs7ixxPp8uqRvkeOXuG3+bqpz+2kb+rbs7bA/I7Dd/FiCCYPv4velmvOKS/+1DrC9E9Jz2xWkZaTFyz6kn+L+y82wRuY9CJ7rnmERohihwVwT42jxiL+wo/34/ZnR9Aa5mLQHjWVHeqFuLh/7veEl4R7w4L1XzXvFNjc73t8GKnP6/VdHrDAvSIq8KlH+UAh/nSldQx4sJ9OLsEPOk2nxYPvhTqCo9i7hf0Hdx1VdxVTYxPoiTHqQOPlmGy3Nt6cX2X95i354S1wUl7zFiz9EV7dqy/ztcXaIu3ER/rUmc+J1a64e+2hnO+FPGQ9IeFFdqlDn6s/LKDnrk/F/zRKeD791l6Nmbbr6WcbGq760LD6i/nFD5dWVdN5jK/TWa2L810artGOkDxJrvaFPtJKS8zbzzcawzyapaD7sd8H8+1vw0PrFlkH+Viswr+CD8ldYHLHdfJCOJCczz1LOManR6pjNi4n/vn2VDXcyNX8ZhV8vdZ1h+VEYmMK7XPbruCdSJgJh9b/6F5yhTXvqLnpd8ynOPULOS18btWBXlwcVktUY3pd7t0tdHpdoBstlzY7wvoIjbESptMbxYN32WFIw500Wb9Iejj4XqQwwS2vXip2+cq31/AvnPGBnOhm8ZzamU58FxeP4jODc77HvFkTONrPvfhQvaK0E2z9ir3Hy+dG03gJh/GVsUXE8904c6k2VPh5sUjHtFipxtORhoenZfaGQ1nsciBTrfQzucwF1mBrmtOVcqYmOAvv1eL7e4vJQ3YH+53xFj9vAEcat7AHjobbLCaDOn5r+PUzHMiARe3D8jFjueAFNXNaMb66fnXng4tgn7rXkPo4dDNd+SGtdwku20wvwNURv8WNzfXJHL9q3tP5zXJ6PdgzW8eYa8bJR/l9qZmwdTatzOZPpVsTpEEHxpqr7+T6G6xDWO9JLCwnozmS3lS7Kg2v5Pbvef642mKMLr8FF7aeGiGHl8uPDoUy1R27bvV5RdraPYevV5eDeS1247CicPJSOhwf3Efn7EuhkRfxC7lQUTp85VG6D8bE0dPD19D08v6PKtPE+Lqn/HQGX3qsKt94KWQty+fsNb2V65vCVHXwbp3DMAt3eH5HOme2fG7/z+JHjN5J522WTxTpD1MewKnf4sCb8GYJOqgqbfKM3Ks4vfAKHY03yp8I3vnJiZGX2tF2j7Dl+2xcC/6I5cn4+dneYn8eTQnz975qnqwJDFoIw24Q//oTu5Ye6y/mzFHFbHM0EDckqgNG6n/wziEbJH+CH2bSaXBwMHvHaSO/Yp/a9i5XooU=
*/