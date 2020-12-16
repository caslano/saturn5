# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_LESS_EQUAL(y, x)
# else
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_GREATER_EQUAL_I(x, y)
#    define BOOST_PP_GREATER_EQUAL_I(x, y) BOOST_PP_LESS_EQUAL(y, x)
# endif
#
# /* BOOST_PP_GREATER_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# else
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_GREATER_EQUAL_D_I(d, x, y)
#    define BOOST_PP_GREATER_EQUAL_D_I(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# endif
#
# endif

/* greater_equal.hpp
fMJUfwPju0EB8V1v1b6A+M6kxR5nnOWuNuCLq9pTXEgqtKpKvrXGP/9YiNOQuOm/Lf75+R/D/P8x/H78eDwIpM6rKKqy+MXg0DMd4FMLTxsAYOs9bYbnuMGt9TosOcY1T6F68tFLlB3rYrHqh1FGajHR/1gM0+AbVOhy/LFPbQxzXAP8++KR8p+Ib44V1vgxUW188wd1+ncVlyzp0cOn/1gcdOAfwYReSJid+T8CCw2/FwUGbG6Mt8KAQ/hE8RnKJ5rPsAAcGMNnMTwazndQWPlvBYfxrooyAx5+E4APByt8OKJ1sDx3RBDcp2gWHKloAThS0SxYUNECsFZEIK5StICctp8WrTBU5sBa2nBFe7JrLe10RfvUQhuraA/1VLQADKVolhy5ogVgqIjjzJEbGKq4VGWqSzE8ZcXu6CnGlE/gOKTUwemB4zA4yDgommUcFC1gHBTNMg6KZh0HRQsYB0WzjoOiBfBN0ax8UzQr36A1AHv6+Ab2LCydZuT3A3mWe8zYJiYILxTNwltFC+Ctoln6rWgB/Y4J7KOixRxnH6d4+I9FE5XTXMaEYkD/nMeUieFB2q1oFjlXtAB98NESFe11VS6Ah4pm5aGiBciTolnkSdGs8qRoAXxVNKsOK1oArxXNKmOKZuU/tAbzH1hQ6a6uz/+qY8rXiCC8UTTLOClawDj5aOepPre0KZqaR53cx5hHVbQAfvloBdx7TR+jv4oWwK8RgbwxaA3mjaemSjGnLm/mHFM2Rwbps6JZeKhoATxUNIt8KVqAfI0MlC9FC+SXoll5o2hWWVK0AH6NbAC/zDnJwtLiwmmFJVPq8euqY8pSbBA+KJqFr4oWwFdFs/ZZ0ax9VrSA/sU2wI+Z/TORhU8ogtnkxcfs5+lB+qloln4qWkA/fbQKpTMXnFFLm65olytaID8UzcoPRbPyA1pDx7usMr/IO9wBfLjpmHwYFYQPimbhg6IF8EHRrP1TNGv/FC2gf6MaMN411a4yV/XsvKLZFU6W1Kili4H9vLNOP+MbWHcNl5xFf2/vPKCjKMI4/u0uvQkRKcFIgnQFQxVQgVyJREoCoQQNAiGhaChCULCLFUEpUqQKKkVUVERRREHEgoAKCgqCooCAXREbtt/mJsmwGRHU9yxv5+X37vK/6fPNtzNzd3tZORwvsTcy2dPiQv04mrGeWFMEQVobzhbRvGeLaN6zRTTD2SKa92wRzXu2iFbobBHtBPo2M6t/35HZOSPS+VLd5b0HD83Mck/XvH27LG9tbrShNgYbQvPaEJrXhgq0a6n/EfpykqAZ/C6at3/RvP2LZuhfNG//onn7F83Qv2je/kXznt2iFT6nzdduMLTtZrSaVPhalZ/n7BbNe3aL5j271bSxKr/RKj/veS6a9zwXzXuei1Z4/uZr4w3tWE28npQbrWkTDPEm65rhfBjN6yNytS4nasfqSW/uedHX/VR8Jp+rGjrMndQjXMsuPK/f1Gy7sI21NdgYmtfG0Lw2hmawMTSvjaF5bQztz8zh/tk5I0dkZZrbubNQO6dRXt/akc9kJxjmdYJhXicY5nVC4Xmdr82gjGmUEdbKmK1rhrmeYBiHBMM4JBjGIcEwDgmGcUgwjEOCYRwSCs/1fO0evR2GdWGCwSckeNeKmnafIb+FBm2xQXtI+YScUIG2VGkzNO1lNeZXaGl3Km2Rpn2BdhgtQ9PsmIh2hqZVUprejnpKu0HTzkNzy7hTaV5/l2Dwdwlef6dp4ZhIH4zW8muvtDFK8/jAfK2jitdKi9dH1a+NpmWpeLcozes/Ewr7z3xtoMqPPzSvTy3QLlFljBc0r1/UtGzVp8qGPL4S7cTOM3I48M/qO2TkMLM=
*/