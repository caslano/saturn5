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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_NULLARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# else
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_IS_NULLARY_I(x)
#    define BOOST_PP_IS_NULLARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# endif
#
# define BOOST_PP_IS_NULLARY_CHECK() 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_NULLARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_nullary.hpp
XvCalNfeSjHb1/KEVdewvixlDyq1R9wNivjeozyPLeY+cRZ87dKZKk7IyOcxHwRXlGMhxcK1xrNkmt14j0x3x+mxkhk74tAg9oRx4SuyCqrctVIxotLVqAWMclool41awqjP1zCKVIwTA1GyuihHKb5AXdEubmIo1RgA/zAB54lk3I0HqUYuATLRg0Tjwang+zebPPi+68GquDJ4OzFTd1B16VoZa1cBbbTZFTYKhYo/184nCqviz7TzPnLiBR+7KYtxl8iTPsfVcGc95XOMw/MWuMlwMbi5cAvhlsKthtsGp+C+g0tb4HNkw+XC9Ye7GG44nB/uGrhauDq46XD3wz0O9xzcCriNcO/B7Yc7BJeE67wQ95TAnQ13EdwSlMeP5zi4P8LdCfcu3Kdwh+F6AJ8BdzHcQrg2uB/hhjztc1wBtwTuM7gjcB0W+RxeuKvgRj6D8uI5GG4N3EUIvwg3EnEnwtU+63PcDnc33O/g3nja3kPnzzGGVe82LW3c1UGstdYF+CM3Ks1ETB5AYktLKKy+W023tsKaseWuZFLPBeEKtRtgUMJEYQ86upmKMbuz1XBzQaG913KynuI2kF6buuFOZnjuYAD6kxmglpxvhX1kQE1GWMwr/sSYLGDKW8DFr0fQ2Gf1D9jevANIWOf0Hbhn6gmhl4GDUcIATiMfpX2dDoniOLRXl1/V/5XNLlO/n14BTYlUCPrlsVXmOenIn9neNRlUe1aZha0O4wwaQlhTmzeJqYYNcs8t7B7Au8rVjQjznVqDAiG1apVpPzmQeHkOcnjOAnmDI9VdCPEqoX6B+f3XsevIZ+y6ZzjJ+cCH1GlIM6Cc+Od6FSqxf3Cri5P2N4p6aIvLvn5FRiMA8hIVaSGVgZIz2mVdcVvIz6Y7SbzBS5xuzm/Xtebw/R/vmfamKsbvhglcvQ/9rT5eHyEzTrb/DeM2McChnMiFcmI8iEfGDoYNlcL/OFouXxtx2AafIiWJd0FSd+BGJrsbHUIE7fWCKB6XIw+5/pM+oeaVNZyLmr/QjvwKIvOuj3OVyJMQmI8DVuPC2wpJlBh5uR2lgQtYJp8G7W2MtjE3SWJeVQEWlajkhQnWfj2MaptmhNRK4lzUMi69tRGFjGCzzYgNjayUM23TbFA6CPld9h1nJQGbvZato+Yez9RuEoLvx5TwW7J1zUGr//T7/dFMHo/rAvpewnsQz7zxKO0360LEBXAkKqy6rzT78ZlyPgrjPQMwf0BVgB1jmH/zGvcEDJz9AeUXctPAEzm3trL9/45U+7plDrGv4ykRMiDs69jHVnRY+oi3Xo2nit/9yAiMLpLzi9sALQiFZ1Tn94Mvn2hoL5mwcKPh/HAG3Di4CXAR/QEYltym8NOnn9X6Wco6bHQXuAJt1zKeN1AZXKVtYWrVrfMcot9Q6lExB7lbvqbYK3v6H5xs+OHYyoYfRfQ1xeseIIXe6/gn7VEFCJQfAd6XLEMIdCWJXapMYBPiBQLzJ9aqAoHlxXMoVi8JVcUzKZQloXK+aC1+iCr36Gyx2BHQPv26HNghAR8HNspJfc/IJvzBjYsvE3SE0U//BF0df+AnkNHxhp9AxiciqUEjcX1qsC4RSg3WJkYSq/ERr6R2S5Rapo3nbSzPP9Wpzseb0Fgt8KsF0zGCPOIvfZKq8kKufzetQtUN82QPbzI6ubpjPksphaFUzX3ZclHbfeZySB9SS+fKzSRk4sCGpMvx/QuW8Uqr83vjmYt72agvqdYbk0keDSD3kknvfJfozz62r7wt1yeTR6sVM0DNSlSRbEk/cTMiqHOgmcfqLWeFtZodQ+D5bWnyRcZ6SpIEXC3M3d9mrUKfohGilgKASSOo7oI=
*/