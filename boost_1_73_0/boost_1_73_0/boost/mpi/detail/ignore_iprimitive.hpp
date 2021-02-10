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
MFld9utlPs/z5Zj9CG6aQNb9X6aS0vBNIT3Lr8R40vGjOnaN1lPguhN0MuxDtzuznonuxuoPfHevjNfD/HCR/gVQSwMECgAAAAgALWdKUrzg3n5pAQAAcgIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDYzVVQFAAG2SCRgTZLBTuQwDIbveQpruIC0nXJG2UoIAUJCHEDLBe0hJO40oo1HjmeGvv06mTKzOTTxn6+O/SdWMIt3GTtjY+pJpy+cD8Qhd+bh6fneNM2A49bY9qzb9oiaC3MBb8h75CbHgMYybse5AMuiEndjxCQL4WugSK7/dSZRUrn9CW2PTnaMekwfx7JzFsAmN2mlfscjlF3wTnBDPMNSJdj2iID1NE0uhW5pAJZsJ1mXSym1yHfk2M8QnDhwvSCDDAjFHRhchk/EBKs8kKyM3VdWUyAzsaegB15rwv9CmyXQTmDS6PdK8FtWnfmT3QZvoJb/QVuJlPJ6vf4LVpVjvzdQTIctk5CnERbKQBlN41nNwKaQTUkNtnw7eChmVOGSvLjxCnpiONKhtq4pmqdf1ScX4DTeBjpAIL+b1Aoo1wqUxllhLjC7tNFD6tTBKwpH3GNFqj+fszoEhyhDTPB6+/J4X66ytl4cPhnV
*/