
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
nvkNa62wbV1lM1Y2Y5BfrTF0e5u5TP+lTc1Nn1YUhl3V1WduVmX4+BJ3iF+763xPtvUlK9/dC+lB+9sGJTZ2/8nnnLZ23at+nc406+0H9bM7THajmtjbLQ5kV+fcbbqedfbENMy1sf0vPldiaztnZn3b2NO3q5rYX8ulAeylETAzzZVdL5ue85p9qP11XBbApi7jsPIXqG/72K081L4fl9vaZWZclQ3Hrt05TdX8fZTsNpfdClu7BAnsp73y39nXs9LWHrP79bTnadd+Te37bJWtvYLCnGnWm1s4sftpd6Ps/l52o5BG1uDmI3Z2i+p1f/C/Rx7SxPt+FZ97hkvz7sfoWuqMNMaXhEC+mPeMEHLJ+PsTa/hjltRO8/LW8YLcTNOKz3W/r5lfLgV9v6QG9Nf9zVDvdjO/W0w/ig/zO4fywxnIjzD7q/zwmS+mBJ9+FNW8tg9NOHcltj6Q10SNUZ/7Ql3tsVa+vKp+9BKyhTqU1fIlvSi/Z5qrIM0dsRhyjIm7PaD8IOZRMVpGXIliOtyxhNvddlm/neTrZ/fDa1/zDyTi56N+ftbz918vrKDgE/+23Mbm7/Cr3N9miH1VMR1GvKJvHVNoIGu7X+dipc5Fhb+96t8enI+ae1pUCHUM9VzkGPE2VsxYrn+fibI/F6Vl/n7m5Dlz0+iG7tNRZ/vYnQtv7GWLAOff32YYvxnqOh+lAWyW+9sM87vbzq7Z76J/7/f7X3Yr/O2G+N1dVz3Xyd5u9btv1O8q/e1VX/vcBNyd74DdA5o9Zn8PmHyEgw1d+emUn9GP+/tZdFCvj4v87hurdDZWNsZPN9VXa/lplR6Kf1HucrPXom/sp/rtr3nCd3+5ta+8cBOq/9111Fk9kx2KO071Huvv3h/h3e/n3h/k3e/r3j/Fu3+Se7+Pd/9E936Sd7+PeS17v4f20F6J7BcQGevfpvRkM1aWEYDasccvteN/T9W0odWVw8k3x/mt9T6+ghmu6thT5RHLyefzignm3LKf6+6T7d12Gc/w65PbWtZ+bj6MzyTX+Dl6yH48M6e0Cfw9bva5FJT8f18djh+ptfzIywzlHuWx/0iX2r/3y46sfV+MwpbTxla4z6h29hJa1bbXAnvFtew5rRsx6vtnb1Urv7bUOS0x7dXzd2pKm9B+lyXG1P6NeAQ+lNn6UP0ax7Sp+fX24wHaoboUv+96Gz9a4keF6cd+/E6l/QO2h3lOurau3QeOxI8qfz/2oy1Me8ts7D2YyP+eNuzV87em1qb43O/22dhrRf2iTXth9jXZ8blPzI51uLch+g5NQaYmcI352MnLcmWnZc4II25btrzfi5mU6Srwtb0jtnYcfwGfK65tm1Dj0H8vYgvbvmOIk9rYn7+y2rbMgbywfqeqzj7XS4WN3RjrmcHWbuhrZ/xtmn01Ja62zdbYrAhgs8A5Z7/sldnYi8VeZQB7rsLQ12TYtWnXtrXttcFelb29sN/Ta2dzeVv769GxzsZmPe57du3arJ1934m2txnWu4Flz2cMaX47+2skIZA95wxX9S3PukzqV9dBnvtdANvJ9rYLs4pm5LrS6m/Xc16d7WvbjaONU+zthv1+ZLt7brN4xfbpnnsa0habqbVtsjik7nuuud4tT+sMY831bvwKch81nlPs7pHL5VcrtYV1sD1+ldX2q6i+90jZ9fHPW4jfb56Eo2r7cxT+VNj4U597p3zx/ta4j98eKsT395+NHx3xo8rGj3Dvp/4+PIYP7gL8xzs61PahEz5Er6/tQ7j3WH8f1uKDVYD/+Siz8aGL9Wxj40N97rv+fqzBDxXi40e/jrX9OBo/Um38qM+92N+PzgF+g27oaN8/nTZ+hHs=
*/