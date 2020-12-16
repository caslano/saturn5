
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
GWswOGeCGkyQc9NcK9aga3L7BLzK1N4RvCQiABg4IzAx9WF5jClXYPmLknjt4a9aFK6KwidCmtcU14EKkgiWg0KOoeHuIqZEbIBDFMJ4CgJLA+HtSaBYxeDEeWamZXrj5HhRnoZDdHCKUYuJfag3jOVvLTYUh7lL5VrSM3hclsqD0mmwF+2JazFrKxTeRcLaKZdJWD01Z6wYrFzEtVDhkQIH4yGp4qloSl4E1DQZcB0JwDMKJZcKlNJVih9YNIffq+iZhcP+OlBCy0AHz0pkJEmHb/dAGlauWJoFQmN2pPnIKgGtRwqFAYh0Lj/S10EBY0VUWAVLct4oXZ8kGiKC69fLS+BEZU4+Oys2E34zHtqaA4UFv6yjWmVJ0Ix/h8NPD8nF/Zs1iV4oYwuLERrVje6S04HZoU0SQ5yTUDyCT3ZL+B4OHts1IL8nYnEVcwXtJmYmNY/H5ZbMqIY6EO24H97ZORnJ6iNJ/AaqxInoqSOn8YQRogEI1+FB+puXYSzmwZVICMnl0A6gfjDCL7/1AbZAoz74dQVnWjVgTBbgVCMQmtWH2+AxCVlxemiPvjBdvayRqR8zIqL9+xb+M2iRHj2mSiu7SqDJ9VZIhq/+ggou5WLKQZpfc44JX5n4RWsRRZgX8uF+T3RpIAmLhuV4uBwRIb8zkohsaJXBe5jzILgSA4jWcdpLbQ3QerE1XnprvBqt8dTWeEprvFqt8RbQGo+3JmoIfnjXSo/kfYB7EtLck7xUz/AEzxC19pJuAkooh6USfhOXUUGFd1GRClrhexUn0Ig4PYRRLpEQg8ytuPSGmW9m4k1SGYQgBYJNgHVOndw4s6tlRldYjgMoI5DIX8ePTDJtjeFrtjKIcjIklZWLiSWkzEEnDAWu1tnIwxfSna1Bc2OiD50XE5ATp72QEXQ5EmIkA50LHi2F6fC4M6DQRc0T65CMKxOdEkBqMANeK5qBlQxnMc3lRW4IIi1CAU6GqJjm7DhIxQRXXw1TEhyZOzVQAZcjkoBxq4rhRUTQUhhHwFJrCCynZEVnpSB+Rw9L5XlX8uAGIi26AZbDG4dqGMFLMYKnGsFTjOClGAFYeg2qETzFCF4NI3iiEdD+6DfhLmF8QYqHFhBysPQR7qcguJ+CSPdTT/RT0TqgkpnjJkktCaInEsnwCTKOn0jyNvJYyineQCWCdrbj/hHeMG3OlBBdPK9YBwgNHgzvnYGKr/f7u7zQMcK3+5DAhddS9zyseMp1oGLtwmMtJOCIUtG+Yqk7W4zelwKCZBYmQAJ3sfqCTOiiOvyi9yv9CfmeJCwyQktTc7zYG9NQB1JcogHo5FEzQUK7EQkS1SYoL2LGQVKk0LcxEPZBSPO8UkbetzEwP9SHS5ja2NGIbsGXIqrqiggGkkBD5ToAk1IKTVKKTUorGMXn0DFSQXgL8JSs6RmrN+PDp/GhjwdocI1UghBCZEgt2tE+bWqwLJdIPBH3enDXFk++oRHn8XNijg0MJQickXEKIyYmxFLRw/HebA/2/yIcznIqjqf6eQlDt+dzAhS8ieuPGRHG8Qb2cHjUJyqRrkMGUWp2vmrwdHwoDcYAEoUjfPXJrcYel0/eCmdWLR56GOIQ80RYNUkGMQf3MPAIBPGg2miJXYJDhfHHww4001sqS430bZpBPBBR7AvTpfZn0XY8eI1iAy7ycpcJvQ3bXw5hkAgEDshSLQhWakcAT+mI+CRLsLDKrmXmwJaI0xWO1W6Wl+5pXg3f8dJ9x6vhO8DTRoH3v/sPWeIxga8bRDNRL9xQhJSNocr1FxgpMDJDtxQG4nAKHIRgWT56Q0K8Berjpevj1dLHS9fHk/WJdgAR2ZMdTJYLoyHXJ7k=
*/