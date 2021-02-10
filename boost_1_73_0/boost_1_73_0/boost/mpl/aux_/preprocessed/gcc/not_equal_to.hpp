
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
JlcljG96wPM4DC/xg1cUNtfxebpw//Isvw7fdn+Pzu9YG/RQYdjZm3i8hr2qNSy12hmpwdRVpbQ1YA5OtTT1Ni83F2AzWRIYTKbqYoUISTIwYitP8PHNBeyOwAqVjcPwZaxlocSKs2UMy9paVQacYQCUIBa6lKmVKxAGagrj5V9mm9vsZdAEOsNf0r+eDGGJ/ZX6CmuUYL2Tm3imlVWpKgCbTBH0OEMp7WBFo6DbvDJEe0eV93IPwx9pJsqNPMNxhJ7ADtTWZYGWT8jpw2TyFDSvMqlPqP5w7k+nU39wPXgC/KE/OHse9aP/tGfq3MrHQS4QvkDjCzS+QOOLf6pTwXBBxaIO6xiL95E67PiSSYHlg50wPT67H8YjZWwPCpWKIqPluzCKWt4DtsDvb3D2e5DWuvCJjb6LpOX101RWuNFhHWICZ2QH70Q6RwccYeIGji4jmpH8QDtk46DIiVING1P3ggDjOBp7xBUkxG9GV6h1lPK1FLbGLsSPuH6WAS9xAmPP5NuqkHCAuHzndEBcgKN5M1i5m+hKlUaiIms0eaq2W1GuYs/3c9zBnCX4PkYiapsR/YEsOomz0kxnI6iEMXTqgFim4Pf/XTCgnAweAC9Gd/NkPOu9oMAwyNndfYJ5nFzj8lAOLNOfUufr
*/