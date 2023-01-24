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
7NfWh7Gnin2EyC/GtGq+tT770wbjvV+88dfN2GdFP/j1Mz9990+LsjO/kHHHX67a++dU7L1y/lfflHLXvp6CgZRr3h5N+dunsB8L+o/Cc+458aW7CgY+UzE5MveaCOzRYu3ktRteufLvpWF5X1+55uz9pkd/j31bzK8fGq6+q/YHW3K+99vW/r3LP9+CvVzMaZOf/Zrt9Yrz1/3g8iWXPPTutdnY38X6+luPPXzO9Jdvm+75RMQ9N714YTv2fLGWlv7zdYk1pqfm3Z3MjrAtgx/FHjD6n4zU+B8cHRvKe7xz5aWfLNbdh31h5HPVT/5kW/aXjZn3D6wzfvfvBZErZTt65/f5OUuf/rbp8/ev+V2CbfgJ7CFj/hx00/Hfx6wtyTj+xHP7Hx1/6GeTMp5Dr55f/Ifsy00dv71q64OXb9qBvWbQf5j+0T0p9qfmNRkoP+Vh/8T+M9ZFHvzty28t/PwTuSei7/nDlZf94W7sSRdRuZbOf/Px847n8r7PTi0a/y2bjX1qzLk3l/3z2WD97zMf+M2DS8JfbM3A3jXGfOt/tPqFR7c9Pe/QPjZUWJWSg71sjJtv2v6xWfp7P5f/dVvxb6LumPt57G1j/BZ5zXcsf9761bz+Gx+IntO+6n7sd6PN37O69Z8/enncdHRZ3XcOvv3bN7AHjjH+txvPnL+w8oFMx8pvrb3tfM527Itj38zY15mz+NMfy29+
*/