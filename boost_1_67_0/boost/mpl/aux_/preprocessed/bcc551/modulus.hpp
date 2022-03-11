
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
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
0WIIGKYZfFNJ4u+DVSA8h62q0J4GiRsMoOFqt0CahV5As/jYGHhBfl8XAsRtfDhwvRgWJzmOglhTn/jP0/UwX/fah4WFE+wcXuZy1BtNwHBDJjlRDOFtAfg4Dtq+yq+fL93z77eXxCfhZ+Ee4D8zVU4T9+NvQ5nlcQ9es0qIsNJLmrDqLbEwzHLQQekFZzcMwhjFk76FJeStw/tX+JUnYa7hLfXtCYMl87j03HEYsgFtCtNK734VPjbg1JJWmgY9oflhcLQbEHCp5wXloI/kVGSeUsgtTIp/h3m78P3AmHQ91hR61FAViJ5+X2rjwaQRJqCPqpfvZzFjhj6JjTuAe4MvKRcpsacGGjjxCO3zvupPvnPyoKkZoS5HB7CaedDRq7F5esKxV5pAaUICaQ/b3qcj/XUFkQHMyrUB3qrZod/a0fLu1R1ZNZXnHSE1vB2qc80JNfyU1pWk/2jV1yrR5j7/27aqBBXXgAwnlVMoN5Oe+FH6Buz+JNTJLb3E7bgptiLSYciovv9Um/LXANhT6ccBD5qBsa1oUKwiS1ZN7d+gvJn2ZfakU8VTij9cg4ttn5js3t8jNKrDHYu01fURCpnyKvEeMc6vkAhoHH3Ma5aYya2Ko2tjNALGdevvUfdrGdLi33UKEGQrCEVACH5DrnYmh+clK0y0eRYIbyizIHax76kLD2hPbHAzMgUOVI191+eiZysJxF3sfDeES3KbIWrCTd+f3WELXE5WoqDUkjPhepChuWmvk0rtZaMjxdOvwAewj0abjM2abloAkAQde78Xbcy/1TK8U1xuU9fAGSExt3V+5RiySlrEuBVoXWWDur2yLjrJmNjNLv0oB8uJDI1lI8wuXhYCcImvHZYQgWgC+qh/DT7D8p470rfLc5q0g2DOBMwvEqOttQUwuD/Du8HCWv2QiuedBw2PBWiIxY8kfGFkHd8T6x+YS1J69/eD7odxI2/bE4hcWCD/pbg2sYYucRG/G6Hi7tIHPwO5LBGGr2niIWf8+g9B+lYLDibE6Picf1Epyecwgn/RtO0/blOwvhmFfq+1Zm4mHBm+gFLyl25Qsa8xn3tfFyjH6cdMO8hJzmfvQF+r+MzfZ63A/ZZg4c+CsTSidxo43rJ2mn2uqg3tTr50u4xHAfaM3feEBylOzTgGj6IvRtWSttNMWR3lEAyPH2+AH+nV3y/nS33lX6bzyDO/g0eS/7JE6cX6n5OHNS3EkNd8kPS9zvHrbAhopRpQRVf42aWRGb5sCn31xBX+sr404r3W9Km6fDuSRMIk30RNzJ2ZnDQQjqHLXmfE1sJV6sjElDi6mqlBrEYzYqSqgYkKTl5sxHJ8ciwMs+Jxy4Yc8oKAXAIzJG50WGlvj0iqwLsNHOBjcRi6k3Hnf4niZljyQQFuWh8jwLeyAdrIb2+SBON0jFbB31VpGfhOFCrBgKWz77XGdmaQDu9pJxcTV+BNxBw7Gnyg/N7JI8Qwb13fmiivmAjpzgEccqhEYIGqa9UcXk/Ug9nvukhJCIyTNWfqAgx+h06J+t0NMaarLFJZ0psvbNwZSGluAsYUqCK+pBHAsNp48TVctrJBdAJf+qHMNGTh7WqDVyse4uPSkRZVKfo8m2Hon9cV+olf151a08aLgBPXzJJXylgB02e2Wi6FD6HhjuuVicrGDUEMudT3n9uOA9zGaSqnaerMdBMDYqFkUWr3fQFF+KiOlT0jYejh47vEZH4sMj9l/BEkdXPW8cOAMtGMXAsW/LJgra4IoUTfOTbN/xJRhf+r2Waa/NRIlMzl3IOg1anmqO64Nik3tFSPB8HnoxoVMgmWLrtJB06X6B+rsHwP+SDgyaGRL5+T+hcJy6G5Qhbe3AIRYpnoJO48ccRNEQMfka3L85VpC62dI1JrUBrrOEFYrzJ3Zcq1j4TT5Bl1uJRIcqJf4dV+eD0q2ljN65lSSsOQWs8WOuokQCQRp5RLEDnbOBQWvKVpIZ41PjGYb5s5kTC8dR6WtoKDM+Q7EU0q9UV7ABU89e9ZYw+ghAc4tEeroGhPxAI3rLbInlxRH8h54r2KnvgIgk3vESMmLCH8A4GBkz8qMP8Cc9xhhVWtaBn3NROYIVxjiCmxyFGN1lsCr3fX2eL9+VJQd2nbTHzISkqD5M3kZ7TmtZgICqJ0i12ChK52NNT9dTTbIH0jayY5C9HRjV5qJ8JNtmhgPIDi876XyB+U6Owa3MPrt4fuH9yBdDK9DrCx+f2R0Oy9s86B7NenujbZiXTU5dDRm6wy8qjLAOr10H6iAWMOakl/gxYc5qT2uY2L3PnXdYwJMc1iuRbcz0uAQo6CV6F5V9o4RYwlMVJNRh9zVqyAVbP2s3Aq14jZ0Pni7M0n4XshSKBKxowsmG4pUV9rlM2GFDSdHmRxlEGAploLpjl+mZbSujXwJ+qRGHK2q6JzSUIBE0zETLYcoQIVquttaFAShcU0+22cm3jF8vjVZRblB/NoPQS25DJ13tgTfBbsuSehpV4/tQxKA4Rryyq+aR15W7LpXq/j4H7fZYRuNQm0LFXUxYzyg6vEIqQXP58QuikZHCecRY1vuniAP3QadT9e4BW6DtlDIP+by6g6XNbiRla28REswfIrMVsmW+Zdd1a2sqpIADXsTjOnIdRZzFAc+rrNjoW9QEHmImEs0crZ4ES36GzhdqcObtcNuAYPpeVKFg4EpZyhmsfifllS2QOgBsdlRCXuGDrCBRVFuTlBVpF0tahZbGhHkeVFhB2pk6sh+IhwKD6hmavOmrauh1JV+xfUvdf0msgueqa6Hsznu4h7t2GVnuDEk0ljNQ8isNbxGIl2ksGrum3UZ1lDSiuqSfbEDpjJ5sellZyKMfvZbUXl8r2FD4clkhZ5roprNbnV8W6TSdRYOQhxjLgNW0NdGZ3W8itLcthWBxlthkDtAw+BcwLgtNWeSPZt6KRq08NcW5TwO7sp9CHbIbC+Pr6AmncSTAgR9xafqXCCwzKS4O2AZAtQ2MCO01jgwZWZC/t+N/2MFzF781aZP5gs6b3Iq9TnyBXUJpvrCYRvXdk/bBFhLUHivpe5CqgrMoaiaQnz4ks03s0f98R+BTN+yRjnWgFElWjfRzDt/brVsrMrSbQuMXanZ3eKXCmzHs86O4yB88bXRXw/kbEcW7BvnWSydBJTm6EkG6K53BiRB4NjhuW4Z1aF5CqK3F52WlIVISfToEUdPlYi0N/jlpHIXLbS4qmHu7R4q7ULGLRIk611rN6oVkT2RLEZ9lzlTwV1VQamFshC3WEP5fvCSNV722jdYT6xUeX4IjUHWBXq8NqBaVYFnIoIUIVhkX5QwkOFVXeJLv9ZwE8SnxofZNKBQ8Me18O+xuVdKl+uFyK4SJo3u/KxNW+/KZ4jRQOXxjyE3A30ph7SeAYEo+s1vmhJYyUI55UlQpsGBmDv+DaCI7Bs+U+zirnOB6D3Xlb3t6Qqt0F/INU4y3dKZHOHfIdjZvTehr5W6EP1ZaAFLSkM3AJQfdcgu7fy+C7FYj/Q8x6nyU3xYv4PgNg9/3aiOwX3IJTWiMnyDDMFpWWiiDRkQXRs2PfH3KHpJCM2ZasfBhssWHI1ixYgJTI+Kt7F9vvCO+9Q7H2aztlEPfGbdmF2iK9To5DT3onI6dtA6aoIdnFNhHzYAFp+FA7hUssy9jNrtCYhXJRPien7VYr9PjKhfpGTflq3lXvAcEG5UZ99AlU4EyX7fjialtQNiTookxZjyPI6ZdMeo9uJLoOpdVxtbQOEAT2D1JML+MLcbiye5mU+2o7tf8MPwDSoHRhVREXe1h9577HSdTSTvwAl7j1nRisK/T3sO3XLU8E/Df5RFDDG0hb4RpJA6jyqcr5nmRAT3kwlM/euKrRHGm/if7e4pVpkEzqnG21NzH/x1KY5F9P5WnNFC3Yhdz1nBaoby2NEm/vRBux5EzVIysuVoNXG3y31msThpwP0v2TVZTuvc51EeN/U7QxiYI1FjGmddBflSktTFTLp0uCh+msYG6Z4a7XGFozGApYEetXlwDjBC9TKUE3WyzOcmNdhtnvQ58TuRIlr9C/9iXmPhkVrMM1EiYmeqkM3zp0WG6vlnCJ/8usbLCpKGGa1DpMc8vos+Wo+jkv3tXG08HT5wJ7j+EcG4USZVFdn31T1KYhHtegEMyQcmXMEqCUEXiYb+VnfFntP4H8a9QGQ8vQZJ1cb4vEBZx7d2qafFTwmm9DMeC4LNWpkre8mJzVBkAGg8tSqK/yTGybDijt1Ggcn7kOGpG8ikgVeyb64v6bDD2Otfi7ZPzbPweXzdGNFuibc8BSDpzERV3XsvnukB2C2yi7aaPtg9uoOJtMveiVseUjnAJrv40nquPpv7ppr8Q070Axx8wzpDv120MQfoOzpIUno7/5JYCJXzLuL9OgnYHzx8jN+cvE7TM5lEeOZ9OTgG6RsOHgPyr510BswjJDWOjIRJoxgV0PJy/EK+kok5Rls8ukwyiFTgFwOJi7GhmtJYlQdIRNL8ukqyrOUFacU/z8wKIUUV2AZUa+8cybiEAwWoZRBQ+PYqmyGe/urlUj8nrUI6Py3Myj8fB9ePverDtc7HTqqflvWnDLz852uUkqnoZryJc4YiboL+pf6Wffjq2h3p2vhH6/XeLRouz2ztKld0DaZMyemkkwaKsL4D7snSu+vp5PKgvW4cP0J1zvzufR+n0M2DlFgwb7LJhJAQVsgegPKO4+oCir0IsvT6KBUcBGUFHAhQ1NT403Tei1m0G39EinHARnypW7xoMXQiPaTw5oZhaqTLRyshsnSyXzysZV0tb647vH4v5MQZeuM6uZrfinJnUlwVt50jo1c1F0DSB75K4/rjx4vqfgg6RJiqXYNOrEsZu5Qyjm40cxZTFpMg60yV2eRn3oOLiPaOwUoGBQz5ee1I9HDY1cgYoKnjiIZ4Thl1XoKWx9cEi1JKB7l89SV3ZR0h53Bvis6JFVYSzGBS/kk7Uf6GJcmViMhySdRpXCwT+ASl7N0ZIjeXDYoBGO65xWqXbUSq5yVVhQEElq64yuvh9Lx8dR6Sk/OMJVC9gm/ulhScs1UUB26cEv0PUpxJKdGI8EGu3MnjPHl/olQ/6cr8lamLlzM8zO/Xrylugj5PSII76jz/cUY3sJjzQaOj9OWrhOVMNPg6tHR68TZKBJTfHJV4WP17dPfbghJucKpWYG7ILcWzW4g5xeE9GInoUAdsA6Jc22mITY4sdzHJ1MikLD7Kmc445v4SMyrhm6oc5sF0+Ugi3139Lg8CNnu2nye1zJmfTGXotlkaLXr7jsDzox2bTkQ32geGfeCqhRIREbDg2hJfu1WilG9QIKyC3/pka45G0l0yWG+c7j/WLbORgyzmJL9GK37cKZl0jGua2WeBJBx3TFWSnoNYCS65OvAm/Kb/eK3wC9zT7LCz/N1yg6zhJd4wCy/yfU3laIOWeQFSCDALB38hkwllQjNJKZV6nqWIpfjqCYar+zfl7SbqAM6ucQ3VAStSVBECkgN5+Jw48EeOcfjqZyHjuMcxMJBvX9O3z7Cef56Hiz5g1xm1RdsuegOhuo4DGwxtY6CO/Gh8vE6E6LL7rzZXzD/LLDoO/JdIULRh39lX/D3vifmkqmCSHarawL+BtDl9SYNUlfIhPT67vNv/XeCxQTNMOhF7c2LzfRGEsplVHrCqaEug4f3ePLJ0LP2+gY2iLaiK/rtUCRxCrC25zqnIegCJfqjE6i+6cjtOgcgaAMP9+N2LWZA0g8JOsJHqy4WSsenBN3ndpJ+wXL2cM+GalRyOOK8XLp/FzH0Llp4fb/N28DzWM7jXDPSeqo7j9s/hXHcOMhNsY928MkF5DzN3wUFv6EMZ4oW6LCGPR8OyHTTWDclJPfkBUDR+E3aYp/cWY5HG1yLnfdXKqnqBga1ljR8rKCjHWrN8Ztau2pyFgmZQ0o+v8QAkjjS9OtOl97xvTlqftXm0fmz5xGEQg8UIZY5xjme7BYsG8XDroBzju2ZcNVSjPRQkyxWNUgCTrQKG1WF6zMEmzdsgJ+v8pDbbE2cd2I9WMK5JVKbAlrZN4gAaAlXId1GEhuFnaQm6UyLc03L1woyxD+3kHeLKqgPLuoahN+YxGiYeUqLe3jBb1BHGf6xt//EWDPpkK6h45ZI2X8Jdqlb8HIbupVRAGfwnHKsCyCAGHu6X9pmLS13WNxZ4RlVSOtdN6VuwTSVPq6kkW2RDrC7Mc1xYkUnRNB4MbW5IXF5NMM9PNJNwzOUQ061Qhza0WceV2dwoC+NqM+UUB2DzT/Hq41/MTUZ1lVwWjLc9EWrL5qWm7CMxEQ25F4rvDKJRBUv8hU94sWhMFSkYYaWik/0JSLiXMB2X/FPtternfVBj74XsrRXlV/p1cRMK+PmmbK3+4djNV1hckyDs/sn8AZ6J8eZssmYE3pd+/F0N+EAKl9oekWI8KJ6yh0fw1IZN5k1zZvFfAodj3MNLVdg9O9/c50dKfUqLo2NFAwM9vd+6U/589jCsy3enyynXRacQUGV1bxOBBxiiJQakSjQITMBlA8tUwaePPnStmCGjhY0NPIfVTsDTnTevRcYspJPZ6XVzExibDUySJZhD6baFp2H7v3XEmrgkVw6qdLhV7HKsIKvMcM1NkwVMds6TiZjlRn7iyQ9KthpCswzyXkD0klHCTG5dX/Kken2i32MNLvCU77idZD9jgkU8zav+ewWiOpE9yCgMk7Si9fTzVpOWJlmsV3FaAUNHqvCD0XqrE81C38gHR870eZ8pURs5MPo/gliW7QAcMFXk9fcPT+RoRZk/l49OZ9vbMysRvAB4NipxU9TaQYjr3BO5Uqo3C+LoxSsxqDe8/oiAQgGCYLkf0Vh7Hujn8PtKaEi99/AAQdZqcPWvQ+OYgP1OOwb3RSIo6AGj25potpAdfO5mWy5B7yLRJXZcLWbLdx2M/SC6OUY/Wb2382VZVUO81ndjjFAz9X6zw7xxWALoVeSj/7sNoS9mV07s7r2Gx2tZV6lZd5kUrOnlLB0AsfnvtfC/odeJF46Tb2Nh3zPN56f9pabuEiH+RuIQVSMDUvIjuJpkAqZ3bq8Je0XRBLmJVCvrChpsmjXl1udIToxHkdQYXcRm3GllBlwUuL9w3drWIuNs/Q68e0vKil4qjTBGR5KdDLTq05Eo6vVXDMI1aTs6Yy67pa4dAA+44VpBRJN8JE/T3FsXitpSMM+dR9JdwEXekq30MzgJuU9FYI0sYDtpiuoTBiq6WI/k76Ls2LayNe3oNaiTR2e7P98DrrLpqGwRJtQ28ds7vchF/6tQaai49FCpnXT1lJsF9BFoJXGVeXQe0Mk3h5dwYFDFfKpJt+F/BkVolU5GEZe4Ex3pMCw84vBtDMbg36LhzvsvusliXdrhRTVWriEWEm1PFrxsP5Wvx4bW+nf7ooLI33FvoBPwEQAMx/EfoTAM6cYkXnjJxfb2Mu7ikyEV9WOry6s/6tr2FnxlCaH13u69OTex7/y/AvwyKLGus7zv/cNun3gvJWX639tXZFQ1bf+EwgIEB1GhlFnUV+ntRSmLaLBckVinbcMa2mZnhyU9NteFmncnz3ZfT4KQSYAjvSnvC5MbrE4toiDD8jDkowgMIQhbb5P5qWT2QDzQQ4QfmVjOt3qdEv8r6X31deb19r1ttfpJovDyfRkyhtMCXnJBLeq00FY58eN0w/FCF2VevXA55tpyS66n7JabOnzzYLLy/cSe8u2RDAhGaYL3en91n4OPNuqh5zZPszaznOWNeJGvVUKeN6QAEqMg1aH2+AMpEd7WZ0BTYD2qm8DLNn9RYNba2KWNhfALLasFrrYqLicWgbMXyVsKe4br1DXculkaV095gi+DENgoO+XZ5RI2yx6H590wr/lR2MrbNZVuVYQzYbELIYM0XCqXrW+JlgFlsqRVd1dZObgInzNNXHDiTO7cz2T4j+8oTIgnyuXbXB/KrSWJ7KJG1RXwcWDYlbiYym8gXV61IewKgu05zwNknc4J/38kxyHZCQ4t2yrSpa7LADMvCrm4VW0QLhbodjT2l8sUqRViSCi7y88ZIvD5jMDoGTgV222gtfMYNjxm20UhV4YGyM9Lz/EQekq1xPcPsFrsWUKI3J+nmS9BTJahfOERHcJbBig1QUXW5QlwLaYGrBu0i1T//j5F4sJM8LdUE7+/u0K39NGZ55EFwtNUzld3XEcwJO5wpZBCTjd4440WGZzUFt4pjevMtWu2koU2OMwipMcP4BsMBoxh5ebNy1Omxp9EtKtr119sryR6rslzAlBoxvYVJvnpjel4y9kVKx55Yjnqe2r4RrmfEwBI//3imxuemnY5w7CH6ysfuZfZ8xYWRvutKVsAhfO4phl/gDYir31hHB63FmF45Sn65ADTq3lArn9/T5SqaXbrH7TCYueqp7m9QjZ7/9SMAhldMiX6qpiCwdi9wUuL4Q7xu6lLNxODOiM3txjP15YE8MgRx/QEj3KUZOoHNNEBTiFaQNJa0OFilqOy+nkOOFII1WWGuBuZVzlpfrK0GyZYjuQflsrRSXsrXZ8B8nfqba9aoLQ3M5AYehmVFtHj7QjlSb5UmQIxh5AMNXbPeWEtPfey95dyvSqbdLGElndP1vYot58UsH5Pa/SwoUuhBPq2PgGYtpgA0RTkkGvylWgUs32HFQjg2xPGI6P1TlLEby0t9UDCfPrYfmoUufuo52BP5ks3+YHiQ5iweGm4/yucMV7AXE3ru+fR5i84DklL1xn+ih5f5LURRI/Sc1RlBh8ltT7Oe8AMv81ueLcuxmWAEOtSzjFyweHD6S+I3NF2EUj5ONAHKEBgzRDPconrGEe1XVxv8iGfLrrviUNTtZORysT6pjn/ObZAIKmOoQzaMDhuA/XqDkU4465EfgTvfJJsr1zvs9ze0xccepGbE01KD465q8DvonPRLsq1hN6jFjz6ppQk0V7LBxZVjFPT/7CY5dou6vSIh/7oQdMhpaYiI9KlfwDwYOphJXGeNbXHmT7yZgx8PW8n0EvM72SlYCRIeo05t/y6fNXxxVbpuurFpkMpxqaxMGp7dXOw6LaLDrZx4yuUQWa25L9pqTBxaRZGeUlvWagN+VebR+sFpdUwk8/TOLWNQQNXy/I/6chA+o3UPe9gh1XlySnqbPGl4DeFnXXulQAY5FUiRCqjvMwt6A=
*/