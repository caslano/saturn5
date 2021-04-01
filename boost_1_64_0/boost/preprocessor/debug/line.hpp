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
# ifndef BOOST_PREPROCESSOR_DEBUG_LINE_HPP
# define BOOST_PREPROCESSOR_DEBUG_LINE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/iteration/iterate.hpp>
# include <boost/preprocessor/stringize.hpp>
#
# /* BOOST_PP_LINE */
#
# if BOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define BOOST_PP_LINE(line, file) line BOOST_PP_CAT(BOOST_PP_LINE_, BOOST_PP_IS_ITERATING)(file)
#    define BOOST_PP_LINE_BOOST_PP_IS_ITERATING(file) #file
#    define BOOST_PP_LINE_1(file) BOOST_PP_STRINGIZE(file BOOST_PP_CAT(BOOST_PP_LINE_I_, BOOST_PP_ITERATION_DEPTH())())
#    define BOOST_PP_LINE_I_1() [BOOST_PP_FRAME_ITERATION(1)]
#    define BOOST_PP_LINE_I_2() BOOST_PP_LINE_I_1()[BOOST_PP_FRAME_ITERATION(2)]
#    define BOOST_PP_LINE_I_3() BOOST_PP_LINE_I_2()[BOOST_PP_FRAME_ITERATION(3)]
#    define BOOST_PP_LINE_I_4() BOOST_PP_LINE_I_3()[BOOST_PP_FRAME_ITERATION(4)]
#    define BOOST_PP_LINE_I_5() BOOST_PP_LINE_I_4()[BOOST_PP_FRAME_ITERATION(5)]
# else
#    define BOOST_PP_LINE(line, file) line __FILE__
# endif
#
# endif

/* line.hpp
wuwo2KAgRxedmsbUYy7y40Dut61U9m96e4HokLKJ+wQbHoc61IxQOuow8OgXORa+KTP1uNTt5fjN4WTW7TBRQUlYUL3pHoqrBsNT5BS/dHcNKOMJ9/IoxpkQsF1bSiykAexHfkqViofNgPaytg7izAC7oJV7xbJ7Za4akM0gL0OlTo0GfmsAJM2qb2KTDl3g56lLSj5ZFsDNhFHXuyLB3+kNOL2DMe+g5eFy+GRrTgzF7HEfCxqofPvVmJ2CQ5nCo7yYGds1zWp2qE0gT5qqhSPsSUN2lDmgcw7gzzt0nZp0ExNFQ0OD/74DUZZ5UGPclo4GqDHq9ax/5MmoTlf8kVMmSX67ZakGOhKWT+1KrRwXRPzm14ll79eHeGZMO/fsFwoCymSzmaOap8nJ1kd9/lToCbqkdg//aHbLcJRaJ3B0g2tFzEsmEYZz4J6EzSFi1TPSkDXmo5st6EBK6PVK3+oqmDSIiw0zxgf5SL3fDwb8hWw1TrbjaYNqSy2MdPXvx0DvVlMRX+b6j7E6QYfKrSo/XaR1Z3lgIEFfnXvk4ZAoAsTlgoQbHI8ljg==
*/