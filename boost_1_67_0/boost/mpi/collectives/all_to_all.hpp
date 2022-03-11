// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.8. All-to-all
#ifndef BOOST_MPI_ALL_TO_ALL_HPP
#define BOOST_MPI_ALL_TO_ALL_HPP

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <vector>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/assert.hpp>
#include <boost/mpi/collectives_fwd.hpp>
#include <boost/mpi/allocator.hpp>

namespace boost { namespace mpi {
          
namespace detail {
  // We're performing an all-to-all with a type that has an
  // associated MPI datatype, so we'll use MPI_Alltoall to do all of
  // the work.
  template<typename T>
  void
  all_to_all_impl(const communicator& comm, const T* in_values, int n, 
                  T* out_values, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Alltoall,
                           (const_cast<T*>(in_values), n, type,
                            out_values, n, type, comm));
  }

  // We're performing an all-to-all with a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it.
  template<typename T>
  void
  all_to_all_impl(const communicator& comm, const T* in_values, int n,
                  T* out_values, mpl::false_)
  {
    int size = comm.size();
    int rank = comm.rank();

    // The amount of data to be sent to each process
    std::vector<int> send_sizes(size);

    // The displacements for each outgoing value.
    std::vector<int> send_disps(size);

    // The buffer that will store all of the outgoing values
    std::vector<char, allocator<char> > outgoing;

    // Pack the buffer with all of the outgoing values.
    for (int dest = 0; dest < size; ++dest) {
      // Keep track of the displacements
      send_disps[dest] = outgoing.size();

      // Our own value will never be transmitted, so don't pack it.
      if (dest != rank) {
        packed_oarchive oa(comm, outgoing);
        for (int i = 0; i < n; ++i)
          oa << in_values[dest * n + i];
      }

      // Keep track of the sizes
      send_sizes[dest] = outgoing.size() - send_disps[dest];
    }

    // Determine how much data each process will receive.
    std::vector<int> recv_sizes(size);
    all_to_all(comm, send_sizes, recv_sizes);

    // Prepare a buffer to receive the incoming data.
    std::vector<int> recv_disps(size);
    int sum = 0;
    for (int src = 0; src < size; ++src) {
      recv_disps[src] = sum;
      sum += recv_sizes[src];
    }
    std::vector<char, allocator<char> > incoming(sum > 0? sum : 1);

    // Make sure we don't try to reference an empty vector
    if (outgoing.empty())
      outgoing.push_back(0);

    // Transmit the actual data
    BOOST_MPI_CHECK_RESULT(MPI_Alltoallv,
                           (&outgoing[0], &send_sizes[0],
                            &send_disps[0], MPI_PACKED,
                            &incoming[0], &recv_sizes[0],
                            &recv_disps[0], MPI_PACKED,
                            comm));

    // Deserialize data from the iarchive
    for (int src = 0; src < size; ++src) {
      if (src == rank) 
        std::copy(in_values + src * n, in_values + (src + 1) * n, 
                  out_values + src * n);
      else {
        packed_iarchive ia(comm, incoming, boost::archive::no_header,
                           recv_disps[src]);
        for (int i = 0; i < n; ++i)
          ia >> out_values[src * n + i];
      }
    }
  }
} // end namespace detail

template<typename T>
inline void
all_to_all(const communicator& comm, const T* in_values, T* out_values)
{
  detail::all_to_all_impl(comm, in_values, 1, out_values, is_mpi_datatype<T>());
}

template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values,
           std::vector<T>& out_values)
{
  BOOST_ASSERT((int)in_values.size() == comm.size());
  out_values.resize(comm.size());
  ::boost::mpi::all_to_all(comm, &in_values[0], &out_values[0]);
}

template<typename T>
inline void
all_to_all(const communicator& comm, const T* in_values, int n, T* out_values)
{
  detail::all_to_all_impl(comm, in_values, n, out_values, is_mpi_datatype<T>());
}

template<typename T>
void
all_to_all(const communicator& comm, const std::vector<T>& in_values, int n,
           std::vector<T>& out_values)
{
  BOOST_ASSERT((int)in_values.size() == comm.size() * n);
  out_values.resize(comm.size() * n);
  ::boost::mpi::all_to_all(comm, &in_values[0], n, &out_values[0]);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_TO_ALL_HPP

/* all_to_all.hpp
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
*/