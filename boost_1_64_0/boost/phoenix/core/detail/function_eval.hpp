/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_CORE_DETAIL_FUNCTION_EVAL_HPP
#define BOOST_PHOENIX_CORE_DETAIL_FUNCTION_EVAL_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/utility/result_of.hpp>

#ifndef BOOST_PHOENIX_NO_VARIADIC_FUNCTION_EVAL
#   include <boost/mpl/if.hpp>
#   include <boost/type_traits/is_reference.hpp>
#endif

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/core/detail/cpp03/function_eval_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(detail)(function_eval)
  , (meta_grammar)(meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix {
    namespace detail
    {
        template <typename T>
        T& help_rvalue_deduction(T& x)
        {
            return x;
        }

        template <typename T>
        T const& help_rvalue_deduction(T const& x)
        {
            return x;
        }

        struct function_eval
        {
            template <typename Sig>
            struct result;

#ifdef BOOST_PHOENIX_NO_VARIADIC_FUNCTION_EVAL
            template <typename This, typename F, typename Context>
            struct result<This(F, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;

                typedef typename boost::result_of<fn()>::type type;
            };

            template <typename F, typename Context>
            typename result<function_eval(F const&, Context const&)>::type
            operator()(F const & f, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)();
            }

            template <typename F, typename Context>
            typename result<function_eval(F &, Context const&)>::type
            operator()(F & f, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)();
            }

        #include <boost/phoenix/core/detail/cpp03/function_eval.hpp>
#else
            template <typename, typename, typename...> struct result_impl;

            template <typename F, typename... A, typename Head, typename... Tail>
            struct result_impl<F, void(A...), Head, Tail...>
                : result_impl<F, void(A..., Head), Tail...>
            {
            };

            template <typename F, typename... A, typename Context>
            struct result_impl<F, void(A...), Context>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;

                template <typename T>
                struct result_of_evaluator
                {
                    typedef typename boost::add_reference<
                        typename boost::add_const<
                            typename boost::result_of<
                                boost::phoenix::evaluator(T, Context)
                            >::type
                        >::type
                    >::type type;
                };

                typedef typename
                    boost::result_of<
                        fn(typename result_of_evaluator<A>::type...)
                    >::type
                    type;

                static type call(F f, A... a, Context ctx)
                {
                    return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a, ctx))...);
                }
            };

            template <typename This, typename F, typename... A>
            struct result<This(F, A...)>
                : result_impl<F, void(), A...>
            {
            };

            template <typename F, typename... A>
            typename result<
                function_eval(
                    F const &
                  , typename mpl::if_<is_reference<A>, A, A const &>::type...
                )
            >::type
            // 'A &... a, Context const &ctx' doesn't work as intended: type deduction always fail.
            operator()(F && f, A &&... a) const
            {
                return
                    result<
                        function_eval(
                            typename mpl::if_<is_reference<F>, F, F const &>::type
                          , typename mpl::if_<is_reference<A>, A, A const &>::type...
                        )
                    >::call(f, a...);
            }
#endif
        };

    }

    template <typename Dummy>
    struct default_actions::when<detail::rule::function_eval, Dummy>
        : phoenix::call<detail::function_eval>
    {};
}}

#endif

/* function_eval.hpp
WJqOzvIlsJDb1Tg6DTbrmDdurs67iBuJbCSH/bWMz34FiW1lpZDvfV4XsecRbACYXWoVquuzuMrhFF9puUPSfBQw+cVIuMMY8VO1bHScwgIh4EQh2JBTkMs8hJLuWkG2RP/fY6ccMF4gz8r3E8h2vo2wczdVUGHRgBgVfVk1/FyNsyZPwW+kHNBVEM0EqlXB3KqFOLJocuGycG0i5VcEBsqLK0ad5vV5taFbEzMIixx2FWwTgFOD2nCo3pUKEJwOmHsrP+DYAL94GAkWadEYYgc7cIJbl9Dpj6mpUjIMggUlIKdn5CvwHThQbVq0HPY8CEq4XL3b66mwTgk6khFoo6D+Ns76tR3VgDaRJVIzKAw55vQnyPv9PgACKTSTQYBhB4PJRyNUTxw/kObwK0YFOgRUaegDMJD8mkC9oEuvTwXLndOhxXiNabRNsO1H7LwYZaWnysyBo96zLFlN+aP/QmSzX9d/YGQmsTYADPprMVEa8KyZBPUB7p1Jjvw0+4+do8Etn8SsVVipgi9SZ+BJQ8JqMgseCsjm3fH2Aj/gmz4lvtWHCuoMvsfZDQ==
*/