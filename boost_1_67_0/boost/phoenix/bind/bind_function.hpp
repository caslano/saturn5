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