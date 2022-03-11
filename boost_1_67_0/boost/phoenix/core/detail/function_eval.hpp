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