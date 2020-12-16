
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H
#define BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H

#include <algorithm>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/move/move.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/explicit_operator_bool.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/exceptions.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename R >
class symmetric_coroutine_yield
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< R >       impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;
    R           *   result_;

    symmetric_coroutine_yield( impl_type * impl, R * result) BOOST_NOEXCEPT :
        impl_( impl),
        result_( result)
    {
        BOOST_ASSERT( 0 != impl_);
        BOOST_ASSERT( 0 != result_);
    }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    {
        std::swap( impl_, other.impl_);
        std::swap( result_, other.result_);
    }

    symmetric_coroutine_yield & operator()()
    {
        result_ = impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_);
        return * this;
    }

    R get() const
    {
        if ( 0 == result_)
            boost::throw_exception(
                invalid_result() );

        return * result_; 
    }
};

template< typename R >
class symmetric_coroutine_yield< R & >
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< R & >     impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;
    R           *   result_;

    symmetric_coroutine_yield( impl_type * impl, R * result) BOOST_NOEXCEPT :
        impl_( impl),
        result_( result)
    {
        BOOST_ASSERT( 0 != impl_);
        BOOST_ASSERT( 0 != result_);
    }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0),
        result_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    {
        std::swap( impl_, other.impl_);
        std::swap( result_, other.result_);
    }

    symmetric_coroutine_yield & operator()()
    {
        result_ = impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type & x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        result_ = impl_->yield_to( other.impl_);
        return * this;
    }

    R & get() const
    {
        if ( 0 == result_)
            boost::throw_exception(
                invalid_result() );

        return * result_; 
    }
};

template<>
class symmetric_coroutine_yield< void >
{
private:
    template< typename X, typename Y, typename Z >
    friend class symmetric_coroutine_object;

    typedef symmetric_coroutine_impl< void >    impl_type;

    struct dummy {};

    BOOST_MOVABLE_BUT_NOT_COPYABLE( symmetric_coroutine_yield)

    impl_type   *   impl_;

    symmetric_coroutine_yield( impl_type * impl) BOOST_NOEXCEPT :
        impl_( impl)
    { BOOST_ASSERT( 0 != impl_); }

public:
    symmetric_coroutine_yield() BOOST_NOEXCEPT :
        impl_( 0)
    {}

