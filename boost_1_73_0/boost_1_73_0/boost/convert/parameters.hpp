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
jhkojKn0H/1+2tQlVtLPVKr7adeKoDCrJ1VdYTYrtgFVGTAKGs19IH0fVioTOT2xRSismmUpdOFv08KAMuurGjQvy9YdmgquXQkc4rZbPmlChdkLQw+tpKZo60KtHiliW1tHeVNLDIdtQb1MYeN9aGTGa6tvG9FFabtsW/6DkW1zz0BJzAp6gxjCuAdLpoX24Us4P48Wc/gymM0Gk/kVRGcwmFy1/i7CySliQ2DUGvh9VXONWdQgVlUpePYo+E/ddC+Yn8NwMRtH03kyjKKLcPRpMIMj6L0+hk+NJGC/7UGvFEuaPBwHR8fBKxTQfwlnepNobmjG+Itw0ugxPofJ4HLkPXd7fejgK9mKU/u1Udi+VKlbmq1R1ja+mkTTOIy9X4VMyybj8J6COeQVHzzrN1Uof5rDHp3AQYGYKBEaz+IjAAtWwwHlQCns/2kDno7i4SyczsNo4k0ZNp7BdR52Stf5lBbIWfogm7I8JJQIyXDYgYPCWpQlov2WQ9eodS0M9xiKhUR1iW8buJVqLXfqtSjTFU9FjlN2vVkXXHoYf1tcWnImm2rvaJ9ywWgpOqPQYQ5SPbgjJNoAPkmdL0pryb205i7Z2MbaQO+wR0V1NVIqQmrDWUsdlFfnlypBQqPxaJOpxgSw0ELeOC5x
*/