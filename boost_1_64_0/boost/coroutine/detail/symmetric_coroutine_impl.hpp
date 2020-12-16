
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_IMPL_H
#define BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_IMPL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/utility.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/preallocated.hpp>
#include <boost/coroutine/detail/trampoline.hpp>
#include <boost/coroutine/exceptions.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class symmetric_coroutine_impl : private noncopyable
{
public:
    typedef parameters< R >                           param_type;

    symmetric_coroutine_impl( preallocated const& palloc,
                              bool unwind) BOOST_NOEXCEPT :
        flags_( 0),
        caller_(),
        callee_( trampoline< symmetric_coroutine_impl< R > >, palloc)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~symmetric_coroutine_impl() {}

    bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            flags_ |= flag_running;
            param_type to( unwind_t::force_unwind);
            caller_.jump(
                callee_,
                & to);
            flags_ &= ~flag_running;
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void resume( R r) BOOST_NOEXCEPT
    {
        param_type to( const_cast< R * >( & r), this);
        resume_( & to);
    }

    R * yield()
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ &= ~flag_running;
        param_type to;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                    caller_,
                    & to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
        BOOST_ASSERT( from->data);
        return from->data;
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X > * other, X x)
    {
        typename symmetric_coroutine_impl< X >::param_type to( & x, other);
        return yield_to_( other, & to);
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X & > * other, X & x)
    {
        typename symmetric_coroutine_impl< X & >::param_type to( & x, other);
        return yield_to_( other, & to);
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X > * other)
    {
        typename symmetric_coroutine_impl< X >::param_type to( other);
        return yield_to_( other, & to);
    }

    virtual void run( R *) BOOST_NOEXCEPT = 0;

    virtual void destroy() = 0;

protected:
    template< typename X >
    friend class symmetric_coroutine_impl;

    int                 flags_;
    coroutine_context   caller_;
    coroutine_context   callee_;

    void resume_( param_type * to) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        caller_.jump(
            callee_,
            to);
        flags_ &= ~flag_running;
    }

    template< typename Other >
    R * yield_to_( Other * other, typename Other::param_type * to)
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );
        BOOST_ASSERT( ! other->is_running() );
        BOOST_ASSERT( ! other->is_complete() );

        other->caller_ = caller_;
        flags_ &= ~flag_running;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                    other->callee_,
                    to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
        BOOST_ASSERT( from->data);
        return from->data;
    }
};

template< typename R >
class symmetric_coroutine_impl< R & > : private noncopyable
{
public:
    typedef parameters< R & >                         param_type;

    symmetric_coroutine_impl( preallocated const& palloc,
                              bool unwind) BOOST_NOEXCEPT :
        flags_( 0),
        caller_(),
        callee_( trampoline< symmetric_coroutine_impl< R > >, palloc)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~symmetric_coroutine_impl() {}

    bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            flags_ |= flag_running;
            param_type to( unwind_t::force_unwind);
            caller_.jump(
                callee_,
                & to);
            flags_ &= ~flag_running;
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void resume( R & arg) BOOST_NOEXCEPT
    {
        param_type to( & arg, this);
        resume_( & to);
    }

    R * yield()
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ &= ~flag_running;
        param_type to;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                    caller_,
                    & to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
        BOOST_ASSERT( from->data);
        return from->data;
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X > * other, X x)
    {
        typename symmetric_coroutine_impl< X >::param_type to( & x, other);
        return yield_to_( other, & to);
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X & > * other, X & x)
    {
        typename symmetric_coroutine_impl< X & >::param_type to( & x, other);
        return yield_to_( other, & to);
    }

    template< typename X >
    R * yield_to( symmetric_coroutine_impl< X > * other)
    {
        typename symmetric_coroutine_impl< X >::param_type to( other);
        return yield_to_( other, & to);
    }

    virtual void run( R *) BOOST_NOEXCEPT = 0;

    virtual void destroy() = 0;

