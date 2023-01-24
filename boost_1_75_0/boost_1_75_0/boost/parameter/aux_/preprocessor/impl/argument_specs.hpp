// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARGUMENT_SPECS_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_ARGUMENT_SPECS_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the argument specs tuple.
#define BOOST_PARAMETER_FN_ARG_QUALIFIER(x) BOOST_PP_TUPLE_ELEM(4, 0, x)
#define BOOST_PARAMETER_FN_ARG_KEYWORD(x) BOOST_PP_TUPLE_ELEM(4, 1, x)
#define BOOST_PARAMETER_FN_ARG_PRED(x) BOOST_PP_TUPLE_ELEM(4, 2, x)
#define BOOST_PARAMETER_FN_ARG_DEFAULT(x) BOOST_PP_TUPLE_ELEM(4, 3, x)

#include <boost/parameter/aux_/preprocessor/qualifier.hpp>

#define BOOST_PARAMETER_FN_ARG_NAME(x)                                       \
    BOOST_PARAMETER_UNQUALIFIED(BOOST_PARAMETER_FN_ARG_KEYWORD(x))
/**/

#endif  // include guard


/* argument_specs.hpp
e0OL6Tl59endH7LZChUoAdNNKv+02IEDhiwINv7MEAmbPpihei3KyTKdcjzqlDV1W+VvPi2/dZmqkNNKrNLrk9Uh0RteakCww6EtTRsszRCmevaK+Dhb31+67r3Ir8mrGdlOc9Bl6JlcvWhQ1TH05G4qZ1rnBZbiBznH0o4h1SwafG+rQJcNgkFNU+MMEhm9NVjkHM4iTZe9ssfM3yorR9Fk3Jgv3emrp9j71EZQmEIsWbO7Gj+1floZVYwcHQ5txo4nWluwJm43CMcFsdg1pt5o05FP5BZjCpioVl/Np8WYXF/O2s48X87zgnGOOaCf/DOrZ04XJAK/OYp7HqS1dcsFYla0qOSUQlEFJ09C0vFb8QvOnfteZNnI27585w/JEAOXMed6/kPRCj6juTn9jO1TM73Bc/uI75vPrygE/ZNLD0fa0MDjoV9Iie+GX5sxMI+DSuUT1BRC9pec4txCoa+xZDm2+bCf3MSVEC4opy7hB/sOxT0I2pN1SB+EcTNX5jm6OKHTj2IvNzKlQW/iu0bu8Nemv+Q4IA7uZtstG9SFCqOvffqTc5jT4sZ9JNjhdNCY6t5AsUQbMY1fJManD58PYHrCqauqYbtPSlPzHaxkPBp7GPT72wUbctjCLgkpJORZHfmsE7I8cvFFxY9ZGnvjWqLG8Pfb7oLxk1G3obSvJ+wOeH1LaJgEeLnS2ONOsBR3TBBC8JHbKvaU
*/