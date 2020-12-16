# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# if BOOST_PP_VARIADICS_MSVC
#    include <boost/preprocessor/variadic/size.hpp>
# endif
#
# /* BOOST_PP_VARIADIC_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_2(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),(__VA_ARGS__))
#    else
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY((__VA_ARGS__))
#    endif
# endif
#
# endif

/* to_array.hpp
b97sezPzKnyP+fxmO+vs3vWNdee/r5Vjp7pz2weK/np/ZFuuy7eOEvaMfxnrZWOtuzqIjTzRewgbbnrd9OTK8RaRn1TaYArtv6UZz/fI9MRaw/QZ9nuK/Y3+sDU31hz5rhL+mH+xv2bUtSBNNS215ViXmXQTL2tB2pjGnMW1zHS+O+W690frZWkqepxM2FeO86B/mK9jlPbirR/gyO6atqES5x6/Y3eqhLN+uqCsuNxa09hX2mCiuZB+IduEzxm+L9pcX2uebzUGpuIc/zTlo2mQ72/AGXAm7nzcBRruuBRdQ+98T4ezMoL9TrNDmCe7R/Ks8wgX/3iO3w5P1iEke8KTtQ/JNnmydiHZek/WNiRb6cnahGQ3ebJWRvvES1xZJ/EnXRnydxQ/dRU2z/DjxX/fPEOd2xd17uDevzG3r1Ug1hy7WHPpYs2BizXnL9bcuNhzARu2d+SBjelFY6acdMuyVWuHf990+9hYcwRjzQWMPcfuD+0cecdrVuxJubDmQy2H1pq6LfHXRYc/1+1w5w5GnxsXa47gv28u4LtSPg/suveFbxr1umBrl8pnH2/32OJYc/VizR2MNYcv1hy7WHMED3/u6c89R/BTuSLpmAxOxR3ApeDKcEbf+e6Hd8MG8B7YGP4eHgXXwg5wHewJ18M8eB88B94Px8ENsAI+DKvhI/BTOMKv4xIdHx2AvXH9+O58TkAvFbaDv4DtYQnsAKtgV3gF7A4Xw57wWtgbLoN94G2wL7wD9od3wwFwDRwE18Oz4f0wH26AQ+AjcBh8DA6HW+E5cLum43n4C/gyPA++Bk+Bn8NT4dfwdJhA5s6AyfBMmAYLYVM4Bh4Pi2F7OA52huNhHiyFA+AEWAgnwhI4CU6Fk+F8WAEXwWp4PZwK74HT4P3wfPgQvAA+Cn8Jn4EXwl3wIvgavBh+BOfBb+Cl0Gk/l8F6cD5sDBfAY+BCeDy8HLaDS2An+CvYF14F+8NFcDRcDMfApbAE/hpOhr+BM+A18CJ4LVwAb4SL4E1wObwZ3gpvhSvh7XANvAPeB1fAzfC3sEV88Nl6Ud/oe4fPQm4/j+dZ/N/1nPyGvr4jz8qjPCvf0Nf3T39evg+bZTCuny/mc/NmhEV7dt4DebTn5yOQV+BiPUdf0s/3H/ksfUM/37/sefruft7+3vv6+f4nn6sn9me3HVzo+Xq//r7/+GfsZf19h/ScfQtuPrr2c/Y78W9xZP2PPGc/8jnyOfI58jnyOfI58jnyOfI58jnyObzPz7v/f0G1vgDgH3r2n81zloKGxszNcXbwLZlUXTC+urqiYFxxdcHYSUXB5+uFDcPnBqjMnhugsoi5ASoLiKx73qDePYnt6cbZz/FVFh/aa9948WuYiD25VZ4Qvv++yr25ABrDlddUucZw5bXC31OAPBF59PkDc6z5A3t1Q2PnPmRr2BtWEK/VXHmeXTS5++Ty8uKx7IUWfJ49ScqnaizeKM+uNR7/dA9Yvo2fXFXtPXscLeGdTFvjj/o8245f3tDd49l9/jxCwidK3BQrbooVN4O4JVK3lcWFRSVFVTpv4eD3PK/UPBhTVVw5rbiS7LnPbwdJ/N6mO2nL1PReLbJ3kATM6+RQdJFUznPk6Uj8mreQrLbIIvcDdwr7XbHVWGw3wL9G/NtMB9PCPKq2G7h2Uh071pwKipwyT9W45RK3W6w4euzppUXV493npgedOPj6mJGSnksQzsU1wM3DXYq7DDcftyA0xyLCT1ogctzlyDI51linvfopzNKSmQU88qO8kXfnGMhx7SRtLWmjmfLMNNEX9Zlpd/Qpt1NkHkI943OfLzr1VU/anPd8kbaFTNsWshSnTBw9bS+ZyJw=
*/