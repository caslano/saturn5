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
# ifndef BOOST_PREPROCESSOR_SLOT_DETAIL_DEF_HPP
# define BOOST_PREPROCESSOR_SLOT_DETAIL_DEF_HPP
#
# /* BOOST_PP_SLOT_OFFSET_x */
#
# define BOOST_PP_SLOT_OFFSET_10(x) (x) % 1000000000UL
# define BOOST_PP_SLOT_OFFSET_9(x) BOOST_PP_SLOT_OFFSET_10(x) % 100000000UL
# define BOOST_PP_SLOT_OFFSET_8(x) BOOST_PP_SLOT_OFFSET_9(x) % 10000000UL
# define BOOST_PP_SLOT_OFFSET_7(x) BOOST_PP_SLOT_OFFSET_8(x) % 1000000UL
# define BOOST_PP_SLOT_OFFSET_6(x) BOOST_PP_SLOT_OFFSET_7(x) % 100000UL
# define BOOST_PP_SLOT_OFFSET_5(x) BOOST_PP_SLOT_OFFSET_6(x) % 10000UL
# define BOOST_PP_SLOT_OFFSET_4(x) BOOST_PP_SLOT_OFFSET_5(x) % 1000UL
# define BOOST_PP_SLOT_OFFSET_3(x) BOOST_PP_SLOT_OFFSET_4(x) % 100UL
# define BOOST_PP_SLOT_OFFSET_2(x) BOOST_PP_SLOT_OFFSET_3(x) % 10UL
#
# /* BOOST_PP_SLOT_CC_x */
#
# define BOOST_PP_SLOT_CC_2(a, b) BOOST_PP_SLOT_CC_2_D(a, b)
# define BOOST_PP_SLOT_CC_3(a, b, c) BOOST_PP_SLOT_CC_3_D(a, b, c)
# define BOOST_PP_SLOT_CC_4(a, b, c, d) BOOST_PP_SLOT_CC_4_D(a, b, c, d)
# define BOOST_PP_SLOT_CC_5(a, b, c, d, e) BOOST_PP_SLOT_CC_5_D(a, b, c, d, e)
# define BOOST_PP_SLOT_CC_6(a, b, c, d, e, f) BOOST_PP_SLOT_CC_6_D(a, b, c, d, e, f)
# define BOOST_PP_SLOT_CC_7(a, b, c, d, e, f, g) BOOST_PP_SLOT_CC_7_D(a, b, c, d, e, f, g)
# define BOOST_PP_SLOT_CC_8(a, b, c, d, e, f, g, h) BOOST_PP_SLOT_CC_8_D(a, b, c, d, e, f, g, h)
# define BOOST_PP_SLOT_CC_9(a, b, c, d, e, f, g, h, i) BOOST_PP_SLOT_CC_9_D(a, b, c, d, e, f, g, h, i)
# define BOOST_PP_SLOT_CC_10(a, b, c, d, e, f, g, h, i, j) BOOST_PP_SLOT_CC_10_D(a, b, c, d, e, f, g, h, i, j)
#
# define BOOST_PP_SLOT_CC_2_D(a, b) a ## b
# define BOOST_PP_SLOT_CC_3_D(a, b, c) a ## b ## c
# define BOOST_PP_SLOT_CC_4_D(a, b, c, d) a ## b ## c ## d
# define BOOST_PP_SLOT_CC_5_D(a, b, c, d, e) a ## b ## c ## d ## e
# define BOOST_PP_SLOT_CC_6_D(a, b, c, d, e, f) a ## b ## c ## d ## e ## f
# define BOOST_PP_SLOT_CC_7_D(a, b, c, d, e, f, g) a ## b ## c ## d ## e ## f ## g
# define BOOST_PP_SLOT_CC_8_D(a, b, c, d, e, f, g, h) a ## b ## c ## d ## e ## f ## g ## h
# define BOOST_PP_SLOT_CC_9_D(a, b, c, d, e, f, g, h, i) a ## b ## c ## d ## e ## f ## g ## h ## i
# define BOOST_PP_SLOT_CC_10_D(a, b, c, d, e, f, g, h, i, j) a ## b ## c ## d ## e ## f ## g ## h ## i ## j
#
# endif

