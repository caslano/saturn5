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
i+Bqr6B+a8QDP2HW5HX9lS4nd5L2nRxPovq443buX+U6y5tJgG1v4YWR1o9zNtM2JUHRRDP0shA7uHnEIdxos2IghIVS7di6vJEosOKkwZnY+wHA7ov4K8bxbW4j/17AYVgb+YmRcqcZWbO5aHRuG/Ts7MgBWb57U4JohS89e7RBl4dVfFEkWX2NBRTeA1nykM43ZYf6tJsHvZMG5XJT2Lu1UM7iZvM3moEE8Yk6iRSBqpVDClJDVb8mpe0fN6Zu32N4Ar+4iRM/g2pv2JbO0yex2jXRBVFyKSYypS4KaTkodzumQtbQHdtBOd0aOG2yRVbHlDew88mUW578Boa6U9In5SgtNevPsHeJ11qar36D9D/TXUPHOPOdpD5gUQtJvT1xYNpeUZBVpACi+zZOXXdAr2HuzUtOL++qnT4qW9BfIiDbnIFm8VLlyTokIo5Ri4hwaz5Han0g+tk5asnLDenFh+K6EDHnBWvrqHH2YPdTbCrmCu4a+VXw5Of+9tuz5pgxy6nakMrZc6RRclw7wu2Zs7DYCM2w5Zer41wWoeu78wkUsr3GZxY+YQ==
*/