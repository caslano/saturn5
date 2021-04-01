//=======================================================================
// Copyright 2001 Indiana University
// Author: Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_ITERATION_MACROS_HPP
#define BOOST_GRAPH_ITERATION_MACROS_HPP

#include <utility>

#define BGL_CAT(x, y) x##y
#define BGL_RANGE(linenum) BGL_CAT(bgl_range_, linenum)
#define BGL_FIRST(linenum) (BGL_RANGE(linenum).first)
#define BGL_LAST(linenum) (BGL_RANGE(linenum).second)

/*
  BGL_FORALL_VERTICES_T(v, g, graph_t)  // This is on line 9
  expands to the following, but all on the same line

  for (typename boost::graph_traits<graph_t>::vertex_iterator
           bgl_first_9 = vertices(g).first, bgl_last_9 = vertices(g).second;
       bgl_first_9 != bgl_last_9; bgl_first_9 = bgl_last_9)
    for (typename boost::graph_traits<graph_t>::vertex_descriptor v;
         bgl_first_9 != bgl_last_9 ? (v = *bgl_first_9, true) : false;
         ++bgl_first_9)

  The purpose of having two for-loops is just to provide a place to
  declare both the iterator and value variables. There is really only
  one loop. The stopping condition gets executed two more times than it
  usually would be, oh well. The reason for the bgl_first_9 = bgl_last_9
  in the outer for-loop is in case the user puts a break statement
  in the inner for-loop.

  The other macros work in a similar fashion.

  Use the _T versions when the graph type is a template parameter or
  dependent on a template parameter. Otherwise use the non _T versions.

  -----------------------
  6/9/09 THK

  The above contains two calls to the vertices function. I modified these
  macros to expand to

    for (std::pair<typename boost::graph_traits<graph_t>::vertex_iterator,
                   typename boost::graph_traits<graph_t>::vertex_iterator>
  bgl_range_9 = vertices(g); bgl_range_9.first != bgl_range_9.second;
       bgl_range_9.first = bgl_range_9.second)
    for (typename boost::graph_traits<graph_t>::vertex_descriptor v;
         bgl_range_9.first != bgl_range_9.second ? (v = *bgl_range_9.first,
  true) : false;
         ++bgl_range_9.first)

 */

