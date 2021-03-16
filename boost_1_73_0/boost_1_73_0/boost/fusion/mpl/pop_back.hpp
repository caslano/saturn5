/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_10022005_1801)
#define FUSION_POP_BACK_10022005_1801

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/algorithm/transformation/pop_back.hpp>
#include <boost/fusion/sequence/convert.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct pop_back_impl;

    template <>
    struct pop_back_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef typename
                fusion::result_of::pop_back<Sequence>::type
            result;

            typedef typename
                fusion::result_of::convert<
                    typename fusion::detail::tag_of<Sequence>::type, result>::type
            type;
        };
    };
}}

#endif


/* pop_back.hpp
vzXjbAyRKlPUjOuMJomPspgZbWaFZjTbipfRh35rRpdJ+QvjZPR520esjK5xhmZ0b1yN/vG3ZrRXgxnNbSCjw8IyemdQRi+irCSSK4EymZCmN8RieSMdP1Ir8VNK/dFWDZMfnPVGWSFrY0Zj8xYudp7cspQG7OxE24GK2yb+gA7egWqGQwW4vbrDYfeiSP5BiYmqQG+Sd5K8mmSA5CCOg2QeybkkuTmqIDlOxxe4iWSlQ//cyOHnkawmyT/d3EM=
*/