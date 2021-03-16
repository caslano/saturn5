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
uemkeDdN1P8YBzlYduuE9qhHe9GjXe4ofojz/hEC7/vdwlZH6a/nOS21eD8aVt+vkw0oaoLhcJ3nG+JVG+H9Ukr60/7h9RT3D3Fcw8fZymIWUYjwcay3sdMQLmwkIxyLKhpBNPFbpWiqwrUxT6rUdVUxuXWeRwhJmQLydBEb554yarUaiX7DuoZn8ZSmbWQZAxasblzI4B2cjiKJiEisna08dzZJMNWFz4GFqEpSC1GwUrZxyveA8nIRcX+Q05c=
*/