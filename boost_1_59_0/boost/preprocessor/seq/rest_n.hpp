# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_REST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/seq/detail/is_empty.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# else
#    define BOOST_PP_SEQ_REST_N(n, seq) BOOST_PP_SEQ_REST_N_I(n, seq)
#    define BOOST_PP_SEQ_REST_N_I(n, seq) BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, BOOST_PP_SEQ_DETAIL_EMPTY_SIZE(seq))
# endif
#
#    define BOOST_PP_SEQ_REST_N_DETAIL_EXEC_NO_MATCH(n, seq)
#    define BOOST_PP_SEQ_REST_N_DETAIL_EXEC_MATCH(n, seq) \
            BOOST_PP_TUPLE_ELEM(2, 1, BOOST_PP_SEQ_SPLIT(BOOST_PP_INC(n), BOOST_PP_IDENTITY( (nil) seq )))() \
/**/
#    define BOOST_PP_SEQ_REST_N_DETAIL_EXEC(n, seq, size) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_BITAND \
                ( \
                BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY_SIZE(size), \
                BOOST_PP_NOT_EQUAL(n,size) \
                ), \
            BOOST_PP_SEQ_REST_N_DETAIL_EXEC_MATCH, \
            BOOST_PP_SEQ_REST_N_DETAIL_EXEC_NO_MATCH \
            ) \
        (n, seq)  \
/**/
#
# endif

