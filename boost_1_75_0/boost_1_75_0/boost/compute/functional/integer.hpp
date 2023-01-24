//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP
#define BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs_diff, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(add_sat, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(hadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(rhadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(max, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(min, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

/* integer.hpp
OVrhP3xjDNBvQ+zqWW+s+1OdMxTS566N6UkvjA2QswO5gcoq745TbW/0o3n5sL+PlaxfyutYMPWyitP77v9RoZ8SUPz47yrftnbdulXS8AALzqtdzez1nw88z8jvk81L2e3CXt1UknCC0f/Bvx2/SVms+cud/iRc6loTQILbAesfeidv1Hpj0Knax28D8g/ZyL/VylIoCt8WOZk03YdHAYOCkeObY1VPvTgpKOYdbbv443f3/xU43Uqrt7s55ptlcZB/QbkCm5xlOlh/ofNaatES3RE9lv8JmYmWvCoX4KdrCUgQWw8AqJucl8y5mE46omxz5Xi7eWhy/cfik97dDuVDeDfHgCaVvJOr/QzfmpQeEqOz8MyOsfZMxdfUC1LvIe8fxO5qSapopt+CjwUr2yda2lTHUh2xdi++VyPK+hrSRqgACL90Vlu2XeiVV7qh/cUHJnxC7isJWZrQ7krOBJF74JC8mguYD/qJ7aBlykSLled81Dk5RO9AScCuV27kv8u+s3JXgBM0RT8DV5ti/HhJ/Qf6ukCOy0/lCwZgQlUqPJsllKQJwEQSX0Nf7FQmyytvj667PaG986dosOAlknt+uI6cnGoK1HSZrv1q3NgbG55pdPZIdt0ClL1wsS1DyWS6yte3bSxiUy0vFbmmdapag4hJF+gxY8sZy90hJti2Ly8WLDNsZ8ILKy9ZkxPrGIZ5jOK6EEMsh1Y7
*/