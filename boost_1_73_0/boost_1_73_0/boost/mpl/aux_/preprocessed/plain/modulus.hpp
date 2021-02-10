
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
zUVqUbs1x9uKfoRbP99Y+Otd+PH722g7xn0iDHOj5jJnejHYHWwn1Md0UrDKk9ZaWZWpMiGn5xdjwCEG5HI4uoCz6fgypk8POwnI9HiSQjqO6R+FAQEnw3QYkM/Xo9Qpz5qCzutSMdzTY1wzp4wprli8FruoEg88P4JnVYJ5oiiGX/yFxrDffxfsUMNdt+T08u8jCbam3lG2ZxfwUraVunUMmkmDxYanMlOo8LcxfLgRWPhWoVyatkqiy+tZorw7/RccfbDtavc2ztul93e13pXXy1p/IkytjLDNknnZdBJ01GTtVbCrsv+/6H9R7+e0pO+OdXmhNFrJWrT+sfQbUEsDBAoAAAAIAC1nSlJMk8pT8gIAAIMHAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjQ3VVQFAAG2SCRgnVVtb9owEP5uKf/hRFWpnRYcWDdK6qKytmxIZaCRVZr2IpnkKO4SO4pNVzbtv89OoKBprHRWJCe+5158z92FGdQm5ho7hAk5VXb7hovvqkh0h/QH3RHpjkaX7y7I4MNV1B9130eE0TWC0UqJ7JE9GGNxh4WvRYKEFZinCwdYvpSI81SgNEtEXH5YiC71OkRkPLcKq09gkmdYRQFVFJDNUyNyXhiYayFv
*/