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
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
*/