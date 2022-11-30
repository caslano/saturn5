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
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
*/