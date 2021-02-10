/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_DOMAIN_HPP
#define BOOST_PHOENIX_CORE_DOMAIN_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/call.hpp>
#include <boost/proto/transform/when.hpp>
#include <boost/proto/domain.hpp>

namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;
    
    struct meta_grammar;

    struct phoenix_generator
        : proto::switch_<phoenix_generator>
    {

        BOOST_PROTO_USE_BASIC_EXPR()

        template<typename Tag>
        struct case_
            : proto::otherwise<proto::call<proto::pod_generator<actor>(proto::_)> >
        {};
    };

    // proto's assignment operator takes rhs by reference
    template<>
    struct phoenix_generator::case_<proto::tag::assign>
      : proto::otherwise<proto::call<proto::compose_generators<
            proto::by_value_generator
          , proto::pod_generator<actor>
        >(proto::_)> >
    {};

    // proto's subscript operator takes rhs by reference
    template<>
    struct phoenix_generator::case_<proto::tag::subscript>
      : proto::otherwise<proto::call<proto::compose_generators<
            proto::by_value_generator
          , proto::pod_generator<actor>
        >(proto::_)> >
    {};

    struct phoenix_default_domain
        : proto::domain<
           proto::basic_default_generator
         , proto::_
         , proto::basic_default_domain
        >
    {
        template <typename T>
        struct as_child
        //: proto_base_domain::as_expr<T> // proto lambda example.
          : as_expr<T>
        {};
    };

    struct phoenix_domain
        : proto::domain<
            phoenix_generator
          , meta_grammar
          , proto::basic_default_domain
        >
    {
        template <typename T>
        struct as_child
        //: proto_base_domain::as_expr<T> // proto lambda example.
          : as_expr<T>
        {};
    };
}}

#endif

/* domain.hpp
RNqCSjEbsSk3FvFKy5XsIDUDy3RuEMKRR8IoiF4iLqIYaSILmbWF+a3bTUotUHmXqsR0k8Z6J7N57eIRFeTRClRhwSooDQvBxYWQK8pTN2IpcLMoY8FNFm6kIJGkXaXBMCEQCtM4M5VkBrO6MqGLggLVcusGo6RxTMtM5e8CsYQIkpZaIg2WAGOowgKHUErKtI/1phuGupq+tC1HstFKQUlUAh96MxjOPkAcGW5CeBjOP08Wc3joTae98fwRJjfQGz8i1pfheIDnzZFJA3stNDPIrIHnheCMesLTXUEgFZfGkvvp5Hbau5vB7/DMrO8BZFbCNYc1BUV7yVd0bMEssY6pxa00+sqItCL3vR/4EEOdedcOFPJ/rKVB0F9MR3+R2bTvwDGs0+nir+BxNy80lzbtJO+3pZKxQKztfaypVSpN7fYNLLsUWKftfdeFJLGrgm3foSsZlzvESEDLYi9KXgrL45VFpMbR58F0x5GLfe1kLX6yNj9Zi5+s1U+2188ugfOzD2XjJwuCxez6ZjGqvNSnXxWhWXgEw/QL08Qwu4uJbc1++Xlv5epbWwk5yymLy+ftlPW+kzUf1qLw+SOqSD/De7UyMpsspv1rdw4/nG8a7WK9cofkVpXFCwdhmaktrlFGg95ggBhXLomM
*/