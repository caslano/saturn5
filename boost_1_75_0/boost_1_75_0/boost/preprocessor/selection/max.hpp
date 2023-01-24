# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SELECTION_MAX_HPP
# define BOOST_PREPROCESSOR_SELECTION_MAX_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MAX */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# else
#    define BOOST_PP_MAX(x, y) BOOST_PP_MAX_I(x, y)
#    define BOOST_PP_MAX_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# endif
#
# /* BOOST_PP_MAX_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# else
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_MAX_D_I(d, x, y)
#    define BOOST_PP_MAX_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# endif
#
# endif

/* max.hpp
Ql64jhpgmjyaOvy6nHsn6SbC6Xz7U78m8Gf7aJ++lYP1s1YBzIDCoLEj+GMoaDX8NYf8NB3NG6FqV7VhwbeXGOjZYs+er9C7xTmd8DAwq9WtDg9a1/dOYq87OUxNwUW8RFgP3vIMOr6ZzVyz1n4MMwn77fRzjmGBIeKdXFt4eF/vHgsPQWYf39ahEarZlnGJBH+TGdVxOZ4gy+5JmCfGCg8XdWkJb/FnePmDngj7MbmM9mV/GS3ceUyirLfR3WblZtWLqiOJQPbcO4+1eDWH4ytc9lknvGaMHFueh07VMV7weCpIpCuEdqx2fhybesM5rH8rsFtwmvzmVn/xqZ8wwDWX5+JtyuPG3tx5j+THJCDRek9P8OniEQ7BY7e0e16epY/VsIuXXwB7zeHt+iQ6Ke6IQScX0QZ47BJSSnvru+CfgS96OXpUa9s7Kcr9WPCgfDxHwOP+6vb+sYCea/WzRwwMXz7wJ+vi2tu1VVJcPN/iiq3ja7kuAz/hoNVf3aNB26STzNAVHWgFmVpqYfMEpGNh+2ppUUQ3YEVHWCSTulK3tX3ldAKQIQQIWC78+flj326xInBLsXsm5w2gqbHRp4/8MLx/O4jMTMPDA14hO6EyUZm3Fuyj3lx2FXfTbvqQdNbhZvYHiK85P76kZWHh9mt+WXNPc/fYCYHhSWZHYYiPAaon4yZwsxuZcraeKZrZKba+IbkEwXNZgnQ5
*/