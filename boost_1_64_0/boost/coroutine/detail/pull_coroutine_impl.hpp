
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
GY0NLB2DjW5KLJ1GLmkv2LMaNu0YWJaY+a/EWWN20C5Y7DPW4unmxNR2fu8DX0QqYio8PVoEPtkEpmgNrmN+Y1siS6tUcaYR67OCGDcKf34S7DsJ/drKmmRhi7ERH2EbE1i7fhp5gqHglx7Ycn7vfBIZwYYPJg6YPh5cxfzantEhPXh6JT6zBDvckbwCY3scX9PgNe5F5wbCn1l7wfebsCesyXJsy5ZtxJ9/ImZmTCNbBr6TvAGs9V4GNnsVsSR5o6pv088LzJF1K+kAZqCdupRp1yN70cgZ982lHL9ZFbOvQu9v4v4rFISfnO9xZLwWctJSExHYi1ZP4nPAPf1s5L7GIreLsBVgjDpx1N+HjnNvz37I1lawHLxKd5Cbou1Y4smcZOIXAYbZxniREQ39/fEedIsc0+Q0ZGcUOYSfaOZK8Dj4rUojxsHaKcSUPmL0P62Cl/do4kPq7vqRHAmx55fPYyNo/12Km32PffnkAXsQS29mfWijBBn4eRZ/rySOW48ul4BPya1kg62fYe5T0vFbYGC1GJyNXv1GTmTiFegR/M0He/ckNnEdIE+D/hWBRwcTC98Cpn8ILHxjK/K9n+J77cztJvJc9VWxsDN4ZwLytYR8EhgqNxfdYWz7KQcpByjTumAb0bfo11QxATnelQDO6oMPrE5sihyewHeuvRx7x/jXoj/fg5vPXAk+w744+hPj7EDWrmatpzGnXsRtrJNzDPgV2YutqftcxvcD8jMFjPAbfGLsbyWzb4RtTnyUNTtO2yPJUzC+7WDtCGxeU9pbei1re6siPsqgYL/H0f9jyGDtImLHqeQzHyE2aaXHvozFBcZaq4qbkdmrwbNH8El7D5NLwC/NF4oIQ7fW3IrPB1MkU79Nb008WxU97gp2GADW6oNe0U818hKPT9DEZDBiB/g5yQk2AtP3IZZ8/zriL2LopF3Y8hbYjINgVWzpTOxewxTwWFti5ARy4KvxC8jUz+R/xhB7TPyCej3BTIeZ50zWljh76ZXE7h3BlvjDUmx5HBj6B/IrN9+Fj8cO3/A4Y9dz6+ORDfBOu13YwRXEKfA8dx0hCjjqHmy7syf+6HX8ZiF8dZAHPgLmIU/X7RvWDlzZMUUTI+BTozfR0xXI6zp88eX4brB3qxuYR1eeoZhGzvshaOwJvJ7OmOeBG0qRce67Ap/kvYu8OLnUHo+CUeFfHv3ehGwWPACOR1439yDGiWT/wQ2OJXdt+0gV6z5mXsj/UdatP5iibx10Ht50QWc8H4ALx5Lfrs/eyRrkB9kshv+ZrxFnY18PFsLr08iRk/Ghf9kPoo/o6jHWryF+cRJrn0CO/yA+7/kB2JXbyft9oQgv+xU7RzGXX9BxcPjyTuS2E4i5ezHHR8Cd3bH39VmLhYposxS5fxj+wtf1zOfKwcRX+7GDdvTjHq5twYaDMR9CDrfFMPdoeNFZE4/w30WF2Dp+V1G6/Ej+lN8tlHktkUfyg59vQeZy4B8xRSS8sbEWB04ge8hlrxP4IWz6QwnE7NfBH9Z6axbyBc78lDkMhk8l2MFrh2Bz0fNbsB+HaXs4sfWd+8D6xKu3gm3D5mOP8FVDw7H1dvLxyFH+42D3HPibT0yFjM2vxf4c9nOTxj6tnXgFOelyI3gUn9NzKvwsYB+DOOZlYuu8Gfgq5L0OpTHlzCXYjMlgCdZ8L3Oo8iLzg693zkF+Wc+FDfFfzC9hDPb6MuSmF3sJ9VircHi4TIBJsRW9sadV8MvHwMjozw4w5WbWNpI83i21FXEHcVpqK/p/km/WkZf5hhzTPeRJCrE1iot8znpkmrxAq7NgyfuZ7yWqSON6SnP2oZuTcyFn0vd9YuVD6P90sNo=
*/