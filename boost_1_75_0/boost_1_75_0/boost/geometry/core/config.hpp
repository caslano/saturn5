// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Copyright (c) 2018-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_CONFIG_HPP
#define BOOST_GEOMETRY_CORE_CONFIG_HPP

#include <boost/config.hpp>

// NOTE: workaround for VC++ 12 (aka 2013): cannot specify explicit initializer for arrays
#if !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX) && (!defined(_MSC_VER) || (_MSC_VER >= 1900))
#define BOOST_GEOMETRY_CXX11_ARRAY_UNIFIED_INITIALIZATION
#endif

#if !defined(BOOST_NO_CXX11_HDR_TUPLE) && !defined(BOOST_NO_VARIADIC_TEMPLATES)
#define BOOST_GEOMETRY_CXX11_TUPLE
#endif

// Defining this selects Kramer rule for segment-intersection
// That is default behaviour.
#define BOOST_GEOMETRY_USE_KRAMER_RULE

// Rescaling is turned on, unless NO_ROBUSTNESS is defined
// In future versions of Boost.Geometry, it will be turned off by default
#if ! defined(BOOST_GEOMETRY_NO_ROBUSTNESS)
#define BOOST_GEOMETRY_USE_RESCALING
#endif

#endif // BOOST_GEOMETRY_CORE_CONFIG_HPP

/* config.hpp
ViKsSufMKgDktJlwvT+n3zGhAU2iuvfCafzxROQra5MqACyfMvK+e/UbCLV6ENWcqdJcl4mXR87F/dR8Pe1PhGD+XoAmQ+JVeDFge6oamvCgznfx0iG6hAfMk9e0nvJebM3AvxJoqdJMkqiQ0vHJR2flYA66cuDoe+Gph89uWYNHVZZGTfJ0vRNn72UDOSQxrHwtayISwnQ2hwxtIXYL81q5675uEP0bU67xZslkBuAouYNz+opYQz8AUqRCkzu+eCHVdtPdcs+uytuvdz2KFHyIFkAcBGZr+EUq1vip0BQJBTGOBbLUM7fwuLXMFfXZO/WGjZw/fcsjj5Wm2zG7wisLUwY2fkuvYYOwLNZw7ODK00mWIoAf61uIKkurEplM813R5LzLrpAiFVP8SZMojSYFlrOA1xcEP59OdwQIwamSbeeFBLOVJtFHhd97UVJ70cVMiI4vFMD2DqZkQ4l/8EfUyGcUDpAVCjge964+Gz1vIhEIPzsj8Jp7VSuyQwsAt5myuwlLX8Thu5nf4CfpQaJ/WsEkAPLolj0vTDmUmbQsiSRv70izqMmbqsz0Gs9sJCdK2FFfbdhPIHc9E7WMYz11P9Jxz+O07B3Iu/xAJwrR3n5FMg6PPNJz74gJnAn3qXR+VEUCGoSpvBU/At71KRsUhBPXx0pa5klWNMpH+niETUaaRT19ybTmJCUI50lewftiKzzVzV8melYS
*/