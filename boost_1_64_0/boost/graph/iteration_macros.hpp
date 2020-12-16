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
UfHVpdO1fplh8KM4v3aKs7akrmKqkyqJ5vsIqt+y/JoaageuW8er0J+QW6QcqsY47CHHYRzGYbXb3+JqdAcLfYGSpkBFW6s74Gkscjd7vO6gGIMnkxDjL45ZEv3QZ5H31QR5X01iliR+N7JFMdYlUYSuGP1+xIGyrohz+W5SvqDD+3cw5Gq8CLdtPvIn8Wmlrphu5h3gEyeSPrvU1xX2rWRft50EzkdTsrSd0oGsP0rI2piQdUjZtA5koa+dbA8pmy5lGzAPd+HtTHZnu0MoccDjnc3rjeOpwGME7sbqwedlAu+eyJc+zQG3W2aQ+GnAuxOuZeDrh0i6j/REmkYZbObI7DHTR1DtyFGjLYM6TEHdVZy8/kur8puasPgJVgaqXd7ZbtLVaSr0De9QH7fuDLjnqtLoceTJ6zyPx9usVnIKELlEH8xI1PtgH17/ERZqi75h7dYvEUG2W0i2W3/ZbmdI2awOy+G/qDE4SiuDjOj2BxjsDzTYHxRmf3AiQpj9IdL+UCHbST20eWRv0MqgAGM5sgzlGGYoR3ZYOXISEcLKMVyWY4SUnST7r0hvcXtnh+ZofZfWbSy0wO9mFM+I4n25yRVyiXgSoz7c4podZGNlHx1p6KPdmSvozQnzSEG6T+M77xPu+SG3N4hRoGU/AZVzgp/p9TDaUCdjwupkbCJCWJ2cJetknJQd21F5hC++hgsxKpUvOmTcd4w/tZ5T1gnXM/GkfYXvEyoqa0sLizU1OqLXS8FJdZBh3sCaCgUYy1EkdYyXfSWf2rjRH2wLeLS+UkhYG7Y9Xl/I0+jW8GLCfaE57gDGXBS/a0VNojlxXJvX62p1N2WGXLPHc+O17RBY7yvtTSAd/rlttJ0SeieTjibG+w6cspYY+l0iq6osKy2cNa0Oa9SKSZWacyegfA6TNmx0z2rKkeWGbYoPV2NBxEfweJ70YwqVoWWOc1JdRWEtX181tbW2LiBfTkBhi4/diYaxW2bop+Vh/bQiESGsn1bKflolZeMga2Fh9zPg1VKuRsidbM5Ffau214B2bV8XZmt6YntbM6StmSe9x6ubxyRXq6flX93/J7Foh43XH+LLR4t65FikxJZV6Vi0xPYO1bFYiR02YPESe7BIx3oBKwE2ielYHrCFiF9vwEql3AEDNhXYrxDvYcDmS7kKA7ZYYj8xYEsl9rUBu5wwDujYDcD+xGvVILcZmB0ylQa554Gdh3iRTcfelXKfGvL+BdjDwD4wYN9Ku68ZMJtdYlYdSwb2DvKmGeT6S7kVhrJkAcu2tq+XKVKuzYAtsQvfWgzYXXZRp0kGbI3Mu9tQlgftwt/3Ddh6u/DNbcj7ql20+XNVhjqQdk83yH0E7FLo6mPw45i0+7BB7huJvWfAjsuybDRgcUnCxjgDdobEhhuwgcDWwO5uA5YN7A1gfkNZxicJu3GG9m2Q+i4w5L0QWBfI7DBgAWATgQ0wYD+Veacb+ymwK23t2+1yafc2A7YS2DNhcvdJOb8B2ySxJEOZn5fYV4Z225l04jh6U8plG7DDEttmwI5J7BuDPnuywD40yCUni74xxoClJIu6/40By0gW9VJlwPpKbLaxjYDFYhLLNWA5yaLuXzJg46XdLw2YD1gd8r5vaN9LZJljDdjPk8U8tNmAXQFsNfKmG/Td2YEf6zooy/pk0b4ZBuxpaeMpA/ax9Le/ATvQQd7vkk/su7Ep6GthckNShL+fSD+qWaSDgYrG1vv8WNz52gKNbnEZbMlsaPO0NGXmZOVkZTdnzgsOz84ZpdLm5+VmBue4Alg3BNwtblfQLSXYJF1nk3tevcw3vbC+1udrCdaX1+AyJzcrJztr+Eie0uDx1pf4gqE=
*/