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
1xRO6MtztcHYWADm3n6mhQTyvtF3SmzBNLFuHfkx/MHKts/x2RLnAFydrzcIB1u+ndaGuii2sKAGrSqyysF54qd+pla/W9VW+bjzkyVfMvenE/7JlPq1hDn4nOMskSDLuw+SJP58qKE4L+oIZFgUdU7O1mo9HYV/NroIhmAITF88xRreE1/FPL8tjFPAu01PFp1YlOPIN5Bnke3zjhC/erBOz/jlJ5iuiWpTNNxnaqi3mFQ/6VdxnZ16iibmVLclzR778zr9M8M7dvxr3bWSelgmuFn8JhkfviYLLR+a72+ig8IV5IjgiFJKID20bYJzwAe4aCz5RrKDOG40es3tfYQykPGa/AftO3RU7TYGhLnO8wZhxp662659yA6lf+/C+mrjs9PRmfmhw+smmasQwYtSyb2SjoUM9QhmTwwt9+tndyKRCMj/6s8gEfRmnJct62HqB+pTir3TVC23kYyhZlpS3m9fD8LZTATQEaR66fFNhEHSgXi6wjtLaJblNxeuBNRV1kag2y03zu4chZHgvVd1jlyTts/ypSrCx0yjaQb3O/6sjzG6THNQ+NlIq5jsCubw03qHshqKObwTChb3M10qVFriv6AYLZFBg6ewbGM/mn6dORvn1zJPFiO7Tw+QZ3nSVeFsTpptsy/leWozTJg6yCweT/Kn5sX5m52JWHRMBlObv98TZVvWzuu7thjIaPf9R++HSHMmTuec
*/