/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_OPERATOR_MEMBER_HPP
#define BOOST_PHOENIX_OPERATOR_MEMBER_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/get_pointer.hpp>
#include <boost/phoenix/core/domain.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/proto/operators.hpp>
#include <boost/phoenix/support/iterate.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(mem_fun_ptr)
  , (meta_grammar)(meta_grammar)
  , _
)
#endif

#include <boost/phoenix/operator/detail/define_operator.hpp>

namespace boost { namespace phoenix
{
#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
    #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_gen.hpp>
#else
    // TODO
#endif

    BOOST_PHOENIX_BINARY_OPERATORS((mem_ptr))

    template<>
    struct phoenix_generator::case_<proto::tag::mem_ptr>
      : proto::or_<
            proto::when<
                proto::and_<
                    proto::mem_ptr<meta_grammar, proto::terminal<proto::_> >
                  , proto::if_<is_member_function_pointer<boost::remove_reference<proto::call<proto::_value(proto::_right)> > >()>
                >
              , proto::call<detail::make_mem_fun_ptr_gen(proto::_left, proto::call<proto::_value(proto::_right)>)>
            >
          , proto::otherwise<
                proto::call<proto::pod_generator<actor>(proto::_)>
            >
        >
    {};

    namespace result_of
    {
        template <
            typename Context
          , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_LIMIT)
          , typename Dummy = void
        >
        struct mem_fun_ptr_eval;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
        #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>
#else
    // TODO
#endif
    }

    struct mem_fun_ptr_eval
    {
        template<typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OPERATOR)
        #include <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval.hpp>
#else
    // TODO
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::mem_fun_ptr, Dummy>
        : call<mem_fun_ptr_eval>
    {};
}}

#include <boost/phoenix/operator/detail/undef_operator.hpp>

#endif

/* member.hpp
Fi+m9PdfAXSws4zDz0c2sCxZpr7k3q89+J17aS4DMfYy+BeaxzL/FOY7+SRfBGJ/9+BnbPpaeldhpPuFipMkFf4yjR5nIpdZLrJlmEuoube1tUedHSeLmzScznJRP26Ip/v7P4kd+PN0vylOvDiUkRjkMh7LdNoULwIq+deZ9/nzbiaPmkLmwot2S3D8hjj4+99+aIq+nMo4z0QyEflMiss4BJJlYX6DJcdeFAJ2cehR+3YUCWqfiVQScQNN3L4MwixPw/ESySiAXGKZIaU1kbBkHMZeeoPjnWdNcR3mMwFDx7/JMkco9lQ0hZdKsZDpPMyRqDCrV2EAX/KZlxOukySKkuswnsKsxkFI84dQsN1c5s/x+8FuCTUaqcKJmGG+BJKnMvcAV4TqjZMrfKRIpXg0TvLQl02oAfMeATwEU3RLw3Nxgk79yAvnzIDi6Soi0KFFEY0IjDNYAnJ/Di6CR6kgBYm/nMP0e3rS9mA+EniewtLIZQprKysITxOGgO1h0OB+2CXe8ALgnTzMsMuiPXYAFbFwIr18CayD047sQUxHC2mSX8O0KbSIEtDJIvJuSiPx/E9xch3JYCoR7nMjQmhBMu3yYoFrwCKQVzJKFrg4b1YZ3UApGL4pXsr0k4zkDdEzzFF2xDzsJM1o
*/