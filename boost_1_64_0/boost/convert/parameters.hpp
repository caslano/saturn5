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
hL2/lc9+14ET5CB2fYCNkK+qOZHnVp/AOTjb1FeItTfD24rwGU/DA/CrDhd8BR60+k3kxR42cc9eI4f2XfBvrOHhFDD4X/BWckqHfsMWwxn/Ohx9Eu+AirmHuIyJ8u9YsHtxR8HH8EUvIZ8G+KKpcMtDcLty8Kk04u0TcNxHsOX12Dj4FZSIfBKYQ9xt4icSXwXz0cOFV+E85A8rXyY/VBOOye/Vbmf9xGjT8Wd1J/E+bykyD8Z+P4bTgmfDmWNiDDqDzWS8T9xxJz7ZH+5MbDozG/0aCnYx5+DtxCcr8VV3wn3xVVnTiO37gBkj4QT456lPwynwVf3ByubYZmQ2XO9bYqVa2Ae4NDiBWGgLsTy20K4e74rRrT9m8E6W3HAh42RyRoe537prszhf5LoRrHydvYE1oWM5P9b+JZgS3ZM4gdgoZDf6x9reOgBWjybuTgErupGPRcca12EP+OIYcPa+3eQ20duqudj6BnSoD2c1mVgCPO42iLU2wGabwoHqYnfcT382ipjqJzi9w0Z86Y8PAefwDY9OJZ71434pCzxA1pvJVYeeB+Pw9z3Gwy9fwo/1RU+Zp8lt+EZ/+DF52F/gwp3xlckij4JuHUNne03ALuDo4/D3s1hrp+nYPnP0eAM/QG6kIRyrlDxAI/S+EvbXhXUkgwdj7gBPJxEjM2dNzqAD+PUT2BHQDFtvA+e3c26LyIX1h8Oy9xno6lV47tK2xJS94THrWeNlcIXczJIl5PfS0CUXXH4ruH0Z3CJv80wGawTf7kIWjYbi88KQQVPizWzOBB0WMer7CxnnCeZ7BL3GR21YiD8fD5cdTxwyi7PF5u//kjl3UwdOpYSA68TBsfjDn17kPPFFr/Qkdtot7s7RW2LJ5b3BRnBoCPtv8w1nBgdbWx75wK+3NiQOe9afvZFnvgTWkXM9h843/xbbbY0N4G/a4RseJCfZoA5rx97qwfNqtYTjgi2friPOgdel/pM5YtGFEehiOPwNX/I9eptZmfU+Bb8ap75B/hGsf3kbukV+5CJYfHQy8cV2coT49PzanA9vykdFoE/kclby7utEU7B3Nn4YDLuHfVfPgrfNIUexEXtzE+/ORPbINRnM969FziEem59CfICd3j4SPLgdnYdfV3+UO3zi7/fw122E/pFra/MJNr0VLHiMN1Ol5KhGkMN8EV29V/2euPsawN2JbV9Dz9/dB07X4O60BnmXherbm4kQmGut2W8W+ANf6pcOr+V+ZALybV+J2GkpWHMUfTjNfVAMdzVxxP2X2Hc2NgcOdd9B3MqaLkcRs5+Bd/6JXoq3p/C2hkvA0CbgyhB4JO+Zns/hzDhjJzHXsCOsDXv5YT3+gz18sRO7KoWPzYK7P0GcAB6UNmIP4NL5KsiLNX79BTINIo9wEX++Bpv7Bh9xFn/N/IHY5X5wJSMPnemKnYLx9eHFYyeJXA6+2EbMvI24k894DkemRyujb2D8b5zhmCDiJbhQW/zUhe7gdG1i6I7EXTPY0178L7FnXfz/vXD2HYzb5znOG/2JnInPqAqvJmbbmwnGIL+5R4ij4ACdVuBf0LVPwaZmXbDFt5DfCuJL8KVOG3QWfnbXAj5PFwAOIOOSA9gG+nvbfciEmKxcAj6wHjhDHjGLe8ykfuTuirm/QOZPPQ6e7AJDiQd3I5PN3B+dZ8yP8Nn34MdiPsb/gbm7OdMCsMQJJ/Pj3FYTcz1N+/vgYNO449rSmHiaHMIrBfAmdGb/7+h7L2JTfPDM2rSdjO/i7r8j/iEPXjqzM37NRmz8Bz75eXDpGeLZbvhcdCMfzjXtE2I+OMWUpuA+cm/Huubhfy6ngofsNeUBYqhm4AK8emQTYjM=
*/