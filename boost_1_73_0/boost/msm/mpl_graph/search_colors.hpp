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
eBJ3YokdAOu5osP8htzShQkiCXa7nUanpwiW3aWYHxF1LP2Uw9whwNq63ruXsINjhLtsegUGe5Jgsj2t+667BZMF+r4wHzckDDWLtER8ouyRMHY7Vb8JDidIqkR0NvcSxmJ+2+XMaDju2WHPf79XgBXZv4a7pXL/HNbgZJJaTHs/HzvGNngwGggabq+xiT2aGunmd1wGBasuNxcf0uHvOeLl77mPUD/nsW/MTdmWoY4zV/wP
*/