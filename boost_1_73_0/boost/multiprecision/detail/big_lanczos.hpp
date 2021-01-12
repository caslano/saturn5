
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
Lb0W4256Hr4W4XU1vHv7Nshox6Xa9X+/l/5mwT3DvSXU07uD/60Iwn6Z8n12udn1s5R7hvMYzo9/sMdfD11bg+cLlH8qdbcFA7AsLWP4Tu5zFKWhsTG/93wxEbYdV38nE4nXcKnU+fS5c/c3dg+fsmHQkq4ViuYMDzoU5qdndlw/WQOnVCYLfL4azjb2y5DjwLNSyU+S2RT5KMvWEW+jjRrmMeBR4JTVeN/17bGbJcKl4cXs
*/