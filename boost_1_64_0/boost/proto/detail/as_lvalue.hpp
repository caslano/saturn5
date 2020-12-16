///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE
        T &as_lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        BOOST_FORCEINLINE
        T const &as_lvalue(T const &t)
        {
            return t;
        }
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_lvalue.hpp
XS3qJ75HmlSXpp705wabtzMu78ppmD14pcFfx3OJ5du8ePNBjnxVJkkDcnAYJ+ca3MchmSX5mbejEbnM0iyVVtiejMk/iaG3IKCJ7CPqyuYmN//lPXM8VIKt1V9G81HbtkvaOheXDd9Efx3hNZ3MOwMYiObvFN4/muO2os3quu1k53aAaChmNjOKjcFpYAzypO6KRhf8ngqWFFsUO5WGtg+SG+6XkW2P1rBkatn0X/ZUJFdtYPzS0S2hvW9DGgjksDyL6XjH5/z+LUmGWkrSBmKU9mVX7eN0goCzCAd9j0tyVWIXjqG8g2UkUx3rccgey5mHujJvM5o0S8TL24suqdKM5YXLb0JrarCk2Jn/ILDnujX6GTsUX/7lq2D5+bU5twqC/dc1sJwvnZngr/HmyNZIqQzjJ4xfh44pvTBhC/D51/AxL1VSGfh8wh30DlsQ7r1fG515bSk7TCE0Ou+D5gXcu715wDevmjwT50dnII1Pz5fafILjzldp09muziHFw95odWVnfeKMEhz/eFZ0RQY7uoBlE7+bKo53okxgHzZWnNvb24nxmohfrmwqcws7wGMfHfuK/JLn/d/A68rYj3uH4D/j8L1tCPwdw49wONgWjTVADP7NmRi+t72/ifRO5wrwJ/s3qN57ftm9zuDTF3uf+O6/wVsex/iEse9xf3AwLrqE7u5AMu0ZxvvH/w5/bX1n79zMus/J+O9wUc+/vAkizKbn/at/h78Hk2wm8P79Qbjw4AZPG9vgyvp43u4//7uxWz63PdqbeTzh/u3f4q7Ditv0eSev+JR/h7uxM046yd7OrnYQ/ub29qP3d3x7b8jw7P0XbLc4fm3EV8RRn3Nv1Z+lD8azFHeW5X2MRI76dZ+DzXiYexxedrPO00IsA4BjSsaVcQAOFg/yQdH6qZpWlQ0qRdcv+DW56mWVCFfrwmZtArj6QdrjPoRkFY4rK1G2VrWgawtnOHfSjXNLuWC658Fo0IXI31kH8QW6QLxfEfHOBeZzzbUp/h/e4Ds+5j1LsnW0p2WJLTJZJ6RL4ccTvJPQmR/vVTWov9NKCXgYivegr0d4MlcJiBMS9+2B3VGM17RN1WadgGGI8b4T72kdHMlNaQQk7Y/xvhfhGZNbqzGzMGz+Ed4PIrwCEx6D+CLgAhrfVX4UjZGEWnPUN6G2l1BP+rywb57wTbR1BdhDvyDvrRqPspc/BnyklUXbVtUUPmtjeXTAp6K3l7fEby9Vm8vCKEl8es1SPEWcncXxYa6Yo5zXCQvyf5O2wksxXu56AOnJ3zKMdVjLxJTNpFzrghXGM9ddHVcoRiicrcT3YRHfVqRVmtmkq/8nvluoDQYzaRa//zlvicdc101WKc3G3Cfus+PN+IAxvzziUwpdycw2nZ7Cpz+NOKM4RtqlqK+FUE2isiJRgRdPCsBdvXrm8G5hSG/6loGPcaPqqrDJRLuCmgG25YnGzd2F5ijnN5smSVpXTepynVFM3wXSZ7813sNUV+iisUz/2/U2nkCMRVGqhD2Imw7fDNoFTDeI5xHOM+1Em3cpzLCDefpEFit9SNW+T8yuuoh4VqKFSzWsF7bXukDo3K7p+GCEqH1rUZ+VSPMqrws+D1wSNApmtRHswwbPA4HncyKeWqjcyLZM2uk8vRpmyFQgL1pP7xl8mxxmq1KqZn2GQTwNExV8xx/LovbG6woPIOQrHkL7cMQXba5NoooynTLfDuYYPt5Jwc7Evwx4y7KtC5k3Q97+XPwveNMYH35b/I7UVZWq87aanFf7tAdvs4nG14r0ehbO83iaNDKrgTU0MT6TRISnEpvUTd4KmGzxmaQ43kldZKVJMiu4xecO4TYc91Sju64=
*/