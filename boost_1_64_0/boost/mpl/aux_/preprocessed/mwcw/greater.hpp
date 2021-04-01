
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
IljRlRWgMgJ3DwWaBOpydWkZLnyiK8PK+fOkuwv+E4N/sr3MFzzYCI0BnDh617Bu9E8YFKPv0ie69z/L7qXbJj0xVVvvCQmlj7VEhn1EKbSJrHkTpxXqzIYs088BsUbv6Oh+t7Nj5+Ot5VfEgyOwb2XQaShoGxyQ+wK8S4CpP3yO7N9+3QQsCrfZ9w89WQg/liexzCIe7xMpiBV+HjrtstJh1jAiCxgpA+1iFkGH8P6fQQAfdcEMjhrFBBBqASLD6RD0Bk2UTzZq/n47/hag7/uy402a4xcpkjYEtdF2BPgMU6MAB+jfkeym6mUrdKdXg64gALJQJzBNPzY0GBN33cOtnjKZQ839C8wfvqha4saCAxmtzH324kti7vmza91muWvoFs5YDEvl8A7Je5aLIdsekYJZvUv+sySX0zJzEPg/Pw/vtZXI6WLxCGxxSbSH+hiZ5/2F0vHgRUMp3zmizp1eK8a8cXRZzNP440pwpM1em/cGu7nXj3NvBmIbTgYndGI+8+F8Ddnlx2m8w2xe13tyRqco2EMYK5TmGYx/gvKM7At4Fk2ZD3DkTQ==
*/