protected:
    template< typename X >
    friend class symmetric_coroutine_impl;

    int                 flags_;
    coroutine_context   caller_;
    coroutine_context   callee_;

    void resume_( param_type * to) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        caller_.jump(
            callee_,
            to);
        flags_ &= ~flag_running;
    }

    template< typename Other >
    R * yield_to_( Other * other, typename Other::param_type * to)
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );
        BOOST_ASSERT( ! other->is_running() );
        BOOST_ASSERT( ! other->is_complete() );

        other->caller_ = caller_;
        flags_ &= ~flag_running;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                    other->callee_,
                    to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
        BOOST_ASSERT( from->data);
        return from->data;
    }
};

template<>
class symmetric_coroutine_impl< void > : private noncopyable
{
public:
    typedef parameters< void >                          param_type;

    symmetric_coroutine_impl( preallocated const& palloc,
                              bool unwind) BOOST_NOEXCEPT :
        flags_( 0),
        caller_(),
        callee_( trampoline_void< symmetric_coroutine_impl< void > >, palloc)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~symmetric_coroutine_impl() {}

    inline bool force_unwind() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_force_unwind); }

    inline bool unwind_requested() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_unwind_stack); }

    inline bool is_started() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_started); }

    inline bool is_running() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_running); }

    inline bool is_complete() const BOOST_NOEXCEPT
    { return 0 != ( flags_ & flag_complete); }

    inline void unwind_stack() BOOST_NOEXCEPT
    {
        if ( is_started() && ! is_complete() && force_unwind() )
        {
            flags_ |= flag_unwind_stack;
            flags_ |= flag_running;
            param_type to( unwind_t::force_unwind);
            caller_.jump(
                callee_,
                & to);
            flags_ &= ~flag_running;
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    inline void resume() BOOST_NOEXCEPT
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        param_type to( this);
        flags_ |= flag_running;
        caller_.jump(
            callee_,
            & to);
        flags_ &= ~flag_running;
    }

    inline void yield()
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ &= ~flag_running;
        param_type to;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                     caller_,
                    & to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
    }

    template< typename X >
    void yield_to( symmetric_coroutine_impl< X > * other, X x)
    {
        typename symmetric_coroutine_impl< X >::param_type to( & x, other);
        yield_to_( other, & to);
    }

    template< typename X >
    void yield_to( symmetric_coroutine_impl< X & > * other, X & x)
    {
        typename symmetric_coroutine_impl< X & >::param_type to( & x, other);
        yield_to_( other, & to);
    }

    template< typename X >
    void yield_to( symmetric_coroutine_impl< X > * other)
    {
        typename symmetric_coroutine_impl< X >::param_type to( other);
        yield_to_( other, & to);
    }

    virtual void run() BOOST_NOEXCEPT = 0;

    virtual void destroy() = 0;

