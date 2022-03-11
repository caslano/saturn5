// Copyright Eric Niebler 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_NESTED_KEYWORD_HPP
#define BOOST_PARAMETER_NESTED_KEYWORD_HPP

#include <boost/parameter/aux_/name.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/parameter/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NESTED_KEYWORD_AUX(tag_namespace, q, name, alias)    \
    namespace tag_namespace                                                  \
    {                                                                        \
        template <int Dummy = 0>                                             \
        struct BOOST_PP_CAT(name, _)                                         \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            using _ = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                  \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            using _1 = BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                 \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_BINDING(                    \
                binding_fn                                                   \
              , BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            BOOST_PARAMETER_TAG_MP11_PLACEHOLDER_VALUE(                      \
                fn                                                           \
              , BOOST_PP_CAT(name, _)<Dummy>                                 \
            );                                                               \
            using qualifier = ::boost::parameter::q;                         \
            static ::boost::parameter::keyword<                              \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            > const& alias;                                                  \
        };                                                                   \
        template <int Dummy>                                                 \
        ::boost::parameter::keyword<                                         \
            BOOST_PP_CAT(name, _)<Dummy>                                     \
        > const& BOOST_PP_CAT(name, _)<Dummy>::alias                         \
            = ::boost::parameter::keyword<                                   \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            >::instance;                                                     \
        typedef BOOST_PP_CAT(name, _)<> name;                                \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#else   // !defined(BOOST_PARAMETER_CAN_USE_MP11)
#define BOOST_PARAMETER_NESTED_KEYWORD_AUX(tag_namespace, q, name, alias)    \
    namespace tag_namespace                                                  \
    {                                                                        \
        template <int Dummy = 0>                                             \
        struct BOOST_PP_CAT(name, _)                                         \
        {                                                                    \
            static BOOST_CONSTEXPR char const* keyword_name()                \
            {                                                                \
                return BOOST_PP_STRINGIZE(name);                             \
            }                                                                \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _;                                                             \
            typedef BOOST_PARAMETER_TAG_PLACEHOLDER_TYPE(                    \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            ) _1;                                                            \
            typedef ::boost::parameter::q qualifier;                         \
            static ::boost::parameter::keyword<                              \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            > const& alias;                                                  \
        };                                                                   \
        template <int Dummy>                                                 \
        ::boost::parameter::keyword<                                         \
            BOOST_PP_CAT(name, _)<Dummy>                                     \
        > const& BOOST_PP_CAT(name, _)<Dummy>::alias                         \
            = ::boost::parameter::keyword<                                   \
                BOOST_PP_CAT(name, _)<Dummy>                                 \
            >::instance;                                                     \
        typedef BOOST_PP_CAT(name, _)<> name;                                \
    }                                                                        \
    namespace                                                                \
    {                                                                        \
        ::boost::parameter::keyword<tag_namespace::name> const& name         \
            = ::boost::parameter::keyword<tag_namespace::name>::instance;    \
    }
/**/
#endif  // BOOST_PARAMETER_CAN_USE_MP11

#include <boost/parameter/aux_/preprocessor/qualifier.hpp>

#define BOOST_PARAMETER_NESTED_KEYWORD(tag_namespace, name, alias)           \
    BOOST_PARAMETER_NESTED_KEYWORD_AUX(                                      \
        tag_namespace                                                        \
      , BOOST_PARAMETER_GET_QUALIFIER(name)                                  \
      , BOOST_PARAMETER_UNQUALIFIED(name)                                    \
      , alias                                                                \
    )
/**/

#endif  // include guard


/* nested_keyword.hpp
DFeTAsQoOp4ccTa8KdAYTEkAng1dxpdAN7A/dIhrcDMP4Up645uZ4ZV9QArNb2jrXCdsOLWNAvatNIouAIRbWlpnoINgch1InucCf26lfUoSiisBADXIJGfD6CAwvwTG+97pB+Nqh7IZEeFRacMX3hgIr7bhIhEo3E5tALRLXAfghyzcI94KFK3GdbKiVlHUGWjCaF7sojp78D0RgEcyaYRbYZd6ACoLLfsMGDO+HMY33k6DsbK+PFq5v3yhBY4FyEBuNekSRe0Yh6IWVxPGh8ZlN4Fy9ppynLWmvHZrBf1ae7v8O9Taff1bG0CLJzkA1rBq9ba49vA6sRo8V2sZX9Lan99SrYX2inAT9W0ptbbYbo2aupA6BnPgpsAJ7hV6Q7vmMK1VrV0U9QSwTl0dmHksDIBzrhWQ8eX9vceCgJp/u1yj5h9Oa/4CtELrfzda+RStYKklL+AQ4D2BPYETdu8Zqv+m+S8bgI+bYH9q2Qtffyc0laNTnqXPwJHi/ZJ4TT6s+Thun20Fv8Fho8vNQR2gx64UOszNAnoEQvvTEX4fxQgUxY1QO0ay06wBOhX8RUwCKlUq2ncZE4fGahcJwWhXIJ/v5URB1LIMR7zb8XGt3epQ9mYYNG/eHLF+y7QOOtM7WFCIDo61XSaDYjgVxYi6oq40qkE0YxT45NEO/VWItI6YR9/tblt4zPZNjLyZHE2291ioN5D4Iwnv091GuFPc4W2xPBcWBhIte0reP2BgG3bIT+b5HceIhvUYNzfvb94j/8S/O0WzMc/NCW9SwgfhDlejMd3zp92yjn66GuYb071z9qtG35clLXM94iT8jzljM6jNgoL4t91wXP7D3zC9zaG0YkrcgTFF+rc5lqsnviPfSrgZ7gxy6mfnGU/eD3KMg8v5EAhq14GA59T3eRb3FxJBJqZyfHq8ZNnwAjwZZkFidsKDgWt2MOxZ5iIhwvacXFwSnzbIiV6HaAF2xHcCGIXJOnCtIUzDoT6Mtz7EdzJhVKRc1PCkq8UheCEJ1GBXL55GMcSAFVfjRVN15Vt1OcXtXHACOAWBtefkVSfERE65M1Wt1RBXrpozboPlidDvRnP3TXTwrSFaRsbUm+S7f4LqI8t2uYY1Ot+3ph6Mhc3q0pDpk2EZ4SCGglkCxdVsJnrHjI0Ie10JQlFhvnhxvhDga3AJhLAWdnmoA0tSTONUWoqjkdaLR+eZHA/zNf8yz6O3x/4XDI/8nxgeqRie7WczPOG9xJjYfM5qRVgPXaXtEjwuQqsPaE3xLA/zQ7VG2UZRtivwOVwjavVG2apKk1ifdwNFtZVvK+vUgFYL1mcrO9De6IjliqLV+PZzPksi5nG7xXYRM2GENgEVboWzu1AzsRZ7eEiiLkKeUUcylyM5PSBwES+tIBUI4DLlJuDUpkDROqOomRkQu3BRC5CnJMxrM0nNhG9TGJbR6SYb2zx9ENgmAV6o/CG9bL2jfKEIjTqjwW2B0HpE8wttIVBdRHp6CV6qHIR6PSs2W/gCySE0FW5NUWd5rhYvs1uk0ckWRXsxOlDcESW5B6sjpJAkPIMlRxOhISpzK30L8TeioPZX1cdmjGArk9IWkNLjBEL/rqYQ65YDuKe7t7Kr/HZRBOKlquyBX9Nws+swFUHsmhbqXbiVaRTXZdFCea4qi7jKQ1TlHarKGQpKnNXtQ31gdwDkPgxZK7ifvkozvqRSx4E0AhAJ2xQOUX6vdJRAVllLgpSYzLdepnsi5nvx6aP4OZ6fN9JzfuP0fKy4xunALQ5LLyCn7YFwTjWc3/sZNFvTPRxoGsGkjemjjOmjjenZxvSxxvTxxvSrjekTjOkTEYPhRmP6Tcb0PGP6NMnmOFCo3erW2/xtO/9BkExx60s6HZrLt8PZQOJZCcSzu0ot8Yxaa8ysJUwt/7PZZAEvXu3HNZsoDJdeYs5BfwmY3UGi2qlS+GRy1y5FHSPpR2kp8lbUQwRPEBpidVxuIjZAPoVj44OlNirjw1eicO8brpL4dHeEhlJec0kXK/v2eeJLmUjGF42KLx2l3sbHl6obcotujC+9kbdkfr5xW77Iu32+MfX2eaJhTprn/VHgJoSrhImLJy64Czo7HuHX7tOmmcMuZpb1oeun09D10za6LpwlBNB1SYlx200A01g6Uf7kY9zy9MY8APuBnyKg4yzKMxlzGBvEnSn6wUkzyEgpNinl4CWwYifyMXK59MxQGsMW6mWfZ2sDhUscJPFc0SwS/lcvP6XOaWr6yFm++qSpT3Ntfog5nTSepi/WAIm2iqr1WlTQqXMdOkicU2eSpjNJU0yVzsRMv1NF/XXEZomnr2aShnSjRr2DjhhPT+Sxu4nTb+L02zmdqYzOwOhMa3sCO1FfYJ+xk3Nw7TjGzpvDMQHurN2AdfT1hViLWPadm3DJBW8Dv3+SQ6Me77UWZWgACCz302PEWpi/Zr+mm+y1ubtD/qH9M1PGFqqleRhVLn3A1j6cqLO2VH3P/2JLhXr77aoxvXYUiwlKpfzPB/pUyrSCf4XzPA1xNAZFiK2TYwd1mZbKOmMUgdN+f8qDG7aaZegnT8FAqhqXLNj/GfWCTzUIWOd/0uapfoA3DxAD0W6zMVP+RmnLG514a9sAMx937Xi08KP7LfNX6eAO04I80o0O084yBhoz3MYMjzHDa0wdBSvOqdnG1LFsxXm1MXWCMXWiOIguT72R+BJjap4xdZoMwEHmjpAHl/ZGsAcFryXVWjtUECOjdqjQRtk7tEG+T4DsyULP7wBcn95nw1X6ugXX1/9PcD39uZqKg/KJ0/86VFNTUMUA1d0pqN7eZUH1Qtf/BaovTvaN1l+xRDR/CppRKWgILmJm8GO0BZoxNV+EqPrbCcbnCSiiJATjzwBj7b02jNfaMH7x2f8Fxtkn7ZEL/b+E8It7GcKUFvaSL/q0sNte69PCUhfq0IXP7rEJxH2vnU0gvkKl5b/fm6bWVStc7uvtq3b2a2cod4UT1H5UugRROn5btt+M3DlXzfBHaPrxe1I7bmvLpax8lB8FemyV8ve/2WPKa9F22tlIIJY5t63hPtgx+UmMWw2il1OflzoAPFfTcnF60+4LqWlzQarpaednq6YX9jX9z5up6Zp7+rrNTvSTQ4sJvV/4KF8sHTY9V/OWfwJXknyysi/ZdSaYo78cTESfQQyaLD1BTz4VZgf9gNE6fojh8EHAj1PErS+MOfQ7lpj6HctMS5eqOtrXy6ij9EZ7iP3o5zj084K+ft6+zepn+VdT/RyCfh5coIaY/idBkP/KynE9JvVKlqm/Ng7VZSD2g/zY/PzYt/NjN+THLtHlYPT0+ntTPX2IJZ4sQrMFcBXu3P03/0zfjiLvTHP1EvqU/POZqTGkvmmVXoQfo6wfWJXJIV8ygrSTvVSDZ3erf8ieCPUet8nMh7PNEdsWX+pHfDl/ztsLK/eLsN+3do9vR70xPBWX6Bxjd3tV+th9C2N3bF5q7O7/xFqet1yVGrsjN8H/5fyzxi59rCbnx67hUfJilLz3nGOUrvhf9/wc0C94JB367wH6S/qgb/mHBX3F+BT0wwH9W/PsFX6u1dRvRFajzv1z+3bNCavOCX11vp5LdZahztr7X872N9Qu5+d6ftby8yg/O/jp3ZbddzVWfisNT3leOQOhWBvZSJ/i1Hkmh4sq/VH/b/0L5v83BW89syD1tobn/+5Ubw/91to7C3pTJ16/xencj+emn3jd0otLysS8LIGNxPRl8/q5uBprf40pBHxj7bto5o93s5V0ThcRktCuxtBe/wFcB0qIqTFcewnV5+7TJoipS2A/sERfusyM/ZDvegcuo/oeWcZGiQ8txgHex2/BppPyxyJszPlIdl/scDiC20W5KLExdCiL9aqt8TK+C2eO2MrlbxjLLtIKRBgeQto5MK3cdx4u6IjQLsvdlzHBAlFmvE3T/eLdfWHp0Mk30g79pmzvm8baiTWYc35amSdhwEt4EsRJNX+Ls813RdgbkaHdykBATbmVHDXlaRJi5qcPa/9Kbu1XicOuJL9/Ja/2r0TsFmFPo2MRgWbku3npWD7MkESM3KIU0OgZ00AkoYvzatIoaqzWdRFNqHcO3902QsvlqO3sBqFC/vXvn4EP4uNf/fT5mr9uGdVQLC+f7XfMjhQni6IL46GVJRE5bBqfdZaYI26CahROh1tJRiUspyec+unLfjhAP33do/T4gTYAjo+c0evj4ZUFJLCMxlX10MqIPDILdeIVLc899ZmJvx9feJogqBDTO3Mbyy+tNJcsyO154m7fjtHlheYIj7oqP5G+zsjtWfaR+SiJ38uL5aIXcdTqd2iD6Wc0IL9/sItY3w7p+YiY+V/exUeChdLxG2qQMCycIFTINg02wBXJnaUljoHL5d+PfWYeSotWdwIk9JPPYLNLQtKDXQ5PzBt1RIcj4NBrfLPH3eVwc5ofaS/ZaX5OOw9pT9lpzthw3448RNlC8lJcVLlgob4k4+KYf6GvLi8DQFF7Ow6oCaeZneJviE9xN6QhhwJzRMsSCyuswNWxBn3y6r+No05fpE/OngUX2sNfdb8zzi91MQBO2l059Q2EjxtewMcGseKo12Fj0SJP8Cf4GRsmnAa/matbXQ4Hmn7h+Lc4O2Qv+rPNT3/iUxbh1cEp9erPdvXHcamDRaUcLKnILFtUKlyrvHPHqyE5Nmaup2Ukl/2TMYv+EgKZOowqFpwJA1WhLZKE2mbZx77FqC1jVgqxoXhfdXLGP1PobSQ1JLfNSkdvu8y+vf3Atr6FT4OBHd7B/eNxCHtK8Uvq9d0m7LqcBF2ffUy7t7C4JMcUJ4KTHW+SKJ5pTB7/l3H+nPqcY1NLjLotw9AHFozrWNdbNYHfWcit47OEDdn83Mo5b+R0FnWrmpFS18LPvfSUT3x+yuxuvrher8724YJddYJSzTyjStLfeFUPPSNGXTsX6OBnJz/r+bmLn4f4eRQFlZuUKg/VZflMke76k6YghsN8StLou+o5hGBnRL5552k4EHMRh183ygfgRuO5oRW1bTg+DAH1xtMKio0JTh791ji/NtLyUlg+VG57g+pcvs7yVVViVNWjaN1YH0Trk6dMvceljbCdGnrV8Bkb0CVxiYKw1ccda+ZyLej6O8TVV632o9cb/fxxE/drLA/fNn6v5SeWZmNVrR+xM/B7u5/Hgp/1/GzifKv4fQ38rrxj1C3nXxX8XMnP9fzcrkbPByZmvlG1jhLnzdnfEJ1V+xgW45+KsBiL4+H18tZ3LFOxIM+ONio4gAfGD0OJ9QXisLlagjEa1vf7OORyJkzr5TwqLs8rhobBNcs2ktN5wThiQ0UVq1YwUTNn6dwbR8wvqvCipq8H6rPD89pG08oXK5AbToTMRQ8lL9JfVflvECv68rO/9dKrF9A6j74LSzLKPiIikxedNCNq+RdSMiFzwhYNdoWas4FqLB1/C32eyKUawOPVA7aEHD+ol8r2zKaPF1gfFXdm5aB255ovToOB8jnS85FuJy0/OiSFllINzG178/Qp00ostlK3HaKcya+LfZVdsZvMRR5xg4Jg7R+sTo0W+bHk+eItEkhGi5keMTNbDMot8sQGV+7X2iq7tN/n1DMekFe93WXh+jMguz0dMgzeixGXw8IbdnrO/uBKYEzf87vFbvtoJavvAKMYYcwGWnV0EIZqdfPNhSlYMu0GtNedRqinUIyxQkzU0/d8eHl7+iE0n4n1cie9uZ4EZqDmQj1zuDG+t/HmPDn+637H/tR0sJP+kre6aBWpEcriEWoX+TRCNBR/huXpLOq+nEcTHOT59a2tb7Aj32SJE33nZ/EXuMILg4ySaTVWM2p2zptrLvBatp3z+jh84h5WAOsAia8A4mE5kEWlNDM+D+L+TIaD1MUDftFKC64vugOOek6aO9BI6bRPL/PLxDtdpvotmkvdHZTyyjtYnH4a2cpjGlXF5pZBknQRPyE4+WpCKdrfK4/RHtkHBHp5I/QmPfMHI64Hdd8L0/jLu4vlDXMGYyb54ImoHIhicZS29C86u2kR7fAQI1UFjGLr0O3+MT7Jz+tTGvwEI6i3+4tLKt+OnS9ueYhDG//wTuIawKUmr47/FmX0mx2xS8UwTJPybBYbLm7Q941S526b41pH8k0V4IFW5Hdes5Dzi0DOZx9xQyMt31jYbV7hcOQ54jXAjP0Pug2OMaJOuueLg0EdKPSJ67DG5F8TsJry0jsH9B1Ru5h1xrOFDgTIZKf1C73el7wTrtFCPa4Qu3dD0a3nLjpG34miNPEyNogrqB+WHKlehifhtR+uuzzyBwLyo4ow8vBEFb7VYkG8xdYcVr6tLmch6N8K4Gqqn4hsZZdvQ32+3urS6we5mozfoj/GT4DF001EPTlvU++f32OsWMPfUT7nbeMnyJ0eABhH6eyFO3Ij03hvutwVzZBbkt1mmum2lfp2eqrAubIVlSHiVsta+f2GY2tTG21qo2aqrRRhQa2Z2bVsx9k4orA45xgNqTgREcwEIVzE3A5jbqcxt4c9REEEEootSgQ3gF2KZXS/HylQt8RwzllYGB1iPmqJg/zS8jiVOUwgTi2JuuWRB2D8DH9vUfhzg3O2NxYlxvGdGtjNtZfIBx+kLNVoP1qoJ0z4YCuRd1Li/ORoq2iWVdS6iVMoJ9FneO3ua7t0gBPX7Pl3xeMcd4Sn+9+uB5aKOmp/CfJ5wx0gn1gS7/1WRYQfOKS+DVZjOWbJTs/4vIhcdoLPI0ZYbMbQILM72gB8zVNokXFqj6gCF0Cz/GQP4WFRjf14C231cfqr29gcYozxUwcJHcZPE/iuCOryer6A6x4K1z8z9YMTaEsdMVdnu7DefBUvM1GVW+GZ8VhuQ8wrlieYa8NT8NN4spWqe+FG8DBPHgfPjC4rkfQXI+CnLDZA5GWDEzJm3BncAF6o/NbgBiCD2JTSNTSJ8pebiVYZIVx4o+x+8xVkEoli+VqnyRFnwCQYVUeZA+NvTMK53zwCcF2EbdbdnC9fC/cdHKxo39rPbtA+wuIhI2FaTMrD1cIe43U4i2b3hRU/GYqYLr4KY6gldiJx2VB4gQvuKCVS4qv8PoZLYABzD8fGAJd1KFx2XiN7I2CvxJMwX8Qd821ZdbEYvspqlAFEi8lHTykRv5EzqGAOR5cg1PCIux9npMJiIftj43uQyWHF+FEcnWCOkPDciKOt1e4MXgIHVbgK+R/3wNMMeDqhHWfkaPDNZVoO88TTYOLi3m/i+oE6woK/yJbkYLGPXjght6ksQ+wRTzMPqCO/0Df5ceoE6KlsQN+Kn0R8pSuR+xblPmCI9ZxvPG/P3H3LMsThYLilfICgujP59z6dT9moSmTSxqmjMlEkKT+iNh8IhluRv5Xy4/ceQ2XQuSeC4ahhmMIIpE2belxQB8+qXSo4LgQIbbxo70xz9SYMiEcscqusOW8Hn0Yl2s3Bp7nADXH3N10dQgd5jnsfU7mo0TF6j7PcTxz6E1muGhYdtJ7kIJfg13CnmHwTzUGQD+JiI6M55nvRTFeH+V582vQBxL60/Qozv/YhdqaNKLNWSMdwpx7qGRzPcgQOwE3oUXirCTXF8wcb4eb4TnD7ce0QH9rzLndo0XhNB6USx5Kpl2c7tLtEZtRRiKWOIzkxGSiG5GlnqdMNZ5t+cPHvvTCNJAoomvzQqI5K+0KjorNMUbr+Zgfqkd94MwWcgGwF50vzg+Ge8rtomdfwUE0L1vBQ3STYkaurK3CYeDhrnBUzJhKi8dnuk406xATMbODT+LSbM3A2ynXndDXqHdYn2sdUMyhRbAFNRw1TrtAh34Y98Z0g3N/SP3bpewYFa0BCYxfQmMUnOgKHabxCTa49PGjNyYuE1hn3OgInYF+QcHUY4SbXATiICjc7i3qsQaR22C2zNszy8l4DyQhO3e63Nqfgk1o4CVLbM8ds+yowAvH2buKA5KwDXaboyCEGWn3P7fZVDEphm4ecCjt2Y7eydR0N6Fs0E9GM2YHdvgqETc6P/SDfV/mHVFvKlCmQv0DkzYpPczrtlQ3huFGHLOfG0uGIMrGRLhhQHFfbJHe3rzrOkToCSG2xU8uWGoJRyE6UTn7Pbgc16vV3WlUNDOR7XJ7kAFe+J+BRBWxQvESl+0BRQLjQ0FesqvgYOhBZ4IrMMgS+Bop6bjH40BohFYyyrbiPX7bdKKtV0rRyEiG3bbNl6uMZaqT2Kkdb93+Ku+PEwlTUpAbGYO/byPQ8zpproUBx+Cqews0uU3VCU9S0pCRFTYMs5cYWBXfir1YquJL4ojvjZVuVHcNDhOoK9MeyHbHbAKv8vK7b1Hmk3PDOrrrMbhywHrThOrdEnNtWLYvGOelLJWyPucD58ajbEBFbrfCc1hnYlxtqWXa5cnDsq6xz2jiQCuWGjvuqt6p8OXAxdt8JO4wA7CR+ypcedxUQbwM/AmX17AQ+ofgce/5EaK9rH0xndwX2CcFst1oAR2Ih+be/ehzsbKOGBds4amZmehc7Pt4V2Syd6LjqS8xDtRBY8Da2N2D3STBlUEyq2+BVkHxYcOAZauMhbPUFSqBaINRi52/6PhrsQ9zMIWrmZ6+nmqGdC7CPunajoUOphly7cTvSK0LHA7vzVVLfyqeFnZxAD6vbmfFpw5zJ84M7eecOiE9xoq7jgX1WQbXoUxvdH+SVXXapWuHJ4ZQ3yBnLvVaBGhQI1jDzNLpYXiGhh3HGhkAZ4zVqoNExaqDdsYiS1hP3TsgNS1/110BKFL1jIqjvBBKzFm7s5hSK70PvQvnmZySPhGZCTArJqWPgnkYWMRgTuXJMVoccNHYyDGXrjbKNRtkmo2yLufqQ0w77g/VyFa8t9EPvcfsqLsJGh4vo4aww3GSE9sKhiOD8vKZoKe0FyxzaGNin3P1bnkf68ryuvI1wNs5BDcX5skKRhMV8qzgcSATeJRI/TG0aC90sEJoM1CjEcdzC8EQqgzw2sVtUsCFR1HkZS0Rx96BAk9gnOJhTYB+sI5tc+4zwIddbRhEQ+5kDlMPBzpmsGExBko+o5lX0IiIPvAj7FmdsQDRjFjOZagVPU/EAYsNEqJZXDQonr71KmdkclO//nY1vLzmDnjHYcXe+Uy2CUGuQX8q86Z0XFheE5VE+igYiZ3+gY4ohGFrB0GbkmLmhVl+8pY/YNCpf3sElDylHIwTEnQyEtsw=
*/