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
# ifndef BOOST_PREPROCESSOR_SEQ_INSERT_HPP
# define BOOST_PREPROCESSOR_SEQ_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_INSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# else
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_INSERT_I(seq, i, elem)
#    define BOOST_PP_SEQ_INSERT_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# endif
#
# endif

/* insert.hpp
iexR6nICFU0oSvPqbDPJYSJbAsfeMGJBYBbiD/e2OcAcVrl/gmDYE1OnFOes57HvjT/MsnlhBtRHvnEtyUw0O+HiUDdT5QUZOuKGxyNSEDGIHEQIgoeN2hdFuCJI+8fM/bvLDvSmgIjN4GpHhh2KBfCKkOVahseNSKxg7LfEETVLbpTLklN1DCmlRrSrN8tOYk9tvDnyrB9iXahGjRbqdlqrx3Cd0wm4qDRm/DeSWE4TS6xjJ2dEtMb/FhVMVFvVNJuMeJQx0eiM60JVc5Iti0nn035RjkCFPoOhp9PF2e+Pt5UwKeMs1bUpMxNcawaf82u+GbEmBf+KEI6RZB2Qmh6MFTNpZGQ5nY8sTr2r5+w4ddpxCts1G0s9hizmHenAyBcYD7LIkw0AXMEELt/mItTiJH8QNqOUD5KWPPDFLjlPFxMtsu6tGghNWc5XlKeZ/7o8gn+c5v6ZYclpyeyaXraTM85BMUrlP0LXWUeYOeSXVK8/XtYd6J7U+N7yuINjWPvvg0+7TQ6eUn59RB+GLKkoHMvOPu199JeXpXHLTNUfONM9VAjPIGwThL1Hhrg1yu7UN39VV2et+2Z7l9bHcQYZH0VnQKqXVBVduukSl6GPJQTtzZC48ZZ3Nbh2RHy3+EplFPJqRz/7jMSUSU9JgD7TJPL6glU/hgosafzE3hSjf1W6nSQpcnfC4S285fop+W4ezD1+2I4g8MKl
*/