// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file datatype_fwd.hpp
 *
 *  This header provides forward declarations for the contents of the
 *  header @c datatype.hpp. It is expected to be used primarily by
 *  user-defined C++ classes that need to specialize @c
 *  is_mpi_datatype.
 */
#ifndef BOOST_MPI_DATATYPE_FWD_HPP
#define BOOST_MPI_DATATYPE_FWD_HPP

#include <boost/mpi/config.hpp>

namespace boost { namespace mpi {

template<typename T> struct is_mpi_builtin_datatype;
template<typename T> struct is_mpi_integer_datatype;
template<typename T> struct is_mpi_floating_point_datatype;
template<typename T> struct is_mpi_logical_datatype;
template<typename T> struct is_mpi_complex_datatype;
template<typename T> struct is_mpi_byte_datatype;
template<typename T> struct is_mpi_datatype;
template<typename T> MPI_Datatype get_mpi_datatype(const T& x);
template<typename T> MPI_Datatype get_mpi_datatype() 
                                  { return get_mpi_datatype(T());}

/// a dummy data type giving MPI_PACKED as its MPI_Datatype
struct packed {};
} } // end namespace boost::mpi

#endif // BOOST_MPI_MPI_DATATYPE_FWD_HPP

/* datatype_fwd.hpp
3DNfUxmol3QqmqvElIBVLkRaH0wlH6vya8lkmOuRJBUdSPkLWh+0PIWZknqp/TS7Zjtz+Ilikh46f58GK9+WMeCYWP4VHFX5CUxzRk0CBT5KK2rCrJl34dWO4vX3JWMGCAC+XK9e3AmUJNlE1z0OY+PP4QRrKeeEHVk0rQvZei+9M5w7EFJrCxpdOzdVl+qJtPXweOWlP+bB4fIfpryjljuk32tE+8b8VYrjRwfjMA55E+uau08HvPVpgWR7ipAzMxZ7BPpx8MhoVJQr4/DmLhE+WmWtrAUljl+9/4/1q1KF4HR9XvS3gMK2P0LDc3mOqdcYWMSAEy6qLfobCUKuJuq9vejOAi8fCrECkjSh5BuIQiDxucglGJfxdg1yCV1Nh2qDFxVoHjaC+n855BHgiGvZbook4dPXAmcnbXVVpTvnqc0XOVPoZ54erX+1qyJs2H4R+RBXCJa1N/THLSP4kBRUtW1V2y5c72vvlvXFxOgBDe+vQftExFfi6X/oWd9r2a65eD/5AZO1BPBfeq2nMMiIP4THP5RdtWkCFz+GDzlfpQar9lO7aO22Og==
*/