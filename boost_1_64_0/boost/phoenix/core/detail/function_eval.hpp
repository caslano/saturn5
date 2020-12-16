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
3XOt/L0F36t4CB7NbQs670vtrH+mm/k7Bt8NT5G8f1fkyczfcfhDit93gXV8+jf8AcWPwaOfqt04l1R84Uyp/1ZgGyl/6vlnPtwnuXr+ORpeItw6/0w28zcOfpnk6vnn6xXi+CA8q5vU2pUx5j8x3EEd5Y/hhTG8KIaXxnB/DK+L4ZtieH0Mb4jhjTG8KYY3x/AW6vjycrfDafvDafvDafvDafvDafvDafvDafvDafvDafvDafvDafvDafvDafvDaftzxwkIdzuctj+ctj+ctj+ctj88ix2/4ePY/BM+W3J1/vgcfAZZ//k9fAJZ/3Et5fkrgt9N0r8UfjtJ3w2/QXL1+oIXvlbxYcXWaO+DX634dXCxPu3j68MueCZrH3hP1j4x4q+D24nXw3sRb4RXkPXdZ+Busr67B75IcvX4+gK8mKzvFlbh+C65On+eAve1k36qmf50eAVJ/0J4KUm/CX5hO/OzDDP9P8Enw5Mk35Vuzd/fhk8SLq6Pivn7O/CJwsX1UTF/fxc+XnL1+qi/BvuLtD6h5q8Wni3cqp/O5qfl8Czh1vlFipnaCnim4i3wM8z8rYGnSq6eXzT7lfVVdX0ePpesLxQtw/7J1m/h15HwS+HVZH3RCBhGX7Z/wsX4IHmm6WPh322n/6VHr5/Ar22n/6WZn6bCA+z6BrA3uz4UxD6eaM4721lfzIaXwCdJ/tQEa/2jD/wyxbdda6X2GvynCW39X/Bo/n4Pv13x4nVW+5fi4vqv5Pmzur4Gf0rx/aOs1rgS/jPFp19q5e8q+N2KH7vC+vQgfIPR1sdea+Vv0yrEQcaXW+C1ZHz7CXweuX51O3wuaV/XlTifIesDY+HzJVfTnwgvklxN/xz4bMnV9Bvg66T9Vz0/fhh+jeTq9cHH4VdKru5f9atx/bBz689zpPgHmts/CU+Fz5L8d+sQ2oxtFzxFcTt2uDPM+PfADcXL4NHy2XBwbkxp68/CxfF5A8ontY+6fj0CvoKtT8Gnk/nHH+CFJLwLg9c0sj6wCf4dsn5xK3yl5Or8pgF+meTq/OYR+CWSq/dPuK7H/tfO+Jhofh4Dv4tdP7uBr6/Z4SPZ+hO8G5v/wM8kXg9PJ94AH8/uL4Kfzcq3kc+vHDG8ED6X3J8wBT6H3J8wHT5LdvX6HLwfu/4A78qOLzeijVn+Y3gdnMVfD0/oJMYH4VNM3wPvieNL7hmWb1uDNSYztV/Deyj+Abyfmdqb8C9tbX3yd5AXs7b2w/+h+L1wsb50i2F8g5RvOnwYuz4Cb2ln/OtvbvET+EvwPMlvXWu1713w5xT/Azxam7m3Gsb5ig+9xuoNfeHnKX4dXKzv3Y3xP0GaPyjHn2PwWniK5FjfE+XrsgXzf+FifU/kbyx8guIHFln5OwfuUvy8cml8vgdlZOd/8KREMX4JH266F/4O4t8s+eA6vDdjWwZ/XXE3PDr/XQV/SfFfwqP53wNfq3jftVL+f2EYo6Tr1+r67gD4SMnV9d2B8OGSq+u7i+DPGZIr67te+FOSq+u79fdhe3b+B+9Hxsdn4Lmk/7fAJ5PrN/+CDyDXl76E9yHjW+H9uL7Erg/D89j+Cb9UcnX8XQu/RLhoH7F/rodPllxtnx+1k753nlWaFvgwdv6x3TBuI/dX5MNvlVztP6Phm4WL+aHIXwv8DbV9pOunn8BfF27F39WM7XP4q8Kt88dUM/5j8L2Kt8CTo58ewD5Erk8ZD6IM5PqhDe4SLvInSpsKHyq5Wv6ucAdbf4CPIelPgeeT9aWZ8DPJ+lYdPIsdH+E5xBtjeDO8L5mfvgfvya4PP8TD94Cz8IVwtn5XCu9H4vfAc0j8m+CpbP4H707Gn0bqqD8=
*/