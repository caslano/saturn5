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