
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply.hpp" header
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
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
tFXEa3YPjpKhMPZNe+baPJjTg0vy+Pmy3//0Udsm7/6RN9W+OY1zI69fjgfEPCqfN8UeiRby/sD1eSqddrXeKCa/V6eQLwfF/tFUXTw49ulnCI+FJz1IJ567h0Qeat+UR4eGTF62xPtDLi9b4vNCLi9bHveOuX62UBiD5KGjAc19xxaW++fz7BXEv6T4vP4FZf17en7I8Ht6QaDrseOFihWrwdysF9xvKMUxvn1Ygunf6ouE87bUdf7duzjQzfyUxprJzI0pL1G8SD/SQvVlOGYYzDJjY3PND1nUq6Xr862u5XNRr0Z6+mRc9PD1eNpTXO9He3r4dm6BG/K9HPu98ZOxmNOQFW0dCc+y9Xly9ixPe5BZ7Dki7UFGsWdFL09enchwr5U9PPwpgD1Hpj08Cg3PUT09ckbc0WmPGbOcLB6QlMfHpD3uTLRjY+7m5lRi5r4Nv0UYTbUxI4bF0tti6ISurfqck4Z6OR6wiXYja9an1jURgPXV1ufrNhvWV1+Pj75boi1mgW81+l0TgT7VMh+KDGzgu9qkz6m4bTtdlWA57tcQhnaAfZxFdys48yIyuG61cG9e85TSi0347N6y06JTXSOA+DV9hqaDMfEEKwK29WvG5zpfXZyOFw+Ge/g3VVvrHQ4v97RsGonHtCj2dEKPmeblnhvwdEPPjPmmRzlvaj7SvUZ5TNZSftm6eULMqDrR+HfMuAoh3HXCi2yuzBRLmJsdSvOJwop2Qvlzkq/NVPOc92IWnaNf7XZWUeXh+7wt5DP7uzOzT46ZySHCdM+3e7yd2/fYO7Q+nlX0GuV3CsMsAs6rd/l6d4YIxreFmfwLU4H1yJEHKUEY7425pAbxPkU8mMVCkaA8f59jlSUL5s+itLzfanPsK5fDOVV0/col9gHH8NWdFoZj3DrJKuWF/Xy/Dwk32Ur5RGF+ONYrjTUYq06wnAuEwvyoxwuM9ceRvk+xYMnNR/i45qvrExwbnHssbE3Q6+A1yJojNmLB2LX17F/pHxsbpVmbti90WsCWl0aH5q+syP7KwgeHFti58cw+EzHp750eMRlb+ayw0jAd+y1zdT8XMYnL5yMmc3XP8Fix+HasNMzhEv9Cksva+S8muYR/pubLzWzaEX++7Jdi7t7JZ0VM5st+WRhO5u0fHsTpvNiLh3xnr8en57t+ZX0+9EW/uh6P7mN/TXyjJTNuUnHzm/leX0/ySVRvrJdOefR66SSX+ZbnJnme2TpxnuNUrUuDqn6eHzGpn9+MmNzzWwEblYRT/l0Qc51w9xz9dtInde7CJJc6950kl+fKd9Nc9kf2eVBxOYyLenmwl/PFPbg+1+kS8ZjnNnfjG+MUj2I7IZrfQuuyPd8s+FDLEdalngeWYlJNJ2tin10K67KkL58296pVZzDGnvJ0Zb+AHzruuruNiUatar8nXx5we8bPj3y9ndUaM41M1j9f0YPzeCWH8WPfI1MfEcaVMc9UEniNdsLTRj7+1DFKlyny1jQcNhoUxlXiQyZTydJ7+mrFzMwG8l8jWvG6H8zUevRrfeadPXidz9zZUNf7+nK9zvsGYeh1ctp+5nSuO5w6yZwc/dkbla87w2HeJBp6qKz/3Ok4BQxh/MLp8o662WnU5pGt3Ee8xWMSJ9tWfulzzKCuFrNyTdJlnd6tni8qfz6vOPagdLF+O+BoHLx+2zHZU+Y2p8mcjtudxmtfcB4h3f8OYbn9ucw7JjG/0+O6fDjsu4TLMdlgv/UZ6iazuz3mPz/u0SzON7fv+r2ej6LO67ydTtfy+L2v6cZG/AHHpR1zRWb+oObTM1OZKwqsAXfc/2b+kOidVmWsbP4bo0c80vCw4+hio+78nvT4i6o=
*/