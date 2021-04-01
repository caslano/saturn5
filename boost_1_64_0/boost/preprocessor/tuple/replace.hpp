# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
# define BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/replace.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_REPLACE */
#
# define BOOST_PP_TUPLE_REPLACE(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_REPLACE_D */
#
# define BOOST_PP_TUPLE_REPLACE_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_REPLACE_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_REPLACE_HPP

/* replace.hpp
0iN7yErHzMOq0/4dw0H6FiZhxTczRNE3yTZ60YDCSKAn0BOuwRK+XOVn1FPwDg0zv87y2qwl1SvlMv5BsqbDPh0ZVR4wj73cWJxBkcdO60gNcX22XMxF4qnLL2N3lH9mTHIABqmycTFA+ypKi4KogO5rA5kURKXjDZNgz6lIrGfaT/mIkRJyjmSGlBO9SiEXnk9XvdksMALniRAdPyOD5GFR21V191Vg8k08iCuWjuGyWDq7jtMq3zxXU9lpEC1/OlV22BuyziZeah+eeqBG9SGYnx+m1IgIko6/Ui3w4kMx+0036UytAl0SsoDHIfRdlMCPMI/SxZu9vH8s96Ehm4KSHKQ/SfC9N0P6NnQXx9hr9M0dev5fdxFSAdhhDiKyEOYRg7xlu4426SS4NZvt3veOaqg3W46/67qwBxenf6YNnj+D04W8bmCAdH+UFq2ZG+fnuf3hLBEDjW6z3ll2nfKapKUcBAk4drk1hCfgi/bwvMFOPXUEpDDhAFbTNGTwhpzJw8vF7IepPNIlVW9s9ulvgoofh4YH70AXey7Ym/+AQBI+j46Ata28IA==
*/