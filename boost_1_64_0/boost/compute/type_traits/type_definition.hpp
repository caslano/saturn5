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
irl5V+JgnZreT8K6UcOp14uKtveMIUYjdwmHu0Y0kNnpa1k0Co0WMj68zccHVsY0NepSHNgS4yogpwa/3iK8mIiqBS106IfoAbMawoW7Q7OSOlDAc6ucq+5FmL65QX5Fz72+u07ivJrzH8WLdfWPSBgqhcaqIQf1e/QAjrhLAqrmmULBgsXigrzJTBqZYAhkn5MXrYtLvXU8YqaAmg+DqupaBx1+rgn/yNrYR7mNAsYgvnVNt8uWn5Wl8G6MelKAzkfCzNfQxv6qF0cVqiMpx0dE7j0048Zc2LPfJsKudPC8UH9WmlPpzW7WBK+qeHmhJDrXdiTdfJdVGU/nJKlaiwbpbJVa+cDjgmQR7gSBXnM8U99VGdbIZF6VO+4HwBwV3rDHivR+TUeLml/mtt51/X0Xxs1XqznJJKpaFC8S2n/7KNsili3ceveeWFXnBFRxGzZJp+5+SzyrRUzfWbWEEP5cqZEBficWVUlVvkTEC/UrClyVfHjogw9pnm9hFN/kk35T37gWXO4vmCTAHjacE1LUDPRiQeRXEJHDoiWPr4bJZBtq+ygO6TDFuQ==
*/