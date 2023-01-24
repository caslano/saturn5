
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
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

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
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
mlMj++dOjSBfoMtY/Vodcb2C922qT69LkXmqILmwOX5m3Gw+r/PR0kdfkdzomub5uFOD77iB3C/PGF8gbiuovoL0+3HrupkWjcmqshydM3T0hhhh3fOBo7uRgg2IBqWo+7WBO8/tCqLhLFgUQDKYO89O2zw1kGRCw9ifPXU8SNWA28/+UlZQf80BZPc50b4kO3LGAYHt2LA1ETdIOb7udZaaYb2rR2WMD/BEjIWvj5E4I+APE3v+8pSWWkNuDeR+rh9vJ4VOJj0EVpZo7L4NNuADNNkDa4KY27Cpj+1OnO23iKqx3Kcw78v7n+c+urNJl4XzM9q8alLLGmjPEdqSPcXIES6L9px2WkavtXdbb9HDzxtHj9kM6WzhL+B/FAs/rOb2dR08HCyjcf9w4Y4mDMVztobIkqOBqO7JmWTivTjCLkUlCC5IS1RjVGTOg7TS2W6xdlDSCC9QB1UgES4DJY13Rbc57qnUPd43PbrxgGc5OUBV/jBmTFqS8F0gx4R0KHVhXnFe4RsEj+IMvTv1zyeciZGV6dof6zLi0bkjWAHiCDTDYh5E4QfRP3eycaGxNBIt90pVdwRfYsQ4NLtbSfnTTzw47uzcdDhU1lcvVQ9KD4txeNB5bifeEXm1FPiK+doNJoLA6wwiyeUVR1DXBYqLu4HB4D80XGHBwhO0bN062f0Y8KvSxEtJQdADCLk1FoJlc/KQG6ar8vwK
*/