/* def.hpp
/k2vrrZb94BbDduta8At1HazjvvbBZZb54Db97ablZYvbTcrLe9Z8XW0jvuC7dYt8L3nlv6n/72Ga520SbnWWW1VbKVNOq51YrsrYGu30f+Lbz5DYrT7ko8SEzeNrrnlmcv7vFxQd1xy1Tefqm8+J3/z6XvyNx+5L1+CWzbq5Pi7p/n7U9TZ4f49WhN4f2DebeyC9dBKJZv81kIorAVrw3BYH9aBLWBd2FqnHw7QYeFFsD5cChvBR2EcfBq2gxtgN7gJdocv6vTCbTp98G3YBe6GXeGnxv4LY6/TnakT3Nuk23zb0ulIxkFv28y3rTfNfJy34PnwHTgIvguHwPfgePg+nAh3w5nwI7gQfgzv1XkEV+k8hH+En8Fn4T7lT//nZv7SF+ab1ZfwB7gfknfqK1gPfg2bmHkvLcy8l3bwIOxp5r+kmfkvI+H3Ol3wB7gIHoFLzHycu+BRnS4T7nn4C9wCj8HXzXyZL6D8pgwM8ZCuoHkz1WE1GAWrm/xNCwncj8tzg+TvYDQQd731Ib5wOMjkXxKcDpPhjXCYybcU+CqcauYVFcK3YDH8EE6DH8FSuBeWmW98M+CXcCb8Cs6BESTmMlgflvN/QzOvq6WZ19XazOcaaL75DYKLdTnD62EqXAJz4FKYB2+F+fA2WAgnwXI4Gc6DU8y3wBS4Al4In4DDzTfADF3+cISZn3SRmVeWaeYpXazTSZ6NNd/8smB3mA17w/EwG+bBHDgBToJ3wSK4ApbBu+FiWAFXwvvgo2ae0mvwQfgufAR+Cx+FP8A/wl/gGhgayn0Q9MEnYU24FraAT8MO8CnY2ex3hc/AvvBZOB2+AC+FG+F8uAneBF+EFfAl+Bh8GT4HN8Ot8BW41Pf3v1mm3WJ/syzm7wV6H61DO9AB5KXQ4lAXlIxyUTlajtai7Wgf0oXaFMWjTDQLLUVr0U50CEUsIz0oDRWgBWgl2oz2IHU7caC+aByai5ahdWgXOori7sAfZd5R9Z216jtr1XfWqu+s/3nfWSuCvrUW34E7WnaHqtqqtqrtf2TzorH/ru//ZaX/9Ld//Y2+dUzwt3xxC/6Wj1vQt3xxC/6Wb9uGi3tSitOtjriljshwuEWIW0ZCZoYdZz1xS+uXni7hLfdYcR/QL61fRqLTvaFxH5SUnOB0byTuI1Iyho9Iz0gYaB2zsbgPG+i03VFdu12UlTUoaXi6Iy1vGve01OSkARfb7m8F3EcMT0tNT1CNjPvbxv2ihOFJgy7OSuk3LEE1MX47T/QbmJB24nm8Y/z7ZWQkEcwK9+6J4RJT0zNOiPe9E/0ThvVLSlZsgTTtOtE/KU3Zcb9v/JIGp6QOT8gaMDwpI4m1Gy3/DwL+6ekjEoYzNiNhwNB0R9wf+v0JmOz3dMS9O9gvi0UhHf4fnZC3JrjD/2Pjn5CZhkFShjG0jv1JIG0piUn98e6XYvvtCfIb1i/N8ttr/DK7duiRlZ4xPGlAhnXMT61jZiSkDEwYSOJPyMvPjP+I9AQKMDmjX7qd3n0nnk/a8KSUDOf5fO73N3mRnp6VnjTY6f+F8Tf11VRF2/9L458+IikjoX9Wx07xWakpyfY57z/J3073V0F+PTrZ8X4dSHe/4RlJ/XRZ9aPh2f7fGP+UVAoww++d7vA/YPmbU/NXX9XM+P/lxPrXb0RGYlZywkUJyQ6bb40NNSR1JFmXmkmFSBieke5oHwcDbTS5n+RLI74BtMF9CQ/aoXqeTtakvILigvzSMhlTRBj3MUV6IbqeMr5Et0kl23soBL2L0gm3qaV/fElJnl4tT8bg+D82sQW+w3mCvlPGwl0S7hLSdpbbN1oTr8eOw3zLc8bRuZW2Gac6qjjXb7M=
*/