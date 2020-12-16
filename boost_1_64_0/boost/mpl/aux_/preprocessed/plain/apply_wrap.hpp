
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
BW9lfDBaGbeH19WEfwl1530vTMEoLMFdRAVRTRSO4zXL7Bdr6zMOwlw+t5kI4/VejMVKPEUU8XobEXgd+xWGo7Fv+T3GFTMui9db8TTv92EV0W4u6/56piXGE1bep+BRyi/BBbwvw0LcTFTyejdWEO1uYNqxPpajfP+8H/G1BBHjiUVEMbGN2PuIp7/aM3iG3/f8v9r+X55coDT+f3vbv6XhPP8CaVPvx+ZYjudalcaa+ltf+XkfEROrnHtPTS6Q3/j+df7Gb9riiVNMq1w6nqi3I72ZZ47SaDT87u8zQB2n/c4Pb6u3K/U2WK76u3+otE3CpR2+wcvW/l+BPlbG/2hrE7GemEVcXlZifG6S1DcQG3avPFtdpR5a+9K57v563bXcfV8+k5uetTgvWe7xJbn7iaxz9X6D8p5mjkMuP/9OU0dv25xqYtaWMDt/734bw3Ub4Oy3PUzaGCb5B2ZtDLP8A7O2n1kbz6wNaZZXYd6GXKm2kaIeWBU27WR6zMnC635qM/OacPfbkMeV7W+R7558J8sIZf9lc6pDvPzmXowBmIAdMRmnYgomYyqm41LMwzS8DtNxM2biy7gMP8Fs/AJz0Y8y8zAYl2NfLMAheCUOxxU4Eq/C+bgSL8MipTxcjVdgMW7GtXgbrsMn8Fp8ETdiOZag2nZsIt9l+Y6z/Gr7qh8qQydp8w3EIAzBnjgIh+NgDEcrTsSLcS4OxRQchpuaUA6+gyPwOxyJ3+Mo/BVHow/7wRhsgeHYCsfiIByHoRiBY3E8XoJq2xEn4xyMwsvwUnwEp+ErGI0HcDpW4Qz8FmfhMZyNg7xod+EkjMUpOA+zcT4ux8twBS7EMswq87VsIfYSlcRpImj1b29frR/5/9PG+l9rXyX+gdpYZu2r4Ed9/6/aWFaWN+ZRT1vKM3gGz+AZ/tuH3+H8v7RtG6cPIEA5/y99AIHy23ot4SW5zn78gA75zqEPIDk7KanB543PN7SZadtqZa2XsiLk3OIYRT5b6VhWRtIV9Z9PbCn9BlpZTtcVWOUc9GHp2/gML+Sz4TUOZXEuelBcQlJ2bsPubdC0xZFjtv6N7GyXy6v1G8ynFvb5tmGcv4zL4sRy6pIMtgSfNfQVMJ7uAL1/gHHq9MrINvozC+RzdBvIfE/IeNvJ/ThO5+rrRsqja4Lr2xl3SD5LXdVzuKk5cYl5WY7nvZmBOt8a9b3UQQrsxPhKx/L02ch59RJWToiX0tZkfavrSr8HwpfUhwnU7WTcVntlW3WSfTCQaME63Xa81raisJy8pOyG5zC42jaXUarMR63HOKlHlOxwnaUeFxGtmL7CtB5xWXmLlyYVuJFT4ao+kXwfZUYO6+Wo1CdHvi+ZUh/LP2vVRyrSsO9NQ+ph34emt2AcY+T7pfUdZkmeQICsq5ZEa+ZZWqtucRyEzuzYYc8d6kYoM4lLzYhLZ2UYc03y5RkareR7fiG2ZR5ltnqwp7NEaakJcSxDXEp8Topsq4B6vuelJ5y/57J+mI9xnR3npK3MVvue53nbxsWp3xp5Bojep+lw7470ROVT8h106jeUe4DwGcozfNf5d3Ui43o4cJ5FHXrIeuiK17ahr+mkuh4khUw91MUlp+bzfZX+0QZsE+djmZ/JseyU4ZjBcYT5cyzTj1tx8UtTEw1HDNnHtH9nEurNuCrDfGpNJMeZQrb7/vP4DO//oi6jvo6+tNWNiSzasWygNo7O4Xj9/ilfyrIZj0tD7fuWJCQlyfcvnmhvVTqLHNbpEvZxJq8/h6n2+nTMxclITVSP0/5yjxPbErPz0p2d6JTHxH5k6Dc26wc269c1619tvOusTPo/TfpXzfq3zfrDzfqN3e/3Pts=
*/