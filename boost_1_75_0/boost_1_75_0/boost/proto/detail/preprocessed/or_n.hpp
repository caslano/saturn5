    ///////////////////////////////////////////////////////////////////////////////
    /// \file or_n.hpp
    /// Definitions of or_N
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1>
    struct or_2
      : mpl::bool_<matches_<Expr, BasicExpr, typename G1::proto_grammar>::value>
    {
        typedef G1 which;
    };
    template<typename Expr, typename BasicExpr , typename G0 , typename G1>
    struct or_2<true, Expr, BasicExpr, G0 , G1>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2>
    struct or_3
      : or_2<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2>
    struct or_3<true, Expr, BasicExpr, G0 , G1 , G2>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3>
    struct or_4
      : or_3<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3>
    struct or_4<true, Expr, BasicExpr, G0 , G1 , G2 , G3>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
    struct or_5
      : or_4<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
    struct or_5<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
    struct or_6
      : or_5<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
    struct or_6<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
    struct or_7
      : or_6<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
    struct or_7<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
    struct or_8
      : or_7<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
    struct or_8<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
    struct or_9
      : or_8<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
    struct or_9<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8>
      : mpl::true_
    {
        typedef G0 which;
    };
    template<bool B, typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
    struct or_10
      : or_9<
            matches_<Expr, BasicExpr, typename G1::proto_grammar>::value
          , Expr, BasicExpr, G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9
        >
    {};
    template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
    struct or_10<true, Expr, BasicExpr, G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9>
      : mpl::true_
    {
        typedef G0 which;
    };

/* or_n.hpp
A+V84ksLqA/4xKeexKclxKfO/AstXbVF6aKQLltKzS3290v+WfYhTgBh/s+JHy64b8cna+sPxK+l/GthU87nG/7FYoDBJaEFROHFq36a3d+feJ5obl3QdosQz0vfsv2/0FrbpsiQHMT4dlKhaxAdNlBbMQPa7T5epqe/gJd6ZQsJIXSZtWqOWIgZUEfC4O+vXtFyUoZaZCibTuJR89g+EkwWdM9RwTytiBn/rBxTQ5ehMgXqZOtQaVaSh7u4UiuWoMuyBzLlsImKoMMqMCThFKWWDRi10ZGLpDLgYOySd+31o/xSIu9lCUpMpU4tKTUrK4FCXpdUHFeWOSSTT4HUHv27X8nXpFiNFuZ2gwPvhUobXKnkS0oVo2iQLSwmJj9OqRZEKzqRlZo6mSZlGsQRKBpqGc0mTIN8JiFPUQyVns8iX/GroEVlfkClXkbi74Z6W9JTSxg3rGJzevb58HJj7F+eQb92nV7wAvU4RRkgMRh+pWGRXEXsv+Jf5wPJ/nqe41CvyYbgxW/goAVkKYlil5X45NOWlpaX5M9Q2hApQWfJySCSCstS1NNYWsLKAWYSO4JlMG9KRBEKrhUwRxoazVTOUb7J08iHI+dK/z0nzrZK6SKfRTY+kYw+isja0LBFm09TIJ4by/YTXfFvBGzJ/p5px4OHVDbEBfGWfUpSh0HMjHCkImO9LhmyIGEl2fC6Da10+NTqCenpv7AO
*/