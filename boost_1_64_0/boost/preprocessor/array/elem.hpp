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
# ifndef BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_ELEM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# else
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_ARRAY_ELEM_I(i, array)
#    define BOOST_PP_ARRAY_ELEM_I(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# endif
#
# endif

/* elem.hpp
ZZDNvikr0v1aDcLijoRKh41h2LnSeZiDmoMyKEc4D3wdD2MOawB+5A5tw6PuXL6m7UrytYNlTteoCX+LaFfg/JjBj2KPtQkn1dt1tD6AdSF99uDbzF+kHboRpOHYJnW2wO5HZiC+1nc4kxdhOwddA/m/p3m7e84HK3QK9n3QOwm3u4j95KaP8F2mC5VWM3RhwpuYLu4i2h4nb/V2t9DDjwP08H2mh/uVHo5d3SD1AJDVwyW+ucTRel42IWd0tX+dZ7SBh8ud0WN4OOyMNvLwPFHW1aKsa0VZn4I8NlB+DqT8/NDX7pHwMjMsJxlfPlocLw8bHE/+VseTvc2xcgs55wk5q4Wc25mcZeptISbnKc6WtmN9crIwzn8cxsbd96INWEV19SBVrjWej55jfRDfkybO+hHH+2r89fV+sl/zblSLpqEzNyPu2txPtayDzmbY8P0Uvn9KG6Y+4jF01f0gzSSM0BE+6lQN0lyqXjEgPbF340h2sc8YPukXok2egfxx2gdA+yDvg0Mn/I7yh2oKvGU7pe5Lw78B7+D4k9uYfiMJ8QPnx4v0PYrP7yfjU2Td1e/ZeLoKL2Z29RjgZlz2uLIrYU98XPZHwvN75evZuKx2Luj5vSJEz/CyLMmB+tc3F7D9p3w+k7eVf0H5P1k5ca7kGdGmPwvaQ9kc5BL85nXheMcd413IdPM8xZV3T/+TYHJvzQusPwAdCL0RZhGX06XjcpYSnr8ZeXt44nskoUV4P2kRu6NM9MGGw4VkCDllFA/tr22/uA7mIDx7EdasSvz4Aw19yItv322iOHzscAjLD+Fwr7GYf2c0pJNAvc1FnldX+Ot6lUhvPsJ5Hoa+iZb4i/l30OcYPfGmdLzyryUYT3OxiHMok5/SCLwTvY7gfK5T1o+li+Sd1ah7gX23Wc6yRfKObvaJurp8EWSH7XJ9rSCcsRmerrSZlUTXZc49ajtM04P18Zyv/QdM9TNGcCeqsssyJ6MOwmm6C5VdOhlqEOjcH/YEHUW8zb9OZ0g9EIwWw7cLawJi0nNr+8FHlfUqlDW3mSWirOqFTck2rIGVjdSpLJtG2PWftQ8T4wPw5nb0SuE/hsR+1eN4XTI+ADyewfjwVZwH0uE8Xs3rFHwn6G0fg9M3Ez3WmLU8jp6LyjrenJE7xDdvNW8gera34cx8PG+bLYT4+3HE02+zbUx+0o+dMyQ6LU87z18l0Qj8JlMfgOe8N4u4FMcXt3MRDxM94+WgbCme/teNsh0Sd/adIHj0Wv2DJ/zzy7EHYAX2Uhwl1oxWsjClQ3huQ+64ejvxkr70JJZHxYPi+e/fJbzhz/fuHsl84qnCJ0ZFHk4zaQCn4DYPlMYAdKPSkG8gDQl7jEMfV873xpNXwd6WaJqdJ8VjGceEaTZ6C83w6T65gYWcnW2xXd3DJ8bjZ3D4LA13bLjM2bkplfd4HUS8EuP5nH+/3s4+8h7jQwx2sKJLJhNZjcg6pq8/ymw97ET7Tuqjiaj+DiwAsbB+u5nPDQ/t7EyRbLl4v5rsNPAQwTclRkYtgvJi6tXpvnpF12F2RmxKJkTpBN99XJhel1Ny0ST94MnyhfjjiL8S7/h5d0Wq925R+/tZGPHSiMf91ZnCPjKwpYMD+oE5Q7vIpc2z/gFs24blW0c50bfYxfzc4RqWt+PApOY/rNvDDRgrvZ5gZVOOlUaowRzMZzLq4mQ1f4x9VZAhxWQ4QO2JR17P8eof6Za9tSX0dS6Fx5i+DiAdvBk8zlvk9xePFbhr+62gf5ukx9ydpD8f9O/gshj+ci88aC8ELb//Ua4jV6IvchHiXIw43O+cV4n97cChT2X57TV88fE18/eA76U8nyzuZdA=
*/