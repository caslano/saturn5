
//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_BIG_LANCZOS
#define BOOST_MP_BIG_LANCZOS

#include <boost/math/bindings/detail/big_lanczos.hpp>

namespace boost {
namespace math {

namespace lanczos {

template <class T, class Policy>
struct lanczos;

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
struct lanczos<multiprecision::number<Backend, ExpressionTemplates>, Policy>
{
   typedef typename boost::math::policies::precision<multiprecision::number<Backend, ExpressionTemplates>, Policy>::type precision_type;
   typedef typename mpl::if_c<
       precision_type::value && (precision_type::value <= 73),
       lanczos13UDT,
       typename mpl::if_c<
           precision_type::value && (precision_type::value <= 122),
           lanczos22UDT,
           undefined_lanczos>::type>::type type;
};

}

}} // namespace boost::math::lanczos

#endif

/* big_lanczos.hpp
aWbBELXG4Oke2L2o9nte5QAx9XpDJc1DYZP+hqYvQM2OAO7KvQFUHXP+TJ+0pAflaPrjByypv/xhWxcRMcT8aIuCfB+8zS+2SD7Z7nxqPHy3L+iZA/LCsBZjnLSLBDN7S9lVFms8UpwIwtyHYD3X4tcdekBmJkVrYgkB/HYYsX56B00S+f7gZcbtqaOLTs/ZooZ9K2cX+qCcyjQi/2F2tnapXuZKDsRCGr2qjzCH+R5wDcQctBel+zx7ChQavaEeJNigaTaxbiz8K2UEiSwk+XGz959Qgt9hzVCfA3GfCiFmugPJ/VEio1nRpYDyOgWRUrl08mLL5ES69XfnTD4dsMA9VGh2VVawPHyq1i9a5Rpu8tkKXoXJXnfZlsH10KoomabkXDPMlQ1eHlP8Mrpu4CyP9ruyC+d0TvE6d6xzMBacc4szFXhvD7jWAomfvn3l44YNnfTrsXQzDjqC44X5GNPsCOsFPUGp3zfghSJoUcnI5QGDS3rwmXnQhQxV2snszihJ80WQMhmvHoY+0tM6GWHYpaWa6twGpprabVE8QWYQMnJfWLS+yCu0rQ==
*/