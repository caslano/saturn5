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
r1tng0/2pMs8uCQavTDYRuTeElywnC1iMa9imbqwNYWxA49iZpyXORjV8hMjYAHuBwuw1RmZyB4hPzgiyiCe6zJveJ7U73QDeIEKEBaMAvjWc/jY7gBC45hA1MVUctzAPVrhTxL6bJJXqnbjVxCobvyEWpG9wdU5RJ7oaRonOqrFAsnKIL8zFmyp9udQAoMrtpaizWV+KqCVobjeZQtaGVPIto4UZaeGfXW6t/CCla06kydaKgKIYS1f09yg3r+WsZuNI5HNFw4krHfChpUOdHuApXGGmLfcLoUJ5FTrHn1YYd1bGAxxAjgke/4Nti15ySmFvfPSHDd4hP8Towp/C0hTLhpWGjGguCTPkWIt3hJQ96nKEgfGNoyaBSdp6CHCXDWxtWQlRSE3KlhxrS3Q6N8osfW2UiWxNYy0QyznSu3Gzj1jhINtW61ytrOmO9RoMAOt4LljKmTXosaiywFsw2ILLboMRagKAy3SD2B4ncXW7XTpVBqwKWl0qGMxdoblcY+hUbknsbTxmFwT9ElLqTM9fys5+mZyxaiurCeywlhGKaYSyCsM0vBKJG1Kx5QHAC0zEI7JdIne13Y4J82acBdJA1KOahXe3CC3SLxEiShaKmo5SDUm7qnrnLgP5m5WCUkbFRyf0cqginn6Ye6ADU441aojxZBAWgZpYlbZYqzFOxnlbwLKtxZeqGNI/tZpMWY4W/SjNXoWbBfR
*/