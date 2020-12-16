    ///////////////////////////////////////////////////////////////////////////////
    // deduce_domain_n.hpp
    // Definitions of common_domain[n] and deduce_domain[n] class templates.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0 , typename A1 , typename A2>
    struct common_domain3
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3;
        typedef common3 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2>
    struct deduce_domain3
      : common_domain3<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3>
    struct common_domain4
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4;
        typedef common4 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3>
    struct deduce_domain4
      : common_domain4<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct common_domain5
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5;
        typedef common5 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4>
    struct deduce_domain5
      : common_domain5<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct common_domain6
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5; typedef typename common_domain2<common5, A5>::type common6;
        typedef common6 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4 , typename E5>
    struct deduce_domain6
      : common_domain6<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type , typename domain_of<E5 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct common_domain7
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5; typedef typename common_domain2<common5, A5>::type common6; typedef typename common_domain2<common6, A6>::type common7;
        typedef common7 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4 , typename E5 , typename E6>
    struct deduce_domain7
      : common_domain7<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type , typename domain_of<E5 >::type , typename domain_of<E6 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct common_domain8
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5; typedef typename common_domain2<common5, A5>::type common6; typedef typename common_domain2<common6, A6>::type common7; typedef typename common_domain2<common7, A7>::type common8;
        typedef common8 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4 , typename E5 , typename E6 , typename E7>
    struct deduce_domain8
      : common_domain8<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type , typename domain_of<E5 >::type , typename domain_of<E6 >::type , typename domain_of<E7 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct common_domain9
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5; typedef typename common_domain2<common5, A5>::type common6; typedef typename common_domain2<common6, A6>::type common7; typedef typename common_domain2<common7, A7>::type common8; typedef typename common_domain2<common8, A8>::type common9;
        typedef common9 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4 , typename E5 , typename E6 , typename E7 , typename E8>
    struct deduce_domain9
      : common_domain9<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type , typename domain_of<E5 >::type , typename domain_of<E6 >::type , typename domain_of<E7 >::type , typename domain_of<E8 >::type
        >
    {};
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct common_domain10
    {
        typedef A0 common1;
        typedef typename common_domain2<common1, A1>::type common2; typedef typename common_domain2<common2, A2>::type common3; typedef typename common_domain2<common3, A3>::type common4; typedef typename common_domain2<common4, A4>::type common5; typedef typename common_domain2<common5, A5>::type common6; typedef typename common_domain2<common6, A6>::type common7; typedef typename common_domain2<common7, A7>::type common8; typedef typename common_domain2<common8, A8>::type common9; typedef typename common_domain2<common9, A9>::type common10;
        typedef common10 type;
        BOOST_PROTO_ASSERT_VALID_DOMAIN(type);
    };
    template<typename E0 , typename E1 , typename E2 , typename E3 , typename E4 , typename E5 , typename E6 , typename E7 , typename E8 , typename E9>
    struct deduce_domain10
      : common_domain10<
            typename domain_of<E0 >::type , typename domain_of<E1 >::type , typename domain_of<E2 >::type , typename domain_of<E3 >::type , typename domain_of<E4 >::type , typename domain_of<E5 >::type , typename domain_of<E6 >::type , typename domain_of<E7 >::type , typename domain_of<E8 >::type , typename domain_of<E9 >::type
        >
    {};