protected:
    template< typename X >
    friend class symmetric_coroutine_impl;

    int                 flags_;
    coroutine_context   caller_;
    coroutine_context   callee_;

    template< typename Other >
    void yield_to_( Other * other, typename Other::param_type * to)
    {
        BOOST_ASSERT( is_running() );
        BOOST_ASSERT( ! is_complete() );
        BOOST_ASSERT( ! other->is_running() );
        BOOST_ASSERT( ! other->is_complete() );

        other->caller_ = caller_;
        flags_ &= ~flag_running;
        param_type * from(
            static_cast< param_type * >(
                callee_.jump(
                    other->callee_,
                    to) ) );
        flags_ |= flag_running;
        if ( from->do_unwind) throw forced_unwind();
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_IMPL_H

/* symmetric_coroutine_impl.hpp
TTvaBxj/G/cfp266gb92kjvQ1qlv8f+r1LlfFt9r4aj6xyu0Yvva9BctsfO3/LaVGkcr9SPxtjXIy6uErK3TTyNoY/cfuUaNK5le97NDJzWOqebgDZwm5/skka3Fwx9w4IVsv46G3/2K2vXD4lPMvXW3/IiGfXSmegr83FJEzYhmXlUKrr7m8yh51Ws08U9ywRP0/2rn7xLzG/iafH3wi3LfxXjgafZoyE/V446Pglee9fFdtMsDfrLnx1m4a7IaPf959SraR226nRzklJpUiB/0tZb00u/4bXkaIMLn8r8N9MGw4zj0xpC9IfBnEz45LD7gRNwWPr0QTl+ND9z3eAU4AdcyrCfeKb5HmesouN6Prj1VLPguSbzQiBZy3eEvvcdZxzPMSb0uwfcDWmOSPz29U936j2IaZr1F49Rl93lqCDFL9EHd4Vhe8VhcvVSeMDBMLy+RC7ej9ejttJ/oXbWI9NvFVDM4K3ZP0GqT9oi/curPeHms/Ld5I9pFnKx0j2UL5Nn4JN7a6pXD7Y+zVzyyAb+wRjE6VZ5mPo+JuS/5Z+I3cDcLFsnLJw4Sc8/yB7nUu/z39kr60JeNMmD2HbAuPuL0f+trYj/7PtRfb+LnBaP500Q6dTzsHCw+Lwz2AfMf3DSfhlnu2ado6qvFVedHaY/Sxh+Hj8urAW61JvQujRDsU4iBQcNppfa0UoTn14FZB2CV9fnmdME0OfcLcqGryrFzaz9h8+Zv7NEZKFf9SJ/9XZ4vTvhZTrVcPLv2T+LljpuM6yjeiIPFz8o3S6ov8/ni5mV2Ubk1/trZig6Ohj3slfgpv2TTyh+Lz7F8r4o+3Gi/UU2cONaapvyh9/s0+1c47m28UNT8bDFOfvaD+N1Twlw/IH8ap5/XqVvWow/xf5E9wTs2Ymanvrjm4CTXc8i58pYp78mBSvl7Mlvdr//rzPFCvC6Hv+t9vM3nC9Nhd9NwpdNpgP00jpxz1jNypDLyr+v5mDXcoWI7he0b6Pv0CXSGz+s0tOb8G7qniTrpxe7fj0ZeQNO1kH/BiqHj5SV8J1+bnHwi8xJ63hzGm7cD4rbudrrkNuNYJtadf0FXuPoaTVRXHBlTuYeD/bNq+NvxjNhPLS5u29GOc/GmZx++j06hDcc+KTfzzAvG4eiXaNSx9q3R4kf1baqYvI7OuagV3kwT0/isjTrF8OP47HPrDSvEOD0zFk59BSt+egKGVxBn2mxtrtZVXvv4057BbqMbw0fjuU6uHVVHf6wvj/kNfMRJ119sHDRIFA3QJKh3vU73tMM9H6gr9lIXwXcfslNFPFV7sfgNwyh9rz5a7UydtugP1jzLsrsawlfy7yvqw+9N/Hp8zvf3FR6sX3s8G27W6hXMjVx4mRroQPniWnMm/+2EV2Jw58OX8a0GwT4uPPIpG3eSM9WOxBewLJZ2hDedM+HeaJhobpInqX29KxbvpmnpvB3y40gxWmOu/HSyOiOcCcvnV7BzrzX8JRVf/Va/CkZ6P8DYK9qXXYpt1dUvFwNtQt6thiXz8tCzc8zLDrE02HqoebwJ7n2PI9bwl1dp6GqZ7NdW7reRlr1GLf57OqcbzQsDD+tjqny7eg98C4OvwrGLJ8CSp9lpl7HShMeLOr6UH6TLz9Qenigix/2RHydZOzoZsv9av+QUl+wN8inany/Em4O+j4ZO71nY0RtmyCvnbbSXLEZ/8fXtuGH3HnljDzmCeI61N7LmQjgjpsPy0w5y8stCYnkfHjwk5xMnS8R5+cbqvJON5Q5zR1/t0c8n7Dns31T9VF4X7LO4332i2KdDcT7ZX87dVb5K50dOYqOX+aR7TblTDRce/4z7506xFl3K3NMQP00=
*/