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
DigfNn7NGJkJcXITSNnRTeB5CTzCYXgxNrnzn/rG0DcuOn7onbWaBfFShfk4Qhn7IGT3K6usulcx9IXjrvrXimtygH0GNvrerptrFlkzr42oc2iFB2/6Ek7VSAqeKNKqpUbNE3Z8ZlFEMWjHXoNH+ZMyUWtFLFvLV/rTZ4EeRC46Cq87C4VreT1z+SyfyicDiUn+/VLHteILPE3vpzc8X4vunWmhbN+Z9Sn3Gas8d35/9xmeBSyOgH3JntuDWR5xrMSyVfVbbxYj0I7/ID/u74JmnJZkUeOYEaMIBflAXscN5sk504SC9im/BVTykfp49dJtpsbTEXI7MnGU3C49YQQKkXTldOVW4bcwiZ69VGXk3HwecVslZIZReElrZpOke1XrosWYN7Vqbdwx71Q0VQ48z9IN69e9mgsGrYFWztyawUDylTW/C6z4NfLK3S0SfV7E2uVgvIPtcvjJv5DqZOmslqzO9stNRZQMHQJpN7PVaDejvFiE7PQ6C2gpWa3r/piacgG/BzUdxLwwrU3tNNoT1s263aWJo66TeUBycnquN50VAGvagK3VwuzLpV7xoJKiaPu22elgJyHFZR+PsSK9PEdNc4GqYSxNbAOa/WhkGYzA9snOp040RiBJJ441ULgaM5cfQd8WT4nMOaARn3GWH7yW8NAeqjdWd7JRTp405rjrLuK54LQRyteJnerk0IjDlYj9eQ9JVsI7
*/