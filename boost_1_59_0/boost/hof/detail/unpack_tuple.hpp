/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    unpack_tuple.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_TUPLE_HPP
#define BOOST_HOF_GUARD_UNPACK_TUPLE_HPP

#include <boost/hof/unpack_sequence.hpp>
#include <boost/hof/returns.hpp>
#include <boost/hof/detail/forward.hpp>
#include <boost/hof/detail/seq.hpp>
#include <tuple>
#include <array>

namespace boost { namespace hof {

namespace detail {

template<class Sequence>
constexpr typename gens<std::tuple_size<Sequence>::value>::type 
make_tuple_gens(const Sequence&)
{
    return {};
}

#if (defined(__GNUC__) && !defined (__clang__) && __GNUC__ == 4 && __GNUC_MINOR__ < 7)

template<std::size_t I, class Tuple>
struct tuple_element_return
: std::tuple_element<I, Tuple>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, Tuple&>
: std::add_lvalue_reference<typename tuple_element_return<I, Tuple>::type>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, Tuple&&>
: std::add_rvalue_reference<typename tuple_element_return<I, Tuple>::type>
{};

template<std::size_t I, class Tuple>
struct tuple_element_return<I, const Tuple>
: std::add_const<typename tuple_element_return<I, Tuple>::type>
{};

template< std::size_t I, class Tuple, class R = typename tuple_element_return<I, Tuple&&>::type >
R tuple_get( Tuple&& t ) 
{ 
    return (R&&)(std::get<I>(boost::hof::forward<Tuple>(t))); 
}
#define BOOST_HOF_UNPACK_TUPLE_GET boost::hof::detail::tuple_get
#else
#define BOOST_HOF_UNPACK_TUPLE_GET std::get

#endif

template<class F, class T, std::size_t ...N>
constexpr auto unpack_tuple(F&& f, T&& t, seq<N...>) BOOST_HOF_RETURNS
(
    f(
        BOOST_HOF_AUTO_FORWARD(BOOST_HOF_UNPACK_TUPLE_GET<N>(BOOST_HOF_AUTO_FORWARD(t)))...
    )
);

struct unpack_tuple_apply
{
    template<class F, class S>
    constexpr static auto apply(F&& f, S&& t) BOOST_HOF_RETURNS
    (
        boost::hof::detail::unpack_tuple(BOOST_HOF_FORWARD(F)(f), BOOST_HOF_FORWARD(S)(t), boost::hof::detail::make_tuple_gens(t))
    );
};

}

template<class... Ts>
struct unpack_sequence<std::tuple<Ts...>>
: detail::unpack_tuple_apply
{};

template<class T, class U>
struct unpack_sequence<std::pair<T, U>>
: detail::unpack_tuple_apply
{};

template<class T, std::size_t N>
struct unpack_sequence<std::array<T, N>>
: detail::unpack_tuple_apply
{};

}} // namespace boost::hof

#endif

