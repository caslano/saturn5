/*=============================================================================
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef PHOENIX_BIND_BIND_FUNCTION_HPP
#define PHOENIX_BIND_BIND_FUNCTION_HPP

#include <boost/phoenix/core/limits.hpp>

#if defined(BOOST_PHOENIX_NO_VARIADIC_BIND)
# include <boost/phoenix/bind/detail/cpp03/bind_function.hpp>
#else

#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>

namespace boost { namespace phoenix
{
    namespace detail
    {
        template <typename RT, typename FP>
        struct function_ptr
        {
            typedef RT result_type;

            function_ptr(FP fp_)
                : fp(fp_) {}

            template <typename... A>
            result_type operator()(A&... a) const
            {
                return fp(a...);
            }

            bool operator==(function_ptr const& rhs) const
            {
                return fp == rhs.fp;
            }

            template <typename RhsRT, typename RhsFP>
            bool operator==(function_ptr<RhsRT, RhsFP> const& /*rhs*/) const
            {
                return false;
            }

            FP fp;
        };
    } // namespace boost::phoenix::detail

    template <typename RT, typename... T, typename... A>
    inline typename detail::expression::function_eval<
        detail::function_ptr<RT, RT (*)(T...)>
      , A...
    >::type const
    bind(RT (*f)(T...), A const&... a)
    {
        typedef detail::function_ptr<RT, RT (*)(T...)> fp_type;
        return detail::expression::function_eval<fp_type, A...>::make(fp_type(f), a...);
    }
}} // namespace boost::phoenix

#endif
#endif

/* bind_function.hpp
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
*/