//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

#include <boost/mpl/bool.hpp>

#include <boost/compute/type_traits/vector_size.hpp>

namespace boost {
namespace compute {

/// Meta-function returning \c true if \p T is a vector type.
///
/// For example,
/// \code
/// is_vector_type<int>::value == false
/// is_vector_type<float4_>::value == true
/// \endcode
///
/// \see make_vector_type, vector_size
template<class T>
struct is_vector_type : boost::mpl::bool_<vector_size<T>::value != 1>
{
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_IS_VECTOR_TYPE_HPP

/* is_vector_type.hpp
n/sAw37vTftm3NfbV532O709HHR7b0l9etnpqjf9SVNtT3rDwUwh0+veoHd9c9183xlr/NXeMJiKSc1et/mxo+Hc7YvBcNaAic3v/kiu5eECRNfGpnn87ybGmQi/JTXvGJmDQh37lnspIO0sFe2HZkYLuguyoVz9rgeOAQDMpya4J7gR5RZCb6FzI3K4GzebazBcM4bGeeKNF4XyJRiQ9OaAFxIW+dymSoEEwBYky6g8Fg0QVrZrr6IV+QKODaGJrimZghiGaVI/hPkjg4nFSDqIbwOifRE5RgAw8rUbrUBzAHFHyVnr5Lh10soLabibZAKPGcEGfJKQHYOjmAaAMZ5HIKgcB4J0tYKA5CEYRAAwBwAp8hrEYhGgMTaPHGcD9oHYEwEMK8CgxDUYge1FgEBZyFCNaad6nOcSUhOGJnL20G5rm2HskoEH6YQPRwytnTMX5AJwAJyX5pYK+5VhBh45ACewXaC8Ut939DikYJEg09oL7hBaAjIaRn6cdHCZIlHBW0ZexxNf81evk8gcjbp99a32GpWHmnApqsoINmhCw4m4rwy5P0IiBRUSKQ4uWsJ0O+rkZtzR7+/v0X1hBJ+AAlDS+p1TI4wg7XDTewHmsNuNFF9IKyFH4+Fk2B729c0GZRGo8Mz5pjH9
*/