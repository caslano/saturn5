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
np/ZP1BLAwQKAAAACAAtZ0pSTrIOunkBAACHAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NjRVVAUAAbZIJGBNkk1v3CAQhu/8itHm0kj1uueIWqqqpFopyiFRcql6IDBeo2LGGvBu/O8zYHe3HAwzvPP1YJ0xZWsSdkr72JNsf3E5E7vUqYfD471qmgHDpHR79et2laobdQMvyCfkJnmHSjNOYSmC7VAVP4PHmDeFrYZIUo3rVKQo7vafqXs0eWaUMr0P5ebqAB3NKJ3amQOUW7Am45F4gbVLOPs8QKAzcjtPEzKM/kPC2jUOtKVxNNF121TQH8K9lLi45bj1Vzt/Q/b9As5kA6bPki8PCAUZDCbBO2KEXRoo75Q+Va2kQGZiS04KfpOE/5k6ZUdzhlGs77uMH3nXqddkjngHdabfNGVPMe33+z+gxbNCuIPyEjAxZbIUYFMpKKtpLAshbIqyKalBl28HD4VQdXwhm024hZ4YVrWr/CRFc/ha4RkHl/Uy0Bkc2XkUFFDeGiiGRcRcxGziUYrUrYNnzOzxhFVS+bwvQqg+hY/w/OPpV0G8jl4IX0C113/vE1BLAwQKAAAACAAtZ0pSC3V6ys4EAACjCwAAHwAJAGN1cmwtbWFzdGVy
*/