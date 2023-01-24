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
# ifndef BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
# define BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CHECK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_D(x, type)
# else
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_OO((x, type))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_D ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, type x))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(type x)
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(chk) BOOST_PP_CHECK_3((BOOST_PP_CHECK_RESULT_ ## chk))
#    define BOOST_PP_CHECK_3(im) BOOST_PP_CHECK_5(BOOST_PP_CHECK_4 im)
#    define BOOST_PP_CHECK_4(res, _) res
#    define BOOST_PP_CHECK_5(res) res
# else /* DMC */
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_OO((type x))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_0 ## par
#    define BOOST_PP_CHECK_0(chk) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, chk))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# endif
#
# define BOOST_PP_CHECK_RESULT_1 1, BOOST_PP_NIL
#
# endif

/* check.hpp
SL4vmAduYb58z8SyeY6G8wvm8dgFM9psFjvd06Z7WgbvFO9mB90QsW8+/Gy1uOw+PbnJKx5n2lc5C3wk91od6HqNoS2im+mpwS/9dYri7xWv19nco1agS19mSMAKRxH0O9XcnaKbpJtvPl/+1X6vI5nquhV8slJGYt24sbwzUB2U+FyMmeZkCfKcFfQ4o8rZ7M99xQ+Q1BNbV3rnUN9A3IQLed+wqZadLvg5lkgTQpaTfrsE/ntNMitt5KdeyHPfT3afKqKbIMs6oqZUTm/zRY/T7PQWn0j3AK2s1G0YscGLfC0i2Tal2hTiqvZv8esAwhV5f7efVWVkaWA9rmt3NxL3bL+LwII4KmGOCC5l14+6LMITaR4H4o0vAWHrRY9kHTw3+P6YaVHCHuG0F7J4tegHo2fBGroAXUm1XzaSSS1bt3fHZzeWoo/iGQOSaqVN4Li8KWfT1TKpq7LBUA/MY+g3Hse81aU2diHVwLg9lcUKecjzWt8gVu6b0yyl9lxHgxF9WICSRBsDI1yE+4v89zJAhmr0FK/4ugTXxviZ05vnZ7gSb/eTfMercbFxYWmYTZcsCFP1EvU2xBU6iZyXoSISZtGtAkJzCiKv3d51fQ7G3iwJUX2OhAveYrf1Q3txWNxfTMrxKuIq1MrB5SXTi/vzmK5zC8lUzMWSZeLsvPY4+3I1EaQhcfooFgfv2jbwvrw+Ez89BdtCHOYJ
*/