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