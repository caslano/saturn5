/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_IF_07172005_0818)
#define FUSION_FILTER_IF_07172005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct filter_if
        {
            typedef filter_view<Sequence, Pred> type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }
}}

#endif


/* filter_if.hpp
O3W64/S0mYYn3r73z2BI4usknodKsdvc3GLCjaOj11s7sRKP+xoecqtQ2by85nIVzQlIvc5C3uuDRv3g9C/2yFr9q267B8f0Ub/72cfCfP2myMVpVcOP/dFYr96Zq6ESVzIMzGu74Re/M0TkzZD2n8AOut/S4/vGbjgkijsWuXM0mrT9Xsc3HN1bcPzh6gd8Mh/Y+X8RiSQqikd49Wy1eDPxvmKGHcYHZilpa1gtMo9v4RuPBCBbAdM+R1DYaw3TQQbFxgMlRytss+hB/ciNEWovj86egxCnByc2QrTDaQYdTg6O/pIblmzLoElLnW4KhlUvmQA8DcwdwS0bNAHYhqGUMip20QyAwXrGrjx5MDTSbwXt19bhc24djvPrIC0bjdcTixKg5Um+JfTPkw/+OD09qmXmqME9rFFzjB8tz2htmzo7hFbRIbKnQSSdZGk4rwWPxvfwf2h9/3FDcjMt8ImCcUzC918Kq6EoxYgWBJyUWbcMmRiQVNNpdtn/JU8762/KYCKYz3yClm/tljoktXGUW2ZQeBw/Itje1chv2x/9+QpUiLVBxWuhTh/9dQMztpYxQS1wf+Y2FiO7GvbofrEgAULmZhGvyJK+jp1TOXFM5aRkKleDbr/ZzpEe/dEpfaQkXRVE81LN6WWW
*/