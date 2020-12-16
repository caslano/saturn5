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
t/QeIjbQ2LXRIWP0/ik22NiNezaVa12LeY1d80qerr1LzPbD3Z8svVHzHt33fJhw3p5CzbuYXV9b1qtLdE6IDTf2TuPiWMd8YnZ9mWf/7gutXTE7ezaf/ob2WK7YGFu7oU9t1hkpNs/2yoeP6d+JGsTs2iN8uTpDmsUmGVsU8VGn3lvFbM1Pujn0Dt2XBX37aMGGghG6L2K2XgYEHpqitSQ23Zif99TvtR/EZhkr8Gv7XL9JxOz6uj4ard94jWIhxhqWXdDuWIfYicbmevdP0zN8Yd9vi/Xt7bMcSxAbaez9xQ/U6uwRs2t464wHdJbniUUam7/gbJ/OHrG51i79/np9T7EzzezZccZefc/oU/vGPbn2xNN1z8SGGVtZUJDkWJbLHo9+5hGtJbEoOydOePIdfU+xIcZSDzUcq70pFmZsV0Ch9lib2HKzhsHvHLhb75ExfXtz7LXJi3RGiiWYuBfnRQ3RbzWxmSbujFHj4/RdxM4wcbvPj9P56Xda3/vuqv0n6Zz3FzvJ2JSI1/bpXovNMfbXvx/5i+61mK3Bh7fVvKHzTGyWMe/gqydqfYr5Gzv7jiVPa/+5bP/SRTt0nonZPJQ8/tE5Os/EQo19euGaC7Q3F/WdZzFbbvrEsVAx+8yWjjGVeha74k7+LO07zZ/LfgyZrfvpc9k73+3LcCzVZccf3fKm1qfLXipp1DlfIGZzuzlj0ybdTzG79tcnDNY7e+ci15nTMX+ezqXFff8mENx9IE1rUMzW2fJbb9PazRSbZuzn0ls0t8ViQcb+mPaezoJKsanGDp+27DjNu5jX2IGTSrQ328QmGpu3YuBgrd3YvnX2cusOzV+0mJ27wzKG6ixPFhtobN/3h3RGpojZd/Gc/uYNWvNitj59S+7arfsiNtxY0cod+jfxHLEJxo5cdOEa3TOxccaeT65fpbPHZfmjh47QvItNNjbtxcav9QwXG2LskXsCEh3zLOk7r2u7vtM8RIjZmkgaster31xiUXYWjM3crt9VYlOMlYZW6R2zQuxkY1Mj3lyqPS02x9jML1Zp3oNP73ve+v70ZYn2ppjNQ9crj1/uWKTYJGPVT/jN1t4Us2svv+d87dtsl12+6sj7jpWJjTd2wZTzdb7Uih1vLKX46GZdn5jXxnVdVudYh+s9V0TddKtjAWf0vWfNuz3mTp1ZYqONLUlfoPUS5bK67y5bpj0tZufLpm/uH6b9IDbG2PQkf32XDDG7hrN2Vk7TPRMbZOxozacnac274na2P5Gm9SJ2nLFDb++6WM8OMbsvB+5YdLzutdgsY/fd11yks05soP29a+Ys0H5wvUvrSVM1t35xfS3gVr90zYPL/G9YEqrzU8zuWdYHs7QmIl1x39z5o875GLFBxtZWX5ThWKyYrWvPupBDmj9X3Mbp3YscSxDzM/ZTbe6lWvOuuMNVX+rfsxLFJtg9G1c0R/MuFmLszScD5mr+xIKNjTvt90GaP7Hxxg5GX3mq3lHEbG73/fjpT/ot44rb9o1PZ2u32ERjz4369p+ahzN78z5XLOPglTdpr4hNMzZ5zsIpup9iY4ztn33bJu0H1zPnzRjj51iK2HHG5hx5N8qxLLHBxkZ9GP+l9oPYcGOrJv8wSvdTbKixH33nROqdT8xrbEPGrmjHSlxxiwalTtCZ5Yo7fvUl2u+VYn7Gvqv9k/5vu1ViJxhrOzB1gJ7Trrjn99aotbjidjRdrc/0O8vjCTK2/I6quZo/sYHGbjr4txM1f2KD7Pp2Fi50LExsgrGvR3lmah+JHW9sa/LsFM2f2OQemyP233Hn6TdCrtgsY0eDer//KsUCjV03cpfed+vEpht7tPn7FTqXxPyNhb4=
*/