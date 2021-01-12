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
e/35Zsh8J8l8M2W+2TLfHJmvSeY7WeabJ/M1y3ynyHyn6pf3d+b7nsz3HzLf92W+h2S+H8h8D8t8P5L5HpH5HpX5/lPm+wla673c04wPO6n3nzOeN5ZiEzyBLfAktsGvMQjLMAS/wXD8DmPxNE7CMzL/73E6/iDr+yzeg+ckP0VEieTnlOSnIbFZ8jNTyuFuKYdZ2AAL8Va8DwPxfuyMs7E3PojjcQ6m4lzMxnk4Axfgvfgw
*/