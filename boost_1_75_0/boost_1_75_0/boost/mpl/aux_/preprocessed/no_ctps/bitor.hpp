
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
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

template<> struct bitor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< integral_c_tag,na >
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

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

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
8eIYqNUtXDAUfBQs6GWAmKL3rfgU+/lqSt68zkkpqTOcixat6+5dDc0X3ZGnbZcCbrhRyBY9Ag+c415fzZuQFRiAqLljHADX+8hFnYBlUpHFrVUhYooYJoKJlvL5nQSSJkueNQd5/A0z/VLa8rNJUdj23k84IREM+O5DPgN8+Z1ad2UuP+vcYcSNaSIGXYUpq1HzUs77mENQYbRkdodYhCQTjOtwHKA8oYzX3For2S5BqmS7y7ZkjQzpHO3/jLj3Q064Hg3eEvOh68/TwAKjx9Y/O1ch1l8cqDQxrJuCK39jFobPYEq72LafS8sMfQ8mUvw86cKq3RMGT334bg9kjmw9mk/AuKoLuXd2e1o85mM1DIHaYtIR51lcAH5r0a1lgHGt9BCtqbfZR5plh39NQQ6ZVzyY5EvwpkXFACvLqxkCDpQKxq7vlCSMaXVjFmcaDF+8Kx+2EeOlhQRurSlAoKokyzy2YqO8lxAlBZIA2heZrFxMdrFYIwuStTHuTpxnRtueOIxBTLKbXKcOg+xD1e3e56PpDaCjBAzkF9tKXhVqnQqpuemEuSvA2PwvWOcdpmr9xWoXvI+e3Mk5ZsUNMab1w1LSqlSO6md6+502GaFTaTnLZB0w+VVsuhyoc8SR7bZR5XoE37Qu5Pu2eWIjUfGUUxTPkhKJx2I9pEk+0SCf9s3CUQGqTUFPtjDZQmWlw3ulEDU7f7m56j2L
*/