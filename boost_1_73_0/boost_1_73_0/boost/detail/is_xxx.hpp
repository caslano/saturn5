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
zSxgjxAjHSvR5QNgGMzFve8sOEzyxcdZ5yDuluYoW5WzlSr9YA8Z/gG3iZRaomH+2CjngTSesSi/fxDVyPDfJ1VJFJGzIfWjfUSt9Fic7wm/7FPhiwlw+BLFQ9PJTCqtSwC3DbnKfLlWkvcOowRQa1j2pMAb7DQ5aJ/roKHwKAiDWL0R5I2/Sa3WKvjzK4mOdrFamdeNpw3WMLDmWwdWl0+cfkzG5qS1Iz4OcQDds8YwVde29Nu8yB/q4BvXatk=
*/