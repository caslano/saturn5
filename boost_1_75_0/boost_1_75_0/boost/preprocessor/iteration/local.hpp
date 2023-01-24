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
NmdFp+6PqKHgqJfsNNNkXh1L1JWNtyL3EsfhR5v5JxWXecWOfCDl8TIBlRX3afcvYDX2sgwhmuyT4ZVLTSmcFzKjvpsBV0l2cGKewY7nWk0+933aywDg2wKeyjCH3vRrJ33J6TD3XuvFj4VltInJ7T+vDItZdnJYm9Cyomf7XpKOqQ+wthXvvkXFoHdXs7iegtkT1t+qoZoiWHFpN8oQuIfR8ArSo0mVoiwvOGzi8jgFawZFauzTpAW/Rtr7WwHgrg2QaGKNx1Jlv20Tc/0a2jHjpbdiv5KUwAesakn+hU7kt+d++YFDMpq1EuVIjBon4udXqk7LwVtBejfoOuUkyax8TcpJ+mFXSVs2H8aEgd+H/GFx5RGgvoEWuz/DTywPEAorpi8XaZODzgSyU1Yl0K06B1gfoCmGpd97qBQdoHf8xzLhBetuROFZ7qk2gSv7SrG3WMCUXm7Ikd0xffKaI1feGy4OnO7NxTdPf5/ipnU9rbhoavDwkuoesMLlnNDc/iMjLjHMG1f4eory7nvsP4pdTcm4yVxZwMMvUF3k2UgElBdej3g+Y19j9J4FnPYjvSNWfgyK2ioUFfee/kvs1Kf2rJ0dQAKhEUJgexWStoGusvX9cp2a0OiJIxk2JMr6cp59WSfK9gK1/nHxkn0ZA/khfDTWuxuIBBz1rtV+oej6TrUteiQKhRyFN+SGrIEuWXtBD7TPVw94Y5SI
*/