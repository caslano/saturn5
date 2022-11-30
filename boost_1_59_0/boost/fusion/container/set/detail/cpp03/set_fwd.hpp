/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_FORWARD_09162005_1102)
#define FUSION_SET_FORWARD_09162005_1102

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/set/detail/cpp03/preprocessed/set_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/set" FUSION_MAX_SET_SIZE_STR "_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;
    struct set_tag;
    struct set_iterator_tag;

    template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_SET_SIZE, typename T, void_)
    >
    struct set;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* set_fwd.hpp
On6GlTmQvUSWPg7RcXvLfq53u2F8616ioRgM4OEzq2VTExS0vLieoB93mW/VBdfZzRhQUtUmIZ2OmCGrHhZmg8HreuRZblxcrOUd1h+5vsou1BcWVkq0eNZe7McSC4Py8zXQQ0PeyJKcLtaV2dLTleADq/Faw/rIdFgTOLrG4mj4x9soUBLrH7cK/aA20dNv9vVNLXYZyodJ8QKrcBuLepsUCCvLjVffriCFujoSNFuqEjdb+mKh1vromYb6glxZURVxm10G2cSNZ9ajpcpOT1PnGmhLBNXRpmIUwAmZpx/zeXu9+/IoOHgm6tjuKD9f6kFFPR/CgRlocin7BSPfTJbgrjT1bAV5cJMQo71+Rnhxk1BMcUV91tzEL4P3H3QK7OzqGCsdcxPWLl3HReare3eb6m0Zx1l4Tw1us3b8qEUoEbricSYmkVZfxe734KRRz6moXX7NoFCu2wIAWS+irHmti2BUiIRqXEx+kRxwajqvwNLuMu6xgYJummeVR03G7JrclO1iC+vvgn5PKKwdbeyAMeVFd7pgwoXgZ+rHCybSlSbBN5MrdlntbSuc3QczSFon5wg2+SShhyCCjJmlxhty9Bd0929F89+2tpf8/LbVFeRa/3ZGLx0fG4zU2c4eeXnCb68ucFnLS8i7uzODuYUOztC3VyXk9jt+4RH/HYPweaiMW32ulW3trY7uYXFCPM5udsOxfKLAQx7TkcUY9WqwBVnwmJLjHjzecWGhKGu+ST3iX91o+1Lbsv1Td25ht39yBEoroFeThvDFgnYB988wx/PX43xoCqDp92lOo0KnOc5TzHvAqWlHPOrqC7uGGN2r827MVVacMWggH3F+N83Io+i4t/8iOJOWNzKTllHevuJlrUlwjOeuEofjHOeRifs84UGmiOt8X9/WJI0Qk+HBPPf4LcRj6ix/LLO2HfUWaOqudfRU/fJqUR++R4Q5BfCTCm2Tq6rKz5DUhO0WVdUIrtDQcnOF8OuqyOMtAKDXyOEz9RNMc2XnSEH5pUZa+k/HpArEyGZE6aYzoO8vo4x3G6oH/8jEaWo3bTxj85WQq+g0q8Gu3zPCmzfZQysG2tZHRxtVPq3eRT+fojhxcW8mRxQ0uTAXEwnxVqikzOFFla4jBRVJMPT2T1gVN28UhlhsgL+z8V3PqSNkf55b5j03PWGB8iHrWOaFxxUBuffK/RTzgauabyvrjjrtQIfv/f5nM7d6dg67dt4hSy4zs42YrArQ6Mg0LO/3jae4/0lU5AcCOhJHVte7Bu9kk/6e9Xnu++7TzQ2HjcDMqy05RwGoTrOAc19MOoSLkJyzEEjO9bN7pmTD4TBx/H61WWb8yIVW1jDLgEVtYcZs2srSkc/KOsPQssh9a1twaGRE8yTsZ5QbWkWls/F1OsPezSv+8Uw+g3QR6x2X4/RXt6izDQT6VmcpiIDhtiZrH8RpmGjhdZQqsNTETOh28rO7OzgzCrkVCu7S9KBrbXUNk0jIyLi8SkvtCVikjyDZiEkraTU1HyKQk4upJQad3OXmmLpw+6CASZyh3fnyx5Kc+sTB8knh5ElcABIs7dOHlhUGMySG7eUWTR6qz1uhuhCPk8yWqWDgBTAKNJzmdakAdT8VpzZoJTe/dfV4mj0USVjT2Cd9WlhMHLVhXPuef059aABxNThoZauXfhYV/t2tg1CD2m71Q1YLVPe/FtYA1TWYyBCWzvS6Ov9zdQLg/3gzCoLB0Yfk7e8MwF47gkRcBnus7XdfHhCj/JnBp5hrbbFubbppwtSr+fDfBB2t9azAag7DhSi/ZuvgAOJ+cBDJsrGRDjPNY8edlUd358psIPZiUFu5MhqetCI82F538xkjcazSS8qi3LDrc9X2U5TzeMzNGSRJ+abEsPHh5sb6DL76YEC77ba6z2ooAjI71EBRZw/VfZg0bF9xKS8ljVIvGTl2cqZRl/4BD+8Ny4Aokw1io/46q2x1e1+mJKSPizrLXG4EobbCyM3Ns2B2WyikvMikpqGlYzsqgvH2UvdqE3YdAL47aXMG3fDDTAxQwAe6rHNlDzqsLEY9FA8Qx1DBfJQ2eASr7Umsp2iFqjVrt3H4Hn/sgH/PCkqElqzu2Vlune/D5sn+zORcgZL8Q3x7J8D44W5zQc5pf0302dh9FifQlMU7OcmDDgFCmMAtK03GuD5GVSn67NzGnEMXWCeiWEDi1W2ySAafqODe/nWjQliu0Z1IopSh78Vv8/GTedXOMKwCTCmkdMNOOoDkKZCJWnTkEExkRQunW4P8AoXjDwpEe0Nia3G4Ln/s4ccKhDD9Xbvaw4X6MDyHcnt63olcPDGm9yFKv4ZovXMrDW/iO9tu80JscP787E63jjQy2PH7ClzDevC7wRcUEVbsCzDNbFFSyBX3k4RoAeGBWacw9xfn/o2xjlOLLCbrJ6cC8OxrKofHVC2KGLkAyxl0s0yyjVk8DwIQc4Ke4BOqIYsiYq8md3HI4Ynu/U30KayugXM4QKYbv3IT1rtwg4l2Vt5+8jVAURUReYqwyY6z+/OWjkctCPo1KRgwrRPkTyWgkAVAYmcxUsudhFz3LfzYA1w+4rxmfqscTnZrlHk3kupPMvlEBCM+suf+qzWq3VcmoFKqV/g38nlP+N9tnE08d+guQFKmY++EiVYez0u9BhNtqDXEUuDQTksvACtZ1vxFPoeaQDuCUae8osD0kOo9fOL/pOcuU6ArfUGmyu4a/7vfakyELxax4WOfNTHFp9TJXCZGywuaP7qwU45FPto38eO1i61gy4Q9FTnF0hvY7sCFskDMaaJLsd2jb3+xysJxQtvpNKqjNqDwrUndjW8O5E+Il9ce9kQXKAXeKd9hEys9TXZ0Hf/uQceV5Uwcmcei0JrhHDvP2gUTU16z9SOwlunNtCHxng/yBVg/Mwxx+cgVfU1g0C/qDvJ5HNouyVPQIR29JmbD/INh36tmjg4m9sU+hRMYaAC4n/vMTG0m1HSuUEj1mSRfVQosYzihfRmxx3bT1dAZfPGI3JvuMsDgP8EjMmBdFSeWidkika2U9MeOPRFDZsh6k8Ry0786xHTsq7ShkBp+/yO5tg5R/Iy8duUW89UQUAHID2oCgYtPkrturnVeF9b8ut3DjW0IY+KS2uDShuwE4gDOKQxDewABZCjsWO/YAzohygMPuodT0KVhdwLsLhdMhNQ6CN/i2yNAp0byX4bd/0pa67ouauZWgv9wEeeaUN14SwzpXEl9IJHvxMry03/HZYxTF3CkcsSYxcTKGGyW4eHDp0Y7sHqf4R05kQ9dhNx1otEVPmZ8Uh9affw0EV50fTcmkJ7HiK8G8IoinVzykbC7ABSRjHb7IxL443tc1dk4rYG7gQQtzcuXcLkFzQDm3Z7AIWzURcVR9w9OqNDaAu+4B14mQ6Prc9sJrq/817g37/fY7m13CGivHxGZLSPIRzJqGX4gYTvBYzhLb3bIlooCyrMltmZKWQWpRCmgX79P776iaaPWNc0spYxVYdAWYbLeQgE1hMUTlDNx1Ilv//snkJk/fwuOvtCC9xrJm91KWDv/NpfyogMveqPe2fcpKOES7nEJdTx0+l0wGXTg07HsbElKe75UVSNtSsqkpVEM16lmYvnRBvv0SWEEhmb19luoGXQhZ0csxaHOEpx3Pe0+ff9zhS0l6V4xcbR4SdWdAPL5lrA2/caD+/ZKV+oVRTRgatKotqzNoG2iycX1dLZ8W4F4h4qkO5WMbHK9wK5zEFDKxi8+klprs9Di0ew6mpqQKgRDX1+Xaoe97O3Vb3gEYhBFo6HXRPj4ht6dKKLQUNhtfTqs6mtn+4PwmeKnm/aHAGAn6vVenjfwz6kijwCZoJ7HzZ/loADA0SYhoY4t8DjA8tuE3dBQaTXpS52EsWF5hZ4KczNm5uwS+SROHUkYv6DHqfGd5Jcvn55+IAGNx2WNcHHY2jwT7YllPmntv0vkZGaRkubU7aON+2sOn2PX7fMheV518mC+0n+IXBK8/bs+lCvTyyiQ0F4gA9bR7c0t/gR++hQ+ZmpWxFpUpLFLQsLLOxmPOkvi2qVB6EwQXLNfi8/f/1NzrVOW5DS0C3rPNuwJ/0nmdO7kXNa+vbtY8Yb9XDR6/1RMKaP65lUx2ONLI6zd/dkzLamlaikwJeWfpGqe5i8LCxqLDeOyGrE+QcvNMfWFsn2fP/pBw+68UUBcXFfxAJKpgKffHKvugqe+3KZsb69YGGrvQy/V1R30qiSz+m8saQcmcy+XxRNkInGUM3QVT45qoxZnWWhrazuhAhq6NdXpbp9+8nAqQcKCiYJjiUXk5EJfFOX1KL/mqLVX0TCH1uUwCMhB3I2ndhfnymoMJye+QpuK5Fq/2dbSov6Co7EB8Jc/2DBZL7dEHpyaCs7/OkpZcsSm6amk4Nm0HCIVFn+2gxI6mXbW0Pg3V1JYaWeo/cbfeq6YfGbGVdba+ijvCeug/fzX3obGhd0UfrtzuY7RtAX76Cp35ZHLo4PeNA86r6t/z/HUIyPf3t7O/IskXMDvLOLc3kbSIpFwaQ794tU1ajoPFVeL5CSB6enkmJnpPTkr69ool8O7wBtPDsfuJxc5jQueLg7V3l7NCadjSuOok+PL9AcaYfgqZqYrYLxAU9MeH2ihk7vWq/SpyVnMvXxZqOQwP9+1wNnpPNfS8iYClwCuMZaSu/KOy/Hbt3eb375NxH14TxHKbzMhmpp6LllWZrXxW/HSQ1gITuHiUkQuInLJdXMLLfdwmNj1WIXOeb27PIqTuXoLZGpwYfluadhcMiwKkw8zEJlY2TDWtO99ei/96adrbHJh5kjm0Yn2+Fo6teM3W7LgCKoLJlvbzlA1hrnJdX6bZSvWxubFsf1IGlelJ0+25J8/R/UgMkUuLy5P6qN4Rcvb3RMA1c4FBgJqC6sV/7uAqI7KS/Wt+ZsKZWGpCfmrsnKOfCQkR596e65FXXU2Jmby9XGuZFxcQruBuz0h3+wrBM4vQrs7fGlmsrPXTB9n/aKlOlsJkAgG/08EwgRdhs7Qhtt+55f/aAg06+rD+m8uIotzxA/1G78cYSKzfV7enjIJ8XRaMsWpCS0S5HpMGpwhPNrievzsWJE4WL+5B+MBHA6mPfbUNGTBVdyb/dkSN6GMMmB+C+OuuHNW1m0AJmQpolxoBy6PkNziCcvLmDjWXObiomOtneIdfOd9/036h8975l5M/E+HfT/PygwzbsGzs6Km4TujoJmBYLRIOiIitNsP22dqvftf72TuxjtM/I+LcyUaz4hjdVn3/+8HIt5jtzcum8Hg6PLytbYshKl8mLaBbZl7qQGHLiuXMiQ1JvtBVu704to9F/b9u4PyRAzjxjtRTsLNzf81MpF7RlG0ZMEm/ZKXPfgiM0WqGw474a6Ox+kCeg1rzg/kXKmG+q0HrTr1dq9kTpb/Gg5h78OfHd/iK3/gC5VxqXWPjw+RsSvPHRmILouJ3TjZ3LxvLnwtM3q9HKOk1HQmAP0XfntuyXs2KMc4ksIr/etqhSTYeffuB1DUAUdV1WcjX35FwfGi+Mbh7LfAUisbIRDkie6MY82E0QHzcrvtHPem4HVVkx7q6oKpG8a7aXG5DwMDDrWxcWbWPb2C/wZkF7LgWr1GVkPeTlZDNHfT8aju6XgB7+vsu8Iw8gtwEmeRkWbF0PtGn2V3x8NEH+SxvqM7QoyaVoQ4uEC5d72XwBGzya/QmtKvD/54cqpVIw3++bOHkbV/8vSPr4DAUIPALuiV5XeT1i2/pQZ6wrmKsO6LQ/NMfrtkmeUWyx+uh4kxO5e2IlPLzTyOx6tJMadnWWkWEB+bFvcbtQfEnaCLXpPhv945w7AAcHTdh37y8tIK8qihTxd5lZ/BTk5bQXkFzcJ6LVquXXeoMQiD+Mt3h8yEQFqtyZs9xrODKFEnAHLNL2U3ACC9lvWwFHJ22i9d3B81WgFBSbL0FWTdPM+CmhugesnPU/cFmh9ulk+8Odcr0J8e6ICmm9IL6tlDsxrtteVK4LdvwRmYQ6bEbZ78/btMxmkA39sZvyJNC8Fzk+LKCmMgVM5qYoTeqFFnivJhe12OjLA10F+inFEqXAYhd+SGAtUVbbGslxdzOyrttxmobkN0/pXM/YVhM/D+tp3f4K4Dm55zXHKjvXA3jr4TRmfim/Yjj8WXqZ958/duh3f0loTsTu9KSkhYVH8N8e0p+/TKnq0fZSv45pbuE+zRrYVyL8Sz1UEMgdsJpSgVppgIyCAEBt4vKTChOJdI7ihameDJWhG0vIRMZ2suN9Nr0s9x9aKvYQas2Cb2YtS/uD4F9noiKtcC7k3Orj/OUj5D6e1Ig2I8OQSqjtd6fB6Hu/uc2IKJdvxWRiWr4/zDALQI0ATJTWuPl6ed7E7nYc97V4oed4ePsZZIITQQFGxQuSP51eFpphnL1DufG4G1blEqkcfY3wPumQXWAROMmbuBbmJZzkLg6JRTIzi+EXBN/IharzCIriiFXtuC6d5iJRiHnMlVnJReuSetWjV7VRn8iBWO7Y0YCAdFdQvlSNxJsF57N4jtvXDESp9QdHgcvI8QM+8KXheeB/qLoLguxVr6ZQKAniGmtLItb9tl/AmIhemL12QmoBtYm4z2T1h5iHcis77etfQJ+eMKnNLMPxXFEmFQXnNbe6R0HVx/KranSlzQneDAgTh0ICyUNQau+etXQ4z1/7OeRoRXDnsDXRWJQX8Uke0puSQNHDt9YKAjWCHwNODFQzIVH8AGC9pFjhTZw3av+jBPJHqHmbk7qgukA3Or5GX/+fRAwOnCf06gaSLSEezIWOViwDr8GDPcrsM93M0uwzWqKqADgyiP3QajAO6V0S8TeFkIxxou4QhJBg4Xktn4Wd3tB1o8C4O48WC2U4ItkSU58aDM60ece28bflVs9YeTyz1bc3FNUzuIvn5lIMNVibXB5WW58WaT2fAxV+UGyBmXS5SqpcMPZUS+1oemXBog6YgAr2O6OEaRY0BbzvRhUriHZYGVuH0wAKE8nTGpev7D0R/ovGFx+WSejFi4k/XL/s5Vz4vvvtcfR9ZESqmSfamsgXZrHceg5kf8s4+ynrIGXTkZjGEi/VKrlAi7Hj4g+Abfxy+SzDHNkxhNBf3INUnehy0K74uB9xXVYOaRCU2SJZZuloEgCU+DbZGOcDfwPrGpJEAwsjAMgjpeUEnl1Pzd9qvMhD90J2wRwIEDVPuaG+TzXC+y9q6NMWn+Jpur5zGTdQQNNyccN7R97WqLXhapaIOtgFEWPkCzGJJGFglgMhHrotq6v67cR4qhtw1L/QPZHlBZ+8fNL6cztKlubrek9vBdh9r8LrDIixPnXxx2tsWeGnHdKVBL80gzoYnxCWW/Pw0Fbp0gOmWdpLyfCslxdnmk9dBubGPG2f7QOhPlsM2/qmW2w/nULajTsgQphjBxeJZMcMHSF9wWHdAN+wrdu6avAtr4t/ifBmA3+enTncZ8lSzdEtlSGImiGG3qYuur89f74S6oTztQY6EB68LEdy39NmdW91RpWjwfLEWj55Mkd8SeXXeVoJ0ASCd/DvlIsPuwt3sEhf/xV7Z5d4cCIq0YgsrILZbp43mTda9OLF1GmHEmnM3fIycM0ovd6Nxf7NCA7Hue1dfm8FGP
*/