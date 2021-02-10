// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_IS_XXX_DWA20051011_HPP
# define BOOST_DETAIL_IS_XXX_DWA20051011_HPP

# include <boost/config.hpp>
# include <boost/type_traits/integral_constant.hpp>
# include <boost/preprocessor/enum_params.hpp>


#  define BOOST_DETAIL_IS_XXX_DEF(name, qualified_name, nargs)  \
template <class T>                                              \
struct is_##name : boost::false_type                            \
{                                                               \
};                                                              \
                                                                \
template < BOOST_PP_ENUM_PARAMS_Z(1, nargs, class T) >          \
struct is_##name<                                               \
   qualified_name< BOOST_PP_ENUM_PARAMS_Z(1, nargs, T) >        \
>                                                               \
   : boost::true_type                                           \
{                                                               \
};


#endif // BOOST_DETAIL_IS_XXX_DWA20051011_HPP

/* is_xxx.hpp
yX8o0y1neQazVRSEi2Xix/HKi2ZetEyOg/AYXsHo5S/wZ1cbeI9gVImU5g+vndcvHDLQfwln6jZRXNOk8RdBpTBufAZz98KzvhV8c4R9Ux2eN44DyHirRSEyhsMvWhzelm9lewtpJVMTK17Pw0Xsx9ZPos6qLufwjpL3eCw/WCZPJtH+dU1jWoFnJSKlQsB8ox4bcIAdSpdxp7TwTGl6Tt6aAk68eBb5i6Ufzq0Fw/EwaKSoNQEHubLn1wfqCJ2GnojdWjOByBR1IdstoxbBePC2CMFK/MMnwFLZoTzsnT37DNcICkhFzdCSM80InAxm7kHLUBsW3oXVR3fA7/HbD4PgiZ0gqgDLc0E2VkFWcozOLqkwbbY3HM+yF9VCR+QUBe3ZcsVbJK7ZO4xO0JlyTsuUr0bmKiUzwYgHpnK0W/uVNq28Ejmuprd7NTo9ox6UhzYUjqKrMI217Sotjip+hRK7OPexubztk9ZYgeE9pwZnSOOSPX4mimjwxSzV8IyskLasxikNpNctR7Jbpp6hgYOoppyKMUKcyS2NxKzeHXNT+DtwIaSTj17kn64XnheNX002xeLuqCGx/FqQIFJC5DoebJd+d26rlpqAo7BZba/hBcoxogqLc+GueN62qBMG+AbonsndgzvxoiiM
*/