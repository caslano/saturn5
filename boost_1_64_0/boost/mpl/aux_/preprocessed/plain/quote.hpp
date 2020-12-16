
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
L/rCs9zL969xyxSjQnSOUUbeyK/9mspjjT33PY8pH7cxuLYoDznKwzxSPcqx5AtnHubnZ5ydmTE0M4NKHsB7i5c6rvcSjp+zLUhhVcvxVLxTKZj5ae7nYq5OqLv1PrCOVJ/4Usq8xmdeaMJUziMCrOsNLDGnsRFXOzXlI886HporH1ts9dIad1WN49dM192mpIbGNfFLS9sT+7U3gOuuWb66ZqRa4jyk8d4c7TGMdQnKLaaranq2S4k0yvJLR/uQXxcT9c0Vk8aqo81IeQyqbyeJwT5m2nBet5oYXOOEcTyz0/PM8Q0ZKC2YscqSNDaYdZ/LuYViH5tspHGe+tqn+W4e/D69jUc2RDGE1/aM4TgHosQZw/CkcUmTBo9JHjd4bNLZzsn+g8n7xEj3+f5nRHjO938cw3yOj+arXcofN26a9/Y/p649z6kaT+2PGjfN+/howbcj+q3HU+u0zHg+ddCIei/sPZi1u+9b6188/Nkbf9y4aeXjuOj7lL5n5drGcemu9iw9MAJ7YSz2xhbYB8/EvtgJ+2ESDsDzcCCej4OwAM/CBTgEV2EirsUkvBmH4b04HB/HEfgEjsQXcRTuwLFYghPwCJ6Nx3EyfoPnONsR6bsSNlL+vM2XuYGUq/UWaz3rvMgL1A5mIdbERdgQF+MZuARb4UXYDZdiH7wYB+MyTMRLcCQu1zhbl+I0XIGzcSVm4eW4EK9w5UPfV4i5gnxcRYrXejdpPWv7sXN1PKdjBJ6HMXg+dsYLsAcmYy9MxSk4C6diOl6AczANM3EpzsPrcT7egDnomP+1TPGsVTzW+V+jFU8TxRODTTAWW2JTHIrNcRS2wHHYCmdha8zENpiNZ2IBtsVl2B5XYQfF11FxhVfW9wR9fyAuc77pqhimca4a4Z91fB/F1vgYdsTHsTtuwSH4DE7EZ/F8fA5n4vOYjy/gGnwRb8KXcTNuwxJ8Bf+Gr+MhfENx7sC6BLkTG+AubIe7sQu+jWPxHZyE+7AQ38WrcD/ejQdwEx7E+/B9fBo/wL9hKe7Hj/Bf+AnWoSyOYgP8DOPxc+yJX+JY/Arn4THMxW9wCX6LG/AE3o4/4BY8iXvxJzyAVYzxqPA0/BmrY9Mqmncc62JfPB2nYj08FyNwPkbi1RiF12JjvA9jcBvG4qvYDN/EFvgutsR/YSv8HNugxi3UdxfKjJRrG7ews8Y9iscI7IYx2Ae7YF8ci/1wPJ6F83EI5mMirsGhuBaH4y04AjfiSHwAR+HjOAa343jcg/b5xKeF6XsK5pBybeNYXqPz6zrsjtdjX1yNA3ENzsS1OBvX4Ty80TmPtb5n4N3avnUe61t0ntyOXfAOHIt34kS8C3PxHrwaN+k8vA/X4f3O65u+F2Azn9c3jc+k9WL8rMfnaZ/zBsdZ1ivSepF+1iuxrFdqbY+qfKwLYlyo37vtpHWcqIIWtf5rxopa3aJWQO0svY8X9fuNFfXfNk5UBWNEBTQ+1H/i2FC/57hQ/0ljQgU6HlSw7UGDHQvqkRa1frPxoIrZ9lFSREvqDSmLtI60lVRKqtqqVlgr0ghSLmkDaSvpUKtQ29HQElpCy//n8vvc/8/LOxX3/88Iq1M/ih+WFtUzfp5V52SjE3B+Tjbfncy/N+Lv4Q2sfzd+2S0w/my2HyiMJAbHHFNqP5Co35sHkwbx96KPzd+bkyZNSs7KoYextkQs/ufdcvx+XFQp+N8Xvf9e6+v3YF+/m/r6fdTX75Gn7vfFYH9X9v47uq/fKX3/Dp1s/m764xtd3uvRt9beO1+N+abWzIm3+fq92ffv6OXjwev4Y6L6u1nHg/9Ov/OdxDPwR+yEP+EArKRxuyvjA6xYMoLPoCQ=
*/