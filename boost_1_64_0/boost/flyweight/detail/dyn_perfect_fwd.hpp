/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_DYN_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,_)                     \
BOOST_PP_CAT(T,n)&& BOOST_PP_CAT(t,n)

#define BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(n,name,body)             \
template<BOOST_PP_ENUM_PARAMS(n,typename T)>                       \
name(BOOST_PP_ENUM(n,BOOST_FLYWEIGHT_PERFECT_FWD_ARG,~))           \
body((FORWARD)(n))

#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_FLYWEIGHT_PERFECT_FWD_N_AUX(                                 \
  n,BOOST_PP_SEQ_HEAD(data),                                       \
  BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(data)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#else

/* no rvalue refs -> [const] Tn& overloads */

#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp> 
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_FLYWEIGHT_CONST(b) BOOST_PP_CAT(BOOST_FLYWEIGHT_CONST,b)
#define BOOST_FLYWEIGHT_CONST0
#define BOOST_FLYWEIGHT_CONST1 const

/* if mask[n]==0 --> Tn& tn
 * if mask[n]==1 --> const Tn& tn
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_ARG(z,n,mask)                  \
BOOST_FLYWEIGHT_CONST(BOOST_PP_SEQ_ELEM(n,mask))                   \
BOOST_PP_CAT(T,n)& BOOST_PP_CAT(t,n)

/* overload accepting size(mask) args, where the template args are
 * marked const or not according to the given mask (a seq of 0 or 1)
 */

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(r,name,body,mask)     \
template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(mask),typename T)> \
name(                                                              \
  BOOST_PP_ENUM(                                                   \
    BOOST_PP_SEQ_SIZE(mask),BOOST_FLYWEIGHT_PERFECT_FWD_ARG,mask)) \
body((ENUM)(BOOST_PP_SEQ_SIZE(mask)))

#define BOOST_FLYWEIGHT_PERFECT_FWD_MASK(r,data)                   \
BOOST_FLYWEIGHT_PERFECT_FWD_MASK_AUX(                              \
  r,                                                               \
  BOOST_PP_SEQ_ELEM(0,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_ELEM(1,BOOST_PP_SEQ_HEAD(data)),                    \
  BOOST_PP_SEQ_TAIL(data))

#define BOOST_FLYWEIGHT_01(z,n,_) ((0)(1))

/* Perfect forwarding overloads accepting 1 to n args */
 
#define BOOST_FLYWEIGHT_PERFECT_FWD_N(z,n,data)                    \
BOOST_PP_SEQ_FOR_EACH_PRODUCT(                                     \
  BOOST_FLYWEIGHT_PERFECT_FWD_MASK,                                \
  ((data))                                                         \
  BOOST_PP_REPEAT(n,BOOST_FLYWEIGHT_01,~))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)           \
BOOST_PP_REPEAT_FROM_TO(                                           \
  1,BOOST_PP_ADD(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS,1),        \
  BOOST_FLYWEIGHT_PERFECT_FWD_N,(name)(body))

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)                     \
name()body((ENUM)(0))                                              \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#endif
#endif

/* dyn_perfect_fwd.hpp
jM3k2ZnMvGE8N/YuDIzFuvWhuj02DOs22li3nUV8wlPvDnQcqNwd8Kp3B1oO5CTQ3YEWA8XdgQYgJgWi/F9wnVAWnV5maRct/gNdsaj9fx4t7bEzlfN6/wA75/ULedayGXRe3215tfyzXs2zPzbDWv5dYt8/a02OasAMs3xygYLFuv73q+P/envj/37z+F9Svfuyuaz+hEWbew+PSka+pGnYdaeuOUAfdiNk10y+mw27OWcadg/KYTfEaRp2q/iwy+JeltJyyOtSbXF5P1aXcrgmYK7uTzrLLUabR7usFEebr3GlV24tnr3K70+uDkhi8pCB05hr2UjsxC6BUFVzh1lUNX2CcEd98jZW6X9gZcP8g/B4QBKXPwHxXE144hie24x4fkAjJ6RQHc0js5TRnKWO5mx8g4k0mgdlidHsXS7oGcnoCUT6p/KRnf0HjWU7/S2VxX+aIy9BpIkWj6MWjxMtHqecUyez3yIoeP7V7EAyhoUg6HCQvaNWBtvAwKbqOS1V5Z85avyPa22NvyZzTOPvx0eqN/4YlneKab01zTvdhc+BauzviovN8tW+O84Yj6TS+m9NT+cbqk/PT/ea6ckXFpz275N7EdNzEhN6ogEoLQb3oHhmyyK3kTk3voBTMttXLzKD3i9O5+WRAlD616/NR9jWVBqixZifRq10+Pz3kWUVNntg8PqWzjbXN3FokPq+vujs6svK6zdb1jfF6tw90ouH2nTTGlWnOhEkRjw2Qr1v4+Y+kmoU49BOklFsc7XERwkOZrOx2dxYSFtYh6wmbNbCTn2mzDLz7/Prg/DvskfOjn+sv9SZVXV/yQ3eX4bfdA76y/yZsr451CI1fZWt7TYFs4mgmEPRwiZiLonHPH19tPD/TfFCvB4ZOETpAQ/9o7J/rL6s+lNTXfl1yQSCFBhu7c1w2bNiyAkee099JIV3jCStD0z2uMaSLYTNRqrGJzg/02eY+89Tg4P0nycerF7/sQyKeGC6ubxOorwMU3kRRdUo7z/sHQl0FMVyd5OQTUjIcgSCXAESCHc4DXKYQIAFgoYbPFEU8ELQDaAih9xGFPiKfMAvHiCIn8MDA6KAIrcKosgRFBV1lv0qCgqKsr+qq7unZ3Y2mQXxf98zvJCZ7q7qqu6e7urq6ipumqpXNIIqYl3Wu4dxiGTg2FhH4ss/B6P4MhnFl5lSfLliNBM2UpCuIcyRAtJLo2RJmch7qIT5byq1x2wcEK8lOpimjd6Gl2NvmWTAlEFfmPRygVS1Urxc3AaDl/npo9dThfxCLdRFEK1yDTEoD8Uand33ZJe7qU2mDcI2mYRtskC2Sb1RXBsohLYqC1wOGiOzk2vB8/poJgQvpmJZkbZRqe2Xazn/TVHaryBBbb/6iWr7NWbNEnyMy5OAwqIhd2h1oNEDdQWfouVMi8BTkQ4B8yy6+yGimjv4B/Kqi2c49/QIkZHiO9NwfZBuCJwYgF3zOHbNo7JrCkeSTxQDHOGkd6Rdaukzg/ludEFpcy4OK9+WCWGimsJEkkJMFudhNPFQT+fhMX3/fxfjobkBzJcqX2k1MfLhiZCNsPJbu8nEijCtpuC3vCVTyJyU3nURj1oyxWvHNlCvDxGhMunF0Ql4Uy2D3gGfB94y34lg/jBAyjcsQeuWDHubKt9S4S2FvSEDs9w27E8FvYdHRUJvSPzHiSW0r6ek9vXYbF9pHzxq4p/gHz4k/sMEVintVK8YwAUE04Kfr/nzFeFxfBOUPChD680XKD3pX4iSgnpeBRu+VyKab/T50qQD6TPB2uaRnDXQtJFFuSIRZgtU8aCZqLQky3lUdd0b49+HctZNLT+kAhIwA8ug/4tM9J9O9mV93A4=
*/