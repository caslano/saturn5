
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
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
*/