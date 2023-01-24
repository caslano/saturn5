# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_PUSH_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/array/detail/get_data.hpp>
#
# /* BOOST_PP_ARRAY_PUSH_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# else
#    define BOOST_PP_ARRAY_PUSH_FRONT(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem)
#    define BOOST_PP_ARRAY_PUSH_FRONT_D(array, elem) BOOST_PP_ARRAY_PUSH_FRONT_I(BOOST_PP_ARRAY_SIZE(array), BOOST_PP_ARRAY_DATA(array), elem)
# endif
#
# define BOOST_PP_ARRAY_PUSH_FRONT_I(size, data, elem) (BOOST_PP_INC(size), (elem BOOST_PP_COMMA_IF(size) BOOST_PP_ARRAY_DETAIL_GET_DATA(size,data)))
#
# endif

/* push_front.hpp
n+Tg+Srmswc06vDnKnjeDfuX7CWyXnyWJA7yw+zEiMyl4xfnEOE5kR1Znv0GTLxemGMu6heRN6XH1ol2e1ibpzFWlL1FH53JUs3LstaY+lw1k0ae1yN89FHpCp+1ztVyxBxV41UGAS2mZCgYWwEr6vgMeDUIj/kVnQQa9T2J/vBKTTS1LzV03HD5UJIZr0ZyXMs8hCqwAtWCF+7VIsSBkOvEJ2g6MzZb9Qqqf3ilkBHX5LETsa9khSqhFdbNa7TeSH7Ap3n5HNcMIJYzwyvvo+g/kTIzGWGZBjH/WwFzYWiHGZ36PG8dXX2SVSD4RaXWv0uQpFrgFkFhqqkuEu00mW0lILk8m5gLGQ9W88SxgyrY31yjuFQrgXFQEs0HUV96Un2k0ALXUS1HHAmTOTmLrn8/wMyxPmv/s6e1ddLLhtFWkd0ToBxnKxCkkQtbOb+JRskFCrywg5fBmiyC+0M1GRWz750ZyQxTMvqaMi3YUnNKiEZZLkmTnjdYhgiuwT2WQqG9uAr1IOmcam4PjPUDcvQdBAlip+rYlaLaWisEXO958MxRivoMOY1Xq+lQHnX2kzhC0D9jbgP3U4+M3iV+Y0mZYd+F92vxCUTjM3yv8rZcB7GKDryC18Nu80oaBc9gmQndHIs1R6X0+NckVRfyqgqjvuJ5ofGALs6CXbUEIjDc+0SVzgL1vny+EN8dDT1zPU7mZUWXde9jTHu/
*/