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
AHhAfvgEkO6bSpMOHaPadpkynYF07bS/ib9mDOg/+UT7nBEpAmH0+X5zX94QeX90ojSgqtSvKhz3kB5dxFq2tMd1HNBeOXGb95PfPjU6oqnCh75su0CSsVPw53bZn19y1a4WNBk3Hgqjm03M8A8u/Alknwu3859aqMFjt3PLGvw6I/1SLIw8hEN18v1SD1uDptmI5INlj686qU1GbeqGVVVTC/YfGnhOuass5yMDsR5Yt8sibLmO3+oXNeVkNnJc1xSXcTQCMlX9lU4WfrpKiJTlTDmXRuG5IGoWKozplwzKPDKBxo/gXLFlBOUYzPhK5KxjILY6a/8aEe//N8nD3v56iEBe9SKYzCol7dN+GkhYhTnCL2hG1p29UClvwbg+1ioIgPpTTC44r47DnAKhMgjubh4/uI/ZMY2A34hM3AoYvjyp6gsq7yPgE6vtLmNbYnJPCL4AUy2i7rx6u+GrvIq9YW6cJwFI0qd7WAKUKwnxsmGOqDfWfXLqVHSvB+nI4yP8c5QpKeVBLHDIUn239+0dH/Lkg4j7E0JTP/HpghZu+mEY1Ag764IhXbyHg0sdDdhRHyHy12DxJDBULP5BbBMw48/oSnP5Rd1PLw5+4x7tUrp8DRG/FpOAP+nemmA63jidsHihsmb1PrXZWrxcSDN+BwEfTP8Gfy0qmaaC/wt/hv8D//+Op/MhG9QH2XjWiTIL1bEIvdwZqPzg
*/