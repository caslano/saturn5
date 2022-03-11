
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