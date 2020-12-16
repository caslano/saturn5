
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
P+EE4WHCScLvCMav6V+EZxEswnMJRYRSwuWEKsI1hF2EKOEQ4XpCL+FOwjsII4QxwjHCBOF+woOEHxEWCH8krP0NxyGkEgoJLyVcRXg1wUc4ROgm3EIYIAwRPkT4JGGS8DXCDOFHhAXCnyW/RcpNyCSUEi4nVBFqCEFCN+F9hM8THib8keD4LX2YkEcoJrz4t/9cX/hnloUfrx6r5qeU72HGqx+upg39jM+zWcbsaWlRroEYaTtO23eCtIXvcw3/aDXtRwvUPdv1nrZd9684T44xML+adqWc9w+yzo6zZ8fZs+Ps2XH2f3Kcvd1o9Efrfb5Ic7AhZNxmNET8/lNRWkzWButb/Dp69bai2o1FXl8gwPcVRrk/4m9sbo36I1va/cHotlBbZKffuHvtVWemXm0YHyc9HIpEdSrxTxubI/vC0ct27mlrjvg3h4JRf0zSH4qnX+UP+OtbT6UbD8RTX+IPXlUf9IV4+P5CPKXc3xqNhPa9zL/PmImnbPNHK+pbm6rqI/UtxjdP7RetioTa42nfeiTtla3+iOz51XjKlpgUkATuGqdy3wlcWp+NxzdH/PVRv2RvfP5Rx5ckvkdYKUFzY1ASOJv7V3IOtrVIAZp9/kjr1cZl5dsvq9p6qiZfZWz2R6IvD/uD26KhiN94uo5vDoRa/fEEI19SdCZic0PzTkrRunVl+0167eXNQd9pa1dW8u+D9NrytnBAp69u8kjdlsX3p93PXMl9Tq+lss5cyRmFSdxnbL7qVVXVK6dz15p4Ze/0t7Ze3Uxb7d0WrY82h4LGZ9asVPnLr9nl3xndSo+KtOhVVxvXrL2C7esb/S8Oxa42Xrlty1WnauetBkdr1yd4jT9SHapuog14qfP2U+nxhOqQXs/fFUnctrc5urPpVIJnTTldKeqPxz5hxJswHnvHmst1EVaOTXt9by1l3LaP7ttS3dziN9oSVyOSY8Avn2gz2a6yvjW6JRIJyU+XE7c9Kv4lnU/UV0FvDbD9SySud98X9hvLiVdHmikEcX69+fK2aLiNjnRNW+O2KNddI+UIy/ZXhHxtAX88C9LeTZqu2cu4PCkx05+EK9oC0eYX74tSuKvpXJub6iP80kn3nZVDv3uNtGxl8zWR+sg+YyyhMlTvW4nxT8E/dnqcY4Qee9wtMVLDa6R36VyNA/rz5c2RVn0+rH29TrnSH1tJmE88VZTq0CPlM77/6Jq9rPWRyrzU9oo2f2RflT+iO0RwJ/2rLRilfZ4h+2xui0T8wVNdaqvP+LOkVjfv3K034+dKCS8JhK6pD1zhbwlF9klva5M/nihbbQm2N0dCwRb2314faa6/Rsr3/DVbJPfNNAG9ObDNv1P6IG/REir99e3+M9KrE7YGSaoPNO9/7MrLgr5t4eZgvCBJ8Z52RgbnrJ7FSmfdSv99Y2J1oPWyQCDEi8ob5TMbba8PtPmNmyS27VSsR2LShMbv5fqh07eGAn6aiF51te0qcltJojXrV+O6ZeZt2x6zx6vWbIk1n6pL487EVwabdDP7tsR2+sNSXJolKtfRa6RH/93VTz+zZYx9idX+SEtzkMvrVJJxIGFr60okFLncT9NEWOlv9VNfUdbpXt/oj5xKm4xfN/WRaFtYBoirjR2n1f62Sm4sFXL5v2zLVVduqVwZIxijWvwtO8OM2xXyqdVPr3ipwcC8s4kz2aLXtjCZeZmk6cSXSFpLqN3Pn4nYu7OVZP7agazVn8plrWzG2Frr16deG6+ISHHtzhA7BhlXa2tbo77aKBd0rdwda33xW0FtoLmV42/ffNUrr6zeesWWC4oLy3Uxgwm1e+tbGf9Ym7u2NhAJReUfH8Y/cawrEtk/4A9yb7Q=
*/