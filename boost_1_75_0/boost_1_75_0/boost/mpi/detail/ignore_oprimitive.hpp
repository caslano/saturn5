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
OYW0vwES3TKjNPbzJ6RzA6ROg9tfA9/fMqI+7ydO0OdKSDkFt78CEtzSovjLGA3u2f+WQIsi36eYwPgEk86QtpLmlX6SGmnmLyvyvCzzgJGjyxxg6VczBdn6M5pBEFtV1bEDZoLsqQ1hx7+5xhL8TU6S9MhEJsgFR46JNMik4Mc5phwuKYUJ5nd/QJvwrT1qaPP43XOIJapj32IyNW9ApiN8Dd+PEsKD0t0gWwrZ6Os1TSJxjXGlmf9LZ5DJ/H3Nq8WgMskGGqW/sryHicwxeZ6TfcrKj1UvIpWveh7PFE3ERfepI26Nyk8IYosa2PeQbzSSWo8A/K0+pFky52V2UI+16QbldTABQ38EKa7ZaFg8Vb8TRhtpqikqhJtYToOU01QruBpfTsigIbR78XWyvaE9HzKAnxgsAY9D8+56S8Cj0bwN/zCvC2U/OnR5vfyx1hBp6/MXaqPjhLj/qXb9CVtNCftVPoTR6nMb5rNneG+fqSlhYBI+e/WPj5XAqPXsvx7tP8TMxpFTx81cxsbU3snKjZPrn0DOyd7cwlXG3orDy8b8RN/HmWge/DROl8tE88lk1I3g6xbzwZvnL2j/QkgbmGJ+1X0FojGbNFS00/FKXm17lZZgwJ87RD1n4hN4R2qXNL6g/CHig8vtMGpTURTBNz1Qp5zx22aqODGhfYWP/7JO8eTrQ5abZ2VF76ysriWPDdNehhPsaPlU
*/