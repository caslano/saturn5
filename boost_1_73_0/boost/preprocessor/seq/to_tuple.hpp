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
# ifndef BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_SEQ_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/enum.hpp>
#
# /* BOOST_PP_SEQ_TO_TUPLE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TO_TUPLE(seq) (BOOST_PP_SEQ_ENUM(seq))
# else
#    define BOOST_PP_SEQ_TO_TUPLE(seq) BOOST_PP_SEQ_TO_TUPLE_I(seq)
#    define BOOST_PP_SEQ_TO_TUPLE_I(seq) (BOOST_PP_SEQ_ENUM(seq))
# endif
#
# endif

/* to_tuple.hpp
UAtqgx/Ugbq6pbMBEAj1IAiGQCkoDWWgLJSD8lABKsJQSIcMGAbNoQW0hFbQGtpAMIRAWwiFpyECwqA9dIBw6AiDNdoDw2EEjIRRMBrGaNY4GAfj4VmYAM/BRHgeJsFkeAGmwFSYBtNhBsyEv8AsmA0vwhyYC/NgPiyAhbAIFsNL0Iy6uQl6AO7gAQWhEBSGImpL7G3ivgO74G/wLrwHu+F92AMfwIfwd/AijTcUhWJQXD3z
*/