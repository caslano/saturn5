
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
BjbleH6FET5P0hEImf5Dbup+ZN61mVfllo+ZogSl97OoMbbP+dgitQaPv6StaKdmx/lHWu+RfuP3lT6g1rD53mX2UfcgQu/ch1b4ae4eDNEl18eUOlW3vH+c9Kqo4Oj4wbRJzzbuDnoOnnd9MzpbDvGhDv6dczCBYeGzqcBODDjZ8PMVdWAnfs1nT+JN/5sL4aAbWAf+QdeDYNLDvi/T5ZBDwT4Q5cD3ySDJ/cRI0rOm+0ui+1RyroHhFylvG6nVofbL2Dhbss531MFbQXKPbK0I/DtELv1DsovSCT3oAIRcus3zq6bLnhh2NnYHLWdBGynkQlPOVw86aerGb3PInpeTDyei2qzfgu6qPUymI04QnHkoKMEsugZ+kGMDxP7DMJpraLchL+TOqAeX2/WHQvpggocPeOsb1vKM7q2T/oPM+cyvTm3N10pqYWmjdM6PyPI9P0/OYbA3X7gM3R0IbKDSdSn/ePiepa89y4b4u19WCxeMfBHTsYE49sHjcIJWkT+vojgt0pvzjbjlqE291rstsDFLOSS3yObsupVIyalJNkvFyIFjfHfxR/y0IQCSYo4LEtcoUnhB7PGta9b0sfdmTAwp7tg0W76h6faozoOCYeckW047MozShMbrHThmWYcenx5/aLigv+Clem77kelBxWMEHqX0mMXpVc3gDRxfufBJ8tJJlNH9vIlIMO0XQqsmvRCCvk6plgyw
*/