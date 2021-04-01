/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_NEW_HPP
#define BOOST_PHOENIX_OBJECT_NEW_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/new_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(new_)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct new_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
        {
            typedef typename detail::result_of::target<A0> target_type;
            typedef typename target_type::type * type;
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type *
        operator()(Target, Context const &) const
        {
            return new typename detail::result_of::target<Target>::type;
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/new_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::new_, Dummy>
        : call<new_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::new_<detail::target<T> >::type const
    new_()
    {
        return
            expression::
                new_<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/new.hpp>
#else
    // TODO:
#endif
}}

#endif


/* new.hpp
Dlw9NMsFve640Zxo8CjRJU5/5jRPD20G08FaMit4IyXQU2HgkbFkej1hJBbNY3pMRX0TdNRM8gpz4PyUHzx/lL3i0+GzNEbN8tdvdSl7IKT0gvAXp5EFePKBC5vHbyG6+/e1dmiIO/Lk273nI3LhEbOI4yQ2kokde4C1OE0Dbfhqf1AqjtIa/7qoJONeRl+sh1qdLIER8CBQ22nyxd8Fpi6ZkOHtSkODLmJQfvnzZtrf+BNAzm2iQ3JZ/Bdi5d0Eb2Tb13VVbQbzU1SLSOaKF8p8NjxmhKNZfbczlvHTWcOPoE1TKiJCrbjnaPlBMPj8fhpJvMRL+FoJzMtWD72w5Q73lNa6kxPKG7XpoBUeD0R9mp6SNbxVApFIv3NTvg3Aael+Tcltebu6mGA1EC5FPf9YZK3N1bVGxvi4qSwE+EwX+9mOHP3g83nS/mKiQNOajjX2Tk3zkTc5ITEV1iq8aaxpWrtBdu0BGw1ZDBNutVBnq3FcDtWebqLgomzz1AicuhHhzgF4l2I8SwmFEu0Sq4bcJ1mP2a8mtaST2a5TebU72nGgXCwGH5HS0A==
*/