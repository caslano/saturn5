
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
ZhXa7IyiyEfQsvAmLhIXpLbXBPPgz/BU2tWGsIxWfp+1h+zsfN2UTvdazbTpEWjU36bCkxkAoc27oZnwTTQ6wChTQk4aYt3KS1KCZOvfnRwmitHxbeY16Y37Tj3vRO+8XPyA9H1N2zTausbgVLkuTCq4Blx8LHJHyIS9uk3sfJD6U6zYhPyVYGqBRmS4kZ8FqagF29z4Fsl3tAmNN0bFao3Iqv5VfmR6uHRIsDVIZKC1vmZ6JFEgJmWuAqchMYXd7a/EGjhKMtES0QegsTXmaCYsJX4Hs/M12WNjVe2xZBi2q5HquDetvV+WOIKPwOf5DXW0qL2VG4xuVEb9iJ1+v5u8G70XtheDdJmuXwS1SOSmwY3UIr+54SuwbMgXqJ+WkJTNkxJoG9fsMRbsCabePPOhf/14Ns0nw/bj1BXlWh3K7lvNIPbHaBZCfb3665qm9mzqAetS402AovQkzMcrkagMa4IIuq8vPnCjwRHdqaQNy132XXBd+pa7ddhO2kz3rDnP5muAeteAnWxbOjutOnnzWMvSuqoDxdO0nGIi8KSF2Z/WBuiSObNoFU871RD4G0hdk10UNxmPxrJvs8DbglWzHMnbUi3HSbmTwWLW0jDeRSTHNJpJ0xiWj1YcceRWfTxGNyL9pdlGPtk2gaaC//q7fQZw4zwUUX3Q2UgQBsdcsDt2ci3gyEaYdV8+yYKBXew78C0GOzZINRzp
*/