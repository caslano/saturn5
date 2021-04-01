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
qEOVfE4cuc82rlVyPAbP8lELncI2v44dxjRhH17TL4LUOF05I/tIyLzKWOnDrQOgJGRifSv10RP4JiKEYz626D17laG8A8BRP4Z+qt/92VVgYes4T+pvLkC80QKLC44Fiffb0mywUFqa7XmrNiEp2h/kLxdUfgLRGEijHXwYnGRMd33MXdIMVaKE0HGMIGEmD6IkdI2rabRHqsgDiHlNth3Aa3AvwvgMAIBV0AKF/8gAfCg2746AqQb2Yniiw1tSznk/woZv7uLFtXMkYX7XTEqL7aeN5Oaqz/QSjfNGqkQ2WqTbffM+mwUIc0BYqN1c4KVkbvfd2C11QT6hSdYqwd6zKT4OEufJPCPW3vM50trZsradFHOCwcixYiz30dg/VwsA4twgWRBlQUd5gpaVHLBPTJTLtoljKPAUg45cQIM1WI/WeyPvHuYKZwraEhg30Jn3UW92ESj8eB22/Cv9CGoTg+p8nuz7srjmDFj3c26eE/fBZ1B5eDNwnP9llaQOTeeRB1qXl3JPaG6PMrQF6QAf5rJ4SUc6N45lIAWxCIWq8cWM5lqPb+YkgQ==
*/