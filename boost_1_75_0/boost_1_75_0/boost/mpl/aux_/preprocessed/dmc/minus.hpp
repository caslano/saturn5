
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
VDZsL5Me/RKdDEkvO0nJ41Ni4PLWEvV27ejuJ2sA/omiTSBElMbJr6i8dGm0cv+VHPB+HiNl3rGwYHkvPdT+oSUR+4H2GxfxDdFNYQMvNf0fvMecsgN+4mdLvtIZHBMMnMQ4LeSDsWARQrLlxYa5alk/WRTqbBrx/dC5jEjbTTPe6qGbdttMVGP3L4KkkSMoPIX8Ps/cGk1KVFZNQuTJy7ErrUiC2YEbbU5nN80O9qe2H5Gy/Vr5UE79EfJHDi82RAxaubmd7StqjyhrGdJ2mhgUX9ttXAsnsGsaVYtW9rNJHxgGiAl2y8LDIYc5xKdnOTnZ+ljDf/gZaNiLo40+tELqpPZLyAXm6QFOCcu5VL5X+NtdBzuFcAyfAtZz59W2t4EbJAUA2Ripe8Ia3gqMNV/l6aTWzTZXJ6+LnVl/8va+LnsVFWsdlQz8qCePPx3zbFbVDcCI/O6UvFVP8fGZ698nyvfTbph8ZYaZF2Xsl3ogww2Fdgz+D1RcHAWjskt/sqEsofOEkNMsnY43uHKaoVdINs4lGdMEqffUq6DF2f202/Qp1V9ajMTnMyGKJoRoKgDwlz/YLQ12y1zxhNPQ/Dy9HkvEF8zKVNjElg/FQWxR53Ci1xle4z6PJem3mSIcTp4beI2NvDQddOh5lFyfE62dmBvEwYhzSV/ZSW2i8BotiiocvyIL5DByIr45/aadsDdsRQLt7WVeqXkt
*/