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
TSbTUS6ML9lVAlbzCltf8C5cCV/NAaMtACxTVcXrPPH2vWHINkauWs2rEMex3qyPXIz8McQbiB7TX4sZBFMzSqO7h3R5P59FaXo3f1gsw7o6ppYaVQiJI/fh/BOitujrI3wfwac4ppWf3n+2yaPaqAytPd4qOD2FP22ZGKGPH8INBtZxN+gFNDhtULVxveHw5eov/LiGq4vL8+lkPB4P+6HVnRyvcj/iZvhPaESxg5w7DrxwaMCVCOF5KLmFNWINPVsq1yNs27C+xJbLVyOC0VxYvpbBe3fm9weQdn/xP1BLAwQKAAAACAAtZ0pSKpjP/RQBAADDAQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0NDdVVAUAAbZIJGBNUU1vgzAMvedXWFTVTlVOuyALbZo6FakqqLDdUzAFLSQoSVn59wsfHT3Fz35+fnbQkXWFsBQxbFSl/fNDw682pY3YIc9T6Iy+D+zzPT5+nfcM+VpGPnds2AYyMj2ZnW1KYmiok8NYX4KJ8SEbUm5hFBPwFDv1RUxp5dP8AbEi4W6G/JTauY7NJpCvaUAlWu86Nbr3ktBISVchZ7sw1sBz+EwCLHTbClVGbLebGcGoG3IuwssbvwewwO0hyfI4Dben5Bhn+f6U
*/