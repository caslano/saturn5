
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
LP7ekpNXMgmJJ4mzG91YvXncH1XiTzN0dN/PpBKeyx43HLxhwfdnFUqbqDKYt+9g/bA1Oe6LYi6YvsJ3ieZoudbUwWoh+/lzXRU7UWz3AUWc1bLlxt2Vh6yiP1uWIIgNyDYKEbOYiMulUUp4A1Sx/ysll++nMVip08o5UXI+vC8ZkxIec8woJlbbl6WgybwqakWa7gFAbqVE8JY6YgXFnkgP3SOUMt0v3I6W+8oLctmeazegccyA4+KW2b/Se5/dz4pL5LrsGmtBtRlHXSeiHal0Ae7YjltOWu5DydmZU0YWKP1lMXv+XKwzoRCVd8sf5+3TYTjuulsQittn3PkO+vkVAworA+Vff0Vu81MTkvPtgdFyNb4WKQD/znEDqyr/N3q08UKOIxs9b8wVRbyOZTOqzVB0F5racjYBmuXZwdU3d+pB5JVkwp++DTwaHvzhaV4uKHdYmQ6ryM+jW4Dr/amQbvu1bhbNNuXlm9jX3CNmYEZe6eHR67sSNQjSHf7m0DS0HKrL2gw4qj/ChH6C2fulvoT3yoKUjMudZ7fnthfEZ8UXwPPgBe9G7+ev57P6q3hbZcbz9Ucr7iNc1AigUiRi24TuhZsM8Si4Y35NeRkS2wN6D5lbsQiAhYmgOaRcPQfFHmqQzaj9uOn39RVz2XvcYfAVe8D86y4SoQlIjXp0ftwCHgYNrBroHPrZOb79K3YLV2b6aSppvgID
*/