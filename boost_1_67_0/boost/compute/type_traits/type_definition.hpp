//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

#include <string>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct type_definition_trait
{
    static std::string value() { return std::string(); }
};

} // end detail namespace

/// Returns the OpenCL type definition for \c T.
///
/// \return a string containing the type definition for \c T
///
/// \see type_name<T>()
template<class T>
inline std::string type_definition()
{
    return detail::type_definition_trait<T>::value();
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_TYPE_DEFINITION_HPP

/* type_definition.hpp
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
*/