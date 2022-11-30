
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PULL_COROUTINE_IMPL_H
#define BOOST_COROUTINES_DETAIL_PULL_COROUTINE_IMPL_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/coroutine_context.hpp>
#include <boost/coroutine/detail/flags.hpp>
#include <boost/coroutine/detail/parameters.hpp>
#include <boost/coroutine/detail/trampoline_pull.hpp>
#include <boost/coroutine/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct stack_context;

namespace detail {

template< typename R >
class pull_coroutine_impl : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;
    R                   *   result_;

public:
    typedef parameters< R >                           param_type;

    pull_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee),
        result_( 0)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    pull_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind,
                         R * result) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee),
        result_( result)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~pull_coroutine_impl() {}

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

    void pull()
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
        result_ = from->data;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    bool has_result() const
    { return 0 != result_; }

    R get() const
    {
        if ( ! has_result() )
            boost::throw_exception(
                invalid_result() );
        return * result_;
    }

    R * get_pointer() const
    {
        if ( ! has_result() )
            boost::throw_exception(
                invalid_result() );
        return result_;
    }

    virtual void destroy() = 0;
};

template< typename R >
class pull_coroutine_impl< R & > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;
    R                   *   result_;

public:
    typedef parameters< R & >                           param_type;

    pull_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee),
        result_( 0)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    pull_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind,
                         R * result) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee),
        result_( result)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~pull_coroutine_impl() {}

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

    void pull()
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
        result_ = from->data;
        if ( from->do_unwind) throw forced_unwind();
        if ( except_) rethrow_exception( except_);
    }

    bool has_result() const
    { return 0 != result_; }

    R & get() const
    {
        if ( ! has_result() )
            boost::throw_exception(
                invalid_result() );
        return * result_;
    }

    R * get_pointer() const
    {
        if ( ! has_result() )
            boost::throw_exception(
                invalid_result() );
        return result_;
    }

    virtual void destroy() = 0;
};

template<>
class pull_coroutine_impl< void > : private noncopyable
{
protected:
    int                     flags_;
    exception_ptr           except_;
    coroutine_context   *   caller_;
    coroutine_context   *   callee_;

public:
    typedef parameters< void >      param_type;

    pull_coroutine_impl( coroutine_context * caller,
                         coroutine_context * callee,
                         bool unwind) :
        flags_( 0),
        except_(),
        caller_( caller),
        callee_( callee)
    {
        if ( unwind) flags_ |= flag_force_unwind;
    }

    virtual ~pull_coroutine_impl() {}

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

    inline void pull()
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

#endif // BOOST_COROUTINES_DETAIL_PULL_COROUTINE_IMPL_H

/* pull_coroutine_impl.hpp
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
*/