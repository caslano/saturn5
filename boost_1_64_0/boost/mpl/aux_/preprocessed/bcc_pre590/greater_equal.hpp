
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
eQhfct2Ox3cn4/WalsQBoe801aHQ4wgnVB7dN4SfIF7s2Il1nB86lubEd6YiQJIRthVqxb6e521o2Z8RWWCbM5kxM+Fd8yKAy0GT3BqasdXWkwvro/GWE3mOc9H4I7b9sbWS+V6TbOFAzC/JZQ8GQ9W8VPRe/ovx/93tJyi3hxd5FgNWz6TQD3A5rYY3drGMhMCC/xkFvTcJ4kJsNFX5gwA4A2iaKcxYC3T9ao+0Pf+sgoho0RXFajGDS6bDZM0wP/g52BL2624Xs7EQYTNFZ5CZxIwW+8i6ejepRGiodrGcj/v3yvrY+iik7ES5NTsj3+DgpvnmqDohR7Ss2xFKmn7svsWj1CZGM1MLwdk45HyMOw6sHgWTB6477/ZWIff4Br3Dvfzlyoh7ickrSGCOS5aAvLIr8we2eD5mGiZVOIEhfoRlP77+lAM+Subek1NSLFkpOfDM873xRVY/eTmbqoPH1cRC8MG178cqz8Uum2QGsrSCUK0Ijv1EVtg4LNoS6hfw8IKxIoGCcE/8YxGmEwNHEjVchg+EEtzKUoKSLbo390Kj++24QDi3dg==
*/