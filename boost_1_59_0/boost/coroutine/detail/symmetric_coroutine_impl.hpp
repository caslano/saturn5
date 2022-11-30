
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
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
*/