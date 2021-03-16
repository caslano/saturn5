/*==============================================================================
    Copyright (c) 2013 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED
#define BOOST_FUSION_ALGORITHM_FLATTEN_HPP_INCLUDED


#include <boost/fusion/view/flatten_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>


namespace boost { namespace fusion { namespace result_of
{
    template<typename Sequence>
    struct flatten
    {
        typedef flatten_view<Sequence> type;
    };
}}}

namespace boost { namespace fusion
{
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence>::type
    flatten(Sequence& view)
    {
        return flatten_view<Sequence>(view);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::flatten<Sequence const>::type
    flatten(Sequence const& view)
    {
        return flatten_view<Sequence const>(view);
    }
}}


#endif


/* flatten.hpp
0w72TAUjPyj+bcMzhTzTwDQ1yrO45dN97JkORl4nMa9fTCNPMhicNaf/G7xujsN+cAaYf4VVr2TyzARTROjlyTkp4CJ7ZoHJp7TPTPLMBiPPZOWrX98OmMaeOWDk1xCY+53Z5PlOqP1+pu7d39nzPZhLwtqffkeeuWBWCb3Mo5dPqs+eeWDkVyGYnrnk+QHMGGMOpmSdN48988HIb0Yzx/0P5FkAxt/YPvrbjA77r4XC3l8LyLMIjLmujhk2oz0=
*/