// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gather
#ifndef BOOST_MPI_ALLGATHER_HPP
#define BOOST_MPI_ALLGATHER_HPP

#include <cassert>
#include <cstddef>
#include <numeric>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <vector>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

namespace detail {
// We're all-gathering for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
all_gather_impl(const communicator& comm, const T* in_values, int n, 
                T* out_values, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Allgather,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, comm));
}

// We're all-gathering for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
all_gather_impl(const communicator& comm, const T* in_values, int n, 
                T* out_values, int const* sizes, int const* skips, mpl::false_)
{
  int nproc = comm.size();
  // first, gather all size, these size can be different for
  // each process
  packed_oarchive oa(comm);
  for (int i = 0; i < n; ++i) {
    oa << in_values[i];
  }
  std::vector<int> oasizes(nproc);
  int oasize = oa.size();
  BOOST_MPI_CHECK_RESULT(MPI_Allgather,
                         (&oasize, 1, MPI_INT,
                          c_data(oasizes), 1, MPI_INT, 
                          MPI_Comm(comm)));
  // Gather the archives, which can be of different sizes, so
  // we need to use allgatherv.
  // Every thing is contiguous, so the offsets can be
  // deduced from the collected sizes.
  std::vector<int> offsets(nproc);
  sizes2offsets(oasizes, offsets);
  packed_iarchive::buffer_type recv_buffer(std::accumulate(oasizes.begin(), oasizes.end(), 0));
  BOOST_MPI_CHECK_RESULT(MPI_Allgatherv,
                         (const_cast<void*>(oa.address()), int(oa.size()), MPI_BYTE,
                          c_data(recv_buffer), c_data(oasizes), c_data(offsets), MPI_BYTE, 
                          MPI_Comm(comm)));
  for (int src = 0; src < nproc; ++src) {
    int nb   = sizes ? sizes[src] : n;
    int skip = skips ? skips[src] : 0;
    std::advance(out_values, skip);
    if (src == comm.rank()) { // this is our local data
      for (int i = 0; i < nb; ++i) {
        *out_values++ = *in_values++;
      }
    } else {
      packed_iarchive ia(comm,  recv_buffer, boost::archive::no_header, offsets[src]);
      for (int i = 0; i < nb; ++i) {
        ia >> *out_values++;
      }
    }
  }
}

// We're all-gathering for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
all_gather_impl(const communicator& comm, const T* in_values, int n, 
                T* out_values, mpl::false_ isnt_mpi_type)
{
  all_gather_impl(comm, in_values, n, out_values, (int const*)0, (int const*)0, isnt_mpi_type);
}
} // end namespace detail

template<typename T>
void
all_gather(const communicator& comm, const T& in_value, T* out_values)
{
  detail::all_gather_impl(comm, &in_value, 1, out_values, is_mpi_datatype<T>());
}

template<typename T>
void
all_gather(const communicator& comm, const T& in_value, std::vector<T>& out_values)
{
  using detail::c_data;
  out_values.resize(comm.size());
  ::boost::mpi::all_gather(comm, in_value, c_data(out_values));
}

template<typename T>
void
all_gather(const communicator& comm, const T* in_values, int n, T* out_values)
{
  detail::all_gather_impl(comm, in_values, n, out_values, is_mpi_datatype<T>());
}

template<typename T>
void
all_gather(const communicator& comm, const T* in_values, int n, std::vector<T>& out_values)
{
  using detail::c_data;
  out_values.resize(comm.size() * n);
  ::boost::mpi::all_gather(comm, in_values, n, c_data(out_values));
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_GATHER_HPP

/* all_gather.hpp
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
*/