
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitand_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 & n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitand_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitand.hpp
JY2bbaXR/FbomMRJfyid5JVFOtc2sUgn08bjzHa6HSraTnf2HdI9ITPpP57unZJuF0l3Q4I76c69Q7rTJ6b9pek2pnOQpHNRJXk3I6Eq4QPCPzswf6mtdJpHuYhOoKc7tSM9Oo02JjmS/vp3feZQOc67LSvdcW48jgtLOo7tbBynsm+Bsm+OleW9v1IGGwhfsm9uC+6wb0mxkWmUR3JiekLp2jr2A6372veUNKyXNCj3lu3xOfyaNNgtvEMaGBXEVtz2d4g7JjadbJI8lHxNT4u2SIuz/BTiIfnhJvlR8FSJaZGc+P350FfiviFxPyb1bAbhInHvX1Jy3PE8H8zYD5NK00dfqV+dl5aufin1R52uIdOG44TpO7f/Uh8t9m+6jMHwkOTtg4QfOhDP0jvvX0xs/D09Y8H+2KxnRRL/ZIk/k3CW+IPvULYUbameA71b2V6UMQUGyXVBIH5D3DUWlxx3ulq2pRqbp0LNkUtuK1vSY1W2cs5L/R3nbpvvwJfpRILx3D5bTnRJktfjCA8p10HP2thfcnlSbNo95bPVGExam8/zPckZhn2TtFuUhVPV25+1qUfa1ttOW3p4ZAYp5ChnhJU/msY31TRa1c2katLG3CdtDDYgTftLSlNKsrlulOLZX6VuJG9Q60bp02eVh3J9Z7utSUrQn1/tQLr1qwzDc//M11px222TzWv1PevN19od5Nr7ptW07wbzNNu3yNOI6rc/A0cdpBOsrTydEDmeL1JxFHNsqZ5BrVBz8abS5WnJ9VL215inxu8yzDPm8ZRStOfnZZ/9pG53JvxE/NnLbe2zKVW/uz1fUkJdTmVtk5KGZMIvLJt3pzSkpN7TsUXc1u05dff29vxSDav2XPLDv+S03HN7bp0PQyXuMzLewPfSnl8gVFDOMytLjpv2TiohWZKSFsOlY0Zseuna9lmrSlcfbR3jUt8s2vcppWzf1bwOrXV7+3qFuNYvK3F/77l9LSmvA2pLHy/J608I5cjrRStKjjv9D+R19MrS5bUhvcb21pjXTJc+r9XjPF/2t5nkdVPCb8QVcZf9zUjRmrJS5/nd9suYrr3yrP8oKYfhBFel3d9cYrrSLU69pbiOvdN1ayYhOXOC9pxpE+I2xyL5bSN/M+X6RWlLhpjSSZ83aUsKpa+v7eckS34u0fbzkyU/52n7OcaSng+89+f3bD+/WvJzfbafb7z35znv9XnIe33u0fbztyU/52n7ec6Sn18dMk6ZH7Mr4p3e3+zteSPEeevxWk2mlvx8r/Sb4vdh4ztgLftNNZZ3ro/Cyij973g+R/19F+UdkvyMxnM/0j9T+nG9iI64DevjS9gBX8ZemIuBuB1DcCcm4C6cjrtxFu7Bp/A1XIqv4wbchy/gG/gS7sfX8AAew7fxFB7Eb/EQ/oKH5XmwI+iI72BTPIoeeAx98Dh2xRPYF9/DMfg+RuEHOAXz8BH8ELPxH7geP8JN+DG+hJ/gYfwUj+Mp/Ao/wwt4Gi/i51iZvDyDVfFLbIb52BW/wp74NY7GcxiO5/EJ/Abn4wXMxW9xF17EPPwOP8bv8Uf8Aa/iJaxSnmMTq+M/0REvow8WYBBewSF4FUPxJxyDP+Mc/AXn4q/4HBbhC3gN38XrmIc38CLexB+xGCtTn25hVSxXjv3G8tga7XEoVsAQrIhJWAmTsTI+jvdjDj6AW9ABX8RquB1r4htYC49hbTyBjij9ROV3cNO+kX7LfqLT5fmJR9ARH8X6+Bh2wJn4MM7BFHwcp2AOzsMn8VOcj2fxKfwBF+AVXIi/4RJU6ulSdMRl2BSXoweuwB64EvvhKgzCZzAJV2MyrsEFuBYX4Tp8HzfgSXwO8/F5vIQ=
*/