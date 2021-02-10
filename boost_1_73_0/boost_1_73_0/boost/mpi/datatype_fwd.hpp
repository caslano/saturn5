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
DxsR2+0CGrfvpcvyzeN86Vgv+o04Ci/zhSOrHa2LJemSRoJqnzHw89Kec+M8UmabBp/3Odhw8bZAi3NnUkEmQii+rlLGr5FxOPtCCqAJZxEr+mgycnBb7eMgXaFHVnEd/wXqCrkwAMkEPoE5qstCvvFGi6U1n11dboeOv8vfr9AVgPwqYbSnEQhGybHIKPmg2P/9BLZ9ERP9HIz89XfzG1BLAwQKAAAACAAtZ0pS4j8QQPMAAABiAQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MjdVVAUAAbZIJGBNkEFvwjAMhe/5FRaII0rLyrqhqJdp0pAmikbFPWtdWq2Np8QU8e9nygY7xS/+8vxiwxi4tAEzZVpXkxxfeD6Rr0KmWsd4QA80oK87Oimj702jr7yaqim8dC06noe2QmXKUQgR0MvLTDlycq3/JBhnexnIRNBZf0CY98Btj3RkGGx3REH0lQFTUt9bV2WqYf5eaT17y3fFeruabfL39a543Wzzj0LHySK92MRPSfKYJkmUPqTR83IZRzL4ZiHlb7Yx9R59W5+hsmzB1iw/5QbhshFobIBPRAeT0BBPlBlGVizQe/IlVRJuIYb/pNE3SN/X+gNQSwMECgAAAAgALWdKUt72Jr5g
*/