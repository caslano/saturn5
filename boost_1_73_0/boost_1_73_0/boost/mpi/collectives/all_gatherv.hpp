// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gatherv
#ifndef BOOST_MPI_ALLGATHERV_HPP
#define BOOST_MPI_ALLGATHERV_HPP

#include <cassert>
#include <cstddef>
#include <numeric>
#include <vector>

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_array.hpp>

namespace boost { namespace mpi {

namespace detail {
// We're all-gathering for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
all_gatherv_impl(const communicator& comm, const T* in_values,
                 T* out_values, int const* sizes, int const* displs, mpl::true_)
{
  // Make displacements if not provided
  scoped_array<int> new_offsets_mem(make_offsets(comm, sizes, displs, -1));
  if (new_offsets_mem) displs = new_offsets_mem.get();
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Allgatherv,
                         (const_cast<T*>(in_values), sizes[comm.rank()], type,
                          out_values,
                          const_cast<int*>(sizes),
                          const_cast<int*>(displs),
                          type, 
                          comm));
}

// We're all-gathering for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
all_gatherv_impl(const communicator& comm, const T* in_values,
                 T* out_values, int const* sizes, int const* displs,
                 mpl::false_ isnt_mpi_type)
{ 
  // convert displacement to offsets to skip
  scoped_array<int> skipped(make_skipped_slots(comm, sizes, displs));
  all_gather_impl(comm, in_values, sizes[comm.rank()], out_values, 
                  sizes, skipped.get(), isnt_mpi_type);
}
} // end namespace detail

template<typename T>
void
all_gatherv(const communicator& comm, const T& in_value, T* out_values,
            const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(sizes[comm.rank()] == 1);
  detail::all_gatherv_impl(comm, &in_value, out_values, c_data(sizes), 0, is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, const T* in_values, T* out_values,
            const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(int(sizes.size()) == comm.size());
  detail::all_gatherv_impl(comm, in_values, out_values, c_data(sizes), 0, is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, std::vector<T> const& in_values,  std::vector<T>& out_values,
           const std::vector<int>& sizes)
{
  using detail::c_data;
  assert(int(sizes.size()) == comm.size());
  assert(int(in_values.size()) == sizes[comm.rank()]);
  out_values.resize(std::accumulate(sizes.begin(), sizes.end(), 0));
  ::boost::mpi::all_gatherv(comm, c_data(in_values), c_data(out_values), sizes);
}


template<typename T>
void
all_gatherv(const communicator& comm, const T& in_value, T* out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  detail::all_gatherv_impl(comm, &in_value, 1, out_values,
                           c_data(sizes), c_data(displs), is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, const T* in_values, T* out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  detail::all_gatherv_impl(comm, in_values, out_values,
                           c_data(sizes), c_data(displs), is_mpi_datatype<T>());
}

template<typename T>
void
all_gatherv(const communicator& comm, std::vector<T> const& in_values, std::vector<T>& out_values,
            const std::vector<int>& sizes, const std::vector<int>& displs)
{
  using detail::c_data;
  assert(sizes.size()   == comm.size());
  assert(displs.size() == comm.size());
  assert(in_values.size() == sizes[comm.rank()]);
  out_values.resize(std::accumulate(sizes.begin(), sizes.end(), 0));
  ::boost::mpi::all_gatherv(comm, c_data(in_values), c_data(out_values), sizes, displs);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_GATHERV_HPP

/* all_gatherv.hpp
MJ9OV1M25ovFbDFlxD4l/QMHU38uNVZ0oE57hwGub8jsVDP6jweyUgZ7AfCiqYB/Zwfp7/MgU2uMqrKe4NL3z2/v42QdXZ5zZXS/SfzZcrmE/5Ufi87gERudt0AFgumyYPPe6dROIDmGtQNXY6pznaqybCEtrMMKyMITgqoAd1gxXbU1T9iAs0yiCDRBykmG8B4a5ArCDPBVpcQctgIFN1dJ38y1jtBMhKwtf2iB6XMgamxKGCNc4Kum4dCRouGgtL/8dNuUnbKJ3dJgNPqx+glvPsJsvli+fff+w2o6umCVfxGx5MPCT5K7PwSVE4/bCe7uCArleFjWNXCFpYGQux7LBHVjyaa2DMRDHG5Ysa1aY7fOE9FVHANv/xPLMjVvjbfL0a/Xnri7Tu6gm9Prz9ATybcohLUn4vX38JDoTvNgfnlYJ143+LGX9I8D+KdD/w1QSwMECgAAAAgALWdKUs6CGMFKAQAAVgIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDQ1VVQFAAG2SCRgjZJLTwIxEMfv/RQjhtdhKSiimMoFNCHxYDDRgxpTdge3obvdtMPr29suyEbDwUvb6fzmP49WEDqKpcMREypfGL8tcbcxNnEj9jB9vGdRZDEzhBGp
*/