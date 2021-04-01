
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H
#define BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/trampoline_push.hpp>
#include <boost/coroutine/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct stack_context;

namespace detail {

template< typename Arg >
class push_coroutine_impl : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< Arg >                           param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

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
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void push( Arg const& arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( const_cast< Arg * >( & arg), this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    void push( BOOST_RV_REF( Arg) arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( const_cast< Arg * >( & arg), this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

template< typename Arg >
class push_coroutine_impl< Arg & > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< Arg & >                         param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

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
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    void push( Arg & arg)
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( & arg, this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

template<>
class push_coroutine_impl< void > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< void >                          param_type;

    push_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~push_coroutine_impl() {}

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
            param_type to( unwind_t::force_unwind);
            caller_->jump(
                * callee_,
                & to);
            flags_ &= ~flag_unwind_stack;

            BOOST_ASSERT( is_complete() );
        }
    }

    inline void push()
    {
        BOOST_ASSERT( ! is_running() );
        BOOST_ASSERT( ! is_complete() );

        flags_ |= flag_running;
        param_type to( this);
        param_type * from(
            static_cast< param_type * >(
                caller_->jump(
                    * callee_,
                    & to) ) );
        flags_ &= ~flag_running;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    virtual void destroy() = 0;
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PUSH_COROUTINE_IMPL_H

/* push_coroutine_impl.hpp
xLxVLgob1b3IAU2q2ungB7gkfwa2lnufoC7a9OnsHx29B8ADoirt9RJYCuS1RhumxE8oumBb66AKDRhJmdcHqbIRK7mLdYFIPDOcM4ah547j2145daa4b4XOFkPyinC+XjxTNBQaNEzvE9W8lF1fX56Jp8TCx0T+aWFrtAhbHRH9eC3EZJTKZ8QPT9aIa5pDJMGlrTeJEM7u5RA0B025Irh8xme8D98YSo0zGNDpe7j2PEcJo00EpsmDnbPf2vKiM99/eNAiwBclqWd9lYxb1JSNmxD647QAy2Ej2xJmF8oPdY33g9nKAWD0l4x2euQpcTTI3rIMMV19E0+3EjMFzarvo278Jo8rGe3Qw8qhZTggpVbwtiq29cPfe0hwFv/NRn0UjctItpSibf//GaSP6RorCeEiZ4s6FjKMpAvWN8Z8HPLv5OIGftfv6fDrLEjGbb+gTg35XhcPepPv9Whu3M9+nWTX4cuM5HMmr+6schlqtJ1v0oCz7r5oLnwrRCkGnvqPeBWZJNEdn+lB+qxoQUFtVG7qQdoGjvTxJ8h7EbuMFyvK87rad/1Qgw==
*/