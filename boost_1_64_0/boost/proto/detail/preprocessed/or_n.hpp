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
wu5cSbjB+QdrKOxqpVIHuAdYeWmj1zI/P8O8hM35weG2Mo8++N4U1n39B8Y6FGYt7Exk9iFlETD5nCs6HXzH+Q4rIezzxC9B7C8w+SyjT7XgfEiHeQsb/6xPQ+YnzEzYNf+YzsqOw+yFtRv7NYK5C3OSsT5fMZhnC5NntHrrb8WY1zA7YeftXB4ps+qLvBbme8OrMnMCJtd9m/Mnv2X8YPWFlRhagjnYC2YuzGfWmQHsPTB3YQ0WtM5nD4HJuGzZPfMcZz/MV1jjhgmflG2GWQrLPJ/F94mdsEBhp1r7zlR2G2YQ5j0/PJLzHVZX2Lh+H0pw79HorcKmBdxlvgTBZMwyzMfZslZgFYR123E1kLUCqyms/QqHg8wlmKzN+wXVlnGGw2Reb9w9trqyPJibsF57bcZzhsOcheWaO33kuWNSlBHmldWZ7xoBmm02tfmNNQaT17yy5k0HZV1gPsLu1nOeyj4IkzGrdeZeXc4ObV2T+xNm8Gw1+zznc0XWCkzW0b7fmi/h2cJKCQvfMyWL/UXbg82W+UV/E6+/sU1N9eurLBDmKMx2WPhnxgUm6+Hy4uL1lIXDZP15tB/Id6JImKyHG9eyYzj7YTLnd56J4HtWFEzmROXFb7j3GJjn/60K7MXJTTz3RJirsBmn9jxUtgbmJiziz46P2c9gFsKiJjfhO+1pmIuwbiNKsTZvwyoI6+OZP5d9CR2jrLB6Pk+/MgdhpsJOenS4znOAlRL2LHgf9xCirRveIfYJzwhWU5h5p0XMszht3e5j1Vcpi9fWbdn4Z3P2JZi1jMuc3z5whsOqCeu6yuymsgJYkLAPaS8Nylxi+PuN/3vOs68vse/Cqop1I86tbsA6goWKdc2LL1jOHgIrJ9b1ftvHnrMDJs+hlbX7F9bDQMw/YUmB6zYqqwWT68YnTD7C3IWVF3bAZyDraDzMR8bMZUkK+yBM5q5v/Agf5qBmk8JPvmKewarKdbGOrGnbQfjZobBfdnxlLoXAvGXOr9s4jzUG8xe2f+iQK5xjsJLCTu8LasRzgNUR1uzvUk9ZKzB7YXU3h95iL4eZCftu6uEb3J9mmy1DrjKXYD3Fub+/2rkpew+mebBYV+XBoWhlCZp1nt9qDHMXdkJcc7ptdx+uG4y/ESLWPSl8x3M4ApP7Oz0gjN/2uTA/YYmeJydwVsFkLkV0q7yZ9TCkqC8Fwp5/XPYTcxDmLuxk8Yp8D4mElRB2/4/9D3m2MEdhlmMauyqLhTkLq33QZg37J8xKWHrfFTt47tqz5D77sIF9AmYhLPZxszKccTBfYdtP1ea74lWYpbCYRV2rMidgZYX91v/un8pMhho/55ZjY06z78LkuqGTZnmw78JKCituvnI8Yw2rImzzq3/4vhQNs5ZxmWDtzXjCfISNTp/dRVmKtm6a6RLOxnSYjOf7N9sXKcuCuQo79G3ERMYMZiOs6beMj6wVbX/pR+KC2AdhBmF9Lzt2ZDyHGedL/oG27K2OMLkudYVNljJvmJ2w3VNKdGM8YZWF+T1MyGGfh1WU5/epgUFZEsxTmM/yXWbMM5i3sHu9Yvcry4apuFSG1b5/6zZ7j2aH15XapawQVkJYSst/rWLdwiyFXV1eOJgxi8XP54VZVzyTx5jB/IUNHzuAewiB+Qp7U+l6acYF5ilsYJ2if8eZAHMX1rzCK87ipdo1h9y0LHq3gVkLW1Gh8jrGDOYorE2XkwNZfzBzYV4W9iOZZ5r1rGs9SNlzzRKn/PYz4wnzENau76nZjNlw5Iuwi1kRtspCYd8Ju5D/ugfnrWYJTr+yjvZqNtFpDvf+Hjbsvxb6X3vRtQJjFjPC+Pxy3VqxHpJh3sJm/TCG3+g=
*/