/* rest_n.hpp
ghVdSO/9U3N8cie+ZP1DOK03RERrI7FOkM0uhNIJ/5cOIZpl3Cn1hKAlZ5BpsMfXPVmKgcdSPzrvNdhDhXNVTXN4VTSmBtDzrfbAal/1radGihkG4A2LjP8s0zKJLe4DIS+rkS3uL6rv+eJDlMokugQtAzhYbzaD2cGBnEMox3xTuVL4uLi49h5airwVJxkMrMTR4w02k48VPZDCm0FuHTBx+P3vrPNEiaYaztGz8L29xYo0HkhmCNnFA4obrnnToX5k7+OHq0mXAkhDSBU9TGLidntMwJTyJ9A0ApjQELqBmZIn6MN7pgrAwrP6HJyxF6VBaYmycKxlZhovMW+tFro6z5b4UE3iLRYXpIfkxzK2jQ0JIQ+8vzLNhWUwUEv6efe4SN/VJScnX8BZp6amhh/8Uy8aaL6Qcbq5uDwkzmsULTECfph6Tt7rPnT0hhzebE+mDZk52b50qJtSv9F6lKSCPRpPwH4ygRVXe5qPompRl/x0Omm0dw1rVLJx4HO5IeGVbEe2Rsu0Tpi3bXPbZkmo/MSiPcFPh/kci3h9ZJLB/mE8rzoygsDUcvr8bvwTgbp0X/rEtztqJM8F5IRd9yIN/f+D0uLi4g2Y5vr6utpdW8LOP5dveaK9KBQvyMhu/5Oebl1cVLTOxCfp4Snmc11kB30st/hjK4W16UyJmg+Nq1sUInF7/kvPPsIMkFj0kq9wzHu19OTpMrnWdxHnqREDrFHP5Kh+CF3Rymf2eHu2Lkx7dyiFEaFicmSjM8YfCRMKeyXltnwkhmdhIhShxEURBrR4iTIVvoUIQZkYXo7BdQ4PfD53rqHou9odxqDGKFI4+kcjcFYTE5OShXVFBtiKalgETBIrPU68oqoKIbkjZZXL1FZfU4VHK/7a0dHxchcGDl6DKmzFAQJqK3gWH3mXW6kBIsYwEX0wWWV9uIUx1JqOFepv3cmpvUvbzWLNe8boQIsIsIPyL6fYYJNELTqXejPz/wIuT2bEHifS2r9sq6j9of+NU5JPYuRNMjdwp6450pAptPaBmUB46bUfNW4PzS79SZzB5cpM+YUwPd+rNxVebzCsgDNQyejgYJm2vG3JMeQLy4M/UAex/6qbdSMfjVTY7+yyMrbD3M82Jskl9aysHWevW+mZNS35NYksIzVdyPReyRBEYmNVvX5b7zR7Bleb+14vGDPC/J6cu8BlXPu3MvNoDMTaJpkP9uwr84nlanJOL8V9gVM++ALSceh1IQLbhHjt0RicXnJ4pGVmGrGAPFsV6odyyHP9rqO2DHMnVWpz7J+fSdplTyPmHvaemOiYgIeGgakPOY2ITyqpM+k1sW+BJaKmadK2kj6Chl9oGGKaFL7NczTucSgAnk+Jxz+OpBwy7kcyuMpNaNIzqEp7MJ4ecVwBtEbZhwCZO+u0lmFOucGJuOiv/bwoO4/cvpvykkA4vTGfT7NmwNybKju0L0HvGr8mNJtx1ILNwYWbigxqHPAI8KHkmFTZyRqlltbczfLyMt09jl0H13rEtt43T471o04fYH5M/8BwScskcRZIlOvrEWBMwqfNQhS6X3Reob87k+6kVMSXK0pV9U2tNL7YkMAyrrlzaUbz5m+kWvQjv55VOHn+EwfCuJEG8S1m9jUVcZLJRJo+Q4Q95hJxNWcll8WoUc7Vn+DpuPD7HkdKP91jc5aFwqbqwLAleyp3XaZvvp8q9SLCw6enpy8HhM0gpRcMT3gwzWfNn+CfKcyqWHiYmA/JHjymYqdwxcKmJp0JR7p1mtC1kLKi/r/RAZKAJ3J1oqJ7l6qS9ZSSQ75xP9NeP7oqcShZ5KnRLPXM74tXBuILIcJG7sTAqOpkHWKn7bfylkPsIyw0GmlWMUPQ+FJ1T2nOb3Ii5hF1GjL6rJgtDOp2PzsJ2GdTG0a0MrCdKA5Hm8yZ1ZKfxT/TDqTZz1YXK1e1QnGJ+A/kd7jwuxfPGGJjYyMNBa9EAz/oY1QAXncX+hPnpBi54luN/+ZM82nuF9BYu4V+P4yge8YwgYD6BctbUIp6W9PoGhKmJNwks0fXd3+zMgG5cPWuJParJDUNDo2K4zWsXC8+ITXPD7O80roKY68FCtBT5TML3/UTZre5zeScxzZ/tm0kMKEEgRRQLYOdtWkcIpRnCaz3aGLUV+il5rFWhksFXxm8xhnySd/i8AGl7MkYsD92VXHVtm/vjy5fZzCUJydsdzgBp88YnPHz29oeolx6PDQ35O7jIIXcEGjArWGfa4Cf31PCOpf1jyzykxW1Hxasgl8mYV+L2e8FM+ydsfYlQwE+Z+eRhW2L4wXpkHNNEGWC61LG9iu0/QbRXkoBtqlUqECr9nZ4TjRsWquNNDqkOPGdYUGHHR76mPG03klIzs7D0Yc/EVOdInag9NBFDlt+wvAPBFzzM5Bfw2tRMLaERnmXP7guU4xNweK2IS2YBZH45IXDixQ9Tk20nlxzwXD2lLoLkq/ECjQDS6brSzcEF5td7Afkq9WmRs7qH/+JgntRWGorFpMDuGjTMjc3N23AX/TMpqGh2Xlep+1C90pju/TVimhsCf6zzw1xleLiCnsy+iOw4GtkfTG69DUPusqRjSv/myh7XySRxbDQRJSuS+d02rSLEPV68qikVftCQSD3Sbqdhtgn/ogtO4GdVw9Ht90izw/F9/hUZRA6La9/RG9ix0gtYCtcmGT/yT8a1T6SyKqInb0gtSl/q+jXVv5nErydrljCprXX5n185D253g74x6QXOvW2I4lnfYcwRTQ87/DbrV7UmSW/L9S1il8gtcgxybF5pKJEWKDmbct/3yeTmPCIa8KDfaHDrU4QX3uAIB9pTRzO6ryOtan9ndq3lopQ/+5U7le4gpoMSC25hNuvOlGvmguFodTXTFTGI/qsrgH7fSY4LbR9SsOafssBr5aOIXKTm0e/nGQVR7H4DznoxZeT6Roj3oIpuqyhPNL6R1xeDBytBIoELHta/iPpMYuf37HwF7k6OhM0yUShOhATkO3z4EVmhtnmtffkBN+O8dzFO/w1h1CJ9nVfT7z/4CxBu3625D2sLoXQnshl2UzJxV78vM71gHtWWKsgkOfs5eJSZpbQv6qwJnAVT9tdlBSxJQNji3zyfOVT/bE9zRjSlqvn6isO89A+pdLxA8tkVY24fsTdB4rYEn5Y+lEoDt86KHbm/42Wx+1B5pvB6OIkTEWHz7xjA6FYbyUPSbrDP4Lj5aUJy2o2UscZuGmwvBO3Esnr6qGQ0KbzZePP6hHOW52eaAruRDsdPGl1kWRlktyifWX5C5CEGbZWujEUgr/c8lgzMyy50zgZw5xS7Y9JuOlk/r3WIBR10/z89BRgQV2rsPXQ4EtnDT2YlOuuTbiGXbz7lrNUBCKm+FeEJ/KMH/pZcN+l4zvhwMwRT2Rb6sD33xvyL+9n6d325lZ23IbaauKbyAyzBQBU3zqnjKuX4kvV6hXYHx5722ncDxDOFVKUjgv5yy0/3vsJHffaFuK9lLB5K2AhcBIdyj2bGQ5fanA5VH7z41Z+p/BCYyeqv3WxkW5DB1L4LpDHPNj189P0n23pp62PflshMT/LV6WF7ZJEMWt6hQk8ghGM0OBS7PfUiV57tLLEsORm0PxWj9tPvGbO9BDYiFj4mXFI/t2VyawQ2C+UXa/arktvNcQBFaC4mb7tT4yPn6DJCWeFants5yLVHpbEa47/aSMG1kJRQyQldmp+NwZG7jPswMTM4LNkDCtm0iZrSje31yG/KHMhVeJq6XDmJIBt/pJhvU3h26mX5z/ZnYvNWapbaPrOg4XHusKuq2OI4DiEx4p+fpGN7d2Yaj4zBusSuChrR8jOqiSSDpTzJvNWkT9lfXJvhyLpJC0CNF5Z1AaQiaroEQlxhHGsYF0TO/ArnR/5R3m9BsSG2sxi4LIpg+iJNmcUnHUkYSnaojyDpsdk8x4Mf6qTbMk32T3qQu1pQI0h64cWeTzqcyqPFx0QbnFxjouZlK0gkeCHXwD7zoSd42ORuxFJLGiv8i+8wMWu0OGcpT1Q4ebK/8ClWzz+LD5Fr+2tSsFBLoyPhNJo8uFkHdqlS6DudQCSI8oeH7s3OOLwodLjOhuKiH7h5ydCG52hdQkuj5jDsHm7XUvxJXQyybNPduBhl1RJ0ib+Hn+CYN8JZzRAjnqjOEHOyIPgQIiq+BjgXHbFcWE8PojYxnn0d2ldcaMsLGIIN8KLNpwxrKUWOMx+7dVAr1Ir+7We5tvAyu4mzyZKvZtnkeaoULhBlM8r05hZofKb3h8HoRQW8YQ3m/z3ncUR2Xs0bRHOZnG4H8Zm+buYLhhi4+OjgZHNgFJO780BAL8x1dHTRkNtban2ORPnl9uEnHcQqbtOZth9o//Q83PADJiGyj5iHkTwM59UuMuS0uI41tU0AfLVep6xLS3+MEekLdlvXf4a+k/0fENaJvuOggOmbEeJj/cTH7H2RbR4sdtKOJPofhRjjcn/eVev9kVSNtVbSdQ+vpWebweTMeyMr8cc3//ecUbmLGqwdOxW3smN+OIr6N0PpV59sEGsZ3aPc6YU+olnfqG3ACWvsSat7c9kVrdUeSJmi0p5uvJwfgudVNwxxtcYlbhK/VZ0TQRd1jk8l9WyNyaMH53VNRdURFk7d7W/M0FabX9iZkBB23Ap5Kc5uX91dahsvrcFtXPCz7Y0l/8+OIqiQ+fyyJdzbvfP8ggfAZAU5VmgTzP0MCKwzyfXYETM5r149k2tyBv8KabAmgmJJXi4Isifdl9yA0Vn76p9dM7UYZ39RHDpSrft457kdR7hl4TMGHGynDrZb6kCY1Nxipj+X6m/cT6rx2EMRaVe9kiluc/j1IVFOPdNR/nPETbK4cvQoiuJdr1ZQIvgXiaM6FiajSJ7G0n0FLZ5xjA5bdAZXXvJW370RKbwZxYiKK/ZKqIM0i9Irq6KPdEnhBFFYdcn6Ec+/p2PYo7M9/UK91YvuHjXVcgijuowSFNDJfvbFQe/G3FdR/sSMBwFuz0MgWm2tnTaTGaI60AuDbzlJqEZFXo1utyQBtuFOx/v5v6a9j1Hpet5EgTAp5LovWVWIrGw3I3hvGHNp71Ngz0gQ5w9x7EfELzbpq5gpPqHGeb3V6Qky3LKy7oSt5zVyqV5Rx3vuSXaLjN3iwFyI0zbauJ8riRuEf7nhVYYzR+ZppCpIxuaeyc+2ZsoIZ7l9wz42+yP2Oum7drPHz78Bqrq63+S3NGZLZ5ilVTxc7NgdlX7Qy80H+ut1pZSNIQCKXVBBtninGxel1WF94mhJ+quq+eYn+6wLd9lSCoXDAM+ndDKennBiMyDBCzMzbfJyin65qaQ6v8sC9v9mh7V2/HrqV1k+cUKxtzx02n+DvW+6C/QnWyWFK/cjedH9QQ3rsZN4/ncFjmPeomFLdzdtu6MkPHs9FJOPPkz88xhV1Paqgm+w+xCUROKk5oFbwL9yDpCcM2QnCbTwvlrdk2xevWkcK3t4NuPxN9GNUDpl6t5qD5AOgWu8GS19SjJFV9WLHDRUzejDU62PPuI4oeIt05shvWmJIiRejfBETwBmVVCOaUEcobd18fU5ZjU6+A3UFvTcly4ThfTbPTw4LomnUklSdrnwQO9v28PbyT98k/eXcXANBs3ThVDHyzMzLYUZ8PmcnpX/kE3BTX1EwXEie+AOQD94sqFBn6xVqMh21rzi5wBUsqQDQDwa14YNZAVRk6Zi+wHwdsqoStOC5oX+0V18L2Ew4A8PtSvql9uWmzzWnje/LTNDuSBrcqy02rrE3gLi5mw6wtxs3wkoqNe+bQs0aF7H+egalKwpJ8uSvXOZQDGplaqYhrEzONkwnyHY+hmIs/3EPkXh2y+eIrwz7iUdTQ0AjeJ2ixyPih9z0s1zHRrtadjHNNkaOwBilesu9fGCAh3HMBwOOyKbLQ0ukzHwvBzCmRDwi42dttOEn7//g2SCE0HepvMbWx0RdiKnYhsDtw/QUE/D1KGK+W/5aGcME5qUJiHv28nm3RXIPapIbSdygdIqtz/yx/ni5cLmBeSXCHV875vYaNvYWmGDTzLv2JOu3zIj8cHm+7stFmmli4RNfvPNYOou0EPQU3WRXQ+MXyn8qbHvkb0x0FVdhMGr3xEH4KyRMJQAMTJtBOFDhwW4szCSV7uMlp/2a/W/YyVMuWyFIQZJkZ2PjHm8CjqRhK+QZQwJt04J0t907+uZnv+qyRuFv2na8gCsh/WgYJXtThcXRwW3Mb1hu5oqwF5r2/33hGWFQrg8AMfQ4RyeGHIPR/Vu7xVSVSQzIPAvEFIrP9jKY6ggmXju4xP4zqz/vb7DV9qcThFVI4kM6NMAlTrOe1BYlr+G6zitLCz1k2YhxIblsv5F0KFx5irmf235Sxo5FQTw0peLze0lpBaF4G42BPsscGfZ6E6FGIayS4ES4CiVhmBLWXUB5TrAhI2zyMON3nA1cvGWptRZ9lvlZwL72YBw6wl2mDeTxjc6qNEtlobmarkLYqcD0rxGUxiO+ibmvyFojxELsC9KDxy+vinSt8h+hWrF8iW29pQv5CO8ZgRHNjDyjrfByDizsjvdkFvncvTe8xEXbxG5NtsEUHUx2sSSHMZGDpjFtcHmAc/HdoqMXNmH6pk6FrE/37l4D7jw5bAW/zEJaO47ZqfrVzAMYBTEz+lRLcAuDj3U6JNcANr+1Cz+J9HQudcLGtfWuqNu5waUvwwZe8dXoo+AsnG3jHNrLgiMqFShNixwfVuzXZsm6g/z8gf+l+4C2b1VwFZcTRxyUtXwr70uQGOX/aFsBtiHxQmNTpkz0d5jwZ3RuK6MhWxo0YtdeEQAI3IkuDuSX526K7vbG5oBSmpS+VylDa31znyqXYQfxktEiRlm48Yt75KeAMF0WixkZFPRVu5624e60B/oyz/nb1nW+61GfGa0QaaO18icC7ivWXCrf1m0n4q8hsrDn+weN8bzk/NR2OuYeKbymc71z/wQKcG7Asqh5oXSzE5Fx4X5zjM+XVPrA88/h8fKBhhE+LG3anxCRHWrW5dWF7h42xjzraRztwfs6bTlAPMt7UGpT06JdrfS8x4yYSoPWDOk9EoqF65rHdlKAv05Eqeeo4Uu80MQPe+6DWSvAEfTszsdWfVakmbsIgty4oXEkAmfcEE+VQeLjeI0deuAJTkSS2CQz4aEQabt7BYFAGpESJv9VGsbzJDia2nlmvsgT29OkPa4MymgxwAx9OOre1nVdXcwLHOGh+TFFux9d1dY3WcC4PLipIPuLbr7gy3WcFvZjWaiq4Mj9vb67OnU5WXlMRBGQb3JQW/jn5VFWa0f71xb2uZ0/DVTwEs7lROslscWqQCHhhd16mSti8ifrUCuqi90PDIUb+10vvflu2Z5Jgl0LYJVTf/tMw7Jm4/fWdXJhw/+zlQnJytx06Pu/qNehNxZ3xG7EoBOisrcrLI9HQum16dOYfRVIv8x0/qa7ZZab7y06HITT7UbaO/cvUmdMObC/JbY6OXX+8wvLkQQt7dz+LHyNFI5uoRzDr6bDP1zWVKtPwb6DMfwXl+6HWIdhUs+3arPwJ/cAV6e/v1CcfmMeNQoG14GH5JJLexC7+GwoXrZMl4MksYoHk8Y0y/Sxk/OKp65EEhYVPfd4JesbuT1LwBiJ4V
*/