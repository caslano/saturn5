// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/serialization/array.hpp>


namespace boost { namespace mpi { namespace detail {

/// @brief a minimal input archive, which ignores any load
///
/// This class implements a minimal input archive, probably an input archive
/// archetype, doing nothing at any load. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore
/// loading of most types

class ignore_iprimitive
{
public:
    /// a trivial default constructor
    ignore_iprimitive()
    {}


        /// don't do anything when loading binary data
    void load_binary(void *, std::size_t )
        {}

        /// don't do anything when loading arrays
    template<class T>
    void load_array(serialization::array_wrapper<T> &, unsigned int )
    {}

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

        /// don't do anything when loading primitive types
    template<class T>
    void load(T &)
    {
    }
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP

/* ignore_iprimitive.hpp
qwzis+OGCjIr/8MAdpK9Ww92NvZPAEM2RvUcGWWfup5Q/6fVm8RrlQHoeJvyXxcWMfiI1nSBQEClTx0mjVblPyk4F/16jDPoOIJWOolHdgEeyEVxhH7HGFI9mWmPrgKE/BWXQkn9FpJm9vaDcbZkZDHfRKI6C/LEsJWcKn89ZSgiUXnHBcSjKf9Aoz+Sd2aT5YORBoiKhX5QMFFFzuCeGbNofLjMMYQ8rTOUusfjQwzqVHpnAOzm8EAC8pFEw0GtC8k3BZFhWqknhXPG/eR1q0VuRQi9fue7Jtr3maK+/xdv4W/V/spvfBxFC6Fewq0j/ncyT5GMbZLC/8mGENrhDJEIGixZjMrJe8lVYoJzE/ZqKswzKQl7nOjlq41zuvtyXym+g1RCZI2eI8hrMgsSRz3r0YNcwNAuw6mti4xm2Qfbre2KXKIUt/ZrafWoH72wz7eNSdJ7WCDPsiafdZCK3N+3P9RfshK4ZjB6LcgxkGyKxe51gDtok6i9BOW37ZfocIEyZuApQq5Rki7bTuTTUCgh+NNLFAkB4VSLyC35AYrBRahisID9D8SnWA==
*/