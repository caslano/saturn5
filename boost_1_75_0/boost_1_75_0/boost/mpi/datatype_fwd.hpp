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
HcOwAIea5bw+dvvNQiaR35pF7FwyyEpXZ6LmbdAG592OG37ivzdtUwm3mCZZFWFf/MkdUvqnfsqQW/zOOYRJtzvCY1yBS5t0W4BZeStb+KKIzBXDbZCHfTwurkgVq5t9maIDmHmbKbn1cvBHrcl7rxGV+SPubfAo6nI8hX9EwnH464PzPeNRp3Gfq7gRqXZWd2bX9ZJHxyYp8eA/pQkG4BI47apDfKAgBrh6WZCGjyq0+ekQyisWtOX1Io58Qs1FwBP+9wXGV2uupIJ8inkYCoUDp7tBbq2suzTQh6D+KF7Gd6oUfIRbZjjUg4yTysesNy7u+NHIHi4Pm3gUrdliW4Yzp/aAF6rxqv1qDOIRnG6dEDPc3mTV7nSqg/SOsl2yxigKMF0Wilqhkgw1yZpz/tfH01b8B9nNTlwa31bsfRiOHHaIndJaobM/tLSbWuLpM/om2CCVSgs9ZbG7ryFJ4dH9HvqYFrg3u6lm14QK6vILMhDlmAgG+ftQ7FC39VYfy61L2KkeKfjRHuQhl/BVV++Ys6+S/7nIIc8DzFbi1VbMz/eovYMsT5pq+4jdnYh3KErd7rjDTcwdxcbDsOP0lHij0A9YQW+qjd5Iw3AOsQ7ivdb/wLVuY7x1HRg6aEJRxa8wF6SSBPM4MxuB5EuLnQhuAs04sG+aFH9Yyyf74sqea0lgF1W7etQOaFCtQ5ujYiF3OthCCXQ4AvPf
*/