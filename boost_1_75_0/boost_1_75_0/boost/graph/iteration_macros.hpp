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
RsoETzkJTQTuLFUlNX0Zr0+GKw+25yb2LFc4rAwsaH5ZVpT00V8TKQIVY5j/ibV5AIlgEvtGm4IQK0B6vHkeYkpabCLVccM3Y2/WJL5eXBVazbazd3domwYAWPTqCTIUfQFNKa2K9bCJeW0eCwOS/uUDm6FvVMC0ZePT+gFtR2KQp/bgnu1lWiflgYDRISD51mNeaX9pPM1IYvPVzMZXge7riyJgYQjC0JfaUXJTyRetQfKRtmjvHSeIJiQBpCxRSAtJ4HaQkMJzVCH6DYq+mz1yi3WlHB7dLVmruvuuLp4/r0QKv/L15eBbCuwp7jtWycct8q3sOyj6uZvpARAvyotKsK4Qvq78xM9VwBnqnDhzkvj1vjNeX0byYEFzZngUQSVvYynIJYieHvmymKwFq60pLSPK+0dUJVH7LGcqYiz7K/8UEXzYRNKZ5M41cAb7MEreXEXgktRQW5/z1xC9KtNhdJhJaKY/+QJXW5St5KfIl+npsW3+YaJdFaHnKa4jFYTE69QRAZV/EaQe/SQu3ZiE+/LriVCBxgYSifkQWopL3lr5NeEOMZosfjZv6fvAO5vChHirwfplVYWft8mklEKMMBI3kTm/vOIYzoRYFhfbm9+WqyY1biPvBNwhpAqQaAhlJsTGSw1WUUjpeVqxbC0Rp0mK1ZBb6wo9v4nGsvEL/hh+/eXxn/SyAEiMg1/9ImM9emu0pkndd4Ah
*/