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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_I(x, y)
# else
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_OO((x, y))
#    define BOOST_PP_BITOR_OO(par) BOOST_PP_BITOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ ## x ## y
# else
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ID(BOOST_PP_BITOR_ ## x ## y)
#    define BOOST_PP_BITOR_ID(id) id
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif

/* bitor.hpp
1qwsC7u9ditQ5kZeqOy7TFRMXWdq9xLQHn7Rk5UXesNSz5eSn7qbb9pjez5QdlmtbvCOEGnk3b2mUPu28sJickp7eR3Xh3t7NfMS0/b4Zo1be53I3Bctvx9u1v6EJFwlJ5mTg+ZkVXmL6epKrfeg7YCmpenby5ZUJ6cGtNiYWKg9G84pI8if70CVOSulO6KcEAhNyoIDRLKqqSeIdJp6bn216R3Vl3xpGDp3aKn76XFKkLeR5WVwjNWJbEFbNc9AT9hSPou5rIxWgwzSA+p0bJ5JMCbQY4ThWad1Sg0CuTg+afUz7uijq8dpzbsTyd50Ym0ibc1Fh3S1blKwi3IW3TVCNOy6UV/mbyKboSdWA8/PpB5N55k5K8VPDuAkyDhf28rpqjHBiMiptpWhXEbNF3X4ZT14Z7CfYBKitENVJnJM3PWIFHasSbC2o/bMq3O9ugAoGow1GeUQJz1Vq/2LMUStd9IgNlBWd4JpU1heW3VrR5agTBaGpU1W+c5LmPV4b26gf1bdnOk2K/2w2XcFeo2BnCOxMv62iE4jOJZmZWuMAPUqmerDKiOREe2pOeKYWyvWDgcoshe0Y/RrBs1JaG9f1hxIduKm3y5LMPvuKwMYyhQN5JqaWE6WaogkuaPzdXLSlAkzXrDaOg8fSGhLLkmi748yeCzEeJK2RdUixbMJl98lO6qwsQiO6dKxxCg9eYpH3jF5xwk0mhnHz79choanqUFPoNVoV2IC4PeZfn/tjUhVm25CJp9qFExikJEZX2PvjLo5vToY6ZJnt9FFo0bSUzTt/DOQdaJyKqIzel1snvHSOtX1m1uC59vH0LevklF/9Awy691aSHk2jZMps3KCuz9JVOTFMvMi6GCCRMMxjWeNxpP0yZtxn2wbqj1Hn02Sasvg1dPy4mDfXzaNB38apV4yaP0Gc6bE6mmzSS5LV6zGYXeYKyTykjRyJF/Hgw0tXTxLcytaegZHZYh+WIbnc2TqZs0uk+G5XIaDxjNVwhtDz2xu6appaW4plwqfzXIvfDqLvycG60qmx/O3mgrrEJli1kDKZFTLPvM/aiViro/2WY7JXdQPkVE3vK23Gu2gdcVShkdaGWQP2e+Lzx1WyNkT7JS/MOl3uP4bTSrXpZMkO2bOo/Cc1f2JYKKthlp+tWDYQ8gaHHO2wLyqEUzZzIuWusRo7VSqn55EONxlQVWZkaNn3AxJl8synAuL81jusKyQy7vnNd5QT19i0WGxHzYdUtqZ2QhnC8JzEBuRqIjdU1dXrJ3G6Dup3GRoqwLn7KF3TdNJuTf3qyx/v9uOt+2Zn8i7GFqDpVpE35sywQ7sjRgmK4XVSJiswQXPorB73u+Vm+hEzG3CJR26qLu4c276WT/tJlf54N+GyY6MfYmiditB3lVeSM4OWlXwQnLBwcLz+RuEzKwl+eM3fyNM7Xpm0WXgSL6Z1AhyTuYcsmior6HqXMN7svML+6j5SONw3sJlXgO28xA5JCd6lPZIDukZvXOyrUNm4n6eubbJaPJK4aLmerUXtCESVMdtZwEVk3q3Vbvj7pQef+K5IZ0Wd+xCv57gK7PfncGePzkwW1/24GPZGudcO2/V9/XK3tmo8Y3MRw0i65xq7Nsk7Ua2iIH3/rc/fQq/R2KmV3ZMa9cgzJO8ayBn782Onpn7yPM1+mymuI4581UmI89RGXJKgmCCqe/2cT44p6Mr46f20wzg3LCJDU9w8sgx7/nrSKtJt9dNmLQhpI/3mkK1EeyxTdYFVkrCFO88pA75gjUQpEkJHWTSvU6TQw92xqUZIu/12LVWFTa1K7qGqMdY/w05/4CXlS0PrrjREawm6OKbzXX7cZckhx4COXnS4/E=
*/