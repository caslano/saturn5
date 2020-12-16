# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/variadic/size.hpp>
# define BOOST_PP_VARIADIC_IS_SINGLE_RETURN(sr,nsr,...) \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
Pu1Pg3uN7cG9hHs546f7l2j9qd3n3JkdVM6LxxZsBWehu8bKCyVKsehWwWHtGKk1tn9e4tSJj5IP7MV4l62Wwf4znPAXdC1TcL8+gt3wrWfKb1d3fPhEV8ff1GS5477gE4biouDzBqNx68LmonuL+kNxmxFX26FsxeXca6+eXFBePM7oufnZdz/8EL5OUNd9ni5rjOLmc8bt9V3kz9A0XSPywXGJpkVc2G+OypluWp6RcjgnLjItjn6vrPD9Hr/l+NnaX0amUfoi1TuInrfXou7Vy4jLvm5PkfKtpX6fuUr8yXKeb5b2rKvWNE4m3CdpvUf9/AKUOMsD3r7F03lI5R2jmeQ/U/30POJPM15ZlBS543JNc5wc237W4dkb2kXeR+zam+L4iR3a0+8V/e3+KvwTrgFuFe413Osa9prlX4Dbq/I34Jv63XFv6fe3obsPsvIdZO/izse9p3qpJHAm/ER1XrW+1yVsn+q9Dz/AfYj7CPdnlX+s3KTcr7xeuUtpu2txByLkN+Ea6DWS8a1eI3/0TM69RuZIeztZ+o00/9+zV7Oc88RPl/ND+sco5w9xpP32yiJc23RTZLRVHa9Fb8/Ek7ah696KQNiYbk2OkU9HR47rgBvDMUw3753oReOd52mFk8SeuzayaHzs96JrfO2fCrP0vLX6tloS3sLas5umb/VPdSW8qXv9mkhqP8k49HeYH9fN+52k7zDX9YCa7sh7QEcFDTRQQ/Vx40h3l2A5WIXLLaBDuAdEvIj7j0WF1YVRf5fYujoelMqLNp5AN/Z9vTqwh4TXjXo/UeP+qPzMYd2TC+Yjwx7LaXr1fpz9+zPsOp/Y1Mgn3rq2jqeMR2sZT64u4EbG1Ek8iw4Oyg+xrEdrvrK8MVpVAXvKTi+sLMLO2KmVxdHv8f6d5ZFtv/s+yrHs8Wz10UFDA32UBRwAJ5DnimCeKypLy4M3F6uMey74Is6FS0W3ky/qeEbzkOGNhRhdeO8BaACniU4vX5QycONP4Dwjulki/eHPQ/l+COev9o9y3ainZaG/WXXcpXmMOIcTmweNvE0ZZ8E3YRlfNnUPlnXVRJ1DI+3q0H4/BOP6rH7Pms+g5fuN6KzwvWIC7FvFDAxclLLGVuTvRpIU4zxXXfKt9/5lf2r0rX2QM2Crno5eZ/QaRj3nw4+pe3Ib4469/BJ/ubyzfhSOfGJX9SL2XD5RdE8n3w3d+xpn0G5S9fdFmNPrKE6+D0tXefhzJdKRzznr/hbVuTjevcxdkv7Wvho+vz6D+hvthn7/qh7oywv6gyO22M+l9Hpg1WeG/ZxB6yZL+zS5xkbUAXakDDIkzCsv+3nW3uOMfI7BZi14NFxJWtZIWc7m/lPBmMlFM3X/jFh9nOprPaoei9Wj9mvoxtg3xLpOFJwl95ejtD0vfrQ94E/s5YQN8Ncx15it7Gp2Mt9C50Fqb9lbxHe9Odqc4mtjpvrS3LGmkbAU3b+f+1xi52VffbRu8NXRc1Hf3WH9Pj9a0nlloKep5T4POF5kq/TetY7xrd8nOyT98XHe2IIuxOpPX5HwLwMZoXDpT+hnrGc0H4rOG/4U/9rYafbih43br5b0JZok7966ew79WcqhnuwCn6llc0Bkp5PDeHOSSTBvck511Ge3n+p7R/6i/Aw3D/c5bhfuC9yXuMtwB/V8+wr3Ne4b5be47xx9Df9e3Q8xxu7oCN+Bpg666o8V5w1rbO9Df5N3HOiFXaf3Lsm0nPeUnZ737tw8twwTpKwzf3JPCGestyLP3VNF/GvxR94jrzb2WEb9eg6FP1+0z5XO6fXFFuWbpdca3bekYoCRz5Jc9JRfEnJA9GeHZmvqG1Ai34HitcU+/eQ=
*/