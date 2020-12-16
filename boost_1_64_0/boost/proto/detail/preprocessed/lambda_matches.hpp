    ///////////////////////////////////////////////////////////////////////////////
    /// \file lambda_matches.hpp
    /// Specializations of the lambda_matches template
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<
        template<typename , typename> class T
        , typename Expr0 , typename Expr1
        , typename Grammar0 , typename Grammar1
    >
    struct lambda_matches<
        T<Expr0 , Expr1>
      , T<Grammar0 , Grammar1>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(2)
    >
      : and_2<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 >
        >
    {};
    template<
        template<typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2
        , typename Grammar0 , typename Grammar1 , typename Grammar2
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2>
      , T<Grammar0 , Grammar1 , Grammar2>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(3)
    >
      : and_3<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 >
        >
    {};
    template<
        template<typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(4)
    >
      : and_4<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(5)
    >
      : and_5<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4 , typename Expr5
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4 , typename Grammar5
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4 , Expr5>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4 , Grammar5>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(6)
    >
      : and_6<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 > , lambda_matches< Expr5 , Grammar5 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4 , typename Expr5 , typename Expr6
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4 , typename Grammar5 , typename Grammar6
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4 , Expr5 , Expr6>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4 , Grammar5 , Grammar6>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(7)
    >
      : and_7<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 > , lambda_matches< Expr5 , Grammar5 > , lambda_matches< Expr6 , Grammar6 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4 , typename Expr5 , typename Expr6 , typename Expr7
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4 , typename Grammar5 , typename Grammar6 , typename Grammar7
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4 , Expr5 , Expr6 , Expr7>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4 , Grammar5 , Grammar6 , Grammar7>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(8)
    >
      : and_8<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 > , lambda_matches< Expr5 , Grammar5 > , lambda_matches< Expr6 , Grammar6 > , lambda_matches< Expr7 , Grammar7 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4 , typename Expr5 , typename Expr6 , typename Expr7 , typename Expr8
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4 , typename Grammar5 , typename Grammar6 , typename Grammar7 , typename Grammar8
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4 , Expr5 , Expr6 , Expr7 , Expr8>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4 , Grammar5 , Grammar6 , Grammar7 , Grammar8>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(9)
    >
      : and_9<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 > , lambda_matches< Expr5 , Grammar5 > , lambda_matches< Expr6 , Grammar6 > , lambda_matches< Expr7 , Grammar7 > , lambda_matches< Expr8 , Grammar8 >
        >
    {};
    template<
        template<typename , typename , typename , typename , typename , typename , typename , typename , typename , typename> class T
        , typename Expr0 , typename Expr1 , typename Expr2 , typename Expr3 , typename Expr4 , typename Expr5 , typename Expr6 , typename Expr7 , typename Expr8 , typename Expr9
        , typename Grammar0 , typename Grammar1 , typename Grammar2 , typename Grammar3 , typename Grammar4 , typename Grammar5 , typename Grammar6 , typename Grammar7 , typename Grammar8 , typename Grammar9
    >
    struct lambda_matches<
        T<Expr0 , Expr1 , Expr2 , Expr3 , Expr4 , Expr5 , Expr6 , Expr7 , Expr8 , Expr9>
      , T<Grammar0 , Grammar1 , Grammar2 , Grammar3 , Grammar4 , Grammar5 , Grammar6 , Grammar7 , Grammar8 , Grammar9>
        BOOST_PROTO_TEMPLATE_ARITY_PARAM(10)
    >
      : and_10<
            lambda_matches< Expr0 , Grammar0 >::value,
            lambda_matches< Expr1 , Grammar1 > , lambda_matches< Expr2 , Grammar2 > , lambda_matches< Expr3 , Grammar3 > , lambda_matches< Expr4 , Grammar4 > , lambda_matches< Expr5 , Grammar5 > , lambda_matches< Expr6 , Grammar6 > , lambda_matches< Expr7 , Grammar7 > , lambda_matches< Expr8 , Grammar8 > , lambda_matches< Expr9 , Grammar9 >
        >
    {};

