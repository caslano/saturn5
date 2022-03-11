
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