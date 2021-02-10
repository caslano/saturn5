
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N2)::value >
             BOOST_MPL_AUX_VALUE_WKND(N1)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* less.hpp
Gd5CzS1spGzhyNbGHREW/PpUXK+6jvcoYumv0yTNCrjfz+/3Z6fnr8/oqzn1YR1IrOuNM8Jf/jZPMuCtaXeNGWxE0o95Dmjxg/zDm07LczSK6LdPERll9/M9Kb6nCawikq9+JIAXi0iWFFmobm5XRYTbDhsYffJJD8/8L1BLAwQKAAAACAAtZ0pSz/xWz/4AAAB5AQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDU5N1VUBQABtkgkYEVQ0UrEMBB8D9w/LHfco+ZJxCMUpZ4oSFuuVfFJcu2WBttsSeJp/95tq9enZHZmZ4ZVAX0otcdIKGNr4ucTh29ylY/EQ5GJOE2SfVx8pMnzu1ByIZWc9WIDcWvQhgtvKhSqnADzHt0JXSTq0LP4H6lA1EaiNcerm2uezxCU1R1OiVCStVgGINsOQH0wZJmXs4D9qeu0rSbfnZTbxzQvnrLdllez9FCw5Vkx/v/aiA33fEVn6gEqHTToOqCD0CCMF4BGezgiWlj7hsJaqNOk5b69o0DlWPIl3x9AW7JDR19+JbK7PAducYs/uutbvORgnr7drzh4WVPy7CWXa/8CUEsDBAoAAAAIAC1nSlLJvxreDQIAAIYEAAAeAAkAY3VybC1tYXN0ZXIvdGVz
*/