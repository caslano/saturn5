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
# ifndef BOOST_PREPROCESSOR_WSTRINGIZE_HPP
# define BOOST_PREPROCESSOR_WSTRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_WSTRINGIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_I(text)
# else
#    define BOOST_PP_WSTRINGIZE(text) BOOST_PP_WSTRINGIZE_OO((text))
#    define BOOST_PP_WSTRINGIZE_OO(par) BOOST_PP_WSTRINGIZE_I ## par
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_WSTRINGIZE_I(...) BOOST_PP_WSTRINGIZE_II(#__VA_ARGS__)
#else
# define BOOST_PP_WSTRINGIZE_I(text) BOOST_PP_WSTRINGIZE_II(#text)
#endif
# define BOOST_PP_WSTRINGIZE_II(str) L ## str
#
# endif

/* wstringize.hpp
39SPsTXzJ7eu2HWuePGoN6ryHAyoiSy/1+kFjH4jrXXcnGq152bQxdVGm3r/kMW5vNDq7xta3If7MLqpPTbWtZNYyrDFCb2YbyqwO3yAo9MObE4QduHyS53C3G9FabOFGbkRouCbVRs4pjCddokLc5JY9sbRhBtpnOphsls6z/VYkDssuvtOHDD3SttwsqkntgTa81b5Ng25A80sKNHqJVpD9WkNnrxp+Hnx4d4T+3uGYOK3DCiitdFGN05m/bSPxupptJ/WT/ssyFZl6xCfrUJz2Tdh2N7QScrOYXlN+D68RwW7jJDg25RNo8voHMw1aG7ez9pwSUCfVfV1f3wA91n1dQ8O9mxW+dg7yXeQ1f8rrJ8MWf1kuAWP1U9GqJ9sZzQ2s98ly+6dRvlvpXNLp1P+F9fpZxTXYEc0mPYbZTYTv43NfFmLv+w4lf3SFrfsM6jsRMvcfrm9sT1Jop+vo1MppVOzyAh99qhRnQmaff6oSQBG+z3mXjbSQ20P0nzeSvXBei5TtK/LtOGkH5NWG05Y89dJkmOG6tmJepr9PZFa7Y9rS/nOoeB9jbrHkWLcppQcspPxgcGefhX7MjwyhC9hYRmRy+1U05JaSCXvI1G2PlsgrDvOr3b9P9PyfSONMzkum3meF1tf5+5UCl8gAhzmybXA9LbA9PYsS29LJO8i6a1D8i6z/NujXv7pFq8Pz1h9eEcLHqsP7yR6Zxt64MFas5xjtfkrKM8rWZ4JK45zF3ACdhLi83wUeIcjwfg1GvEOD4owvjZzJyDFcXIfxZx3Mbq8PmDNx15LvJ7LeP24Vz/89mT3BmMLmK+azY9eDzzGaEG/wf+0+n2esvcT5ndU9AvvjJ8y+Ma2v5Hb9sD3noejpzCeT2E8X2Dpy5uprc4nfbmQ6v+Wuj6a7uH+1fFTuvu292guOITL1yH5nkP030b038708W8sBvsdTB8vtvTxnS14LH28hOi9i9L2G7tZ61xmzrTPNtkmbDw1dpLtBehvGL2H61bA/ZEjfWsgumPDzJvdiHRuX97nm8fik206ap1f7myB+djxNCbTpzEbcanV5h8kGX6A2uRDJMMPM51/tdWnP0J5TqWx+HLK81FW5jGsHT/G2vHjVjt+ogWP1Y5XEr1PUto6Z09xjqIw5c1tLBjTvcusvn0VlfEZtwyz1mgVour3DRslLA8gO2P8Wa4HymcoT9AoRvSLao+qPoc9uGtYxd1r3Q4ypx3qwTdb2JS2FpbsxOeJ9oX/oznstYDHrHuar1PrcTWbyKDqKvUQfZ/uer4+2ct9z/a68vOJyzc/WKRkguCDEotjAL/yK+WyC+tvX97k67+D8AH0uC4q96eieZhvnz5dLCQnjV82Is4SJxCtm320yKPu33awgCxmgfW9W6y+96UWPFbf+3ILzed1v6gxnp0HfISNW40CAfm0xv8qX+PXuRNe9UfQ5Xc5f53KNXs37Ptk3yDc+hCfJ4IixdDwGKuI+r6sdDHzb6X44wPHlN4iv453U6Fr/jTfbDF1yEynJTETc8MDLs3+VlRgkZHJm3E+JvrN7yViwvxeyuYCbWKj+b1cdJvfK0TC/F4pxszvDjFt5ghdNEcwdxKZ89le7O3xQrK9LeFQ7AuqHf4Wa6MNde+oM+OG0aNvW3r0nRY8lh7dQXp0p0nbsPhwFsOtz81gbo2/jTv12YbvKb5OhTKLR7Sf8fuARQP4GQ8imncpGhXRTmdXfsDtdB3fix4rPmDNWX9IdbnHqvetUffh9f4xpf0JGz+3R73f09b4+zMq66c0/v6c8t9X318dT8oA0wL0Lx1X8VUw0qpCVTE6zoPxdLY1pv+a+HBtfkj8hvj4bd2539w=
*/