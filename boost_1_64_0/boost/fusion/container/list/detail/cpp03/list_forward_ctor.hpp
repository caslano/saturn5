/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_LIST_FORWARD_CTOR_07172005_0113)
#define FUSION_LIST_FORWARD_CTOR_07172005_0113

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define FUSION_LIST_CTOR_MAKE_CONS(z, n, type) tie_cons(BOOST_PP_CAT(_, n)
#define FUSION_LIST_CL_PAREN(z, n, type) )

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/list/detail/cpp03/list_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_LIST_CTOR_MAKE_CONS
#undef FUSION_LIST_CL_PAREN

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    list(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
        : inherited_type(list_to_cons::call(BOOST_PP_ENUM_PARAMS(N, arg)))
    {}

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* list_forward_ctor.hpp
UNI5WNI5VOw+TMZG+8FRsD8cD6PgbBgNy+BAOA8OgstgLLwHxsH1MB7WwSHwI3gE/AwmauUpv99wtEV5Hil2DYcHwxHwUDgSDoWj4AiYqtPnaULfWNE3XvQdJfrSRd9E0TdJX9+i7xQLfflS37NgX1gAo2EhzISzYSUs0tt3aWB9F4m+ZaLvYtG3XPRdKvou087qkd8g+W3ymM6EmSxnNWWK3imi91g4AE6HsXAGTIDHw8tbODYavmrHGB+VszBaPE76akK3Dhkr/fijroazMNLTgjv0PAz/2Om/4xyMzjwDY3uPoW7Psy8qGD9djqxHNiHbkLBazr9AcpCFyEqkrtYeZ7WDHexgBzvYwQ52sIMd7GAHO+w4odP9/8XOSk8H7P3X27H73uczD716Vhf8NZUFhWVFntJSxTPlUOcGhOvWBUSK/7275DEYeYJBWY/f/64paOm6gBjxl9WI7njxl8UgVdgV69WdX1iSi87mfU6B5tYnavPWyZmkHSVp+/bS6S++zkjkJOLXVKtpF5YUVrQpXX3+lksayUgYkoicyr0N3jTmely5Fe525m9n1a+Koly/zzAC4b7SuSUVO6Q/7t/md7P2D7beH9dRc+V3FH/cYqdyffO3dySVhaRfsUv/ys1nJm3Maps/LhaRZw7PItPeR+KPUTgEBsME/Z5JEi/eIl64+A/6whh4sBZPngWwv0W8UPG39ISRsJcuXoPES7aId4CcHR8GE+GBcH4L/RINtcH/Wd9EZ/glbJ+E7ZMw+yS28R3qdVewIxpJucv2O9jBDnawgx3aHzp9/X+xs7xw1jx3WQeMASjv+b10awCel3fVcvqiMXA67K3s/3+29p4/Wp33O6VwVslY9c1cfW9d52h6jX6Nbv//OtM7bCjXNmjv6GRNOcZPrtfDCN912V96T+OZf6rOIdrncpT634uXqul4uKbo67L3WlknOx0edA558u9xLve6uFd9f9fuH7YT93Pj3dr9su+1bk9/WR+vraXnn2r8DURIJP75fI5bTHzJV5pWBiy6d2pjBoZ0C4h3FEw/l3iS7wx/PpV71Tm9r6l1wzuFzPENPcf4udD0eZfFxs/LTJ9HnKt9NswLX6Jby98XSUf6cE/1eRZtY3xJYWvmzZvHNNJgWJS/7mT/ApkrXrHA48ZWqbcX1LhuqQPtfEg2UjCuIXlH5te/gbEx8BEYThqO8032H+MuK8xfMFY/7rSqmfZdrWvftRb5WaedY0A7ljZQByMczbftRGNbM7X3ef7ysWh/1dTZOvJ9EZ+/VPMp+7ZbtT9pT4/IfX2lPUxaIp9N7WFFN+v2kLHUsjyVFvGvaA++9QV1O0vCO3ntT4YRUVxfKvP05THrLMTyVpxtYbY928L2HAvbC0y2e0y272M4zwLDpI5rulEXO3vHJw6/QOrY0I5cbjlfQKvjZ+S+SKnjIRdqn7WxwvodaKzwvzp3f0cfK7TeJ7/1Y4j3qWOI14ZeWBDrju8SfcML7+7918AVbRtDrAqS/oz0cxZTZgOV70qQf05xDMyEw+EUeDTMgm44FXrgMfBqOA3eBbPh+/A4+BOcDv+AM2BXdB8PY+EJcCjMgalwJsyEeXAGdEMXzIflsACeDAvhhfBEeCmcDTfCYvg1LIHfw1K4DXpgb/I2B/aFZbAfLIfT4TxYDivhqXABPB+eBJfDk+HT8BT4IjwVvgJPg2/B0+HOXfjDf7vCM+DuUN1/Hp4FM+FCeAw8B06Hi3VjpNJ3oMy5bhojHSNzucfCdDhO4jUg8pvNb7k33v78+1WJt0Tq7wJ4OLxQ6rEajoXLoBNeDAvhJXAOvBQugpfBJfBy+Ay8Aj4Hr4Sfwqvgl3CF1PM=
*/