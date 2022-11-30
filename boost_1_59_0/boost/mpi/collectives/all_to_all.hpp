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
                           (detail::c_data(outgoing), detail::c_data(send_sizes),
                            detail::c_data(send_disps), MPI_PACKED,
                            detail::c_data(incoming), detail::c_data(recv_sizes),
                            detail::c_data(recv_disps), MPI_PACKED,
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
  ::boost::mpi::all_to_all(comm, detail::c_data(in_values), detail::c_data(out_values));
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
  ::boost::mpi::all_to_all(comm, detail::c_data(in_values), n, detail::c_data(out_values));
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_ALL_TO_ALL_HPP

/* all_to_all.hpp
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
*/