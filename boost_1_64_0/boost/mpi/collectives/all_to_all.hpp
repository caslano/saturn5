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
9uio4WKPOu9/gX5M5SL5LpfNnxM2/Tl1wHban8O5pxtPeBCh2/kSQeuG2GigvewG3xAS0dzbuNEjR5zm8ooPZb2HvHeXhH/deIX/+cEO8B/liP8p2Yj/KxUd4j/Ign+3bMF/7dhPjz/NpxfHKfzfxQNKctiFF/Cn0yhCLYjXP/XBlnMJXU4ezEeStL483qovl7tl/RzEQbdrQAKRERdey8rhrpGi2Z+QWE5OzRfHpjj6+gA8WZ7bAH6s6hNuY6baB0+fpOjh+ueB1Gbl1iUJxutys9r/gfBlJvbsa10/FwZI/px0tAT+deX+noNjLfDqChzgPTChi/D4/PNY1f9e/VMC7aZAZ3lU85cibygNKlD/dlH+0gdxEN2AEzX66ijr3jtE1S2goY5cGZkHg/z+MWIB4IljDnONeOk+y7EnqF2PZgoApwNJvwoQMBSsdLaBLrTM44KNFGm9nzgMKPBMJi1kGrPf01e4tUddLbQhILNtSV1rD9BDFw1SX6L9MZDL6MUTMWPBeODq9uJ4c0F2MDGKF4hTTal2eh6hBDEmLtP7fg0f3YQzsHe7hLWRKtTlthEWr/HlK9YA1CfgD///Jvw9z98P6Q6AT/PR8x9WRjL1/XRovTWRT5zkG2ARSjh+ZTx+iyLXQmdGS2cw4k7uCj47V9/q3FLf1IvPDmcsOBvGEC5YWNwvG31DTcvliOZPuwuDJWZSmx/2MBNOJoKuy5IEdev+JX3NhMLIBZrChNT9w0VyjKSVv4cSotWwdXSABitEZnKA1IRjRxMoGY8/9c0O/gX+jgYsT4C/dvge7PfZjYc5fyeX0nxD3u2VQyjxUcc3XcSa/CVKzsx3e/FjIhkLosDt7cUNe/tnB6EEMe9ZiQv5mvKmOyx+JkxI3KbC36cEYGsjMU+Z12WUd5GU9GFetZQMYd40KRnAX2O5JIaO5nJ0H6YWhTeZvL4avy1hMZ43TNid75idBqjOhL858Pco/F0Ffzf3P3z0Nen5HgR6sbc+y7oeR7NwpXBL+F6XzssH6fz/8WxPCdf+MDNlmXyoo2XyZ7nmMllrWSbbcpNCZF21Z5GU7WH8EGaldc05lTwgPrZ/fxEQXaBXuPdMF4cgfYMTeVlspmW2hVXipmsP8dWH7Z3HI8ePS6bHpVmHRo9SZ3rMTkePS3M7oMeNuZoe156g6DElN4Ueq0s/C3qw/3e04rc/stmQFHjVnVfLaOc+UlOfHCXw/ulL0SenWN18YyjG7aPjU5TH/kpx/PkU7X9ojXXvqqZiv//iWIVPRs8UNayWFo6jVIhlDcdymaoZo1ll6sBfyE7ek+2n92SLZE+W6sACWkC6IW+73sMS5fuDPsG2q4P/FxQTYx0sPSIYBkBw88/6CKli7ggfaQlTb/zCLenvvx+F9OGLxuKowDS34GITJMXlVJ+MTtjvURFwTxUrzShAozkwPE36ykHN86GvPz1alrJ5ceBzgH0TaVV9ad1lT+5zPMcr4ckj+gLvpxBJwSktOTtGSE5tD+wUjeP28g94MST+OeVvSssNNJ336V48SkOfOSOt8kKT6fW/azIVehXC5x88wF9a2umLPs80zCTSKiRSFIj0VBEHvpxprB2KdlTN1CTDv6CRA7rZv/X7YXK9Qr/wSJO5FhCgixkQ36DQjUY/OOyTOMEd419K1Px5LT9l/sxScyNovA2lIBibZ2xiEm+MRnNJqYUrB4qgyJ+BYOCZUUX6sobrFy+mH+5lPqVrVwvZ7v85xtQ/VrktGPaO+uHfPtG8xFBWA+q3BBITVYzwzcqPWiIaAioCl7iTFIHFav9r4Ceatjr+W+P3D1da/aiS9KPerB/5FpzD+tH2Yq0fjU9MNZU=
*/