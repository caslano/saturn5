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
i+rhKElu/7En866K2WzjB3fB9K9O/lETJA6HmDxu2ovfSnmmix4NIQosL8y+9elLuS2eA2XGi4rJiY51Dt9Ub8kN5RjhRfmXeDfpYsqKioQZl7PSLK9Dt7Vf/D+4c+q2CYXKR1mnwCSTeHmjes1KPm0kGE/LMPKg3J8afH2zumfvJ6aTyt1F6vOK6TavaBBBua7gZJ+1xgjNNm7JzWnQuUkzxXil/P07igfnyiZwogfe/CsKZ3IThpddivit0v+VjfvmOvUjRMBSbPYj2DWbtp/ZfZd6Ih6qXcPM1KhjVIRU84esr9dP19Gdb0+C2n47DOLEzED8xoM4EAGZ8+CK2B2bmPK55xxYmdy3ZWPMcd13elqJnfDdd15ZBXZszKCUWFE9dmRzitkex+1w348Sh5Mh0v+cxTCsTizXPNu0VI4mOosz3unkWD79IUuZy10y4KSkXlkU2kPCAWRftrIXsHNvvWh9WqdzLBCUxxohuOwVe2a5m3ixJV3PGXFzpKydX598XycT991xxWid3qBWJ5ryXOyK6oqIrOb2BWj3sL6At5P4WVi+cAne/6J2jMDQMi43UhOunyPcqVc+RhBvML8gcHE7X0SByuf9TEaM9whiYtCMC5zPHEq3Sqb7S5QLXvrjt4JuEdzx6cJZET8SRP1qjSdEbV9c4hVBXnDg827XFMPI+pazrv/QtUPcVMB1i+cVy+YLAlHJ0GrC
*/