    symmetric_coroutine_yield( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT :
        impl_( 0)
    { swap( other); }

    symmetric_coroutine_yield & operator=( BOOST_RV_REF( symmetric_coroutine_yield) other) BOOST_NOEXCEPT
    {
        symmetric_coroutine_yield tmp( boost::move( other) );
        swap( tmp);
        return * this;
    }

    BOOST_EXPLICIT_OPERATOR_BOOL();

    inline bool operator!() const BOOST_NOEXCEPT
    { return 0 == impl_; }

    inline void swap( symmetric_coroutine_yield & other) BOOST_NOEXCEPT
    { std::swap( impl_, other.impl_); }

    inline symmetric_coroutine_yield & operator()()
    {
        impl_->yield();
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other, typename Coro::value_type & x,
                                            typename disable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        impl_->yield_to( other.impl_, x);
        return * this;
    }

    template< typename Coro >
    symmetric_coroutine_yield & operator()( Coro & other,
                                            typename enable_if<
                                                is_same< typename Coro::value_type, void >,
                                                dummy*
                                            >::type = 0)
    {
        BOOST_ASSERT( other);

        impl_->yield_to( other.impl_);
        return * this;
    }
};

template< typename R >
void swap( symmetric_coroutine_yield< R > & l, symmetric_coroutine_yield< R > & r)
{ l.swap( r); }

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_SYMMETRIC_COROUTINE_YIELD_H

/* symmetric_coroutine_yield.hpp
i6rt0981quB68dKFD1Y4KAaK0rXOaX2PPGmt2opazu4dxvAILkgJtD5ex4tju9J9n3t+B/PhGTuX8ddPaRk5dIr6QIr4O7rE+KLUGkd4Pps3eRjfefafeuMicSVdDdWlWx6Cmx0f9/l42rgSLvP5kqDP+ldloHfGvuHfcsUsfN6Uv3Y0l58eU3M7QU+k2uuHR/Ph9gpVxFw+vOLabdpW7WvrEyOG4Am/79c+0d7SNmnvaru1XVrweetgv745vHAOfqssl+mkpluIhjXXM39vbdfvefaqBd0tj3oM/j4GC9Tp+rzmupL0sGum04s/TKLjHtHw3+SL9eULOE4bbLkfVq5V68LPw/jH0tv5+SJ7m3qJrwwc245/08FdnsB11+CHYXLlbfDvIJvLKa+E9yu6w+6D/At2lM0H62/gU/DyNtjxQk1+BW/a7wjBCX79OjyE6+2Xiclh9mTy8+L94Pok+gv+/u5FGIKLd/akyeinlQNgNv74Aq4uCb4r421xsZIPmYcN+G33Ifewd68JfkgWN4NLm8eL6be57puqfqI+NsO7HpWu5kN8ZJU8bJbzovDv7XfQq+IlRLeuWYgD9S16hfzDeti8l3Ds9Xi3E3uJmYcb07tDvDeeGXJvXNveuvsR8R68U/MtbrlHvn0Ipy5UCzwk12wl96+BN+T7o8xPu8P0dgP8mxzpXR7raLPE5Rqc8SxsSQ7bow5jcdbVX5ovfN70pH7DzIHj1dDvpmcj5EF1YF099ihIL5iLTeb/hSniBocU6Bh8P4c4XMGGl+o7fIyy5ycLH/SSv0zbpR94JGKz65uqJQe5Gk307WL+zR/ubKRmuhQGPulc51+C42q457ET5p6/rmCjz0rAUrbZ5fztO2Hmo3TcHvffSTOphawUh7HmKAx3tlxIE91HY2XTjZfl7I3Yv1/97XGaQH/zmudZcH+GcTzm2c0iYNrPEaHeMewc7B1fh+PlJAvZ4sP97vlOUC9VC9hn3uLkxt1wVkX6oTg+nS7GMv1O4zbfzS/iaLFp1lneEQ+P4x+cOkytu2Vbepc/nvR5eH/o9HuZt0d6ZpTr5CZf3oiTSxg7Pz2xAgd3p/sa0wPHrWkE74k9rd7yYLCHg2+a7zJvyou+hzmD2N08Tb+dZi4nTvhV+WR1wniaJIJ2uZLf88NgjavDUJoeLkxai1+uos1bhRjPPht+vFH+NhN3bfkOJ5SVK4yS13hu9R3GR5+kwPhYOUvbkmpS5j1LXypexz/5d8lHzOVt8rP+NAmbvnmR+rE4W8bnX7tTPInfImyWCk8TxM93jlf27CZbzENMCCaoN5qHkWpcVcoF32MNB+m5TmoJNfnZuB/gfwX4/KycBp9HToKVeOWwOI6+FgaXk5vCjPxskXCQLfqIOTi9gqYd3UVOXA0vel6ae2wQo3Oaye+NcbH2oLZJm/xbvut5O55jY76VBMuP6/e1L4pZmn35YetHAT6kyVMTcbzcbRC7hMRYnkfN/2vyqM+C/Yb4FT8NTcCnfDFaXp4NE2+YATv7qEl1Ng613ndni8tB9nGY61vSc9aaDtNUF+zhBzi3EQ7/JDN4t9f6zA18JVn9IRKnykdT7rJPLtBaySEiyjrEEn4jF18WDQ/kDe2HBdfBaBg1gHaYT2u8xueKlaM3WtvHp6byxOIIhpMbsdP2u/B6QzrpVdr8XdwLH2rDrD20Y3HnfZmtntRV/vkwTZFXnlCSP252rrm+zD2bvcDvO8DeaGtk/j7Wi03kR2MiYVU3fuZYNa2m1lfrfc5/E2OwNlT7vbZEi2oizhbQ4JvCp2uURZdbL15EO5jbR1Ph0AFY2lNNcBs/j6K9JvKrBvTEZLVl+udVeqo=
*/