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