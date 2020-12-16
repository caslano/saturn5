// Copyright 2008-2010 Gordon Woodhull
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED
#define BOOST_MSM_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED

namespace boost {
namespace msm {
namespace mpl_graph {

namespace search_colors {
    struct White {};
    struct Gray {};
    struct Black {};
}

struct create_search_color_map : mpl::map<> {};

struct search_color_map_ops {
    template<typename Node, typename Color, typename State>
    struct set_color :
        mpl::insert<State, mpl::pair<Node, Color> >
    {};
    template<typename Node, typename State>
    struct get_color :
        mpl::if_<mpl::has_key<State, Node>,
                 mpl::at<State, Node>,
                 search_colors::White>
    {};
};


} // namespace mpl_graph
} // namespace msm
} // namespace boost


#endif // BOOST_MSM_MPL_GRAPH_SEARCH_COLORS_HPP_INCLUDED

/* search_colors.hpp
C6yU2ZkrRyoYu5z2WkkrScssSRIHlHnHfgDjn02P+jzyE/7/uRMbrrn34O/tsu8hqFFL/0HGlo0PYXdrxpWiCdzyiIKDjM4KP4z9pOOQH67Xu0cpDnnJe4+CUeTCvGNmDCR3knXF2yhOrWt6u4Gu5GB5U8FwV02kvzRG6Wqbr+xQ6VgJYj6/EzCS/ybuGbIcCoZnaEYe398l6HV59W3i6G4ZAzzEcBO2wRpmsCnLcWkPpavthQGLdC6jFgv4xRIjKlfbjPFR9mk4bDf6MJaYyjuTuxUj7dJ4SVtlv/PvJvTtb0Eab4OgnX4ro4GGvguZV0vfSLHH3CtpZQFZbKQP9iNdFhfpY08yevO+ucnoj7Bvgn5cxWn7z2WOac4FLOTafwCw4PPNI+fUayPSX6N03jlSXtIJTucU4aos9oe7e6k+MEudxHHCKgeaQ/Osof7z4/Kd2227SdGyM2tRoIUO4j7l7zqhDTZoScV/luZYw9ydhH9p7hKHudWX0Gdq7Mv5qCwL6Bq9OPMwCxnRI58+Lu8LQQyajcBJrDIyj2rjd/fj1I4C1HB+AIqFvIz4DqJjJi0iO1Qi62LBeiL24zbYMZ3/Yh9KKLpYGXvKDzOwabB9MCdhLUUbTtHWKWK75KfQ77kf8U9l07YelrEzUZAESe6VufAAqehrj54m9kihlzqphynjdN6nSRt9P3DB/Deq+pFjUW8YnFbj44F+GoxmtI6EWtQ3iM/TNiQemEt4HutLxGI+uiWlHreIQVUNo8btfaE3WFiuKiqzIKNtbP2tL5GyLYsFWAvDPLU6VVmlpIX2o6eVOP2R04YvGFYKq7PdtY1OTyjIpbyDcrnCahdOVuTtHPSvK1qhuq5rioxxZoPzt5dVxtDeymJvDd5CLuIERNtYRcY0zJwkj9rMGForBXi0O1X6s50VIdgaw0xYGCzQCrX+vK/ImrTiOA6hgR0oq5fEfhn/BNV35hG4qAVJ1UT7C7A6YiFhV/4J6guYZ0GcezlrHpZQ5/bRT1D5vCRrw2QKqL3wrJYj0JXLpRYcdPM8bYesLlZSFJDsM+fkMqdyh+XPtbMqbaFUwMIxL+NPhkHLcVyY44tnE12eZdpfjp0BczA65F0MGnFmT6TYrNP+Ag8UN2GpTbq8DJaQc3HSevy4ZReOB+aA3eZ6vk/rSUI44fsODIGuXk9Wx0iSywA2BnNAJ3H/B99asAWegDNNWp7t++W1fL50ha3SCHLM3wEDlQMGAwIRFJ6fhmFPZv4j1eVbmBFLe/XVEtPsfzE5otPxvVvoDAED77h6Pfh2cE+OffuM204jOwrg3rSg+HoOfZzO3yIGJw3HtbSciMrbxIRc7pkosW14NLCtesHNs/rOBzj5WwHvIs/i7HG/1ftq3XTZLk061EHL8dvfqeO0fAVzw0YcyVdw04wh+QqOjgCm1KlpOMT8osTAYVbH4PcPtlSYL+kYEZOnxDSPoedHNbpmM3G7xHzJKC++Rcr3++NxEhYJ8yK52FPyor9EcAnoIfws81j8XHoeKE6QM48DOoYkguv2WeaKUkER+zkZO51Hfg4vidYGeAF3tPejDuEbZkmaggKWgdeBs+73sybjU8vLHFiqsgwkCTv5OkpD6rA+TPQQgPczuxJoBZap3kDZ8y+dUPbTIIvCwolYiYV+2OnzitT30++ScjAPYyiY2C4IJ96MnaVVUDxq8V+vymVnWBpgJ4BmLfRhcHBwt/5mr8rY47nXTosEXijXOz26Pr8m43IrTNycHfaIOLwNZyC2G+aZGh2an+9BZCJ2ieqvreB6c4P2feqBG0I7lN6H6+48QW2675yg+q4U9qPUzYLHXUfqdk2cJDFyHMePWoU=
*/