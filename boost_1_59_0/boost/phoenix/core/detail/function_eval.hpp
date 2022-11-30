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
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
*/