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
UpEmM728ljQs8uxaAH6qp+Ho4W3yVgwJP2UaDLcjITBQBPn/AtFf38GVpIGqTScv42NlPLz8OBv9C1EdB9tJ0hP8iVNCoH9922OuOgL1WBPqcoDKaIDNVT8uWFcUft4sXyvlP57DcmMQlI7Tg3VVUgn3NCu5ORqoDSAI2EFdFH7JhDRfIG1UkHZjH38o+dIvCDKofxeMk9FXsxuIyFn/Iv6L6+yPtOgXeHMVPIw1tUCp1t+rYDuB4FRGBHdjRgnVijW00J1m+K9rUVH4p+YQPGQZAjc3kRjeSAPIwNB/E6efq7A2eHF4xMnf8SKNfW3f8G8EoMLAOLWKOhZugWKCzLsTWaem+uzCOOaqz7kLg+IFiP+vSOZ/n8n/ran832byvzxC79L8Pz+Z/5cp/v+ScOp5yHv02H1lI9euCsExSTW45GHLt/DezZr3BNY4htX0M4RfZw4NoEWMXL/FD97tKxXn+YjzfIrzFmvOE2jvns/QGuAnP42Izj4cRcaGJ0h1RJA2Vp3tyHRfMfv9dUu/lzP0xDGNcSwo0KSzsNgvHUuYIqGF7VoV290tIFUtY/uZmu0EnfnjFdu1mmz33fDnhe3M9e23c9nfof1TIVh21GJFC5+26tFopTUuhPx0vamUNyBdlyv79zzhp5fdkOAiL+/8OiIF1I1NKSCrvYAPeDwEZSQqrWkSiVvyM1dgXTcZA3cDQNGWx1LxAHptc8KojkfaJQbuzRHivy0KLzHNgHmC1kPnMjO1sJrNMgy/sACLlzcDUIHVbyQVJkxIw7tDANKS/Tda/wKsBSLzxt0m80p7o1R7ED/JYPG8A36RrcZmUu+k7+tYXpL3eaUJLSzQfn8OM+t4tZ6H75cytui3O2eoVbwFjZjpmA0ogyEhXasYRkSmZb5AFvfa3uFHBCAp+AfPUEbG/s8Ht3bAvwMuEXvVEofDfpHRFjs5zoT82tnCnfe4Safn0EAtQoleMCTirewbcREXBs7RXDgCLdWxkMFhhMaqWyiPNVfm6xOhCCnTt8/RTP1Xl8m92Xj4jLm3yugxTLNuuWZdwfmdGmal78DP5OGG+CIARjDGj9YsS3sQMzSHgFvpFDKEA9pwmalZVtq5hdtJVAD3YL+orSDtVJmn8nYeK814EkMazZxmEphnHU+N6NGANpgKvyxWXNesuC58QRK/xb+o+M34vPCb6V9/EXRro3st2oXjoyl72Tza7/EqzJvUVi/TEHijjl39W90etkDdZIeQyW+xSeUciWzQzxmqFlqCHxf7cxLRCdqGqf48HxAVn0GIfAYB2vYKLXnb5fK5opMjLqXlG39dkCKB2cYaIyJo9/nCqZg8INEbK4Oq2GOWeSLwMzy/YsbHVlwg/rxa8R3jitSGnnV//Xh37Uls4sjB0VYegifF4J58WZIZKeRL4JelLPxp/yXAwrj+ltlQiOOQwtAujUIkC7lWVofZ7TtBpLKR9zFsaJ+mzO7wN3neTK0W39swNAMXFUbO4BLXSokiLnE4yWf6NwbM0ftL4tLCEA2nM1SteLzkdq8yONvqyqmbnNxIyX5c4eHQ1ARfbR5xtA9hzEv0BYlTP95b2x3ZfoK3LpsyvZj5dafTU63Exc/ppkpQSkn6S9JWMzyHimOaC2DZBZbwJDYdBvLo+XvwS4qffLdlNP0AUsiafvFjsuK4N5DxmJViMPB0k0Qb8Z8fVlWP2Y8qFIOS/pxH9QOPnkCwedSPwdrjgXbUHyLPmYlCynThnksr7ei6okw+D+bfTdv0IEiyJc5BZxLHe8B3g3kgLw4P61j8v7RpfZvxO1juIQz+Wgfx1jcyVLxFC4GTz54pnFzNTGcGmW2YRrVxcp5OK6lHHWc=
*/