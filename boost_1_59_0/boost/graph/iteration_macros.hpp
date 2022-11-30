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
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
*/