/* lambda_matches.hpp
D5YA5gNLBEsCSwZLAUsFSwNLB8sAywTLAssGywHLBcsDywcrACsEKwIr7tc8npIe++X/02yhAz1xpSbuFPf5B1YOVgFWCVYFVg1WA1YLVgdWD9YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDeYZ07/5gfmDecECwALBgsFCwELBwsDCwSLAIsGiwKLBYsBiweLA4sESwHxgiWBJYMlgKWCpYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVgZWDlYBVglWBVYNVgNWC1YHVg9WANYI1gTWDNYC1grWBtYO1gHWCdYF1g3WCeY/s3PzB/MC9YAFggWDBYCFgoWBhYOFgEWCRYFFg0WAxYLFgcWDxYApgPLBEsCSwZLAUsFSwNLB0sAywTLAssGywHLBcsDywfrACsEKwIrBisBKwUrAysHKwCrBKsCqwarAasFqwOrB6sAawRrAmsGawFrBWsDawdrAOsE6wLrBvME9i/+YH5g3nBAsACwYLBQsBCwcLAwsEiwCL7NY8nqsd++VtQtAM9cdG9cbHnuJ4Z0xsXe6nLYo2tcFkcxMWDJcAzfWCJ8MwksGSwFLBUsAyx43v2c77Y+IyfAx0rkP+05FeL/dXevfDnbp0hYsEm7qaPuvy0N8USTNx3O5c8pzka6/EsMnFfHH0vwLFssVBjHyz+6xbHSsTiBv6yhtjYeWL3HbjxPp0vx3k8I3rifrGT//PwMH0Xl11XcfEP2u9iw409OvOeVdq3wX3jLtl/8ULtPzEbN27JjN4+csUFL6+6VPtBzGts1bDmOVrXrrji4TvztD5dv/fnee0faZ257GD8kjqtF7GRxkZuy5jvWLrr965Mf+07x7LEhtq4CbN2OpbjemZ26UOva7241nfuY0eHOlbses9vb37qVcfKXHbMe+c86lil2DBj60o+2K9nqsvOnLYtTM9Gl23Y1XqNY00uGxCy8j9aS2L+xm7YVfQPx9pd7/nUlsfP13NFbLCxiRc8ebdjnnF992X3ng9CHPOK2WeGbBt6nc5yMfueM3eFPqMzWczm7+pHrtH6jHTFnXPmmku0/8Rsbtd9Mu08rTOxUcaqlyz7XGeW2Fhjn71y6HitJbFAYy9uPeOA1ouYrZf68XGaowLXu6w+NGKAY0ViNg/jumc/pLNAbIixykM7MrSWXPb972ZucKzCZc9e+dhax6rE/Gy//2PfiY5Vu/az4Mil2Xo/EzvGWPZ/6j1aZ641vHhhyFd6X3LZebGJex1rc9XEsPMfXKN3G1feP628XeeLZ7zHM9nY6LdTXtJ6EbNrOLrgzne1Xlz2bvAXw7VexAYa29x2+HvHYsVOsHX9v0at+VQxr7HDyQkHHcsQs3W28NX1y7VexAJszb9UG6n1IhZkbH7kdzM072J2zx7c/nqezhAxm/dFia3bNLdig41t3f3Tz3ovFwsz9sOnA5ZpjlzPXHfVXp9jHa49y5wwbKLmTyzQWOS3S1/TM2dC32fuPtx0p2MBYuONrRy7TM/pCLFQY3tm3rbbsQQxWxMXzFsVoXlwWXbdyS86Vig20866dXOjdO6K2bzf/u2uAp2fYjbvk9703K774nrPoryf79f1yUQ83pjvoUdLtT7FphgLrfviXMeWiw341QLEXPcsV1zQ6bU6J7LEFhp7vfSrG7RexMYaW3NwyzF6roj5Gfv5uTP1bGwQs7U09eEpQToLxOy+PDvx58W6Z65n+h1z4fNaZ2I276OHxen6/Cb2zcOR1Su+1nu5WIixVc9P1bzHic0wdqjq1SlaE2K2Ps867pZDjuWKBRnzRrxSree7mN2z2TdMy9b9dL3LF9V77tE9E5tu5+6+6dv1fiZ2rLE=
*/