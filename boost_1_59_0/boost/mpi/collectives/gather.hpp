// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gather
#ifndef BOOST_MPI_GATHER_HPP
#define BOOST_MPI_GATHER_HPP

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
// We're gathering at the root for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, 
            T* out_values, int root, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Gather,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, root, comm));
}

// We're gathering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Gather to do all of the work.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, int root, 
            mpl::true_ is_mpi_type)
{
  assert(comm.rank() != root);
  gather_impl(comm, in_values, n, (T*)0, root, is_mpi_type);
}

// We're gathering at the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, T* out_values, 
            int const* nslot, int const* nskip, int root, mpl::false_)
{
  int nproc = comm.size();
  // first, gather all size, these size can be different for
  // each process
  packed_oarchive oa(comm);
  for (int i = 0; i < n; ++i) {
    oa << in_values[i];
  }
  bool is_root = comm.rank() == root;
  std::vector<int> oasizes(is_root ? nproc : 0);
  int oasize = oa.size();
  BOOST_MPI_CHECK_RESULT(MPI_Gather,
                         (&oasize, 1, MPI_INT,
                          c_data(oasizes), 1, MPI_INT, 
                          root, MPI_Comm(comm)));
  // Gather the archives, which can be of different sizes, so
  // we need to use gatherv.
  // Everything is contiguous (in the transmitted archive), so 
  // the offsets can be deduced from the collected sizes.
  std::vector<int> offsets;
  if (is_root) sizes2offsets(oasizes, offsets);
  packed_iarchive::buffer_type recv_buffer(is_root ? std::accumulate(oasizes.begin(), oasizes.end(), 0) : 0);
  BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                         (const_cast<void*>(oa.address()), int(oa.size()), MPI_BYTE,
                          c_data(recv_buffer), c_data(oasizes), c_data(offsets), MPI_BYTE, 
                          root, MPI_Comm(comm)));
  if (is_root) {
    for (int src = 0; src < nproc; ++src) {
      // handle variadic case
      int nb = nslot ? nslot[src] : n;
      int skip = nskip ? nskip[src] : 0;
      std::advance(out_values, skip);
      if (src == root) {
        BOOST_ASSERT(nb == n);
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
}

// We're gathering at a non-root for a type that does not have an
// associated MPI datatype, so we'll need to serialize
// it.
template<typename T>
void
gather_impl(const communicator& comm, const T* in_values, int n, T* out_values,int root, 
            mpl::false_ is_mpi_type)
{
  gather_impl(comm, in_values, n, out_values, (int const*)0, (int const*)0, root, is_mpi_type);
}
} // end namespace detail

template<typename T>
void
gather(const communicator& comm, const T& in_value, T* out_values, int root)
{
  BOOST_ASSERT(out_values || (comm.rank() != root));
  detail::gather_impl(comm, &in_value, 1, out_values, root, is_mpi_datatype<T>());
}

template<typename T>
void gather(const communicator& comm, const T& in_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gather_impl(comm, &in_value, 1, (T*)0, root, is_mpi_datatype<T>());
}

template<typename T>
void
gather(const communicator& comm, const T& in_value, std::vector<T>& out_values,
       int root)
{
  using detail::c_data;
  if (comm.rank() == root) {
    out_values.resize(comm.size());
  }
  ::boost::mpi::gather(comm, in_value, c_data(out_values), root);
}

template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, T* out_values, 
       int root)
{
  detail::gather_impl(comm, in_values, n, out_values, root, 
                      is_mpi_datatype<T>());
}

template<typename T>
void
gather(const communicator& comm, const T* in_values, int n, 
       std::vector<T>& out_values, int root)
{
  if (comm.rank() == root) {
    out_values.resize(comm.size() * n);
  }
  ::boost::mpi::gather(comm, in_values, n, out_values.data(), root);
}

template<typename T>
void gather(const communicator& comm, const T* in_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gather_impl(comm, in_values, n, root, is_mpi_datatype<T>());
}


} } // end namespace boost::mpi

#endif // BOOST_MPI_GATHER_HPP

/* gather.hpp
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
*/