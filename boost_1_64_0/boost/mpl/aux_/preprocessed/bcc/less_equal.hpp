
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less_equal.hpp" header
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

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
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
kKBw0ri1lG0GC23owsevWSDzYiWkLslsVOSX/owYNga8c6lo4yjkBwJam2hLSSA6SqtR4J59jz8sZTasb0RNhZZ02TjGpsvjVj9FqzYCoO+hO7ob4bYGlqZt9ZL3b/FP8AFv+R/dqENvdlmaUe+z+I4c/fl/X1Em30nd7vuO4NU65sV5LEAJUsulnlyunz8RcUIvIsKPbT8WeV6aqrYTaPa4xwqEz165vMoNvWkxlF1k8+/Jwr+34/3idfMIoieW1JshejKwqrrawDqUbtDlt1Vkx39vDAcnFr//CVOEdEx9DWxUm8p/GG1kUmh2YqjjR/iKe2BdffE5ED1xvaKbcw1Mz5uTy7j3Vvr5VlFPfw80FSOHrRm4Z9ujkrOjPbKRDj8Sj+FkGq8DpgbqthYNNY6+ZSh0j+/oCnCV3c7+QoiZHExvxi3tThP9YOedXdQTzpcvjVjiNHmW8WYoxOsnim5tsH6G57mKCyIMRMUhe+GlWqebH9kEmpwQdNE6zAsjhGSGio9maRat8+a9Ik3tgkNg3RhkcTqVXpH+Vbpc5RtEjvvxoRth3vUDCA==
*/