
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/minus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct minus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< minus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< minus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct minus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct minus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct minus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct minus
    : minus< minus< minus< minus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , minus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct minus< N1,N2,N3,N4,na >

    : minus< minus< minus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct minus< N1,N2,N3,na,na >

    : minus< minus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct minus< N1,N2,na,na,na >
    : minus_impl<
          typename minus_tag<N1>::type
        , typename minus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , minus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, minus)

}}

namespace boost { namespace mpl {
template<>
struct minus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  - BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* minus.hpp
/3Sg1MN7KMxJHSxz6PZi/07ssejDFkC+y3xaPDPE5yUJLR+sL7AFIi7tfWPqPa3QZ13EGN+T5FmA4kbbdJJRh7ENqj6uoCASuUp9Ql881BCQNh8NmNeL3ZVWepd4n4kGipfpNk4dXJKKUqViTu/WXEFtylzvu9ZHMRqIzsxa+PVkQG0Uyhs2Yf1eaXjk3Kp/S04w4+PJuH5ZQnoH6/oAjelhmKw7j3CEQO2KitUh6chBmOvya8GYhfqZndjFMaum3DNToxXB2LJS26N2a/R3vzQexQS9OF6sLcXh72ZBJPid4YVc1AZT4umoHNedyAt3kwdJElixO+gRf+PdFWXs+kj626ZQdMeScGYV8akoV8VxqvcRwR0xfjfOHVGsdeipRm/P+yxoRWxQGjOj/aFu3L6NPu9ovypLiXIP6gfWRXJZK7/Urccfj3Yh4eGyhjEM9qfXWlZG67zHq6+nMDYMmnq/mz3OvizXlKfDRzm6HPlTZZgVRY/pHv2zG7aydcLbZdFqywvZGgiustyEFKn5y0HRWFvOkLT6RvHcydkViqI/2pLFJ+KYSFcnJhj0XPR34WwTPIPpzmfVQ36rA2n7c30JSLyOhPUAXuem24j2oCi/mzOVtfoLq20AXOMt9ADn7fkO6Ou2GkKYBHbdZbp9LnoCJjcoAT4wxEzyzB78wocg/dcBBkAhDQEi2Ll7TbwTvcwAoxiaTAaYBTzP
*/