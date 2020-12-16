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
# ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#
# include <boost/preprocessor/arithmetic/sub.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/not.hpp>
#
# /* BOOST_PP_LESS_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# else
#    define BOOST_PP_LESS_EQUAL(x, y) BOOST_PP_LESS_EQUAL_I(x, y)
#    define BOOST_PP_LESS_EQUAL_I(x, y) BOOST_PP_NOT(BOOST_PP_SUB(x, y))
# endif
#
# /* BOOST_PP_LESS_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# else
#    define BOOST_PP_LESS_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D_I(d, x, y)
#    define BOOST_PP_LESS_EQUAL_D_I(d, x, y) BOOST_PP_NOT(BOOST_PP_SUB_D(d, x, y))
# endif
#
# endif

/* less_equal.hpp
mpr2i6FtdsWI1l3TiqJ57bk0GrZ2VB+cbEjLnje3Xz620LTPFoVaRW7INHTk8H5Z+fdmyv3SqLpDU4PLR/BVoLPzX+M7UA1G8H2irMwGme731tXr2vtD5MkXzNJVuu7B9K65G+qOqTxt1LRho/iGjZvxSu7dh9oNHZHDHQNy7/TTLzv3DkR/fL+o3PvAD8+911bG392O9KF5dxQd1E/dayjvO1YNkv62UmL/xry0bzAa81S5/cHLebkcfc+F5JRwp9TUDu6PE7m/ccHtFdqjhlKTI7dq0GJ0bdclnBBK1ZROyb1DPfl1iqRgb34/hLswaK+lJAX5LyKn8p2489JrUDm9dvnV475SOZ4O+cMeyf2yXnrWkAHuj1k0aNS7UXqNgsJPpDjJ64vjLJcX3aJ6NFFfcYvnu2sj4vO/xKa+IKh1RGrPVNWVxlt+oHag90JJPM27JUc42K1LOLd3wyl8mZBvBPJSt05JweRQ2I2knqqvACZnouXd0KK3enLhoNjcL44f70xN6NqhY6LkzYNgnq2cQA4FKWoEW6WnDB86YHjfwbGJg7L5BmhdurNe3vdWY9sP4tN8/ABSYhp33Ehv2rB5w0Z5qdNHDq5xvDk0is9PRSXiGzZqFt+8ScP43EP348jEfa+wEt81xN1K7/Jc86EvZMBz9EM/Hn+noKZNWroFRezjOIo6ZjZ/qckqiysGDaHN6tYUhe7z1+vE7k/I/cVzmDCF79XX/4TzGZ41JGtAofuqDix0z78+XLs+yr3/RcF92kehufdzT9S065X2qaZNVlonTZuptCs1ba7SvtO0eUoTq0DbqLRtWrwteZpdoO1T2kQt7WGljdTS1lT3pX9dS5ugtAe1eGGlfahpPZVWytH6AK0TWlUt3hi0MZ723qy0OVr9blXa+DIF2lilva5p45WWVE7rZ1WXmVoZM5Q2TNPuU1qUVudFSjus9cEKpcW7e+NnRJb+aEmzldjAjbbMYaPz66u2LJpiS/WLHJm62ZJfQrbENbPl9ectWWk78s12W95r5ciYNo6MYtH9Ks9vnmXLJ9exBiou8s31liRioQeLOXLdE5Z05L2elcttyWnD/mC4LU3Jb+SHllTmQOHAKEuqfIFdMZhT5jhyWRVLFhWzJZEN6qxzbYm51ZZ6sY50e0BkVz9bUlZacjjekrrrLInfYcu1gxxJv9iSx6Jt2bqA/niW38zYYEtGjiW3XmbJgKmOjJjmyNhXWKMNYv+40JaP+thSbZolD/KmVhpvaNRvbMtG6tXoADY/lXjlbUlfbcmmT23Wk7a89qbIS/RZq+YiL+9wZNEW0sy0ZO8zjrQ+y5J6d9lyfZQlGz+3pMFjlpw2w5YuAUcSt1vy5g6RjZdYEjzfkff6kJaF6Pq2lmzeZslPPVizH2Ftf4FIN85dyj1iS3IKe8P9lnS4g/78SeR5xqXRNkdWHBa5P4N8GI85B0VKNHbXTJYUOduSewdabIho93eW1Ey35fZvHOn6A33chjIfETnpoC09++CN3nJkQitbSs2wpNpN2NP1jMcEW/bTzquvsaXuAUvmlXHkqgmOBKtaspzxvKm0I2fcaEmYPu/TzJHvlzsypD+/B3KeLUE2ddOb27JklCNzb7Ok/A+WrKUvoy7BbgZYUvZhSw5FMya8AZhztiPDqE82z4uVtOSdEiLXdXTk/F9t6dRZpAzjMxibOHM0v4nDxnwk8VankY7H9Y9b0nkt9RtpyaNjHVmwypFXFzjy5Bnu/smSC1o48mIDR64dastdiY48wkI8cAr+Bts+p7Yls9+z5Ik3OD8ZJbJ2lyVlRjry1F30LxP+cuI9d7cjO8ZYMuYQv/ExzpYQ7Tl5pSP7frU=
*/