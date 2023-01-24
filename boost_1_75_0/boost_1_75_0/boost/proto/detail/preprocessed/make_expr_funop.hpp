    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_funop.hpp
    /// Contains definition of make_expr\<\>::operator() member functions.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename This , typename A0 , typename A1>
    struct result<This(A0 , A1)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1
    >::type const
    operator ()(const A0 &a0 , const A1 &a1) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1
        >()(a0 , a1);
    }
    template<typename This , typename A0 , typename A1 , typename A2>
    struct result<This(A0 , A1 , A2)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2
        >()(a0 , a1 , a2);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3>
    struct result<This(A0 , A1 , A2 , A3)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3
        >()(a0 , a1 , a2 , a3);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct result<This(A0 , A1 , A2 , A3 , A4)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4
        >()(a0 , a1 , a2 , a3 , a4);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4 , A5
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >()(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7 , const A8 &a8) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
    {
        typedef
            typename result_of::make_expr<
                Tag
              , Domain
                , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
            >::type
        type;
    };
    
    
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    typename result_of::make_expr<
        Tag
      , Domain
        , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9
    >::type const
    operator ()(const A0 &a0 , const A1 &a1 , const A2 &a2 , const A3 &a3 , const A4 &a4 , const A5 &a5 , const A6 &a6 , const A7 &a7 , const A8 &a8 , const A9 &a9) const
    {
        return proto::detail::make_expr_<
            Tag
          , Domain
            , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9
        >()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* make_expr_funop.hpp
SwVN1UQeLMTfcoD0Nn+qJqYcQHlewnoW0qGXHJ6UBJwwasViM7wp/U5wo93hGM7UQ3ZZ/r5p2FNS7EKeBBmpncMlgnmXqs2v4A0zxLPaCxfKLs/6G8HyZIHAQMXprWKuOPPufrbihjeY4R2nrVHB1EoM5/G1L4YBlbyfhlRYKGCxGaIsAdUqyRV+PgT8rRBDFWWBiB6s0sWBQsuHEHXqYKCOkD9cWSWxRUbFK331V7rZWxBTzdTDTuR7wV2wWZPyFTJ7EwOyOPuAYaQzZJoE8TwWxGyFPhyKPHtVpQMf1aEzUuVQcilQK2dpsL4J4WK3cpYq4pYM7fhc/CddprlSDOTvsWoWg0Mcj9417qASngLQDPY8iCwMzQViM12JX8Hd7Qr6IVBJ0UhD8djwdLbIc+K02BRnWO9ikG2vL5bTOsCBkW/hhEFJlv1XrEro0DAKLH8r5JClj7B535BVnf2unHOk+g1qGQInTrh0kuhyUmovH9Vo1p96azVBCR2Cuc2MCf8OU33i1r046qR9IufkqmU/pBDtBQT0Z/2GV6vGaEN7swid+LCsXdcN+AcKUVsel79kdbEVgz2wBcUpdTwsc5R+ZKCRm36m9slwamb1sbghzAw7bSBopQTDYxcLCgeMiZY2K0BtH5+j6/xQ6Kz/PvQs67rdpdlSF1rRAGH2ROEZo5vQ6xPPzCGEasr1DTogUyLUFO4WjXLFC2W4
*/