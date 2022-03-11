
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
N2FkdGtpLjgkFEuzVF/EZLHIUjkM2XM1Loul+X9CuteV8UFzUxfMU/F1LyXkhZcnDiQvbL1zd9/96YW5mvhM1B9TibTKw50o1WY6MZWearge5+8q0PfXD4gyTLdo6lwgGgMwxNAkhFlyEqYDOylqwFLGahOioqGE/MDPkyXkJW0kIau4FbFY0AzPKZyEIZRm1q2VMVUZebwPhGR3+di7dotZjMvIVv4irBwndJa7yjm8uPACSEEZN9ByHWHh7uXfmkY7rAETgzMFeMFeZzj8EOp3K6bQOSMLHaXqAOLoadggGMNXVxwmsm6sDntM7jAjTlX96V9jbAqiSGMP5C2/gFu0us4gIN4TIguQ1pgJ1HIgluhw0oFO8EX4iHr+JLx82GN2y1Ym/+Q4qtbGuO4TXccM7Li6o4iriJuvNcGrOKNp/hjPxUeL+z+5Qbyq/Ln9FiuNwHV30BDj1xEojCNk2I8i9lYhU6Cwh3elUxE9UCte/yupdXdqpPgTIG2KSrTsTqzzW7L/ocTkwlnfzNjpEhBDx+DwG0lJUK0DfuRFqkq3lz/zbauaVigk/I7UEn4/BgNcO838TzfEG6nde/dq3ZHo68zRwt/UHH4QDyfXazhzKQVeg2GeZn3sHWh9KKX1tESCZi9uN3zHK7GYL5nIQQ1/8rOEGqjqgIsnCh3Q3FcH9GKxR0nfZq0O6PRidRhJ2matDsiFR0PYsHyIeZD2CemBd2gS/k6yolytBtgodCuYjNlGVbcyX7kNC4YdWm8AnZS7k6YenlNJhLGdjQRCpXo8WEqkFWkg/zy8RIMLl3A4PA8pcvdUsd68YinqwzV4GBZRAM/+LY/ODlKCLRgJJo/uXheJKcG2LczTVuhpsYTbiGopQyDsyIwPaTphkohbHl+HqzFTbeF08HisfI8V1u6mHLndHoA7BpOYUs9/+e96ud9iM1TPsKrZV26aNBMtmOzp5UbCfT3Oh85vJdXn8HOfA8f3+Yj1nWDP3Uuszyv5w32o8dtb2Vi/3h+jHtJQedHi/vwbxBBsM7pAlzi2oftn+3V6fGO6DAc/Zm9jpfXtmSgGDW/bTCXhZ/JTpi9jMzIHp+sqp4qj/D08otMN1gWuk0WIw0Cb8n1XrsVYW9ikWpVnkE8QSxGnamwqh6D5uHSbVZXjmJ07tSv4mxHNAMu1jo+/Pv6U2iXzcLk+xxxH+WDN4bMU3EN0MLwSBuDatm3b+Grbtm3b/mvbtm3btm23t/ecPLvsJieZd5Fx8qJfDXXdDM0h+baa1aF8abV4pNO7JYbFGviXIRX/BGYupBFnUASV/ILxrxjpOnW2M6sbIVP5OuQZ2+ujGV3Qy7seVGz86KjGqroj6eUu4NgLRugE0Yr/w2Y2+S2TfATpIXiQi0HXr4yYvDyn7kmubj4N4f2JTAEYYnK0WqS84XOgdLWPYxY0BKkFkbwAgZBIEqaoTqC5o49ASMVqSb/McpCISAmC2KSmTnbpi1xEinbkwQGvgp/leBiPUgn3P6Zlu/8MQMgLzHM5koRiB/fXuhrMTY1vto86u0JjCoj5eAqQd6aeg12AAqGdvWGcTj+eZXvj/yv4CtrzaJWpu5AUrn2btUVMG4a1WCAgWkD6JLk+HkszrlApBTMtZ8xTMn1CvBD8REeu2MJpieUqJEDFCuVvgkTBaBlougyQWcrxikwk2nsrUbE0qVFtrsH2bOvRXkGmltpbvcoqnRcreTaqrRKkGcWHxildtSULT7M3hyr26o/v3bVOhpB18s8k1B73ZltEqciWtPrY7Cek67LcnAaJf4poc8SJmk/mBFoDSTsspMjIgm8hZ8jaqNf6qkI1CJQN9YKYugG4PGIXkLr9T671CYnFYETfSbk9pS/TwGJgjwHKsQt/RRKFpZOL6hCK6xtI0PjTDSSxe3I6TKl4XuEQeUyTXRG0AznA4eu1EAQH3OqkkLZtDPKLK0N3AFwLIvMa/l4Xb2/TrqFkKB398LM/8Bryfa/P5CGzhBhePYXayIn/IB9ukXy9nc+uzZTLximW9isUPwd5Bzl61WLYPXvFvRhAQOnrXZ9EVb4Z2AHNlXrfwp4czNBGrUWmUAWWGzpaMnMqWd7X2tj+MU4GpikPP/MQE8UmSaA/+Z2MY+JMlX5uAadU6/hI6200LicK2D+857aTz4VuJmj3PNNBr9Pupe8HfTsL5avj/OGLKyGHm1yht4zjv6ZDgGweLj6TqWrzXffZ42t07xFWx8g8l3sWWFULhRCl9BJljGSoREUDNMLJ+OczaTLhnaCjsVUQ7VI4btkIOf+v10m8mG+3qb4vtY3GF/rfd9938eURvDSQBU8yj6FvrnMk+lXA9MfZGpF/5cckhfnl0lb0PYlIGMtbukNKmlp4b+942V3ahiI8R6l9N+UX56i7hfGp9d5T/y7zkSwmvKqnXgvnalSn9haP1hHGw2Qn2rZSyQ2GhGXwfGT7NzpYlfYTD1b1ckTF4mWT3cwWTrefOOP40BdKkfn1elL50BdPv5/eAXz4hHOPnyQ4HemNBLF7bUkdNk65wPNtSKN98iYKq8AyqaNBZH4Y6xWgGXfySoBKO0wNcg8BufgSY7Usx7ZuzIUY5wa/PUEFeLDTu4EHrbF1oPKxw8XzEuw5kCkCdzX+kz0abeWFy05H2wmFd4QunwYtUPc2YJ8fsC1ZKkMz6eHsgr11a0TvzHs1HCt/TLMjz/g52HDW+ZyV0Laly2OEPuH2GOdIAFlEKNxoXJGYomCjgtYFuwF5/9h5rr2gMKtN11t1p0GjhV3V35TNaU7kSIuPv4IrZCh74fPeZujh2Qy9NjI5VJ2SiSoVdxhqfnGmeJQOR9tneWzYzY0aP/m9RD/VP7vzyZYlQZBgP0dmyIZRy+SQdyfhGOIPtANAxNueq3SqownkAC0clyNUQxgkxVYHUAteBZnYfZvEY3GJ2WABNNaS76ihdwddtbnDeiELCdd+q0RnrBjyTjodqD/jjUbjqey9i48Cal1ajFYkZFBamTelrmjKprKuwiLebFy7wgWLbudatilTw7E5TrfaX+DX14PohO74jzqJ7Lzisea/W0l9tRAxINPnbTfpOWOJhfj5QyWnkzHlZOZJb+3rjy3ePl8TfOiuupIsVxupZx9zMu3EwkZlbpP9cHsNkQisMCyM2QH34oozIrmZADvzqsIntjiJULsY4xwaE7g5MNoGULIuVUpGaDcgexBt+a+z5gisGsfAbOO1PMifZXfG/s19v+ITwkioqYb1aZa4Ne2Ys0iu7EWhoVCXfm9hjsKe4xEvicMuWM4AZOBrBhuVqapCTh4f1SdGNqhGefke4OJmCZq3B+kGHNbQC1V9pzq08F93zSXyV1u8OC6NDHdohPDLYWYYl1BP7CYpIbM69iAOKVfMVJzQVvkPNB/4pHqsK2N37AbSYCxmQzX0NBvoaEQs4IRhuG7nAKQSoe2PCWdONkSOUL2BkXRhz6pOf7w2U4xMowZMKGKrhb1+lNzh3yQZ0GuzCyAhgYzRKQAllMswDFkquAp4iVoktlh9UlMtSHMMjRahkLBKmqo2RYSeA4ZBgTmvwRxeWz/NH8xUZsNdZgn0Vsso50MtcCMaE+c6LCmPPlLV/8KLafqX5QtGFAuEb8aHjj5VX+qrl5Tf5jPyy9qBJFhFR9HYaiTMYlrEnTHuFoA6yy3FOaywnLUEZiXQxnjmrLRUsK1afJTfzrGQ77dizeGy/NHxJ4ha3O5jCgYF9Kl4NJIN8jCNyYe9kohja68RMhhsYmxTndADywo+6v1I7tCqYNyfxQUfRu8Y/nubRlUeHqBF+nhnJTaR1vQGRxOwuA+RavyS4IdmP1TNJzQu16IAACz/00nJyf8vs98Xd9clubmVD2YAeF77W6b2Ql48XiOefGIDPnGvuHz3DZPHCXPlAIFTK6D+uzsIBNdqbi9dqV+9ME4nK2CshVptZsz/V/X7P19QMAd6nskH3fj1B10HsJNreemEgzaSei9/Yq+ObaSnH0L3lGPaUdJJrRxbVWOuJ42TOv4GdMqKNFRsRukhUsKC5TlfBY7Q2hlFoWMWIPHrlE7wFHbma8qj6V7tCB6Og+JGxgTwec7NrNCZ9fI5DHgd6qzGiX46Zz38LuFcLmCTrHk3ZB92rJp/MNFVg5NPKPZhRr6kH75kWEl8ODmau71krpw+/JQ7OXd8/3GJGloD8CdSSrmvZkHqFo8M1PRoxPyYDQITIH+4b0AMoUxhhk6s5EwJ76/ej9GBMZuhraSh+k9yvm2KJ2PIRnH9WzoZEs6MMD7hS58iVUa/JtHjj74Sn9rRuZPEhnGYs7ZvwrzSdsi7sGl0M3R/PEPy61BSjndMTpLntMtN49hhCgCSnb8M9HzLyTwYQ+1+ZJaEIMAjZ/6NhmfbRWRKAUIGSVK749DaBZIZoLR6y9fGBR6B27XTryw/SqjRV9DV54Eg/Z3rsuqXqUiN1huru4AKtw08n6B+69VydegHoZJn1IJRKfSeJRL9x6+u7UE+cOJpQEx4l1ZXKMSt7bj837NAN7FtEMKYwzGWUvBd4mO2h48ijjAvtrfQXHajxOK/GF8YIqjLdCeqQKkC/lKdjwm7sbqXgcH8TJ93gn8gVQt49s1d3Jk+mV94H+1zA7sObLF3vfC3OrehlE9vr/v5fTfw/ak0TeQwlPYnoAtWO/Cu4UWAP5v7kN5v71heo93fEOz4Bl1l8j3r7V/M/14MRmV/NklPDSG4Df0K85zt5vquvP5b/W1/fMTwSiT7iOpj2j9VdDamgeJNLjbahcNYL52/jG9pLB50di6zpId5xV4CwwaOtk6oilFScyKzx8UeNzWDPtrso/DWlOeJiSmi3hfe+qhL9JqcGVa0gTfrRS0t2k232Brr3aAdmQw1yjpcVXAgMTPmxUOru+0EnQgP3Qyyb8RbV9bY/SjqXh0Uu3LJUEwTn0VjRPETx4oUvGbYmkJLF+bgM3ycmlbGyVbP2FgM+VFUrxoHPAfEyOm+ws24U9cnnIPWdOqZVNX3gcGo7Sxq/TE9Ye2/8aesrFuIYmZ8nwKWOxuAcRiep5WHW1J9FOj2UWoEsCKvvMzm55ySNM95mKK+Z25j+ncs+pInLQuw+YQH7yoHJ3CR9gF8ReQ6xKPDtgRGRykiasLCHfou/J6odCBGqL6r5dgdk3p57DlwKxtZGOJgCc0flWVoofHZZlXF1eNWpkJ+qUGgJdiwcFcBgVs0fQXye84KgizUdSzsOA9f3xtWIe1pPq7YiKmCr7e2A/uFsQZFA5OuGhJabttMRp4yE8QolmoCTLTV/c+7PjPBqqmq4e6yrylQzd4PRlrhzI+NPW5aiIFOg0QfyJG7hwr5MTy/eXjwAFR+6NnZ2fXAPPdbagXsqhUEZybCMaxhgiIcA8yNCfZe8YXHtotlTnkiWS+MtV46EhRM+x7ToIvfOCq6Lx7Wurqs5lBObIpWEpJgz3BDloiwEMesKEuEfQQxNwy+fuQS1EzxqyEd7Oo0dUwjs9/0JP66JaczlGhItKQPDYGQfzKHO4qQ3zS5V2bxoZUSeDTV24w5nNYMqrdO2Q4xwCS2sMuhCvW64kpjYr8V3+WjrX8Z2ajfU9/u/QpDt5tNgfhIkHUCiFyGyvbL3sChBrXvOkQP5Dc4NMA4CjYie5bMjre67nmofUPB93VtSfC2DftA+3qwvxvgRejTAX8JVLTOhcOvDlEeMjjdQ+zhEumlm/xUL+AbIaSVw7Vam2mQRQps5LteCmW4JtHr4dGoaV/sVNDsc0UM/dnDu+EKlLu/433YdkFztAy7fhFSEXKEz3Pe2xWk/tHqYiVa9upKjHJi5HQ1CvrjQ2vE00GCC3G4VSv0C7KHb2+h65l66uIfGbwVszu1rtlpHW1aUR9m/aM04HsmGdMh8Qvdg9ryDhg7HitR1ys9RUpUl8OC77IVIHp4fnTVqNWTIAxuqMj3lqG8mw2OspQWPFn42JF5iG2EndYgtFwkhN5WBxa0RGioChcY/H80wXc+gk0p3Omprkyta+NLV+kkXhe7v8l1parFsCj4Soy1rb55F1JxenkeOMpkPCnhadd41NL+5G0KIrAUUidn173XxX5bXnKKn+imMcvXIP0zAEdSr6/N4Eo9xrFXlR/c7PfcTVxy4F+HOTxrOCuqg+IpI5qHdqHuwLdhUdHxTwA8HJT/2jmkKHOKUE4ph42SD3CKOdToNow0E4waHRM9UebBE3T/3eklQXkTeDz4be9u4qKyoMNwQTnJ/pcYBLdgia0bJcxwAftVxRQSQ2dSx4Subq1/VsP1NL5OLxJWtw9+V3moeEbuwSXlAgqY+chvULUUyMMGFNXAt10SR5zbWTrfs0l24e7RYSULXt/v0ImF0bVwJ/o2hLsxD0ledyIl6qvz8/kw9t53rc7nBXtMATqdT1WjxRzQExcktrMatDhzhUuR0y/rS5mVjYkLPm3MYEVqzg9G3SPjzFD4e3pXm1ImNCci1IeFejWTYRdiymK3AV/kfU0ehLU/KeaCfx+3yW/D6/d0k5vG7+rs5ENX1z1ivkE+jSLjTFtM56b7dsl6WgvvihFoE0r/5IayUithFAYT9uwUMw8Z7nx2Fo6PRUN3zQLCqd0xEV7hYw9XIVEjcYV59FTX9rB+yIxY+3yTk3aNwWsGY21VAJsGTAgFCThGFAe3gpP09cz+yPoyWA28Bi8lc1Xw4Ag6bLO1mslCwwohSj5+SO44MK5bHDyPcrsaAikFx9pTTaEG8cm5f0M4ApmlZ5IUbt25QzBggVJXZ32zFoEhgFNvxFVkC9YRAuxkdmY64Ldoqp9jfYeH2H9r4SxW2pAI+Yj5Cuwn5n8qbyVXZlunGMRr4YfT6fR3U51Fl3z6hZx4IEZ/NRQzoxFNZsguQej3SOS3lkZOpOaGA3ggKHUT4LUU1EUS1Z1lHJgr8WR1NE2gjaHo4DABdy8HXBYwg0DlV6/R0A7TRXY4ioxG7WgNq89JaMWP1zIXhfFWz3DA4ayQOp8+R/GqEuWN1LEVekl+VZB1VKTXWAoEM4ldmmiOiXtK1yPSU7HtiwyfUPtJj/TBBucIgjGsQ3DHYVi4SK8nMuQtRxoVHqwXgbSCjGJdxYCJJU4vWkO3mM9eDSR75P/VflnWoOCUNMqLdtEzxPqM9bbWQ12nvN1HreLYyMCilx38kmzfUIVcWfo4uE+dMdk0Y2KPo9vIiEXqtixWk4ybTSQs8pxZ2tUasfZ4JNtOAc/2k4pdyTIFmttNF1DBhAH9DP+RVUKaZAfyuvkXifOA4mu5J6YHqbQTlxOXu3xuQOHn3z7P5nC30OMsRKuqM0qjXQNuy3plhG9wfwbrI+pBB+NUz7DrlOmuOIRFqSeKo6wwM/HRRr6JjNiRNYhpmOke1Aoo9Nt0QYjDGtC2XwW3d6tALR8hFxg+DT62bloNuhAcEXIAD5AXFQIdngE5S4PNml9vwEUjhLZEaxQnW2gjU1rhBu4MVuiHCJn1x7yikH1hflOGmqeB5rmkOsNJfAMoSIPrXZ1Hk/1/OtVVLA0EaqoZ/1BAvutzztc2KAluqamnpd+W/AnMq4YqB0CSnCfViF+MOGwJ0IbDW/efYhHjkMBh/BitBxc9Z0fqjGwcSYdEPAw+Ncl3lxOrC52YcCem0GSgrnNlPTAGj8M1LWtWozRHvasQocegZ4ni/iNR3ARRwsVRthr5D6EJS1qAV1geHt49vOuxPMMrA6L/XrZwO57+paxoN0/VDE9QxyLri2pEOUnpMSCCZpef8arMdZ5zf6bPrkItkoqHdwAtbeCluuwmgXmgHvIkx6NCY1nU2DXM+qU6snTZFWMbTlIlc1/noZ6Lo6764wGHymqlgkMzuQJO9Uz2noA8s1NQ9bIIfXAMfeMghBpBtIScdh90sJPikTpE1cFYm/8NN0125rYHvXB/yjqD/UZomgTfEu1dfpSoqwj8MtHGvJCK9uhtZmH4ln3he33j0+nsR7vDD0lALYN+lU2uKbty2Iu7dPm14XP8FSZDPyBObSIaVOqRZtkI0c/jnESqOQSg0XiHmcpH3J+MfLY9iTYWGqhp6QvPrfectNx8kMTCaJ4k8oHzWaUlXI53vNRvPROFUlPcrk6xjnVrIuPQyTKS3LGFqzg3hgAknJ8a88N52GoJHVOqLuR14b89j6gpZLG0RhhQtnBnxNSFqe25iC/mul20Lxg1mbsLIGq6jD4V+9Xasxp/BUx81j7/ofHBJT9DfSB85RGluoKuDPU9Lpp4tNoWT1zqnOCqDtUqCoPHpQv+AGlV6amurAqIwwoph1H2qNNHuX09n/TshTb+Hqt/h76CvwIydDW/4SNg4afMhNplYpqUXbLF4Usgt+p8P4+z8bUFNx6Bl513Ean/1tBcEeaYSPoKIBYpJigvrXYHXhQucKZMZYr7M1HPgnKpZ+lLH0HwEtuEc+BnM9BYgs1UiirUynb45bZ6GZe/3X3zOXopXT5n9D3dt1OKnATxM46Oenv+q3Zy5FXJ3PQDFFt0Jnl/n7KFk9afoRlOHs5KREHo01ESDCsJvvD3msbDtiIB3LRQ1hY9YaGkQ3bKQE1N52RGVSNzOqGs4TnRRORqIlJuJXIAPnf6uf+5v8rCsEtkVjRGyeAnTUWL6Y7559UgkU2fkQO0pzOndRKYCjYUNyTv2lxCPwwa+OOTwN6xIFAwa0xuNQMSmmzvI8El7ejqDHKidE+/dZAKWEvBZDj+JE8LOA4y2uixXu+RmLaK8XFPsq1E5jrr3PMc75x9xUOdkXNxUXCeD/V8YeL87Ix4YeJoYDh9haMx3Hwifac1gUXMdOtyBqkUOfKiA3cvbmQy7Yw2MFmAP1Fp6QbCojCs+2t0Z0cRfTcHwnu6KlB45/hvIb5AuwsyVVhBt4gC2qRb90Up9Q6T0Dt0djzu9/X0H+nsYIbQT9zx1V/OKOk3L+nXNDRC+Sz+hW5AQJ20Ffj/l+7sbmhvpeNv/hxdCgEgSsViy6Uz+fiCg4sQOtBJUtCAJgsjJNSAWt/W2qpNlNbgqDmiItDZWEBhZeXQs7RK5N7BCM1iSalK2gWBfiqVCtXRo35XhGSBb7jx28cfnlMScpuKn98etowsntZHbb7Z04+fMuqt8nrj8/AOdXGWImHpD3Y2jZ/rMl/oCq//ohXvY/Jb6Ys/gVihTytBNfYL3n07WAZEohA=
*/