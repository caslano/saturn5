# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_DETAIL_BINARY_TRANSFORM_HPP
# define BOOST_PREPROCESSOR_SEQ_DETAIL_BINARY_TRANSFORM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/variadic/detail/is_single_return.hpp>
#
# /* BOOST_PP_SEQ_BINARY_TRANSFORM */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SEQ_BINARY_TRANSFORM(seq) BOOST_PP_SEQ_BINARY_TRANSFORM_I(, seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_I(p, seq) BOOST_PP_SEQ_BINARY_TRANSFORM_II(p ## seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_II(seq) BOOST_PP_SEQ_BINARY_TRANSFORM_III(seq)
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_III(seq) BOOST_PP_CAT(BOOST_PP_SEQ_BINARY_TRANSFORM_A seq, 0)
# else
#    define BOOST_PP_SEQ_BINARY_TRANSFORM(seq) BOOST_PP_CAT(BOOST_PP_SEQ_BINARY_TRANSFORM_A seq, 0)
# endif
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_REM(data) data
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_A(...) (BOOST_PP_SEQ_BINARY_TRANSFORM_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_B(...) (BOOST_PP_SEQ_BINARY_TRANSFORM_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
#    else
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_A(...) (BOOST_PP_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#       define BOOST_PP_SEQ_BINARY_TRANSFORM_B(...) (BOOST_PP_REM, __VA_ARGS__)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
#    endif
# else
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_A(e) (BOOST_PP_REM, e)() BOOST_PP_SEQ_BINARY_TRANSFORM_B
#    define BOOST_PP_SEQ_BINARY_TRANSFORM_B(e) (BOOST_PP_REM, e)() BOOST_PP_SEQ_BINARY_TRANSFORM_A
# endif
# define BOOST_PP_SEQ_BINARY_TRANSFORM_A0 (BOOST_PP_EAT, ?)
# define BOOST_PP_SEQ_BINARY_TRANSFORM_B0 (BOOST_PP_EAT, ?)
#
# endif

/* binary_transform.hpp
dWlN7LT0E3RzpyimKOcE6G4k3aczZbu18wJlXgzzfTrCktLJbnkfA9luirc4M1ldT9JCX50HZ9I6sRZrybHqWvKR82huIB1tLemJj2XnxfN0VyHdyVS+fOpzfdPF2ZZyLgZ7tb2XvITi8Sog7yR7LN3GJv2+Kgc6GbowbZUth89W911ibJZD1fY9nMaWKSwJJ04ngoczG8Xb/a0ST/UBH9jlvQTC5pNdBzNlHXVvpepUId9fks7HpHO7PDe0XBDuCOjX5k+Q78oxOxXLYz9kg8lX0wfMjxvMfht3mcWOVe7vk3LY5X1fTxje7axqY78U9gfzF+Y/sGcsi7En38ZyseZdGvNp7Ad9+Z5aa0vcsEGivsZQnvaEuaiz32APkGj6INYRX8FSe4xzbyfysgRQ3mYqy0CtHnTnv1znLb6fIZ0WRUdbbwidcfDJ70nncZ3f6Fca+EqIdLYgnT+Rznpqg6niDIB7LVXMvcq5Bj9jiPb8YRV0tPlYXgsqc286le1DPPUfpO4/U0gWI+uo5d9B5VfnGOXsXtTbVNK5ysSfkZzMmk28PIP7K+siZ7gzKKlrHjm9L5HeZeZnzO/F0nmHeg7c4kPvVfcfn9GYOkO1xdbG70OYbT0mbb7kMbQxZifFiVPLk3E+vy+Q909qGk04eeowafuHC9Q836S17Wj5nvRFeuraUurw6saAl0m/Lz+jVfN8nWRj6F7L00pp5MhnD0giqKYRJBtPZv1FPk7KJ4DeoZWrySnbEc3mSgrLVW1OF/l1ry+t3q8k/RP6bGaVMT3PoAIJyxM85BtLOvUXGnM39dizrDenqjrukBNHuNS2RD2bW6iPxOSzHdZodvDbFtI5KyaV5cUkd9tvJbIE1Vduyt8bJX/tuUOH6guzi/YCUX0RVp8TaHP6XrJhDnL8CUadE9i5rB/l3SmPFeq++yya+1vZ2UiL23NfVHt61k0txXP2bE/quU0rDm60urGS/tOWKexcC8VR1nziOUpyOpXXrcxdT1L/1vyr37/bqR2OZZHp8HrrL48ltLDSz6sTyL5x5ia8nf8Yuxq61bYVeGZVdQreF0d/S0q4fEYCnqmY5Odh4vmM/B6Svh/aG2mPh9xqbEoaAaRxJ08j5vJyJY27cK/XWQGd1ZTPwsvUfCJ0NkJnDaWz0NdbOm9pOhsjdQYJnRQ8LFzLdUxLH0yKsySZBiXFmXkZoM/x7hRwRLpFiHMPjxO7dJOS7r0R6bZr6e6idH967HSXqOlew9R0I3Q2QGcd6Vx/IFInW+hsh856rhN//SdJphxkfPR8D0L/Pq6feMNkvXzgqYzdz+VpK4uUvH4dEXeComNbeWJvOm7oPED2rIxRdDYInbWWmbaPcP8g7h8CPwx+BPwo+Dccteue+B34Md31Rj0KflzgbwU+IfDJKGk9Bf6dsPMiLovA34OfBj/D7wU/C34OvEnc/0E8q/8j+HnwC+AXI57rX8R1ItJ4CfyykG8W8j9F0X0FfDH4VfAW8GvgFeAbOYrw+QK36t6l2izwz4K3gf8C/iv4b+DXwW+A3wT/HfyWyGcOR5H32+B3dNf/AN8C3g6+nYcJO94Fv8f1xPUOcb1T4PsCP9CV60PwR+CPxfXVQv4J+FPwLvA/dbLPwJ8rMoVFvN3C7j1C9pbuei94pQj/ArwP/CV4v7jeK/A28AFh/0GBX4G/FtffgA+BvwUfjrDhCJjZtGuTei2jGfcWsBUcA+4DjgXHCb14m5xXAt1350TIksB9wckivB8wBWwDp4L7g9MEWxQmuVw/6cAM8G3iefgqc9T3SWjaSWBj6Zl1Ot/d8ZxB8zzyd0mpsH7OVLoeWlUzqqhQyD5tUmQF+UVC9rY=
*/