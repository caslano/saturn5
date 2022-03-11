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