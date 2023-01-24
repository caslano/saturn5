
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
XM4SfsHWZu4ni9vXxEKF+wQ3BLVivm32hiCu2XoCSezqsY5/uAhZavcjGspICFkqsWLAEEJ7ZQDWr9uN4NbpTHNrp6MTVPMNDfdU7tR0Zo65+IpLblS1yJ+TNav0RBv+FUNbHGflwBeoDOCPelRjbFaregrUgBmkTrn3CMOTezRp5RoSjLt7XDRpEJYx5kuBv+d9mYv1jt2FJjhUJwEG4L6KG9C8zTfbzQ5GhXp7ourRUwXfvgJZsC52/lH9we1ZPfwl2R3KL/tC+kU6/+wMPauwtDmP4ugpXfbLw7kbk2O4L9gRbvY8cRuyH4BwD+8AgwSJe6nJMb1F1HudMKBworNPHtOs2ghz5ZxgKcRNofhXUHONc37JS9OoeOTRVzq4oZWNeUMAjc3I1YKu6tO15u2pw8sDaLaF/jLCMiBU9kXOWtqTDHa8Ye8O3ab2EX+u/4X74/n8Bw4/2+BLwsf7e+8BRD6uKPVD4I7Dg97DE60zmahuBKR8W2L/SDyE1OXAOBBB1IF/ju4l8+M2qGWCFEE7dMoF/zt6s18+E9L/z+Cw9/+J3h//h1ht75pBsYg6zVK/qZ4h208X37vj3Sct/HHgrJI+rl7Kh4kkKeMkwF5Lehf03FCjGWJFph9nHFvzzi1nmZWqDwOZJ2bRFnlPTg/dEQQ1fiqXx2iW0KsAz/PF6QsonPk85WZ2TChF1zNkEb8SQdve8s0R/Jv/
*/