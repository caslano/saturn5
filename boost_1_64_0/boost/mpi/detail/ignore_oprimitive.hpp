// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/serialization/array.hpp>

namespace boost { namespace mpi { namespace detail {

/// @brief a minimal output archive, which ignores any save
///
/// This class implements a minimal output archive, probably an output archive
/// archetype, doing nothing at any save. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore
/// saving of most types

class ignore_oprimitive
{
public:
    /// a trivial default constructor
    ignore_oprimitive()
    {}

        /// don't do anything when saving binary data
    void save_binary(const void *, std::size_t )
    {
    }

        /// don't do anything when saving arrays
    template<class T>
    void save_array(serialization::array_wrapper<T> const&, unsigned int )
    {
    }

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;


#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::save_access;
protected:
#else
public:
#endif

        /// don't do anything when saving primitive types
    template<class T>
    void save(const T &)
    {
    }
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_IGNORE_OPRIMITIVE_HPP

/* ignore_oprimitive.hpp
tN4iANrevBwHUl5Ehktpe1XxbI8W2YCJXQynTYuYYp0iKL32tBpBQ4kz05YPpkrCGgKyKPtrPj8FV9IZSDUQkn+jepc9ErxZrThFyRZp2AjIJ/GB/tviOZdrO9t7CV/a4AkoppE7j0gKN5Ca+xo6ttZ3sVLR5N6ObVRA0i3vbs7uOEDBbpOh8Q0kIRdvr8BRNvysdxGbuvyXJz9hsSAUX/xNhTypZc1kmS6d0nJEi6fhP5dGUrlXuJjV4mfgjhHBXMKORfjlw1g787gN6zX/jbNVYfrczgXS84r+MSCf2Zx+J3guIM8+Mhxluai9woGG5GHgtQY0Vc770w2tVbwpnUdBr8nTK5dnMzCmQCRsyB7dAzr8EEL1DF+QqpPpAYxt7djAp4oB+lkJlJ9HLF3ingfHJAVMgrlFeHpP5Gut7Z5XiTkpwfHqHCQntYtH+DZtW3ONW3OR7sA+ofoOoTU2AW0c3m/xACVhdhfPZomZoNBz+vOXOR1KPqjZfQGxpqsVGM/uGx4IViME/aaGmSb3krJxnSYpgaMMJpH0O+8QquBjbF4j0m7Yq3C4bQ==
*/