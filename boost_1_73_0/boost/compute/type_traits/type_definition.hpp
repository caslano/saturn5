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
2paJQaTPTdoxN2/DeLdfuqf52y3+zb/5N//m3/ybf/Nv/7Hn/2H/mvn/zef/Hm7P/xEyfnssEoSMQV6jsb7iqNW/l3v8+EyC9LMoc2lkY9DfBq9V8UeyNqLT9/ypKtzm/v4gOcNt7tSdKjxBPfX7eO5nfx/vDdzmHHhDhQ+n5zzA57sA2V/3bz8ebspvn89WPedqn93nFccPsYW5P0sbt/Z8+596jv1aPcceTd34/eQK3b+Y
*/