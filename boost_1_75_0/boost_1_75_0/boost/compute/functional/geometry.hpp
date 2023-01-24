//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP
#define BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

#include <boost/compute/type_traits.hpp>
#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(cross, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(dot, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_distance, typename scalar_type<T>::type (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_length, typename scalar_type<T>::type (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(normalize, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(fast_normalize, T (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_GEOMETRY_HPP

/* geometry.hpp
29/WI4mYDA2REDP3a47S6j6Dx4bd+EW7y8ZInXUXyInVaubecrWlGypnZKP7+Rm52sDfg7nm4bmSXUl3TdPuxzqoGNdVNXl4A340JUpuTf1SElFXf2xBkLJzenlp8eaJEtpbXYRU5p/npfAUHjn8g5O9UQRY5x6vlPL4qLPPZwF/d67YlbLI8D1kWpSLYZ8/Ck6Sj0j2Tt0T3Lv3I4muJ55tpuqUOx6/tS5x6cz3jbrMx80eceNaNa2en0J6xX0LIadLPJ58qzgJD4Dy72o/1kLE09NMAfc0Vy8/4EJPXZtILhowjr0oKdrTkjGQXo1TdOuwkG3c5fczvuyBYyZP/Sg+eqftL+vaJ85//rKuoCHR+YPS/Tft0YGZLGKpnJ1lC9/cqZXJ7h/x/xGg/ia9CZAF7XhfLFG/c0xdLT1fni05OthjnA3/x1yCqI9+0pJ25Dd6zH6Huotc0mBxk+vf79PWTyZJ2VGMazXjVkI/TigJTiTZeSrPHUiBS9CjvzLSAaxdbprWJb4CAPlxvYsjO1FC5oLEcn80jb5NT8pp0Jf8KtZ1byRRR5JZXZnX6zOQZqVPGR58koGgvheYQZhACko+Z/aRhcXELflDtjDFPHnTZSU4WkJWWdE6cb8NUDe6DbN93E0WVzA65+pNbYI8GObADDIpc9QoVyBkzbRztmkO7vPSETKanegh6k32H/en1nBH65XsK1tLsY/J
*/