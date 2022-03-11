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