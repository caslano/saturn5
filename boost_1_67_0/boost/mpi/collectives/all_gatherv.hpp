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