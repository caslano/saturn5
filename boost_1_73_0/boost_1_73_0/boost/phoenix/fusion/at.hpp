/*==============================================================================
    Copyright (c) 2005-2008 Hartmut Kaiser
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUSION_AT_HPP
#define BOOST_PHOENIX_FUSION_AT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/type_traits/remove_reference.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(at_c)
  , (proto::terminal<proto::_>)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    template <typename Dummy>
    struct default_actions::when<rule::at_c, Dummy>
        : proto::call<
            proto::functional::at(
                evaluator(proto::_child_c<1>)
              , proto::_value(proto::_child_c<0>)
            )
        >
    {};

    template <int N, typename Tuple>
    inline
    typename expression::at_c<mpl::int_<N>, Tuple>::type const
    at_c(Tuple const& tuple)
    {
        return
            expression::
                at_c<mpl::int_<N>, Tuple>::
                    make(mpl::int_<N>(), tuple);
    }
}}

#endif

/* at.hpp
XdgcPfynNRXB1OGKDFwZPlLIlHa2Z1Rh9vXMdO/k2tjxPEBN9vw/Fn5rKC2UcOsf9VBCb3Y9JHq+vRc62VVz7qaeFJjiaj3Mp8Ayr0jcVsoZ1qyqZNdxKjgkpFLzENcDLC7YQHOV0iSrTb11tsgfWZ9Xme+ANRJ9GzMdjIJydYtzT/rOUX47cpfeU9WjG5BmfgwqLJEkBh2ZTr0UbwqUu8BkM/rC11XpXqPYCxJJKcFonTR82Xnb6fbwNAn41mtf/MIJvVndgTfHxRFcfNWpE9FEn78X0543PioZTwTXtwnq7YPYZC3fKUf+VFDI2kpjX9bz/wBQSwMECgAAAAgALWdKUnf+dgdPHgAArG4AACEACQBjdXJsLW1hc3Rlci90ZXN0cy9zZXJ2ZXIvc29ja3NkLmNVVAUAAbZIJGDFPWlX20i23/kVFfdJkIMxNgGmQ5b33OCkfSYxPHB6eTTHR9hlrIksqSWZZSb57+8uVaXSZkMm088zDbiWW7du3b2W7Dz/fp8N8Vys/YzpvzF84Df1OI3Df8hJWt16PP4i+H/Q6w/4vW6QHZF1+TJuivVdvgiHuozVKK/x7/F43UB/IG74Ywd7/jHGP6EEumHPozC6j73reSqco6bovnz5o9gWu53dTkscu4EnfXGe
*/