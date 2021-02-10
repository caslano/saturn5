// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NUMERIC_VALUES_HPP
#define BOOST_GRAPH_NUMERIC_VALUES_HPP

#include <limits>

namespace boost
{

#define BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(type)          \
    template <> struct numeric_values< type >               \
    {                                                       \
        typedef type value_type;                            \
        static type zero() { return 0.0; }                  \
        static type infinity()                              \
        {                                                   \
            return std::numeric_limits< type >::infinity(); \
        }                                                   \
    };

/**
 * This generic type reports various numeric values for some type. In the
 * general case, numeric values simply treat their maximum value as infinity
 * and the default-constructed value as 0.
 *
 * Specializations of this template can redefine the notions of zero and
 * infinity for various types. For example, the class is specialized for
 * floating point types to use the built in notion of infinity.
 */
template < typename T > struct numeric_values
{
    typedef T value_type;

    static T zero() { return T(); }

    static T infinity() { return (std::numeric_limits< T >::max)(); }
};

// Specializations for floating point types refer to 0.0 and their infinity
// value defined by numeric_limits.
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(float)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(double)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(long double)

#undef BOOST_GRAPH_SPECIALIZE_NUMERIC_VALUE
}

#endif

/* numeric_values.hpp
iyvyRDTJkbeeIUPoYtKBRKN5wpiv0TGxCzVH4awiGhpqa5Zx1zcnsFtBrIFtsRJERhJ3xJdEZQk1rlhNODUS3bgNi5pE5LkrsYwdHpX3LrEPIVXkfREIj2DTY04PmUgRJoKtZacT2EgkrfWyMcBtjPNkSaBMBtAcFB9mPH6Au4HGiaZ4NXsmLq3BegzSUXZoJaz+uV4kGuYVAs1lhdaNkhqD6PcMwShtSsJXNYZNMhVBAE+U82EjB1wTOe3HgtwEnkRW0XZK0B+CjDoRp8y61EGBAOhljJyQMj3ociJMDIiMtEATNuktJOWWZyxXyjky5KJz3zXWMztX4EhHI9yMzL1y2Z6ItrPVildhtgW35RYUZz+NIJ0djv1qJyHUpRwBj5DJU2XuDfO08AAhp50VNjonzMfcaXyDr+705nMtpMXi7mSX/ZsvYsVOpj2sXL15tcWeU09Nfi1kuFWicjZoK2rfQyKUxCDRGiqKBALcApTJZJ4EuT6eTAgzdumEkcUnRIun/sfy6QIFAeGSfIG2Fr5I4EXH1aEGtC3g/5n3VDxZSy4SwFOD2Rf6KNEjSf5xU0ehkHc/AiBZZFnGwQKvHxZHoYQOoj0Y0r5hWEWQcM75PNncMaKOaZp8z9zGF0AP91jgHmPXEZ5sIeeh
*/