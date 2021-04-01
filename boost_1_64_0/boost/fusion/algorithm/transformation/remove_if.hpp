/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_IF_07162005_0818)
#define FUSION_REMOVE_IF_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct remove_if
        {
            typedef filter_view<Sequence, mpl::not_<Pred> > type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove_if<Sequence const, Pred>::type
    remove_if(Sequence const& seq)
    {
        typedef typename result_of::remove_if<Sequence const, Pred>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove_if.hpp
RHfqIIX4eyAvTzbuPfLqxTUNJaOqOFFgdRoetOOItoX+EryKZA9pxw+T63wprWiucXiK5BVH+uArtOni09hr4cqw1gKrwAKN+ebe04dDmCepO5ZNmKToMq1fQFQEiazFHbUmDVBG+8zKiK1YUm4xt3PnkwHb5daWKl/kd+DXlE1hLcp6T9/x3h3FKh0lGDI/Y9hRgmUK/f/deZ/VAbz7TV3EH3NwxnMLeOC6CRuutuwsLNQ0qV46nM8nJlkRL/9cXVdaPnL5MHK/6g6Bf2yw/351KyVpj9pO4U1iw0NUiPShLy1JFNTPMRkaOXpdnJxukpcndfq0gsG5DGNd2p3egxSrOEObJFvMLQrN+2ikXTztPC7RRYKiC4n7GHHQE38L8gX7TCglUMZfasU4nHo0A/Ry0KNmefJQRWWFrw0eTszLG59ORYFfN2ZM96WyCXDjBpZ3CT/PcFP4dxmwKwH5sCXhiU2tH4nVuzeNcNt3uE1lgsNrkB6hGhk7NGkcTCvvMC3gBixrPVY8zdBaild5MXhcp+TY1C9NGRbvXEJ7+4FvtrUybUa4UEarFQ==
*/