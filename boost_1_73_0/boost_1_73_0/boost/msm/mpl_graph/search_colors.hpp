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
PmPGrp2NaGNRDz2m+mvkOnZmLtyifYy6hJ8Zy9jeSC1JxUQj+Il21HNt2oSf9KgxIchEVjEdY08NbykIKzusZvNwbKMG9S9E14E6cUcSRVA+YUEo13XSNhQWDeQan4K00hi5l97mUKwh/2gntMYMPE3JIQkoOV+siexmWy4S83ZzV/NfF6TrfTKFJ+mjqQf07WGA5BfkIaKHqHFcI2gZYI9oIQ/axZyJlxFLI3rvolPOgHUWj6a1eJkPGPKKjU6JEU4XWmVs7UIs4YusjN3TroqrR9JS0l684YuH33e7m83fjF0phT19Pufnny84W/56wtWPdMOPayPDb3KT+XcPfP5v/wNQSwMECgAAAAgALWdKUhY6YQaTBAAAxQgAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NzBVVAUAAbZIJGCFVttOG0kQfR+JfyhNhCJFDLbBWdYjg5RNvAlZEhCYPOyL1czU2L30dE/6YvBG+fc9PeML2WyyAmG6LqerTp0uGHt2vhCOz5Kx1JXBxz2vHowt3Vnybjq9an/Q28k0Gfd2nnGvC06eJc/ohu2SbeZkycnYcqNWCCiFF6RNseDi/jRdsUs7vN7gcEBH/T5d/pG8EZ5zmgY+oP6IPpolHIM+DYb5
*/