#define BGL_FORALL_VERTICES_T(VNAME, GNAME, GraphType)                    \
    for (std::pair<                                                       \
             typename boost::graph_traits< GraphType >::vertex_iterator,  \
             typename boost::graph_traits< GraphType >::vertex_iterator > \
             BGL_RANGE(__LINE__)                                          \
         = vertices(GNAME);                                               \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                       \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                        \
        for (typename boost::graph_traits< GraphType >::vertex_descriptor \
                 VNAME;                                                   \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                    \
                 ? (VNAME = *BGL_FIRST(__LINE__), true)                   \
                 : false;                                                 \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_VERTICES(VNAME, GNAME, GraphType)                    \
    for (std::pair< boost::graph_traits< GraphType >::vertex_iterator,  \
             boost::graph_traits< GraphType >::vertex_iterator >        \
             BGL_RANGE(__LINE__)                                        \
         = vertices(GNAME);                                             \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                     \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                      \
        for (boost::graph_traits< GraphType >::vertex_descriptor VNAME; \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                  \
                 ? (VNAME = *BGL_FIRST(__LINE__), true)                 \
                 : false;                                               \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_EDGES_T(ENAME, GNAME, GraphType)                            \
    for (std::pair< typename boost::graph_traits< GraphType >::edge_iterator,  \
             typename boost::graph_traits< GraphType >::edge_iterator >        \
             BGL_RANGE(__LINE__)                                               \
         = edges(GNAME);                                                       \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                            \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                             \
        for (typename boost::graph_traits< GraphType >::edge_descriptor ENAME; \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                         \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)                        \
                 : false;                                                      \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_EDGES(ENAME, GNAME, GraphType)                     \
    for (std::pair< boost::graph_traits< GraphType >::edge_iterator,  \
             boost::graph_traits< GraphType >::edge_iterator >        \
             BGL_RANGE(__LINE__)                                      \
         = edges(GNAME);                                              \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                   \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                    \
        for (boost::graph_traits< GraphType >::edge_descriptor ENAME; \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)               \
                 : false;                                             \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_ADJ_T(UNAME, VNAME, GNAME, GraphType)                     \
    for (std::pair<                                                          \
             typename boost::graph_traits< GraphType >::adjacency_iterator,  \
             typename boost::graph_traits< GraphType >::adjacency_iterator > \
             BGL_RANGE(__LINE__)                                             \
         = adjacent_vertices(UNAME, GNAME);                                  \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                          \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                           \
        for (typename boost::graph_traits< GraphType >::vertex_descriptor    \
                 VNAME;                                                      \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                       \
                 ? (VNAME = *BGL_FIRST(__LINE__), true)                      \
                 : false;                                                    \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_ADJ(UNAME, VNAME, GNAME, GraphType)                    \
    for (std::pair< boost::graph_traits< GraphType >::adjacency_iterator, \
             boost::graph_traits< GraphType >::adjacency_iterator >       \
             BGL_RANGE(__LINE__)                                          \
         = adjacent_vertices(UNAME, GNAME);                               \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                       \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                        \
        for (boost::graph_traits< GraphType >::vertex_descriptor VNAME;   \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                    \
                 ? (VNAME = *BGL_FIRST(__LINE__), true)                   \
                 : false;                                                 \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_OUTEDGES_T(UNAME, ENAME, GNAME, GraphType)                  \
    for (std::pair<                                                            \
             typename boost::graph_traits< GraphType >::out_edge_iterator,     \
             typename boost::graph_traits< GraphType >::out_edge_iterator >    \
             BGL_RANGE(__LINE__)                                               \
         = out_edges(UNAME, GNAME);                                            \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                            \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                             \
        for (typename boost::graph_traits< GraphType >::edge_descriptor ENAME; \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                         \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)                        \
                 : false;                                                      \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_OUTEDGES(UNAME, ENAME, GNAME, GraphType)              \
    for (std::pair< boost::graph_traits< GraphType >::out_edge_iterator, \
             boost::graph_traits< GraphType >::out_edge_iterator >       \
             BGL_RANGE(__LINE__)                                         \
         = out_edges(UNAME, GNAME);                                      \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                      \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                       \
        for (boost::graph_traits< GraphType >::edge_descriptor ENAME;    \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                   \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)                  \
                 : false;                                                \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_INEDGES_T(UNAME, ENAME, GNAME, GraphType)                   \
    for (std::pair<                                                            \
             typename boost::graph_traits< GraphType >::in_edge_iterator,      \
             typename boost::graph_traits< GraphType >::in_edge_iterator >     \
             BGL_RANGE(__LINE__)                                               \
         = in_edges(UNAME, GNAME);                                             \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                            \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                             \
        for (typename boost::graph_traits< GraphType >::edge_descriptor ENAME; \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                         \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)                        \
                 : false;                                                      \
             ++BGL_FIRST(__LINE__))

#define BGL_FORALL_INEDGES(UNAME, ENAME, GNAME, GraphType)              \
    for (std::pair< boost::graph_traits< GraphType >::in_edge_iterator, \
             boost::graph_traits< GraphType >::in_edge_iterator >       \
             BGL_RANGE(__LINE__)                                        \
         = in_edges(UNAME, GNAME);                                      \
         BGL_FIRST(__LINE__) != BGL_LAST(__LINE__);                     \
         BGL_FIRST(__LINE__) = BGL_LAST(__LINE__))                      \
        for (boost::graph_traits< GraphType >::edge_descriptor ENAME;   \
             BGL_FIRST(__LINE__) != BGL_LAST(__LINE__)                  \
                 ? (ENAME = *BGL_FIRST(__LINE__), true)                 \
                 : false;                                               \
             ++BGL_FIRST(__LINE__))

#endif // BOOST_GRAPH_ITERATION_MACROS_HPP

/* iteration_macros.hpp
q7vXR/+qogazZOlpdmUvYfhwu59bcRt+eQJAPY3ZF/FrbyvoeHBBsCylCzP/zXGEzbq+qgkmxk34mg2GWm+6Bk4rAPpu1MiL4MMBwio+jlmC919wL+h2vVy3jdSIbuRgzex4qfEGH/M/Gx/WlZQAX8zJS0QFOwli2wY+HA+j/VfrjmGeOAjuYA9ZzwksNU/qMysBpPXHbWP9ywi2ZEb3QPSqhn+09xBF+o41Jd7qF+bMnoUKBH+0S1LGs125uCcVFdooNXT7zllCBwfDe+9bd5w93BhzYXECNmPCXg5NbKgOpM2Tz5lIzSYiin7I1fUxGGvZPFR04Bt2Sc7pfxD8Le9NimCWhjkR4SKBBx43yZvEDrWeyK9tPjj/YzCMoMU0Yreom+kzOLOYtBj0A4PO7pCtek8nMXGaqLUUKVjmvfv/T4lAWSGpbHqawcQVP969uk95ishubByaEpc/Ripl9XjQbUQW5F9Z5/mfsXuLR13MqVVVlPYoJHj15pFsge+KXDfsGfbgkBNfq5RozBDa6Ys34MsTqiJpGY4dtTK4EXCpr43IrB5kQ5XHYQ==
*/