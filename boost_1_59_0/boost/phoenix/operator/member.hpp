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
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
*/