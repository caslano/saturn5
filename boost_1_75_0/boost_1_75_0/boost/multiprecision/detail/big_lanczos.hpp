
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
Z4hqfvF6loB0TtUYdGtfs0m5OIr3uyicF8TFpBuFryzaJLhi3zvU/W+bhLsmstPNF4UWVnoK2oZquojajfHrc43x6rUbX4D+/mdrN/bnN/yv1G5MvLg5tRvb/WkXtRuTJaN2I4EmODXeXLsx8J69qdqNG+P+L9VuXDlG1G7c8a5d1G78biix+T+HcszkuXH/ae1GUw5as5ux2Lf8HlCChvaEFO8WDaZsYMoEi7yl1uZdz3nZtR7eVBCCXcj9p8CC5XnkBJe85SQ03ivvPexVyuWE9+XUbTPaZNL2YeXWWniq+gqYgVtmKX95Uz/MdA2qyUqtcS1Cw/h1wb5/SRJ7Icaibw/gZ3o7/MRH+iAQ9hOTVvfELU66HEPsLS5Hsvk/np7ODvY9TSV9ZEUiNCHJdwIazUo95HNkJrxf3TlL+SAzIVLdBgs1dIDGJlkJH2BUxFuXk6XWJbLc3GiYK0ovxeTOPa4Ltq6WA8OAhVt3h99or7IVrThpDTqbqbYV57SP1ZGJmJMba1RNORKqjTXGVFfx4ClTfa53Q8cNt4+uetDUZrbp+GnT8Y0NtnFW7TZqnMlVFaZ6ZztM1zebrv9guv5FdajPRXxssvEEVgpFqbUIBF3OEVVGtos2RmoLPQ/GYtOdxaY7waGJavdhlOEiRr3sQTrINae62L4hlOpC5LqY8cx/JWeseW5A5av2YbOzfQ3vU9TzcL7lnfoe
*/