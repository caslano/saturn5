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
+NOFGN/bK/fYxkLTWuSNMF9Vce7fbre+Kt2D59ix9wng9D5xmuPrPjfk/tNJVx4W7Oueir7o8/DvGTHSlXzdM2NMRhPpFxh2uuPrjqHccfgbqzO+7taY8XWfHQtf43B87Ml9oONjB+cDnRhjPlCx3NkD041285Z9TiRi5AuJvV8quo2TVHrz/V8ylo6TijHfSOGhsvFjMWy1CBujOa50jO+jHTfnBAKLcD8H2XrHHxoAtoHL
*/