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
aok23CSpr/g8IDTvgfMrcizMaR0StSMiq1NpFrcxNHmbdC8eVzuBsz86pontZanz/KYi0iRZtmx9zk4NZLMoGkrCcNkDmHqvmlkQhly55nvyOFMbE3+XJonRksTTlOUtm41oUrSReLjvhditC0vfQ4A1za0iVNPIs2HHj/5DFNyaQZjja7On/3mEHM+sIX59xp7aI0maYCN0O65t/HQG9Gk0QJNGYR2fmuU/Yc2EBelFNbgz+zbXEDzBAHjpQmBvlrs//USqyFdaG9Gc3opfRF/wD7T7tqAHFpYPCKWGG9LWE+r3NGmpuADzsSJm4rfe2tfpuydVXHWqfCTeWtGo2muFk8wL9lvQIsMdoOiyZdIIxLv+8xnrruXDsw6IYgmtEsRqQCpA/nEI+lSGMH76C0+QZfx3vEKklEWBmTnbRp2FKS2wdL14wEPuAYD5TWlCj0VJkbceNw7bKMY0U3l6qtf/zMxmT/CxT0ZoEP8WRT0UoFX3CYuws0kRVDzCMs6n5S/LMfLLiyMoriwpN3XkPjGb89s/VeHzXdt9G7L7HtQO8hUDfR/jk3fwmg==
*/