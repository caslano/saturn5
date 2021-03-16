/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP
#define PHOENIX_BIND_BIND_FUNCTION_OBJECT_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function_object.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    template <typename F>
    inline typename detail::expression::function_eval<F>::type const
    bind(F f)
    {
        return detail::expression::function_eval<F>::make(f);
    }

    template <typename F, typename... A>
    inline typename detail::expression::function_eval<F, A...>::type const
    bind(F f, A const&... a)
    {
        return detail::expression::function_eval<F, A...>::make(f, a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function_object.hpp
s7s6g2gjy9N+5iwnloUGsvGkU43CU2vhebBr+DwR0+Z6C+7+rub59PamDY0WzN8+jOQlt8XGu0jhXRzqH687xqTtg/1zkoI92cLvdTe0Sn6bc62WhHjJ+Vx/kAcenabwnq7gO6izivj+JA0fLJNGy1SZM3LC9RteLbfo5PPI9fMP3czzACudv6vo5769grSXA/dm0NNmvyDt56u6Lgjxj+Hb9gzy7yIFe7FF110dzfOP3YI4dPttHJfnmPuIWJ4=
*/