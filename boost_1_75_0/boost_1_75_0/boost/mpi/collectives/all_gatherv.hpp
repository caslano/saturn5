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
aXztouHPfx575VhT2hP69+7dP74n5752U9Gb5sfuw/45xhCVzN3v4tcS5PkNPaL+hp5Qf2s1nt8jXt+tWs/v8jDP74Phnt+lEZ7fyyM9v896ffdFeX5HeZWHvrhmbuR0YYd+DZb2IjE+4cOGYNFHz17OxB7wLJV9tmpooVHZyyUibAKrt1fWWi0bN9itO81mc6ucwwRxN7ul0b5nd510y10u2jXyGEttrXOlWCs7SGMUHXUa+5eSHMWKcdEgyfL+S2SfT3I6SX5byIxBFshdT3HRlIedl2cRzuoYO0v0VqrjsxSPE3adcCtawdgjK8Q4/vhyMbYbIVkbobROUtqV5K8IiyLE50PkJ5K+T1Ic51aI8I30fZDCLV8pvu0U7hTl78RCMRatorQYmTNkX09tPHa5WDsronAG6DhZDj2VeQ2lZ6I00qi8jlh3nUVTWloKq6U4xsnPeirXIKU3grTJ30i0WBOHXxv5aaU49RRPE8UTSvEeoLzoV7jj01F5WihtE8UxvkTQH5H7Tlj3xr6NgXg5SPFXUnotFIeR4pwkfIT8T5DduVSs9UfL8x8jFL8zTswjbKhL4sF5IHhH9GbiwTDlLZ2MkfycJrdmfMeJdQwlb5Hs5dTrS0zicld+9U5lnLXA+OhzRN9RnL05r6S0+IYd2aa80sJiszLemm9seCXv+vpKz4c1zWZl3DXHmHkb3DMr6i3ebuEs5kRJ
*/