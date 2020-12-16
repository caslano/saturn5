
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
WIA+6Mhz+WFTbIH+2BLj0B97Yyu8AwMwDQPxEwzCCNG+Go9GHI7BOAFD8D4MxTkYhnMxHBdiBK7CSHwdo7C+aFcdg+1wCsbibGyPS7EDrsGb8E3siLuwEwaJ9tS5GI9LsCuuxm64ERNwG3bHg9gDv8WeeApvRlM7dy9si73F/WtLbcU5WJyTo/hDX/68SPxWuk30gxkqtv/t2BZHYDgmYQwmYwKOxOWYgqU4CmvxnKOxIaaiK47B1ngXRmMa9sW7sQOvPRa74TgcjOl4F47H4eL+yDE4CdNxMmbhFMzBe3AW3ouPYDYuxPtwMd6PL+JUtLfjf/yXijn4AU7DALbTdMzAmTgLZ+GzOBvfwjlYgg/hWXwYbUT/kyH4CK7HebgJ8/AtnI8f4gLchwvxKC7Cs/goOvI5fQx/wcfRwOdqCdbCp7E2PoPO+Cw2x6Xog8uwFS7HNvgctscVuByfxxtoSn8B0/BF/ATzsZkj32UYhKuwC67GkfgKPoFr8CkswJdwLdpxn9ureAeuw3Rcj9PwdZxcm/vzMQc34kzchItwM/6KW/AOvgC24uP4JnJMXrXvzSDZ/8ai/80WrpMck9dKZFRzXP/8f0RSdfb/NzRW+/9PryHGYXIk/xeaxhwqruloEDmodsihax5zqHZ9y5zyVD01p3y4XsU8ZAJ1+jxkMHX6PCSOOn0e0po6fR7SgDp9HnKhbiV5CHX6PCTfoeKYQ/PVOmWdp6h1yjonU6cfc6i3Wqesc6Rap6yzh1qnrLOjgxxzqCpjDq2kVD5mT9VzmuvdF+MsL3HCRnzWxGfPFDGUQzb/z7ES4rEOdsFR2BXfxm54GBMwmv3VHROwBy7HnrgWE3Eb3oyfYS/8FntjAvuzD+ZjX1yD/XA99sdNOAC34y3oLsZECMJbcRYOwsdwMK7E23ATDsFdOBTf5ifGaDyOqViL/Tqmin067FfJ3ykyZMiQIUOGDBn/1Phb8v+kuzLurqbr/7aa/J92eaLsenkd4VHTNWiDRf7Pq3NBS1z397+G/H+RnZrv77WtmNduVuuUXPw5tU7JxeeqdaFK3q3WKfn5cLVOyc+7q3VlY6dTF6bURety6UrnKbxqPn0t9yoU6fLnY7r8uaSSMd5LdWO8n6gkdz5VSe58oXzM+awKeTiL/LPvTdg4yVR/vOjR1He//vBi6bQP7upk72tblieXGMQxKY7RPHSlHNPNc9gAG2Ej9EInbItNcA4641F0wQvYVIwR2gyHoiu+jm64GZvjStbBA9eiJxaiF+5EbyxCH/we/fBXbIH25L8tsQ76ozO2wmxsjUcwEJ14P8GYiOHYGyP+xDyK/jJnlCFDhgwZMmTIkCHjuocdJeV65f9JWSMnZKSOG1sNuX8TcvOTJDz+k23IA5NS0oaPyuApzW0Cjpo2AaO49jiIUoMykDKTxKXwsoOpTaA3K96/f+IwsWJlbQKGa7gXIFMUbR/4PPFajuK1TMv18mYdqKn4WsPoVnv11xM5LuNZUVHDlFMuG/ieXZ2ZF1/xXve5t/8zPTpUvb9qdeW4lc9XU/X+rZtsTfU3eY78+b6howJqZI26Mfu7kXvZh+b6/fOP7uw0MvXZnJ/uGfGqd37Nquf6lffDtdYGYL1f7TJz/bu1G20ZFha2rUPNgOjx7l1crfe3PTnJvP3P9gzZ0H1N4ld7no9a2m/Jz9bmEar6PD9X6oebZxDHuDj2C7TzKYg2hBrojA7ogvWxKTZBd2yOvuiDLbA1BqARgzASQ7A9hmE8RmMPbId9MQ4HYkdkvfgsiM8DOor1qoG+Yr0aiPVqiPbYCFewDH0ArzpG16HVjL2PpjH3w8S4+4sr6StoH6vrL6gbm38=
*/