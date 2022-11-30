
// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl

{
    typedef typename T::type type;
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

    {
        typedef typename quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >::type type;
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

    {
        typedef typename quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >::type type;
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

    {
        typedef typename quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >::type type;
    };
};

}}


/* quote.hpp
Fti42vdNQ+vUPEmRH0tKHQAILPfTKT1KUYPnuy1/xbzwsHWed7kyOVq+nzuWJiJTWGhdd/Ru3q8Vvu+y1Vnd/nmsndWD7ywhv1w49wJ0+/0swVn2NWwtw1o2NWjqVtU2q2KnX/nH7ve4BG9y+dg/VQVsTzDA3Lb/fWo9YEKOAvx+y7aHIEmAq/a2J1UFARyOJcSbS7g6K1BfUAMBmRFMSNgyn410CD6kk1h5lDQPLh6dggEsXgAzdjc2NSsVJcuQsTYToyePPQkdEikYnpBi2QCsFSDAJ0ArRMNCS2lGuxIAqKI9KKn9Ho5nMpY6tLkiflzzo4DZTwOWYgWyJyDIIJoJJpItSJSbAokX8eQbx2ikIjvKAVGQDjWGctLlf5ISGugtI8mkDCs2w39MRF5WdRoNo4J5hz2dcAzQ2pR5sNiabTBDIk8qikiygFnYTaVhWlaQKj9SWi+nW0qyFGiqhIH4QsoVc1mmSW9QeIX93Od7lz2gf6Z67rpN/SJWjRxLC/7pEarPoWCDZ5L31RnH+9B9uvv8m+l5Sb2pec/b20Xu49q9c1cK1tXkuObZsGr1cMN6uc3hViHtFDVwrv2Et34+F1IrtwIl1DBASBeKixkPLkvjWQ/t1E49yalbj0DVUFMhXediRnrs35L8ZFjvMJw0+GzPWuKXb48NHrwSBK08V7xW1NJkprJeIAzEwIPJsMhetDSYchtIL04hTho+fEITyIw1uSbaka8jK1sElRER5tHoqcROZg+ybxGmdT4sQo+s9O8w7OE0gZWwb85ZEeBMLRZBWUkJvnAhOwpv/i/kXJSXwJsMTnhy0G6cmGMhPiMlae9EEbYVRJCGqJszp61OzxqM4Is+SvF2PIzwbXyNR63OGa3kKmNXruajjStkTrPuR2gG+fUZxogi2hICNbhx/ne7LMUSF9M3OuDTYuv7t0fD0HDGdVaRW3nZCJM2XAAmbjP4Hk/20uziaRusnJNNTXD75aWYR4/NFrZ87GM4SXcWW0TJlSpPV7S5iqDRGjvWjwxvH2q/HRjTpXAAPLws/M6uYeA05LVNAroUXQB+0Mf5R/fmfo9vWTFWtUobb9LMqkJW4mSFZGtWK4vhhKNksMxpugXNkKLhPFI+X2CEDIVQR8yplZs7hMWoz7QXTvxRfN1Y22FU9mhoOlYkgOOkmKP9bKKxAFHhoBO2M7ReUqLfMmrbS0GySp7F7inxlcZYbcf0tub8TUa2ic8OadDJ8vL21zuITQ0A/uGTUvLTxbTIIY5L22t97h1GTxCVtZHGIjxEvQL/8dO+Rsx23Q0tNDH8yFCy+kN+DTSHR7lUH2aqglFPZHpjo9sYhMI+4qRtUbpTgCN7/5HSvgS3UBn516brSZFhBMjPa2fuNT3/APkY5V/40eHnx5luGjWBY8j14GdOdz2aUnJIyrLnbA5yEF0zHZ2PSgfjA5+7JkOLPqySocSw6vw/29HPB7ppDc8XNdfbrdWm5t1hLtYDAz820QtSwXIQD0QMTnJWlSPVunOXlgkKMPdw2jELEYHzXfgytXqAVqX4V0hoEYr6OFPhjXSVLnDg3AKugwJD8QQNI8bEnVPz1M1CBIjHZ28WlFVtfJZDuTTdhQZpFtOr/LxxDlctb4sGnPhdmPddtoiJYNdIQGfuvLSyvUMzjg+zlrjld0vmst8LeOSuPEWkrMy9hGUllQ7p8EyhNDD3L8Z6xZSaMZDKo1PpIoKgHNtJntmxmQjs16I/rsSNbX/l9vBzXjcs/YGE6LJWekvyiYWsm/ZaJA5PukCa21SAPoDcQTZ8+yFzJKwoUGfjSZqTDcKJmNiM1MO4xjLrd75I8ZW9BGISNWo7yadsa1SV2F62gwWBno5Vca+A0tPoe27sNiayHwnBC0VCM0ut24Y1InOtXEdK26okUB0+Kp9rINUYrxDhNAummTXMN4kk3+9DfINAudwiyp2ODA/6sZvH6vynNFIUukLLuzUc2/XMQO5KK0kH30AuGk+WFhgDLDInqTzaKCFhwcORsXEUIedZJPTVIRLYn9jMulwHfGyBPThH+RHYrmIYO4IkqwZG7V7jwoqCG3JcoRADUEKQlj9nPhaMam5XW2EevUGQb1RY89zVpHVT7GdvZ4QdfVa8TaW78drIeTgRuUhjnacmCGJ6lf5dvfzJY9gaFxzhhHnoqQnZd4C5St4kUFcL1d7YLy7UtodKpX5Fwvq7pz/iIOzqtRa3ph10RtuXnTNJD2aevtE93K9kxJQLulq1EOM11VFoF6E468Vh67yEBr54++G1hWFTy9KOTRJdybMh0pfit4r6Cayup68TegSjqrDqbMAV9w6LsiylHn79XBvZv+zyHuJcWIkYuuUtRHZzOAW2mnt1qpWan2hLrFCK2X1u57z/owdb7pGl3+yPYMrGIj7AJkZTARMiSqbNHASBUiJVkD1AoAFoBggA9Av4F8gv0F9gv8B/QfyC/AX1C/oXzC/YX3C/4H8h/EL8hfQL+RfKL9RfaL/Qf2H8wvyF9Qv7F84v3F94v/B/Efwi/EX0i/gXyS/SX2S/yH9R/KL8RfXrzy/qXzS/aH/R/aL/xfCL8RfTL+ZfLL9Yf7H9Yv/F8YvzF9cv7l88v3h/8f3i/yXwS/CX0C/hXyK/RH+J/RL/JfFL8pfUL+lfMr9kf8n9kv+l8Evxl9Iv5V8qv1R/qf1S/6XxS/OX1i/tXzq/dH/p/dL/ZfDL8JfRL+NfJr9Mf5n9Mv9l8cvyl9Wvv7+sf9n8sv1l98v+l8Mvx19Ov5x/ufxy/eX2y/2Xxy/PX16/vH/5/PL95f8LRoy4nbheSXWi5xHAX4YVG7tlk8lExjpk74oTr50zETcZ68kSuSWo5dJ+8bI3bvcaYrVPhjRl9JFDYpOQgPqvqg73vNr+KzJRYMeC6TaGhubII407Vytb6jHEkX7z41/Tco7VTTrdCHiC45DlgBimQLwpKMiMlLDjxdOlJe71NPWYM3iHJbXp/YkwMQhQ7i35MeSfEm8bUx2bMlMNm0Y2S2y66EifcbmP5LWElzSNxJfTL84Nh5R96pW1pQ8XtJMud9bHENvnYzDHQtaOV7yd2imird0Ttu4HsFTp7b4P5aXDnTzROB8GGKIwLrpPidVpVPJuZVOl6z2JhcZaIScU7D8ePspLqOOlLc3BGebIEHLp0yCy5owasnhAzm8KmsEfG2BIEcUbGNaATVtrt6unZXtjxJcjKwMrBQMPCeYTxFHmrS2OB/eMDaOJnmGD9AN1R7HbdXs8h5B+Uf1H1ho9xBPJkptZoWVcwMKunQe3Xg3WkafmXvfvxA9M1cikJoZ4hnHC8zVUVKilhZULpoJKrejKmCfimJERg4pMo40j2aiR+vDvjHQuNCHrzsQ7ZNvc5OtYwvxbFagvLTbRaywfWLhvNYBTTuLMTKtrNR8rcmbOk6Mp73bV9NVbNT5/7Uu/N/kZjeCY9YyqcSCGtqx+7v24V/mPZrxiiDeFv7XKeS70u+TKEFNyjI+Fht262edMsYiZFYRC5udYCI9iyguCVLiLZlJbzTZhOkX1ZDldiy+Q0rw5Iey/X1Pv+lt6gGBxdVlwDwpptNJG7mYmr1Y1WNYQzB7xzbqgVKrcevwpGtv4euwetK3U/G5J5WreajxhuuOuagjVBM0ac58i1CbvjXTA7ip5cr4GUDsUJIZfc6lsDNpF37CYHZxU7L4q/0WcPR4t8eqptXBEE9/0vspIjZAlLHfGacN7MxvP8sJ3y03k0jX9eAPusmDgIzsDnpqClf/snsM4RyJFmOBuUAVV9H+sDr+Z/UHIusyeB1yGOQdSFRy22+K8j317BDz1mZ/mdo2qpaPsR4c3qlNfDQdfhZGJDArHgmMLwWlnQMtAQqY2ep2JHYVqwPAfCL6SUjQojwFE1ACGCzEGuMnKcwmB+kL+yUbBdEA5q12cZ52FvU6Vx9gojEmD/yRYiEUs8Bj0TLWMrVg4LKff9ztzgI723YHUkNc0GJzlPxeDwe4KearcnDQD4HckPKb1X2lIVT5H7kbhXGzXzMgoLEFeefrZ1EQqfK85ttZRFdW2OeguzFC2CKaiPBRwCu/ScLQ5idTuzCSGjMGE+2PRDgO754rVn3t/w5kAR71+x+hvnxJrZBnPVXoiYxJuqMtWYmwjSXya43ZPtuA+IToeIRoRM6AzcjTBs8+wVCL5EhUIpAn0zUcG6P8Qu8rmCrEYPqClFFcOcV77ZksBGdrdSi/Q45w3cGhM+VBgtVHQ/bF+sk6EX/XpVSIUy1kujmOPX8TsWTSVhTLxJjp3LwBONKGDdIBgOE17u1kUXSShM57Soz1Rcp3mngAocDjkLoLp0Nz2BAP106kzqYpW7fCohKUAS9RUrwZBFWhVDunj/1dC1TH+lY6rI+eeupQj/uF+aI+NGvdSXeHoMOshJEVDPtAlp5MINfPGbD4RLi6dWaymjmLC/SLXUTu9QXZhw8GduEuw5GzLzbk5LyLzWygmbJ5yy9v2qZOLjlARTWOvI5tBU2IgKuZvM7+n/DxsZ5QKtb4eqp2ZzaZjpjTUcBFdbyoDZNiLY+2DP+KLIh6U5bDCrBEqq2Fj7cML84Rcuc1jFPWpDBX6LNck2X6AbdA/uML61dkqywMwRmBFi6s4JJcPKVSj4QwZhsjHW9hzBwy2tEaYam7cyG9WTrmIqi0WFrAZSg77l/Plx/0Xp3pbkQQqEtqeecHkaoeFRRWN5fLOdV7Q+Bohtdvj7HBxh1su7kfuU9bhJ0X9RN20nW6yjPNRwxy8NwDFmbXJ/qBS8iGmmjfu9X9cO+9ixWrZz2CON/FL9CuLV28wnnkrQ6/nxSe8zVo3HG8W4C/AV9+Bw8GJgPVyTuZWQQNLcB7rs2FqXyGqfy/SSy3WPVks1T4SCVl1XLlezeB3HLVRJhc9I3F4D+/35IiQjRKN/pit1+ddbzSH9PSkqJrsVKx5FAVL1wSPqfB8h5oOWc+6GhhMKwoPyU1CEhUSkXAT/1HwtkuiT1QSZGDgi4mHI8lGMnK63wuJsMVlBt+ndTJXDRD6ZzxLUSfZ0qj+XBq1ygj+4F2SN+EXyxJ66OfBQNM35oZffkosHzTTVJia+IZ7EyvyJMEDwOlC6q3FJUvgfKJ6r2W/YzT9b2lXVu/t2BqDIRBBil8Ba1Qr4JHM+t+ZKgL7BJibLWvkDK+n4BIPPA6KXTEH6YXP1oqbS4+T1cWDydXl3Fb2ZlYOK54357eVTqljfd9KNyeXoMFf/By8fcO82SYeLbKg5yVarIi1tShRkcvevIP650wEDItOa+6kfVNWskO5P/kVl1pLg9+QPU9t+AoyrFbGRxNXIJ8r5H9YnhaN1cXex2kiCK2DTzPfBBvCyU5Fgijzryw3LqG/Oo85o4QWPPX/zMGaDnKwp8l904WG9lXrVneHXQ7Do0/o/EmSyV23c/qeVtkpJXonrlaMZ2lYRLlf5NxM/SPkwOcJus7toV3Hw/uNVmATYSOy+1OmxorquLi4sCC96YkrmVbcUKLrWcoQyiYixKMsF0BVEJOSsJFT9rGbdOLg7E6fOpLUQI6a17RxnbsCXUUvNBn23WBT8f1TCL9VqaMrOs+kSqmVuLgz8M+WS0X7/uf68PNEhb15CluyyU8ueYXbeMJyOZIWL/MBpAwERs5dG22RheUbVdINR0Ml/HUgeARWic2plUImTkNzRhU8LDZqE3IAIQwTd/E7h1HHcNdOmkT4sDWpsbgYCggJDhI6A+4xnWJNNZ4+OcZVbh8j42bbUM68azvYiiV/3gxR74o5N5XUDbvLi9EBvdx2yiM07WTrvC5noef5bJM2pThLLtDjXtBN6kenYnWADa8akA/cfdRNYfF0O4Rxxx4448G2wha9htEndmzR43vU6OvG2k05gFOfuiY28ishfGIZR5xQbmd2rAcr2w5W76ErrPL7Suv15saYsZ1tdNRQTyxzQ7yaAHrp0HBrPwI17h+AHyggDbSdfu8uAAADpt8pED0wABbYIltvHAAADvghF/8iqB84IA/8rV8vAgggIQRMhx8KoB06gC5IFIndPdAstAASkCedvJTfI+gueq8eQFqG3y5IIDkoAAUASCAGjB89mCIUxqA+ErA8DCAqWCQUvWpeCvgX/JRPqwMAGmg9TR5RYByMPiOYDqY8nfwUcBZ4LUwfOnAqE4ABgDFYHiYwAwwr0+7sriCwPBgwE5goS9w/QD9YYGtmv4Ve+UAC8EAOcGVOftVAO3BgbnB1q7hHfjvYPjywGvjeVb9X/114ED9CCDh/P4gAYWwKa/5mgQnwDRDRFWagXkSQOJIwMn9+SAEbWCreWWENlybsW9tZ2j4IOH72wD24MDIKRsA8SH97kBHy1VNAp4BeZPBcFJICAApwfZTAY6gsJ35JQDsoIGXUojP+f0D0uMCqlx9dVXKg97NbYtp05uI/+emcctXx6YM6QFadtlgPOE1hL6rSpIbics27m/Ow5I+ckX3hA+piDno7FuZWcFL3ik6xoZW60FQBxHv1JaucO6PuvND2mbb1TDQs9RyaUDs0ooHoZFHI9Fsnl5PrqAoBuTtyPLGsZVhonCx/RsLoouAGLhlkBk52LDyYEfEStlmWuAtJ4+Ykzazg7w5fjSap3eNY1Vvik9ftJW/cPx5zhF2iX5hP5e3ykt3WgldkJIYeyB4GL9iJjdUJTYYF6ZOMc2LHMhl0qVuyPoPqjsZlcgcJLMK6LJ9VBbdK+ueEICcEBEr99GEQ8hh/Gwf0/3dNNgDV16XV8lAtQXcTPyTl8jdwMk9UYp2YK9vOas7a01v115nWamoYB10Gu+nNdUxM1os3dc4bPQE+mJP0n+vYnp1Tq5ParAD6oqbV5gC7gDDB37X4sVvh/yiLZbD2DnzVB4HQXpmrIlNLcEeT1W6w9IljWlyurZs7Lra3BbF3V3nwwjMuk0PNDNCOJ0TABaKIWLy9Wi388h0OUUJhNKk0U2Tn80UoOCpIRCSH6QDCAACiYHrnkgFdf65sUq2opf4ZApJgalSTnbTbtkheKFSkdCRtGbEiUMfRWANdJNRZAjVBBgEAhfHTyyH7ke9RDivxPLFga3Df1bvKFVxRL8dZ+FOdw+VD43qOSANKKyRjqEpbSOwP8/05M1iBor1N2QQjLn6EWEP1NZUnkQ85c2jJSfYR2Xj0E9Ev/lc1Th8jAY2KEiT5Z8l8xmB5LPpuQQbqofKNUAXqeTluuhIQVM+6Och6s9LJQzV7WJFvVrEoLAeKv21KPslYZQMiLAPPtXWWCj0vE00ul1IdqlgYxfJVcBJpwuxbCL6mpvxJKpDOvEI97Tfz6DZldBeQM6OFWoi/kxc00D8dX+UfKZGPPqmydUMKqVv8qeuH1IiS3keBB023Ag3APVBLKAwcyYcMZD+70m/zX4OkF1tE3FefhLYpZoyagp22K+RAJDIoWFoHjynjQl/0Rx+/QKKY01HskR2EAJcrUJ6gzDVWyk81i3+VsjyBJhPbmcURK5afxUaKkaRCfML9ClhbE+o8X5R4Wkwt6z0tor+l2q1mP3cSzEFyUYdsRQlmyXr1vpMWzPJeH8B5r2zR17p8l1RxjmKayd1dgow0kt8NrwgOiCFBKJekiYJnGxAuhaVh40RQJIiOT9ZSmrAS
*/