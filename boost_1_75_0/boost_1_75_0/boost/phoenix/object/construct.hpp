/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP
#define BOOST_PHOENIX_OBJECT_CONSTRUCT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/object/detail/target.hpp>
#include <boost/phoenix/support/iterate.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifdef BOOST_PHOENIX_NO_VARIADIC_EXPRESSION
#   include <boost/phoenix/object/detail/cpp03/construct_expr.hpp>
#else
BOOST_PHOENIX_DEFINE_EXPRESSION_VARARG(
    (boost)(phoenix)(construct)
  , (proto::terminal<detail::target<proto::_> >)
    (meta_grammar)
  , _
)
#endif

namespace boost { namespace phoenix
{
    struct construct_eval
    {
        template <typename Sig>
        struct result;

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
        template <typename This, typename A0, typename Context>
        struct result<This(A0, Context)>
            : detail::result_of::target<A0>
        {
        };

        template <typename Target, typename Context>
        typename detail::result_of::target<Target>::type
        operator()(Target, Context const &) const
        {
            return typename detail::result_of::target<Target>::type();
        }

        // Bring in the rest
        #include <boost/phoenix/object/detail/cpp03/construct_eval.hpp>
#else
        // TODO:
#endif
    };

    template <typename Dummy>
    struct default_actions::when<rule::construct, Dummy>
        : call<construct_eval, Dummy>
    {};

#if defined(BOOST_PHOENIX_NO_VARIADIC_OBJECT)
    template <typename T>
    inline
    typename expression::construct<detail::target<T> >::type const
    construct()
    {
        return
            expression::
                construct<detail::target<T> >::
                    make(detail::target<T>());
    }

    // Bring in the rest
    #include <boost/phoenix/object/detail/cpp03/construct.hpp>
#else
    // TODO:
#endif
}}

#endif


/* construct.hpp
JK3Ypc9Uoedmpa3s7VMo1nD9ZjexbhM3GyhLYnwlGDXB2oPC3aZdfwTcgLWZ+mOjB49fkLtzSGadJU78w7GbhrvhX8S6HYb8YdwfQNwBj81G/FFCNmBtfF/DWP0JqsZIYJ0eS2PNhs7h0iXj7gbWEDQcfHWNtZGYPmTm3liSbJwDNzNAs4BSND9aJsbJ+p668YNHqPj2jCiJP3nsZmRE5mbWkHVpJiEu3BwGzp2Z/2tY+xrW+xozZQTFzZ2OXkJiBik/b4u1CLcOQ23R0e521kaINSq64jYZg7WvrVURnTUH9A7gbhRVyAs5EnJaRYWjnFLHZI1SNWojLBHrlvp2sDZu8DMlZQIkgi7R2LnMnIUegPZ+Tph5O3Fzk9WmqbtZqz8RsUaT1Skf7mNt0Y2sQcjuKuv6Slwsbe0C6wZ/E5bEzJzFXVLyJm7mDGfelhuXaNraH481iNcmGpqon4Ia4ro6dlpPPUxNUhFrbytzwLq2NLO2LdxZ7cbdVdYAMVUY7zzrAFOG/E0hbj9jkTBr6pgjuLcNXQ9BZxq4lzh0Sc78o+DmYI3amiLWluZFaTGYNV3tMHDuPK2RwN0Z1q1CRh+kVVjZSdaBZkjmUAFAZjTupLGzfDvb2CVlcZw2Lpacdwx3t7E2ua8BxtdoSgzaew21NT3MTDFrH6tuZo09eROabdgh1i2AsliLsxVXxUnWxNSUD7OmKFMyI0VB
*/