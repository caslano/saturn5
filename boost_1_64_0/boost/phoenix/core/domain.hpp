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
BFZkwkRWWAmidWWIqEAW8sgSAnSMgpRnPcRe1OZ2DwvkiiNv6U14di5/mp4bZ0ti8FJuJhcGeZS8Z9XOp/WzTz2u+sYgBgVy9e/+fJqKvzhJL22mmesiEYWApjMPfK840/TuV0AqbokFepVoFdnu5wVgrbkHVZPGJH/tc0GDQKWv4hpeWPMiVqqZSii8G8cRMwCfiJKgOdHe3bKucrG1G01TwsQjzPy2MivBF1myRElxa935OPw9R/OP5MHnwUsDvJptXVvXes/RYVOclmAOJH93NRwhY+ZnDkFeZkdhIQxEymnODBl+8NybZ56SrmmMgbLUEocx+7Oks/5qgPaQH9HcvP5X606DkTkpeBPSuCCl7EL5fewVjspXsOQKxZ4zn6PJ7aYPSO8apGw39za7jV+iTh//8S7G+D8Vpybu9V6stA38iqu/R+k5bQJCFkX4JmiEmGUjf+J9rLXzJOuZsc0lVqOmpQVquvKnfrGY/82WwO4J9pkVELPUfXVi3UP8ehJCrNSJsujFFCAFsIZOQZ5SC+xXIVbVTA/clO0gPtFrO1lyy1SB3NxtKg==
*/