
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
d3XfApto6teVVqjtlpPJKEfsYr9ho0wppMfO1nPrc6NYHophpjnEY6FQ7WCqb8XxlCyU4XqOTXM2Bc7Mn5FUuBnQBdnIgAK8YoQpZDREDNLJhl0vOuRGnS3UqNxN4MZrO+F820q4NdyLFN6mF1G9sdYHZrvnDYejiF17tmjsqaQTZzw3Wq2kIzDkDHncljuszCbOiBZ5XsQwWj5K5mDNV/9GGMbvRWco1zVL8EhV27Th6DdY1FRVywtyrl5sD9ibczmEETUCJXEcHfYfENHMwTOqxtFXlOTQQbyrJDRKEs8M+8xQaEc1HpBzTfSM8knFA/FUjSLQv4vA8s0I7QwmmOJHxeF3NIydV/foJycVkq0RJgpfMBgNe9wTcRJnWYCRtUaNhPYTEOm6guE1rlZ3TtIEpAEEk9wDMjXTEpq0bZDkT1Jkx44fuQ+IEEc5iPIno0yg4zk45JiXh8E/UNuDWyjIv8n68KnRYKC9m/IV/ow6YBXAKX9FYX0X5X5efkUrh2+qCojc3HtGCYpsPCAPSPOfhzBA4fQzP46+fSFq+BcUXOi+fbkZ+/JPWCf+jzgUjMVIQpM0XgM7fwr8LIeKqL7QDUlFv3h5njxj2AoWoV4IzLwWgRyzTHsDIgdbhU8XXPaE1+iakzuw0Gz+
*/