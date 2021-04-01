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
# ifndef BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
# define BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LOCAL_ITERATE */
#
# define BOOST_PP_LOCAL_ITERATE() <boost/preprocessor/iteration/detail/local.hpp>
#
# define BOOST_PP_LOCAL_C(n) (BOOST_PP_LOCAL_S) <= n && (BOOST_PP_LOCAL_F) >= n
# define BOOST_PP_LOCAL_R(n) (BOOST_PP_LOCAL_F) <= n && (BOOST_PP_LOCAL_S) >= n
#
# endif

/* local.hpp
+hJt/UmTitB+e6VRogAKTE/cGEmPbiG6+NvEPi1IocC5GNvASa1gIsbeOAohJ4afstKmFxaiGatHoi1DtIyciRvSjb+91W4zy+JeA/88nIyayM3MDkbY26wpoCBiG17FW9dpoB6ilxlNc8pC1AK/dbfRMxQdl+vWKxnOj5yFEl4xV61w4sI5YNMdnS0OR7+ejLBlVPBBzpN/VR7cPS15Cd9qBnWjDdQSmbgAQQz2uYhL6zY7mdxWFiyD3FUqsKsw96Uyk/N0JMQ3MUQGaqDDGiDMiN9TR8I9P/GCJBGPqGAof/ixV8w0ZHq/BhF3v/uTeXibRa3go/phnxptg0IdNPuH/mIgT0Ifj4Tl+VbDatnQoXusVnpaEQZeEjxi04kcqYqEcQUVSU4kM/K7Ah6zhX6hbSjd6J1Upl4hKdDECB3+sECKe+JuiN1BgfrrEyGhXr6lVaZD3zbGH6fSZt8+SuZ6k+ypivHFTKeOATIjztW69Xc4/OSswvjXNo3pWaD5iRoWT+Z4GrZgpLJ75GwFkymHMCi5ZKSY0nZCr3o7r89k8FhP8chADlGnOg==
*/