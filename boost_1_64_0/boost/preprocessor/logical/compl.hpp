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
# ifndef BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
# define BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_COMPL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_I(x)
# else
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_OO((x))
#    define BOOST_PP_COMPL_OO(par) BOOST_PP_COMPL_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ ## x
# else
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ID(BOOST_PP_COMPL_ ## x)
#    define BOOST_PP_COMPL_ID(id) id
# endif
#
# define BOOST_PP_COMPL_0 1
# define BOOST_PP_COMPL_1 0
#
# endif

/* compl.hpp
wt8y0xGRV/j0uwXRV1PrK0U+OHLne6ybSLrXd2Mil7EfIQsOihmzBtZtPaciP9Gh7i7r7jqfqWPzYL6s47PWxCPhX5v1BzxBwZD9WqsW/YK+78t/Pzz15ryP/6xxCd4/llTXwmlXvhMjfNPZO0JWfp6ALAuM1A92VFbRaATfV2vp6ehtlPOV3RmZV9lhn91Tqadq+hWkz3yi3eZIOHyIBevyqItD3ift9DmQ0xxSweh+pOeqyTlTj+ebPVJu6qbcNQ5eeqqcng3V+OrnOuak08WQvvcTZoH+heYOQ0wO2ROsqZuVN798pemur79LmQy+U8V6Xw1mUvJThGLEcxpml9q8NewGT26LqvJ2sK5h0jZ2ErNh1ijT+s0u2jY+Ed4qbxPzmlZQ2YxD+p4LdVL3yOPm4/kqaO3yVSLOYfNmh4YG2bUq639yV4uFNlh6lKPMrrotrnvuyw9NmbPtfA0obFPD7R1pC792Sbc/QngL5d+ZiErod2zWUvikcXdEvhD8LoAp0wU+e6RLfBQuX9Szrt8gdjqLQzYWbmyVHLTX4HnnL+yPXtgzPGadhUVRvV/Ebkw/ph2y2mRkdW5Mq8xq4OXeT6/UT0un+oR4Tr45XJvPXC7rmaBhtRvoFy6LKilrFdW6N83udCjlpzBFmzeUMQ/8isYrF3nZs9x1mIi0dC5qcm7CffMpBPxeyq+3dFzTrb8bJ++7X7lsgRnPzbNfjlKnXrBA16P8EIbKkNVSf0P62LDfoCQcWqGX1wfFhV6aHLcfYrHmNqGj3397pfdhmuXqHPLePr991kFTcIZDd3tT671yLO6ZZFNn+dqG7u2rTe99QvlFjbAen4twmoU2831UTZN/sXYmsJV+UwD/7Dz7EgThs06HttN25j9GGXTajhmqrbZjp7q8Tkvb97zXjiEi9j2I2Il9CyKI2CJijy1ii52IiC22CGLnd86557v3u33tjOXNnH7fd+65+37uuec87I7dR0jcZWxj+k2rq2N693vyyuDq/d6+ylIzXo26d9y8mPpF/QcenbU4oKN1JRe1Xomw8hq7jU/hvt5K1YXrymKp5327g8+TfaLIzsGJ30+0LyXTwRrS2PtF7RyhzlYrNMKQgdnIEFJMJSuk/PYazzJxIgy7rKiyuDv70Pniy5Zho5UcJ6nUJBS9ZRvs1ImQ6ny8eP41rqXphw48mrES3N+MbLBkLAwtQ0UZlglliyph7bpzWyS0m031stpaUf0vS0JJw5H2bXdDuBSbVDpO6labN2lCMe0siHrJC6W7A5ND39fi1l5591ROX1l8jjy4HUgF0RCq+o26xki48G3TOw9ZGyRPe+419CTJZXKfUBN4GvOGkEVd4Qkk6kNq9AgLghhccdTvNFW6LCYr4eDTx8zt9LGyb+ji8NDQ0PDhHmTFGnR7+3ber2t9kGEqZdXXpUvsLNbKQmdRUkwCGOUuUT8d66c7bLIeG8/fpudplY/dpUGbGJe3t0xvZDetgx40XQ/DyTx8F/JU3UKMEaKnfTuoMQuokqmOAFR9/mEf+GbG52cJvdsGa3rXkfyd8+/ynOnQDnP5wvjskbOz1YXaUXqc7U8sLl6LQnDav4MbBppi+OzskruzDOLsf/Tds6mEYTeVpa1fZiI+RX9VplMj+ltSdqrx3ikm05tvASmCFLkCLqVZNLIqvKV9qSUKqP1+YA99G7mgvieqML+0sMUNzgJU30Wa5mWTl8xVh0LP3ZKiivKy4nTVMFUWxX8lQOjKMSwcO5lKxC3TJHu87iX3kycXer/KGWn5zGuoCldD6jrtqq6hN0w1ZmluJKhnTJo2P05xPoN/bz4+ijZZCkxs3dMBWi/X2j3axRbfnXo=
*/