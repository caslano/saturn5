/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fun_ref.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object reference adapter. The adapter stores a reference to external
 * function object and forwards all calls to the referred function.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Reference wrapper for function objects
template< typename FunT >
struct function_reference_wrapper
{
    typedef typename FunT::result_type result_type;

    explicit function_reference_wrapper(FunT& fun) : m_Fun(fun) {}

    result_type operator() () const
    {
        return m_Fun();
    }

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template< typename... ArgsT >
    result_type operator() (ArgsT const&... args) const
    {
        return m_Fun(args...);
    }
#else
    template< typename T >
    result_type operator() (T const& arg) const
    {
        return m_Fun(arg);
    }

    template< typename T1, typename T2 >
    result_type operator() (T1 const& arg1, T2 const& arg2) const
    {
        return m_Fun(arg1, arg2);
    }
#endif

private:
    FunT& m_Fun;
};

template< typename FunT >
BOOST_FORCEINLINE function_reference_wrapper< FunT > fun_ref(FunT& fun)
{
    return function_reference_wrapper< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_

/* fun_ref.hpp
8J9H1wRe8+m6t2S/TnaWNS45U0K/dfsu8j6zC3tE8ygu2VJCccn5eRSXbGP5hO+FcB0V0HGiOS7ZP4/ikufm0Xkr7EnXvDXqpZr3QINKad8LK6XzViGXK4PcVdZrtivzqX2+MrDPWb3MYdbr4or5dL3w7HyDdfEBV3uO6mqBS+bT81gb5tN4b94BV3uO3s/WARZxE3kBnW8U5Knifi6XGwpy863jJitKaNwkrYSekUgrNb7zUVJqfI982FOu9h/dwbr9V5TSdUB5KV0HVOplhmrrAMO4SWkJjZvMLDH+PlUelhUvfv/poMvWYx6xxiZXF1BscnOBwfdvucxQkBkPdrGQeWgBHbuPM56A/7hMGWQGWcdOMhfQOx+LgOceO5GedtV99Pfmfh7L3hW+kY28bPH7l0+71lQxKfBFEBg0zHR8fiH18ZeR5yWuZ7jMBiCztTUmUUspJrm9wBiTXJ9P11T3LtTOaIn3fw/p2v4v1phk8EIaNxmzkI4xFYd0fveuOSaRsU6HFOGbeAspJvl+Pp2HOy40uP/Byw05LY0dpCrdLOqyZREdg3ctouN66TMufx8bYB0z+aaUxkzeK6V4xGuR8R2Q0EXG49AFroMMfnLeehxqtYjOA90X0T4X+axOZqU1HrmGdfARxqGLpcZ4xG8RxfQbnnXNEePawpxbA1ZcWkZts7qM9p/6h3W2+d4ak1xeQOMmH6CuK6Qwt3NbLyyg/4b+j5g3S7K7YZIsroMMOlSqAXUsfC64jGKSJmV0jL2ml7lZs40hLnl7AY2dfL2Ifh/3zALah/6G+cR98EGVrrJj69YudpK2mK6RChZTfHKDyw4GP/jSHJ98g22yRwrV4ZOIjviNqkkPSCtH6sses5hilIv4fhFwxfshPvMpRrmKeeeAnlPE/aIjTNcA0BW+UF/Pwq6/lNE7IrbFFKOc5jIVkFmmnVs0xChdUNc/eAnfK8Bymgp2DTEYGy+V0XsijZ7T2fW6WhfC9KYY5avFHKNMFDDKZ8ifB/knCD5TopddxTCK4qc6giy+N7mEziX1l9AYfP2jTHYQyF5ijk8+Ql9+xEOPT44h7z5ZX+6ZxRSfPLGI4pPLiyk+2buIfsc+neungH6p5vjkOJMn/DvAyIsR9z+PusbK8b/T/tUu03Zsu5SuO3supfNYcJVrrTF+u7bWMJT5/RIaD/xxCb2vm8VlyiBzas3nig4voee6fmNg8xNcrgJyh5qv3R5eQjHKHuTFCf5Z/5hLzwnH1TqwxAzGKaiteRs0XkbPPLdAniruZXDZDUD2ctXh9m9+aGPYad0YtsL24Wh9WfmL6LmKBUuN1wirlxrfT7+lr2P/mm2xeSm1xZNLKQZNP66T2xrmIpP6ndHVb778u1H6tUIh1q+J4u3273UsXWqw/8/L8z4tTTzsnHlkFUo1rYdtuVNGe6EegcjzFf3/eVc9Js5x/ut/jrtNz+Yuo+uP95cZtI1eZkdr3LJ6GY2pbFlGcUsVl6mAzHrmvl+wjH5jd/Yy/Td2gwIqbJL2F6D9P3gBbdgr8CcIdYRgTw8MxDOsPSWodawUCs9e8PzHus7n5KzclFkFuBcCfBVokeTkZ6XlAHW+WwpyzjVz8orx+afb7BkxlF3qLvkH4v3kEwwrQ7JBWg7pHJR5egvuEyZnJc1K65yckJGTURghMT8DneC3WJDbH+e831TnBamDnDrjHBCC9edysJV11cXf2F/YAFDEvb6oYy+mY/ALrE8yHWdD+i3ky9tKdEzIS8pPyjbRswjzZxnpyWTZ8L238L0YfK8u/LYIf0vB97x073np3msDvnId2vLMSUnKRV/xVT0dqt0Hurzbf9EXfKS4QJvz/XA=
*/