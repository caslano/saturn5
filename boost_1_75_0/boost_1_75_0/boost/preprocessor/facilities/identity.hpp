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
# /* Revised by Edward Diener (2015) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
#
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_IDENTITY */
#
# define BOOST_PP_IDENTITY(item) item BOOST_PP_EMPTY
#
# define BOOST_PP_IDENTITY_N(item,n) item BOOST_PP_TUPLE_EAT_N(n)
#
# endif

/* identity.hpp
VskqS2HKbya6Pd1vk1BPV9aFglkgl4+DnyZFs06jtolwzIjXAqGl/gVb79G8ryRcyblw6aE0kno9zdWIHeWGHWGuhpJQbb+4RnZIncEu7RrYKxWsP7BJ60JS13crZcA3d5Ls/kgkZJUbxl2DNr8SJKK3w3eh3heSXtPUlEUzOzT+41TWXm/Cqfnrjc2PLpVlnhuXou7wx3JbCMvpgZwJorUk7QEZSTKE/tHq3urK1E6HLixEMgOQppsM7E4+AF8YoLuAK03YTqFMhinaPcm/ebdeePdq94re9nt3pCZFc3TYFOmt9snaG8hSL37yS6k24V76clygOkRGmnTSxoVSeaxaXpcq4Li+NHLlmOo0lNkYmEENNmcP20bARWP2LCv4EaY4nYuC5vyXpXvo925xfAbfz30mHr6YL7n9Sku9cXOXWdS+BognkcbFTVUjJKcsQb3RgT+NK7Nuv8EZQVxGIfyrjsHfw6OLM+YzMtdaBdB+k67EYgrN5iLdaQaLtG07z+q9q5mhaeYR7AKRihZEneAlpHAd3geY0u23JizG9r1T8KG++EbkStgqy39r96a2ZeDexTRZJ9kIPKYf5sF99fTuCTkYUyosb87+NbW4G4t9B8bdKISywdDZEBqw+px+ja7cHx7Q4T8rUSCemOmp1lFWM5eSTPYpcFQUQ3NR4ZS4CqhaVhoTcNI0ZnXv+V01r1EVf71YkVjr1fP0
*/