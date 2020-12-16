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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_II array
#    define BOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif

/* size.hpp
Y/GoLt/OFzAYdo3Y/N04bNTHgp/ifDf4G9WEMfoA/UCHl3cReelNdKcbPuc2ZCcNrD6S9arz0dMdxOL476bzsJvE/NUjiSleF8m6jDbB95EnU89FuryHj/gG2V2E/XgT37QBfSnH107BlxdhYw5sAZM8z3qHXdQxG/nD1zd5WOSaF7FZHuJ/9HY4nxfD6Vcx+BB52t8U3pOjeOcI+Z+bRca+BCbGP97zOOP8BXsBIstnNkOO+T2Z9ny5C34/hEy8CibaQp5jKWW49kkRsrMJG7kK2QJHZsP3S9D1DfjiRT9iR3Zjz87XRadcdRNNzi61yXXEwFWFtPEUcFMWuB6ereyLr0VHF1+B3yauzFyuyfzbdVmNb4/8lnMX8W8fvoVdoA0bPWCBqWBs/Mw8xvuWlSJFz8Gz8WCVF8gFMF57HkDmSxnLHtxjZ3ywSy8g4zUzifm6YMefQYbw7wfxo3HX4hfPwkbj308eRQyKDj0HDqxEBsLIU+jYWGNv8Xsussk1zcl/DcTW3MFv7J6gQ0vBelnXIh/hxLynsNLkSV0eK8AuFcD3T7DRN+ty3hib/G0S+5U6sMGMjxs7lF6lS9F6zjwbR45hEbm0DtisKpF5YF9pje93cH938inPgGvGYwOxP0N7adK2ELsIZvkBv7SXeCd2KLYGPVsHn74n3il5GnmJYVzxKZsPoa9x2AFwxCD0KnIT+gOWGYcd/hLsXzCBPMcY2jVMk1176D/++PpLGSvs72nErHdspX/X4NOuAdfAn/i52D7s51J85a+FyMCnrBMLIW+Qzbqmk8GGyPIqyvZgDO/FzuUTj5/sEtHQ9cYO7L+BPV/EPkQw7h/gd8F4N9CPSbTTfT/jT8x0xSuMH/LzyIPYo15gkNvAA5ORtcHwaS/3YLfPOIucUyN0rzFx8kAwlLE2ph+Ytj06+Tl+Ft8Xgw49iJ8+xPhkz2Vt8RnoJhjESbwVTv7m8XPxD+QIr96JLIAn+h7Ed+0DD6Db6chbS/xX9gtgbtqcuQqZwbdGIGONiM135mB778U+gAHH9oFX+OOL5+Oz8atvVtpk6wx05H38zRZs51rafjFyWg1ufk+TDzoxrgfFzKm1gjeV+8D+r9Hek5CTPHwueZY+92syhdzqEHgdC0a7HRvbFdkYgI+e35xxvRgZuIa6sRmpYeRA3oQ3F4H/dN73ySF2fBy7sxRfTw6nHTHDIcaj1x7o1NWRXHE6mOfzJ7AtG7h/KJhxEzruIg6Cv1luYh9wybsXEX9egp/a6ZXli88mBsSW9cYG7V+BbryCTJHHfagV2PEdcPkQ8Nk+cGZ3zcz7Pk3bDjIeXYh9+mPX3NiZ7WPwXeBU4b4WXFv/suHbeQ5290l4P/ArxgQ5b7sff0D75qCLo84lX3E7MhoFdqU9We0oUw6vsEv3g4dmk2vq1A7ZRz6/oo3LYojhq8hnP0ZOdCBxEnFrs4/I/fRm/MhbntECnAk2rSKO2otuLgInpGIfJ/Pct2rAS4nkp4281UHyRpOIPbCJny6Dh7HglXPRr/7w0sCAA+hPC5uMB8PkQsuOgOfE6UnG+uJwYswE4TngYtpcdB829m+afHshfUsEDwiyBU9aJeO/70QWyYXuyEP3n8Yfk3vSPGCQ+2k7+MqdRN5lKs+KQ7areXOD3GHKR9iOXfiCOOK/LOITcN3P8PZlfFM2sf1B7MHlxL1TO5OrewrVGIQ9B7c/jL/qzO+dV7FnTCWxmJ1YvR34GL+qnYxcY28vac14Et9Nwe6dUyXYDGzpSehcFn6mG2NMPuptbE7hdOLveegK5eeeA9+IKTN+QD8vZTzmgvHCsAvE7o6PyJ0MQsZYzxYPD28hproHf5E=
*/