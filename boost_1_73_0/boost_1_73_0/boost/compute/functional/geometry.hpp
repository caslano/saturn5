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
Gx+XISOyyjudPWS2ypbYLgt6HcLWvzg/z9umgifnhcv9eZ5CMVmHzZFXH2HNJttrtw06ON16M9Z0/VhvXGFLekWI8OG2XVbWr8e9WdiwLs5do72pqrgcbrXGiwtGz2K0xnSl3sJ6G+jFu9rTbru12xxciLDGhcq2qbEdwoLrCofAj3VbF6bh6zkQaZcYZQ75V1LW215oV8MqPbqY6elspJeZt36sP0znr2/ez/WHi9vbi+v5R33zq764/hjX+316/QrYsNi10ebTtjEeVjTabraVNcXB5v9opavJ/DXwtqS0nm3aKlj9ox49/1nPzBagfv7TSI/i1/07LRfaGtEqs9xgldlrfX3x9kodLnV3ptduF9PPIT26k298dTW7vJ2+m09vrhUHFn8QQPdgmgdrdhTPo1U+YweVCIqg0Zdq27hVk208w5sAjb9+a3Jb2hywrFEQK8CpRIxNlq+BijqncgAoa3rlelN0a1zhxEtR0PZ35TT5GdrgGptVz348vSvfdSvzwhlAi/yZYFS6jJyIpm1svdI7ZLzzhqB8tLzJ/P5oacVLD8NTHsSEbulDMlHqoqo693xikePIUXyAutJ+gudsFS224MsmnKXRzcv/Xl3Op/+7mo3U/IklXFmiAFGzMAyeZktb2UA1G9bg
*/