// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_PARAMETERS_HPP
#define BOOST_CONVERT_PARAMETERS_HPP

#include <boost/parameter/name.hpp>

namespace boost { namespace cnv
{
    enum class   adjust { left, right, center };
    enum class     base { bin =2, oct =8, dec =10, hex =16 };
    enum class notation { fixed, scientific };

    namespace parameter
    {
        BOOST_PARAMETER_NAME((   adjust, type)    adjust)
        BOOST_PARAMETER_NAME((     base, type)      base)
        BOOST_PARAMETER_NAME((     fill, type)      fill)
        BOOST_PARAMETER_NAME((   locale, type)    locale)
        BOOST_PARAMETER_NAME(( notation, type)  notation)
        BOOST_PARAMETER_NAME((precision, type) precision)
        BOOST_PARAMETER_NAME((   skipws, type)    skipws)
        BOOST_PARAMETER_NAME((uppercase, type) uppercase)
        BOOST_PARAMETER_NAME((    width, type)     width)
    }
}}

#endif // BOOST_CONVERT_PARAMETERS_HPP

/* parameters.hpp
QuhfAf2GEPaIH8H793YUczTqTo22a8dF9YqVdKc6uvHnHV2pdKd4qsaKhdybja3s6B5IMdSHGqMmNUWEbaQWiz8FRE0nlv3VVMpGsZH6opiCJTrFp0ispsZsqDYbqsyGSpOhusFsmGs2HGU21JsNdWZDrdlgLmm1uaTV5pJWm0taZS5plbmkVeaSVplLWmUuaZW5pFXmklaZS1plLmlVJSs2GBpM4bmm8FGmcL0pXGcK17IxrLQUh3NsZ3Ebb2c=
*/