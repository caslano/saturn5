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
5lAz/cPFDvVqGeR5DTJtJu6kAR2lOwqQ03eK0FiGplfY5h6m96u1BAkEcjW5Rek51tMaVBTFjqV/VL4Vc4QV4zEt5xZNF7fba6nileQQlJDIXeYWkVszjItGwPN7bdhdFhQyy+liG/7GFBYRlBiWH2F30MtO4TIk6UvG5N/7N2rX4vsYLUemZK+k4eJCJJlij3a8pR1jjMCXdPspMmVIaTRKm/egWHJKFV6QaqZIvZMAsGV4gDO08X6+lVOC9CvcFkaihp/ZJHBP0UwWCE8pghYUNIUUpKP/suwc+gK0CXSdesY+g+xKjMi/9WeqF13bRf1zGmtbC4uZ5vRibVyRFQOWoqspqRPz8KWwDGN2hhtphvP3J/oJrvSKXkSKl++GzmTCUrbnFJD6sq5Ln5Fk4aqyDMrKDLIYDEAQA/8kA/vB6nlJjSrKVpFCBWWjWESmmFqN4mqg0lYUyQ13l0zMz9TPH4xqyZb72PB6C8w3lJNtxkbXvqywq6+w9uKSUYiCdftDKlSj8GGTTUNIVNk1nwkhkyhO5uTWoOvRq/kt45cn8QOnA8ja2FrTWt5a1JrztAgq05QE+Fsb7a0UKngfexInD18GP/wRv436Vhzlu4+eOMqFSceFPeK1ZQnNCgzfCaNc9+ETPbkB0qeh7bhAilt+lO3+9ER+roS0U2j7WyDZLTfKbL9nIij3Seo0pB0HSHLLjtLfr50A5XZI
*/