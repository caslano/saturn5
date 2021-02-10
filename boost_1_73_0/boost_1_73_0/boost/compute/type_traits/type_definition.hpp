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
jg0bcMRo0JQ97hQOZwJ/KKnDpjA3bAc7N9jqUYjsaDUwXIXJtsEg/bb2NX5qpoqquBAiMcC3reTZrUjeL8jtCDhFDJs4T9j1CwkLjcTAy3TT90V5VpMpMk27LfVyaZckE6r70THbXeDUHVT8vUXk4a1VdyIDFNLvDd7pvW6nr8EhBH+rg7e8cBur1/Xp9EB2yn5GbuLKcfnLDCqGaeXoGZnA+QBPBNjuMsicrvl9ANZafmjHl4Gw4Zt8FOzLW19zdCBDhPfKZvxOgG1Wt9hLAz8wDfQs9I0WeXZUwXrp/rzCF0sNttHBpQG9Prjp9xVc2HA00eFLwReN88r9BddfZzwejnWt93tHvkK6D+PeBFts/JohN3CpTtT0S47x5qbb7YzTr7XJJYyk37zvjN8MNeAEa6vfN8jX82+VGZxilP2egxXEY8Ou16gUukit2LFyhq/lXSRNk0kNe7GK6LJY6To2SSf717YnrxBMCZd4EyTyfEBpvUHoPTbU+UYser+ZUv7XTKbnF2oKONsdb7LiWYUIqMo/EJ3bqMyVR98fnVu0XHSKBjA6bD1RipItfkXfuDfopGj4n9xmHXcTdhQMxU78BKbzoiCtY9EHMPA2N5nSmjX+zz0zo8NYN+lLQ+UkoxupGEhXJ6gH/Lcb
*/