/* deduce_domain_n.hpp
h/9hPbfUiQEOCaRlUtfymm4WmUJtMg1hOU2td4AYq5s/ZqIX6+3YTHVr9Dgyj7qG2rVan+vH82S3OV0uNIoV1DuGqgw4hqzTgUzMdEwqNVMEH0uv0DL1V+/N7fa5XehQlq/YZgp3fCZ+DPElahwTR/Q5Pq+cl3YcDbDpc9FssZanVutzhfw4muLQPGI1Hr9Ax+VR1/nx1vKE2eQZxpZqec5reYISvdgKh+YRywc5Ig3+bhyuriNCWVzUe/8deji4r03M1JZLcUScurZR1wTqph07g3jbtF+xPlnoCLbSrI1vTuLYSZ7m6GOH5xEL4Dgsj7pezlItz608z6rZ5YuExrBok/aMnfe55mr7lFY5Pk/mNIujAql51DVCnbU84TxPWfOvvhElHqnObyLu22hjW6nD26duTZaEpImOSNPQ8TOKJWp5QrX2cVvr8PZRV2pxZBM1kOn2340Jox0+JqhLvTisicT90UV6nxts8yx3dN1cRtZ5b1zV71OHt5G86ItjQqmZKqRMkTaZ7qBM4Vq/KzMsEz/ldky3q8ukrgXjqmUawjM1jb9vutAx6pxJosXUf6uO3UleDs5kXRwmcUKWmA3UIcHUXOp6MdZcUTyXr8uAbKF3stb1cpUlOjrXNP5PHBsKjxGxzLV+pgRHZ9KXsnHMmYNoJ3UtnKu0dorm7TSr/ddHhd7FCqzfTSZW9/dHviXXOfj6FayY46CMuN3GUl+M1tptpcP7Yv01exwTDOeKY271+uN5h/dHPseSAzuj2hdTpPF9BO+LPcccSRcaz5rVHwsnODqPOm+V4wLh9hlnvT6SfxydRyyt5JA0on3E2kziGcVI3j4uj00xCR3PutU7jqoc3j721nNyzAkGbq8EFmq9B6Fd47ab6Oh84rvYMWkaypP4u+NptMPz8PnqHHc4NZBnwu/OKXY6fLyTp/B0TKi657zS+d8d/Jg6Ft35G63ULNZ6TPEO567eL/Lxc/D3b1ZaAn/SkTbN4rA85fy+1wotzxieJ2ru6ZFCJ7LW2r3Wpfw9tI7qeUWZo6911ZlV+Rz9Djnja6jPJbNq66+8fdqoz6Qd3j7SWjEOOiFS26gpX1MpTGujWN5G5058XSh0Ekt01f7a2FlkqvR2dCZtvmbHxKnLo86lb9by3MXz3Bnb7bDQFLZLK32R+m/V+0UOP7+bZp013yEtpOZR147qqD0jG6u+5+N7j/bux2T1BW3xPeQk2sfNqPbhl0+Zk7PSHTMyiFzq2mbXaO0Ux3N1aZM1RGgqK7TeN9KOpdobHJ3Ldo53B10W2h0jSP/OeV56amIaP9fJlJPF9erjF8Tj9fajaPTv6s5h09J5sEmNDjY0Miyq35CBI+qNFV5P6M+4x9nc90/j7w03+IxbzGvvmAfKkydkpE1I/dPPuafA9wUMLZhWd0FS3SXY1J2FRZoarDt5Tn21mI1uUn5QiLmh//R3WjpbCOrMiALh8sxm8Q2/RwHXA/hr7Xujb2Bd+/L90Rj/Z8v8ACsHZf6nC4vLWsBiG12/avv9W+W9n23483VrbEEbLOssdqzhY/wP13MwstC4zPc1pu8aXliFv8u9TBpDJ7NxE/XS5LPiyxpfv/wOo4Elbqh+721M/zW8sOqs57ul+p1iU5o8luva2Prlw7vBRx2u33sa038NL6zCBsVESPWbzpq466XJ5c9KG1u/6j0i48qL63ZmY/qusQXVruXKpbqdytLT9NLMYAsb/b1Wd2PHwN7QUP3e3Zi+a3hhFZYRvU2q30wWna6XJocVNbrvqutSGFdgXLfTG9N3jS1og2XNZtsb3Xf1NTeMLDgu9zS2/c/X8T9SYFzeLJbY6HqW1hX518qd2Zh6/kc=
*/