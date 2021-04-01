
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
71WZa/lrfC+Iy0W1MLCz5FX2BbCiIqOPtm9qaVkHWoc111m3AmszfJKhUOOyIi876snYzoxQzJu6I/dMB2b4PmqUvKuswR8bVyMvJknDvJp64IoVk0s5Em+G8WjuF92FwxWhbQmLuE+PB0frGQVb08wg2GLIBAB37CW3Oshw3umnJJln7Ss8Dd5lKNXQTU81dQMB20RK4QjmEbPgLaGsKxFtT7rB4qovfpz97q2r0oHMWvczkJjiFrIEVyJL9V76baoII2MY6md/Z7K3QFTbaNtfv/UsplhYATGpW+X0sunCtYPv65M2Y6pl6xQxZJjLDWD4OuIuQNxBh4bkQjrVhwKe2TSAdxjFT/YW6ynwxp+M1jQU5Ksm/j75BC4aLxgOWJ+hPf1azSsDnxEbO3m5btpsNIFYDJ6riWNEq0EWShjyLKbGZbeqXR5nYzTfGdmDOgAY403Fmf4ipz/Esx9U8K6uyWSdTgbXTy9p/0Ej2nxU+clAVQ4tPM5v+kZLc/1UAuNNZuotPZ86j/NYj6OZJOTL40MKDsplbCSkE8WQELfEKGn0DbRGdlnTWA==
*/