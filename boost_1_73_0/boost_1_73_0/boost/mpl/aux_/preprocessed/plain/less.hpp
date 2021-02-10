
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
sQUsjG2aTpzbGzrTnCMPuvHowLcYO6DVBDvEDhJqe58IdYosW/Cw9s6EKLUhvbMh3VXj/QTK68f4BlBLAwQKAAAACAAtZ0pSMMmbsewCAAC5CgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDY0M1VUBQABtkgkYO1WUW/bNhB+J+D/cHBQdA3i0HadAFEUA0M7NMGaJliNvhQbQFHnighFCiLtVPv1uxPtONvapg8pEAzTg8Qjj999vPuOdh4xRK0CzkVu3NLT5wa7W9+WYS7OF4vr/gXXV+8XaXR5cflLMnO588xl2iz2xB68x3aN7SiYEkXeYmM7cihVVAlRTg4nMB2P4erXgXitImawWOEBjE/gnV/TymQMk1k2O8nI583lYiASYAbMdRR6Qy7VDUK4Ddr6gAPxyjuHOhrvMthNRXRxtOga5L2fo6xibQdiICq01hPpRKrnpivUN0+M4JMik7K1SVMuN3Wlcr+yhjemcuveIIcUeC6qGBty35p7EL23YALcViqSAauAYFyIqErwS3iuV619LnJ2mwtriuPZS9qfTAG5UzWmMkG9stGMGtVGqE2NjQ+R0Iz7BC2DaWVtofQNLH0LsUJYGovA7gQjEw7k2te1cmUimkn57Jy0fXGdPeMQ
*/