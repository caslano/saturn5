# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2003.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IS_EMPTY_OR_1_HPP
#
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/facilities/is_empty.hpp>
#
# /* BOOST_PP_IS_EMPTY_OR_1 */
#
# define BOOST_PP_IS_EMPTY_OR_1(x) \
    BOOST_PP_IIF( \
        BOOST_PP_IS_EMPTY(x BOOST_PP_EMPTY()), \
        BOOST_PP_IDENTITY(1), \
        BOOST_PP_IS_1 \
    )(x) \
    /**/
#
# endif

/* is_empty_or_1.hpp
PIlgQf3vCVvYhX6+c8JfY2JAZfsoewX3NYeer8yt2pA5MipSEp6/DQG8R7IzBRxW4jbNSHgGRc3kOvykKiwRcRnXCnMbh9OK3uufZHjVooRWgarPh37wee488g+XbWR3EDK5Rx8Ycxz8rJJlWk9M2AE8MRjbK4pdvOTt0YhHbxour8hYz3I6+584NAiPVdKVoJ1qkI72+RwhnV799Zaci+yeouDgyqmhClv4kapu3uh4QECFzhK1z4NW5CaUMPDJn4taWvXy9WNB+kPIveD+oY3xoQpDBZ+yCSUSOMzeop69XDw9QTGgaBlKXgXz7/TLAE3APg3IAL1CLENIuqfBQ7pNd/jU+d6dso2uYlWuKj7ln7LPchdPOvLBnDkTwa1thW8evLGKsVPO2TJlVrNO9AO2hQ+CbiXwHt7ObigMg0Q7t7OOv4RGPDfad0mgGdwSw8XEwUbG2aLVpq2C4sQBwEZMsT4Sqe6F6n+ZK2XPo3t8oKH2xnS34/ZXayUsaeOYw3h52sKVhDWqpuM4FOXyiyDxTnlXaEj6SJqEXo8mZlzjHolodMa44Qg5fw==
*/