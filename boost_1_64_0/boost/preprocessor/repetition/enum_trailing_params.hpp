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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_PARAMS_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_TRAILING_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_PARAMS(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_TRAILING_PARAMS(count, param) BOOST_PP_ENUM_TRAILING_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_TRAILING_PARAMS_I(count, param) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_TRAILING_PARAMS_M(z, n, param) , param ## n
#
# /* BOOST_PP_ENUM_TRAILING_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, count, param) BOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_TRAILING_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_PARAMS_M, param)
# endif
#
# endif

/* enum_trailing_params.hpp
QYfzh2szmf/PH/6Pzx9Gf0/bfsfm0+f4+nsGdDOQ9qQXeh3Ik/ptDuEBQ6W+hD4GpL3Or0OfgNS306HnAalv26AH2ndQdhV6Vl+u8tdWG37ij9Dh68pV05st3zGJdN0Av87yGewXvbtcHXf8DPjyXeVq/zssXwtf97Vy1fdOyzfBb9yLfcfPh1/5/XK1/l2Wb4M/eqhcbd5oeDMnUfLLcrX73c5/bf6bcrX6PZbPwR/8Q7k6+l7LH5xC+FkFmPE+w5s2dGdRhcr/gOX7sD9/XIU67PiVmp9doZpm1Bh+tXbvvAo1YbM1Xwu/tZgXkB2/Hn7vxRVq9QfhXR7m+P3uj1p+I+Y75+C+4zfr9LwU9z5k+a3w6vkVqs/x2+GLb6xQ5dstvxN+7WsqeJbS8rt1eq2tUGs/4/zT8X8L9ndYfr+2/w7MP+vir+PzLviHLH9Eh+e9uPc5yx/T7n24Qm3cCe/WcMrv55bxz1v+hA7fxyrUMZceebUZzCrUTmeeD1/+3QpVt8vyhbX4/0Pc+6Llx8AXj6pkLtLyxbUZ9KdSle1z+lSL/2+tVMe/b/lp8EX3wf/A8tO1+++uVOt/6PQLfutu+DIbHtbouTCOtumFhjdryrkJVfS3LF9bS3wzVWr/iw1v5jCL57BW9lLL1+n4NFTR9li+SYdvPv2QqhpT9ubXWv3kz/DNEd8W8bmI74v4lRG/OuLXRvz6iN8Y8ZsjflvAD9H6U+v1X/N7In5/xB+K+KMRfyLi82el+XERXxLxmYhviviOiGcMm+JXRuarIn5NxK+L+A2x+xG/OeK3Rvy2iN8e8TsjfnfE7434AxF/KOKPRryaHaV/xI+J+PERPzHiyyJ+RsQ3Rvz8iO+I+L6IXxXxayN+Q8RvjvitEb894ndG/O6I3xfxByP+cMQfjfjjEa/mpPnCiB8b8eMjviTg03/YbaC9d3V+nqv78k2bZefHJmJerOs8vrqEl/NdafdhmMY6A68dqOWLA6eat8Ua7oOSa+24S/oVtfArQZ6Mk6HXAelXbIDeBobJOAhaz1MVyD45+Pyv+nH2Ye1Wk+93FEJPB9LvKIeeD2Sc19b09P2madf5ftB06CYg4Z0PvQJIeFdBs88kCe9G+B1AwrML+hBI5p2vi9ZRrqffCQpkXAfdBJJ9UNB9QMadK6E3gdNlnAe9C4yUeRno4+Ac2VfwMtwHo8R96BkgGYdC54CMQ/ug14DRMg8GvRUk66LQe0CyLgqdN8+PQwuhJwCZxyuBngdkHq8ZWvcBnuHnJdhH4efx1urfn/Djzi3a/neYa5N9a/AHwXmOPwR9HJwv8X25nYeQcWcJ/AT4Yj+vYObpL4zm6S8K5kXK+c2zZN0RmnGrHnfasRx8Lbzs01sLr8exl0Tj2Iv9ONaMywan5iHBPzHP8u+u46Bvfp/cfDNP4PUTXu/TyZfyBD9mgS8vxdA6vAX/Ynh7+X0YvrXwsq4j4Y/XcbZgR8K3bYHVVwnfbvhDQfiOLCC8C/38/1joaUDWVcqgG0GRzGtArwFa33Ng3UKrD6MjfTgz0IetC/FD8g86nic7iKxA0g9aLaL8yjwE9HhQKPahZwBZv2hc9PT1kV/3GjA9CT/hicLv5zlteg+P1kHzw/RGJunZ12zXvQqCda8tzcE6LfTBYF/hgWZbn0l9dLzZzkOM9PpO+vn6p6jFrWP+E/pk2pNIX4ZE65RSP89rseEZKvH5F/3L8/ti4vUuk17DRD9bqA9Bst4Frce0+ZIe8GNaffqOg14R7NucCB/u26yDbwOSvn3Qm4Gk7xZovW90pPgHr/eNjhL/4Mct9vX7eOjpQOrfcuhG8Ayn//Og+8AZMs8HTX2clIc=
*/