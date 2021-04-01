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
RoyMJt/hBcKM6rnHdGRSZSPDSBYCZ9gc4s7Gro0AgdpW1BUIEO4RPluRHvB/B1u+wDbkvtygiDnnvOF+pKbVAQm19gOzi5uXbBn3ctChhQqS3ZCrlqz6/7texpK8+st8K2GxFu4mSkoDPc1ZcDLAgDL08mS8havbxplBs5EbwiIHsMH7KtNPlohgfdkDTK0e4tzTksj7HrYaRPghWbied4SWN3pmREnYyIMIRH9FnLUUnmEMd7M2BIHMkdK86vK/b3elqL8v38z6+9ysFmXcBmWp+DhFtccX/Pg4jQIZb4tg0iKTYzauIlyVVYmD0pMpFASH2xqYpd1Z7mlTj6ojxb6xmmqo6H7sbXh3kqW8lHZN0rQGCYNJ6hEUYhse7a5U1SgtaIiZHqllE/7JKHjnoO28YJXynd8pl7SvBZn6jVYs5AzpAr09KQln3tjCjU2leRFCKp0WbRFqZCuZVhjZNgZFgMkxTSxCSS7DYIxjGdRBAbPKmSKoEDzArBg5Gt5nl9LtagLy9Mvkvu7+J8KF0Fe8joXyWtSpaziFc+XYIMu9Iyprvg48PuRy1Q==
*/