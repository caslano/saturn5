# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
vlbBF34LV8Gz0PXvn+5wvZ4EQ0OrfnfBm9ef219yfivbxoqN1se8pcbJAMZF4n/F0TVYI8ipUxOeduz/MmcQfCZiHO3cUVM0gH4eYkObnzFlyi140C/NM4RHmKYAtPMWiYvrel7LGaIVDg3/GJpoQytA+jsY99mLrwUbeYJa+di0b+4iZGHapyZ3ygA2vliO9NFF74wzScvd/WZa8zpFM2bxWkH3GsfjbpOcHOMOJsttT2MXZ0MMrmBXs2AVzE0YTFEP/ww8tGQecUqUd4YVEoPjhaZMyHflcZDRpAbrAqWizc+GRbJvd6pXCbRB/gSzroGtS06jOIeidnbWHh9/pmAfnogr41kntfbxGIe+2knSCHq0W5SiC8g6kI+8op+cxE/eXkmBedl/ZkbviAUKo4XXtKh+H7rBRQNPHP/++Olk+DO1WsxBgleP9gpPiVu7FvD5+7Hi0yt64Cs5sQdtSsQ4e+Zqrj2vP7o29IT3k+FfQnOuHs7kTyXRj4H+/ievQ+83AZi3ssp/ig+NjqChuYGZPE7pJfNG5nKnlG7pD9VcYE80ZdvyXDkz+QEeDarFXVfP4f7c0jI1nm1YabzZR82CVLsQn6WIoVhXh0a7NdM5A41vGjwmhCv02Wh+yDgwOmekAa9ySdfAo0a9yaZqZ61pmp97BmZPl7VWZhpsf4mqMphnIzoZJNXGmXVkTpMNdO+JUILJ5Ye9LW9c
*/