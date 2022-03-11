
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