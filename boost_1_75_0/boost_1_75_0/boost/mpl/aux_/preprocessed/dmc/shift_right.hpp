
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
iUQ2N3KIH796uuQTxzjxkKLh4MGmta8zby2Qf8CT1FuNYNTzcnOMfU+m5CC9+FiZfFzEfuGghzTnT4+y3BPbCdIMvTl934zYC+U4kbrUxu3ERjr9hTVJn/ylni4Eo7XYFDqR1OnvZiraoLPLCQVj+36K5rS6aQuuRCK1cldV6UxC37E5IrmMMstAZ+baUhFcuSvhVMHUg2fCX5ZdXl6lnam9EG7UIK5AtzNSLn4q2VYCDjuskjFxoe/6U2rx5a4l6bJltRXaVO7Oae25GyrSPazm6dZXZqJHihNTPfuq6cDyorzxQD4/0ryRr51NpNlIfba6bDiqxsDOcd30pnvDnD+rC9g9ojK7FdO7UqemfhY5nzEU3xdDPtACQpqLcQQv0vQRvGvcSwcdwg1I89JhXwUFqD3l1r+w+TPXW9h7pQ18PgdPjL5Sw9xKq2muPXTxTbASadDGC9mPK1S8BzNuseWV+gU7cbHHLLnJwM3KzMXV2KPs9HxshaX88sL7TSod07e5G1+FKlH9PavfBHeuvvNflAauuovR7UFAO6TCjOZP/hapUEuyBIoMV+/62EaVSZ9s82MGy9C35tgQQBL2VcyqWlB4z67n3513BpyPAdazutF7KqOMu6Byzzcmj7dx1+Otkt3ZYsFHoULzKgZPQ8+vo4VcnsIdCqM88GQgh7mbE2WyCHqP7oXavaUIz25IZrwO6GBIjKKFn5vv
*/