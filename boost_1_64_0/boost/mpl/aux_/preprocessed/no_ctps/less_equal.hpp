
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct less_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
PDGkoGNbcXzLs6433PKOF/YIeS2zyaug44SZ1yWqSN51mcHy19sun7G6CrLdZF3UeREPnHe7PUxeWTZ5FXQcLvJSbzP2cRmHSzVm3Ui5/8Ff9i9f0vPknWvOO8YQFpWQnO8+bXssVu8vvCb3FLQq4yrXKQ86n6v5X3HPwH/LczWbRSmve/lMnnxpSA/vh/e8f7lpoYMT/r33Evjq5JxKzrUCbMY62SFfsTuxMspYL8QEy3mSnD/xOfp1WAYqUwOJEW6InhLrXAV9sBY2wUfQD30l5rk9tsK+EtMcim0xCdvh0xJzvBw74kaJPd6PgRIr3AtPS2zxz9KfUFies+iBfbEuhmAz7IdtsD8G4AAcggNxOIbiOByEk3AwLsIhuBSH4gqMxNUYhe+jHvdhNH4isclHMAa/ldjkE2jAq/gk/o6J6EEdJmEjTEY/TMGWOAa7SYxyL4lR7o9paJBY5UQch8k4HqdL7PISnIhLMZ3/tkks8w6cih/gM/gDPotn8Dk8h9PxMj6PV3Emlma7z8by+AJ2xLkYhPOwD75kiYWX8z85LwywiYWvJu2sOpbDGuiF3ugtMfkNJCa/h8TkD5CY/MGqWPx6aHlulOTXW+N5sRukfb6HdXAz+uEW7IDv4+O4VZZHPcv5HOd5srwSGCvLWyDLWy7t+jX0wRXYC1dKzP4qTMbVEvO+Bl/HtbgK38I1+DauR5KMdSPnZPJ9v8DFeqybGuqxeOR95fN5X7pqeUxW7+ukHotH3lcsn/etd3B5Waryab5Ptl+uvM9fY/uVlfouhzWwPNbFCtgIveS4UhFzLM9RJb3m7nyW6n18luoxf9f/6Oep5vi7/uNx+//UM1V9bxV9oM9V7Xar6L/92arjXmM7kw6QckgeK9x1LUmhpHGkTNJu0nHS7RXOvmHn5Jyck3NyTs7JOTkn5+ScnNP/3vRP9f+Hx8b+7f5/pW/fTRX3X1H69qtIX1Il6dvP+lPVt2+K+1dWIjkmXvpPC/D8/i2FHny/jHZ/0P3rr9Hulyn48/j/0/pr/tP6ZUYZ+2UyVpxsd/b4okLDtk9o2rhHiMF+v4x2/4u9/pp765dpqZP9AatIf0thbCiNvZRcL/dAd7keWgnL4TRXnUPjkHjPMF3D4vqV8foS1464lqNcd7n366AP4hrogxyfJLezm3OMEptrnbbXObnG+UDHJbn7mCT351rmnbFIHLsX5X5cv/R83Xk90jk5J+fknJyTc3JO9296sL//I/kvNSxOnzzyfoz9r/z+L+2pk3hO+f1vExf7KAEbGdeMv/+VrCNikpPy/a1vjuf05LOG0fo0nU1s8wKNfCrxXu/rlnwieQQ9j4EPZ1X1iUkO3D9QSpVnuMyXkPkIm2ctp0os3KsSt/oK6TFlPVX5E3qfbxy4eT37lJH1tBkrO8Fgeo/HnWfSN9HJ5zxRnknvZ34Gc6YLn6NsbZj/lrKon8vf2Zdym/OQ2PFfy5GvIdm4bur1Iw4sT+x9a9Zv/Z3tSBS14+PEW9ZP9bzsLqryqJ+XfVHi/pvK2P0+2I33Btyy5M2nwpSqyfdZ5Zr5S/0+yhsM4bEj1OP1/6jUh6p+k0mGWH08WMYkn+Uj28V2PWQb3KC8SlxSK+YHKWVG9Zj+huQ0g17WWR2HvVEqMp4PlMRR2INl6/6wWm9DojJOhoPPQnfHOFYswiDrbb1PSduSePr4KD1LtozFXtVLnv+ttd427Um9HjMlNv5taTtrSHVYVvAVy3qwDmN4REgkw37k/xyNu+0jtZR1aamqX/X2knL68LmEyGTLMxNkG1vdY5M4hmXIfTPqdqFer1CJky8u26co1id/36vW66WPv7NeVR3YPg/LOmg=
*/