/* unpack_tuple.hpp
B18CmSIPIwdXobJzsCI0sfq6kC9kD1MyQzbPU0HJdXoycq/CiQXpxh+a7xqP62nmidjaRUsYXLaHIF2c+3gq/w+Byq2wpEUAgENLvb0NeFPHlTCsP+xrI7gCDAgwIIgSHEyCgp3EIAck/4rEEBnbshPAsF3C6qVsywuScRJDTGQ5kmZF07cpm3a76bvvs90v/aXZ7uekyTa1bGIbSAiQppWDRCH05xpBAiXxDwT0nnPm6s8mafN8z/ORWLqamTtz5syZc87MOXNGeoPs6LohVBbvmY6DTkov9FLswG3Me07uVyhcOqzKfpFGYQgD4xKzWpfJrO78fBQie8LDA47YwzIu1wmIzlAq4z6gGJXS/RBnVQ8kWVXg42QHRlTjWNUtZZLVnYG82P1JlmX8KPlWSH6rODZQB2ul1/nOWCwH1PEb0rILdDgig7uMAnfZ7nl6g9pt5RNOA2xG1lqcA0CvGbPs4rm0Wbbv/LhZxiuAtdY0El4enNzbH1Iq3DmeN3AolXunb39IpXBX4ERfyTDJlWrsXPW4xvalN6Yb35hzNiktzt9wBwG5ltoNztYU+2HnaM1QXEvnSK5JZyj0rAGtaS9y2aWvlbqwUDnaUX+Isa7dIsw6eco9vN1f9xVOpbQwNveJnRh3EAQoLj1+Qac5ToAclu019s/MOvG5+iTt0hrx2O4/Dz1CL6XX430JXyDS96wCOvwG/vQgqXtKFK4N21fuscPygbg9KPnkfkSF2SrG+GKwsB+vVDy59y5WDkPvrqVXHqmT+gBT4uHyYtBAsFwulhrYs0LGV8l7mT4ptc4Se1LYb/w9YbzYPnT8FpDFyl/gCIre36CLBo2gSuzsv0UEY4dh/m/0ePTww5hmm0bs+DEkyO2cPJ2512R3jj6a1J+unR2mYLo4uhtgXMo/SIxL0HmLaBRU8gW/Hzfi/Z7X5COSgXJDR3er6HCqqa0/3CLFd+UvfkLMjRAxC4TWnYoO4EMKELfubCD/n16BVgbidX4PBsf3eyiOvYcuAvDo6RM1GKnz3DDnv34PhkqDUUjqnG8/mkTVuej4JQV6C2nqXCVSJbkEUwVYobsptSZ5OYWD74+vQNp8QW44fd3Y8WiSmv9x/BtbuEl9M/2A9Wnws0U6dmORbht8/8dneHZArVSn/1Phh0KF5fBvm/x37dYiXYlise75+CLdYfi7Ac+PQloBfCuyspRZGf9U9KlWjkvO0sDfpKwJ/yaxeHq92A7Vq9Qk/6k0GvIoYu+Kh094h1nIdTeoAcPmftdCcqlO+k81LbwPrXHbIoQIdIcO9Y6//489UuoZizvYnopG9rTFrWaPmDzxOHw/Xey5hd97SrxHXXXeuOtRUKQfYeUlwQpTHNtjdcUNzp/gYhQ/mBSsWIXpI0Wn2RVWbgpWCPGRq2xUaojzNdWn8LxWfh7dHFMVxRMKjdssvrrncXZCPPwutFEAFYSoOwsSXeHNyN359hnenaNbmlloI9+O7E31p9wCqoATugVg/50DKq5pZLfEw2NQa//IVXMf1JpQC7sTtdprpTVyrQmglKzfPQ3BolLS89zt6uXsLc385MjGXvjc2Auk1ZuJT2xf7NhKWxKl+NhAOw4VeNf2w2Tv4fU7GkWvQL+f3pAl33H4iHb4LYvovUomJ3aEQtsqEalXsR/Ok4jnUeiLpMRgQ5BEIFG6SyddQo/nK6GP8ArlqtgUKXKTO6ZoIEl81dOXqlU8HCKBpnPPT8qTlwEPG+zSgx8Qc6DbG0EPZH38Yo68YMU0AqSBWoMKAAYs+dNgNJ/GBqTvjMC6nlJ/TadWr0h/D+lBbQE7Vfg+buyc3JyG85NpOD8+KI8kC8XyKadOevBWnB/VwM1OaQ73KQPqlDsvZfMUHPN03CfPE9gstXZpN43W+AMLeKjBs1K5DwO0KalXWs8q/Kmin8qXRddkT7cYkjShcxq/kqkyE1Tj/TH5ea0q7csW17zhIzrX3DvjoI84/FXa+KESpczU8Obx5l6HtIXc7zTp/jvy+xiBsIpXY8ZqZt2uGpfBIeXzKuDHjOEqreCa5pCOzpeTeDOyz1AKHwJFvTsZuqj3TcMvna9Wid+Cr1bls6p7J/YHJmAtHYY+yQZCQ3p4pRGjW/jqjVN2aHCHiw1sCA0JDkic66swzpMOPcjP1uzQNDok/4N4bOVayUicfuauRPAKZEdqmh/eM64ljfJ273xsUe8dbpnhaKyTovAWflc+SO6ezVs2Thw/DLZ3PzuAFhzeq3rePR08TGInAaBsOgkl2KGPtZA4XRp+gPTAXvInkO15uLtLhyp/nguv5MDfZLGrE935KTZy4UBtsF4jbHD04aUr8DHNDh/T18PHjGqM4zUFPmbNlf4Fqg7Qa9BAqXpP9oH1Tgy8j3u1zUVvS+scdKinN7k/XZqwJwImKnCv3u6gc7AVRju7iqfO4o3sun+d4F+n9a/T+dcp/Os07nn+fYotfrcmYaMrgZqvNWDNpb2wlG4z2J3nYG5Ar/N3rLBLps4cOhYNKvDkVQiZXtaESJ/y72n1P+3yf4uC03swfmSw3LVDYZe2/OgKV4pd85jnn3hUdbU9Nsk5cPd9MC2vlJA3KfN08C1s709ly9Q+rbm/zcbcOtDdvMP+Si16B7iWBLVeflueVFWu4DFZ3t3ARv2VurprP5D+VzndSBfT4Q5wnXRHOb9aq1LH2M/5Wzp8q0FggAXNN/EB8kqf59mMFBd2KuMcKQaoESwYmoaUTUbqsp/A9bN2WpW3ItxTQALJ+2nYc41deuKHcs9FbzfhiXfRfS7ZvZqJ3cuj7m2ok/6hDBoA4N5lo6SHYfd+Uca7l5fCgqUs2UW+fquT7injS50G6GIA22qALj6b0cUQ7+LA+C7yMqQz+xl18VvYxaGlKF5Hla5lySEUAb3FD1LbQ1rIlYdzkZxE8UV4bVDtv3Rw2WAe3KMpPK7G46422dD7bB0nuMzzA43Q6YUwo5eCFvIMKLR4oQmszTt/Q9cJw/y/fySO37uLuAc32dkEdKxs2L/hefaoji37jvcy6/w5j6+vdc3zdrfMtjc4pJPFIxQJZwM8F/O3WbWOaV+sdUj1VgC3EU/z9mu+y4N0COXmcNthVq0tumx+yzUFitod0jIrx/nXdewgBQKgdkC5v5O74heGzDdZ2DXbHG2ZUQfcahO0id9HVlB7wfWuWum1N69Q2Kmf4Rp985YMm5vnUp48n+kEJzIUA65XhzsxzrwSuRzG4MpD5jGzBllGPXzMrqS4XG6N97JLOHATRU/L7PY378LNaWdxXZHO4Z4tHbifQB/uxGSV2+D8DGa4Q1r1ACXDmKCHNQxLrJZOcfYGK/6RwrLrax3b/T9D7Vy69zr3HrrcstrTr0J7aKDxVqA6HhCBLWp3qMla4QDWNwdZubQFkAyJwEQAcz33EQY8/ep17qOsk7PbhDyA4shup5E4yEuJgwVQ10LpOXiVVeGB/AI0kQyotvirnKCCvy2tkWG9Df6QHxqTSKSIDuKrndgNcxgx6EQMrkUM1iEG6wmD+w3OJkSXZOTI4twRsfK+nbfUGNTO45EjHNJC7kxVFPee2b9KPh/zasU+tOpk9CIfejFfqgUSgBy8hcch/ZeJsFFtvtH29m2QkQfImEnI0KeqWQzV3CE9BW+iEY4UKppHq+wpJHguFaf7l1iw7zVINTVeDI9gAVaTlzjt359FEPMwLP1BuxLPOwmWjqPuscIeFhY7nkZjR7nK3iA9sZrQgeZ1d66ztb5IN/T3dIq2fY3CZQ1klxp2a0v3t2hK/223xpcVu0vsGqh11kMxvOlqR8EG6aNnchS0T9QgHS0iCdKXZQhUK6urOrrdv8YjZH1ZCiYGKubESw1B15y4e5FzGbzfIH0XigeyoPFSg3vK81AqUBVf/0ipwfUJe7B9tcE93ylQud1p5XICVcoqLDMSyGJi0emObpeJjw9kzvGeduf6lFbaYIjpHkl4b8QmQWLRaXwVYPoto+3KPqXCNdUZqcMWdEUcCWfc97LZGxokw0O4P4NZ/oXStRUKfr59M+tFmjHBwPzbehyY4l7PjUdb5ju/R5Ucp3JC/3Ol8hnbNx7lN3OnXtshv+b00RvfWUHS38YnKQx4UbdULRcZT+8UDQQozNtNnOMVVyMGz0GCQmpHLjGrCX7NJmIXO37MnVZ0eMyjBxXvUZzdcR5QB3jwgnazwjWHoVu1LN/S6ANWW2cagvULlRvkGa7D00A70R1eWw0q3zxgRrO98ZYZjcBv65cD14bv/76H6B7qFnFi1QHrXUnOBFqHtAseoMhRM+k+m9ENhM+9x9ZxAnf+73qcm777CCFGfqwQ8leuS04Az6WCBD4AOoCmlK4ExGgmFP2hpBG6vuwp+LgHZ/y9TfCx3AUfJgzlY8AD7vBXgBcQw1++2HGNoygPUfT9z2QUmW+IHR8g349xZ5P2fTiPaDtpk7HGcyMubya9BYhLYowuQq5zsAH2vlQJXQ1WZKuQv5YCDt7/JB6vxmlqAllR8Gk8Dl8h0rSWeYd9m4wzXPN3KKGC2cB1cu5FgyHg/A4AaecyLldgPKXuUVDxpaWfyosZYl1GQM/cGkRPQW/RGZxndQ1Q91s3qYlmrsyllf3oEV7W+d+E6vkmQnVpkvakd+QCSX5bkkZ/TeikAMje1IC4tuFq0NNmbNJgzzAkPYZ6N+FVw/eVw8cKK3wUoRArVrRNdYapxR8vp/lBcgcgXHZDRnk16/W3GZcF8bynBW/Uhea2FoaKTnvPiN/uCWr/lZQih/okuxisWJ7r30khkfTSvJVcyTxZdNR7Bu+Q2o9LkTwg4Ovoe0f7+EamKQk6lSTPeOWFb8HSXgqWx80DULunXxPULKWwSSf91Z9Zzcfp8rq3gLwKoGcwRK6WzPXNF8uzV5fiWgbGzAIj+KOluLzJW0ZJNUY8VrcEfkB9FsAz6s4wh2Y34vxaRvqLsRGIwLWU6y8Vxnpoc0wPdZfAouU6LKWg3ZXQjBnymkJjAqZi9ipILwXiOxka04Wuw5oMyqwJwFhB3kOQtxp+W4DUrK7SHbkyWb5UCFDlQhds0KRyKS3KinH6xmFmX26ZgaT0FJTB7w/vTkCkB1g1JTKv3G9DokOeVNiPMhidU0Czyy9hy10LgUPM855pmV0H034F1IPf372bOo/NoF8n4H6tH77dxzAeD8D0I65mAs7vTwhOvmjTYeegEzN43Ap7aEgHCzbE+nzIXSBZCUAtXlIo07JyLdJyyYR4KWLXwUIyNXWiMZuOkgptU0NDavHwwQHSoWMi6xzgiq2nOzskqeuCTUpQSn/6AEZJwauh+oBXdt7Jz8u9DOt4dhAv6LNCB/xU5gq/+rdPoRymYufEjm/KGq7zATr/eZxWI0Xd/jfR5nHtx3xV8qNUrYYtUG0nVot0tIKq/SRRrYpXa0lvWaQio4kial5VR/eTc9khLFMGoxy7H8t8liijCXTeQWU2uqqGq3ap3Hexzrfp0nHsPu+7J5QNuPF34t2G/oOop8dWsENUipDkP0Q5pMHH9Owg5RyinIOUc+g3SU2an3710wXl/oPt6VsPMr+poUAtjqLTb2q4ho/mRAwruskzmtVI20Xk7O3HeFUuuijQgpe+wrcNL8uFbzrAhdFskaPAn4nuygs+qsLwgJuAe4ldX53M3lkrdjwJNcEX3oJS+C6bHCz1yncRGVy7WX2pBUpvC11Wm09hcFu0PkLtTtHzS7JslBpZD1r4xcPviIffwrgq6l5z2GVgN9g7bBDGll2BhdhxjEjJF2NtdDWrXl1PJ8EM6qg6ZP4t1rx7YGg7XbFaajGHgOtsA/amg25DU+shPRBuv6DsvqAqOvqKZulxFj4VE7vyC9+LsROeC+J7Fya/5x12U1R63zQrxxrK1dMxtecjDdsEYEJ/ALTQ7i7PLc0QmcsmYytyd3mz2Gls9s0sjnZo+zQdl8bW1a+oseFQTIUtnzzP21aPbzsro23V+Laz5BuVqHRs7xcBkS0DsaeWA5D9SjYHQJ3qunJ889mp5pXrMxp/3XMLry4HHu7TsTbK2MqUMAhO9rvC3wYrVLQLvXmjXxlYO7l9DDjE0d0zgBc3EVMY2OJ/WNPsOVLTi0nIL/iMeBikMKbeZj/sq+ilWYdyMR9Z+/uXKHqCEdWvM7LWBJxgwV18rdtp5Lz1S62aaukl7ZaNzRnrS0Nqvyqf+OxoFhJ9MUK2DGSxFtdEU2zwMbUCPkS8B0anEMkFMG70bl20WAdy0TMq7p0qdrV3LCJ/kjb4ctodsCzA8/eeG4JrhueGDjRnkwOFetYSzk46l+KKNNZCFWTvnS12+b5HFQRfgC+erYw1OgV4K1adVk2kAav59V1p1ahiy9MKvEYFXkovoIlNdb5Ayc/xZBSpIE9nOXdRqpUDBeq/BQmMr7A1rvmw0hw+onPPxOCJnlGVaxJgyJ0NekyFxYWutxVUh53quHlXoo4K+ayCDXLzcb9ktnMZFfkAitAeKr/ozhYAMRyoAVFLjBUEcIWvE4+tBAjo4Zjv0F18I7nYd3Ar3SJuNPk60X2nVPC9tASNZAc5V32brPnduwWMN3U4FMtJSiM/SQVeo68TZRkLhSS9D1cH8KCDh5n4IHB2DT9n4aqA9bBjSFkSUhaWngPgWdgxoLF5CDaQFyQu2DEFHbmRzqAfNshcBJk1dofvJRSXGMsV8gohfZl0cyge38H94ByS/Y4R/FFvNIGc+cUiEPMT6XkZvHYP0bMpRc+rUJ2RDizCnVEu/Ewd3f2dGGPzZNkcXT9d92Eon6Pzd+HxNfdieevDNb39TUSYsDunj14cjWXzB4FV7XxZ6c4LHLqToka1XxfEb4f8B9GQ8bLKndtPESkw6uzLGvyFm3godl4W8Bde+IUB0V/W4a/X5Dx26AiJMdrwO4hldpQ4O+5artvADr1G9052cjcKO+0CrfjZFW5wBerVEKWcu4OTKYWhkMUhxqI81J4Uif104Qgt3quctDFP6x8LPzEB6/e35i/WfW3BYt0f4TsLvpct4L/XwV8+/J2BdPTSVSrpD/8pMP3OBan0THmrTduP0tMFL6jWD1c7NcAYBGQWOcgnclGZn4xrKq1C9P4Jye85JN+ObtGLxOgQu9BDzSiWCqKXG+0PnCclaGyX+Nz/gw9tRqNKfBbdxdk/I20fuK6woG8iji77BtL8gTGe0kmU/xySd53Y9f0lpKX1EvmLNBl6Qh9pguuzZR+CjeaevTP5+h/qhLTd2acurjf3tFwNrFOE/qTxnBBY36oB14rAOmX7+XNi1ylfpSJ0TlD3gJaB1/SNDC891h5a6FunBJ7SCsypUSpazDeIULO1N9AiupHO47FqihzpOaLzDGj81c4tuE/1z6vlXXvPJZ2MT9lOgchMIhIX6LloEphcQYh0le1QUNQGmC94BOfL8f8FXGjQxhkAo8NNM4BlMsGiS5yvyYuCICCYIlPCPzVxyaD7uTUyCS++QShx1ab9B6gTTRRT18GDSDJBOlOVoyBYfGQRgseLOgABlhb1xkmQloW2E9cmbuOBOf/xH+NxWTl3SGUL5RUPKvU/mJ/iBlybXyZr88vpBVOaNr8ScldJe8hKhZFJ87BTDzzEtwAy90MMnhua5BYqwrwHDS8o0aaj
*/