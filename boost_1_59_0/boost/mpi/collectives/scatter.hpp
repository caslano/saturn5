// Copyright (C) 2005, 2006 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatter
#ifndef BOOST_MPI_SCATTER_HPP
#define BOOST_MPI_SCATTER_HPP

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
// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (const_cast<T*>(in_values), n, type,
                          out_values, n, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatter to do all of the work.
template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::true_)
{
  MPI_Datatype type = get_mpi_datatype<T>(*out_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (0, n, type,
                          out_values, n, type,
                          root, comm));
}

// Fill the sendbuf while keeping trac of the slot's footprints
// Used in the first steps of both scatter and scatterv
// Nslots contains the number of slots being sent 
// to each process (identical values for scatter).
// skiped_slots, if present, is deduced from the 
// displacement array authorised be the MPI API, 
// for some yet to be determined reason.
template<typename T>
void
fill_scatter_sendbuf(const communicator& comm, T const* values, 
                     int const* nslots, int const* skipped_slots,
                     packed_oarchive::buffer_type& sendbuf, std::vector<int>& archsizes) {
  int nproc = comm.size();
  archsizes.resize(nproc);
  
  for (int dest = 0; dest < nproc; ++dest) {
    if (skipped_slots) { // wee need to keep this for backward compatibility
      for(int k= 0; k < skipped_slots[dest]; ++k) ++values;
    }
    packed_oarchive procarchive(comm);
    for (int i = 0; i < nslots[dest]; ++i) {
      procarchive << *values++;
    }
    int archsize = procarchive.size();
    sendbuf.resize(sendbuf.size() + archsize);
    archsizes[dest] = archsize;
    char const* aptr = static_cast<char const*>(procarchive.address());
    std::copy(aptr, aptr+archsize, sendbuf.end()-archsize);
  }
}

template<typename T, class A>
T*
non_const_data(std::vector<T,A> const& v) {
  using detail::c_data;
  return const_cast<T*>(c_data(v));
}

// Dispatch the sendbuf among proc.
// Used in the second steps of both scatter and scatterv
// in_value is only provide in the non variadic case.
template<typename T>
void
dispatch_scatter_sendbuf(const communicator& comm, 
                         packed_oarchive::buffer_type const& sendbuf, std::vector<int> const& archsizes,
                         T const* in_values,
                         T* out_values, int n, int root) {
  // Distribute the sizes
  int myarchsize;
  BOOST_MPI_CHECK_RESULT(MPI_Scatter,
                         (non_const_data(archsizes), 1, MPI_INT,
                          &myarchsize, 1, MPI_INT, root, comm));
  std::vector<int> offsets;
  if (root == comm.rank()) {
    sizes2offsets(archsizes, offsets);
  }
  // Get my proc archive
  packed_iarchive::buffer_type recvbuf;
  recvbuf.resize(myarchsize);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (non_const_data(sendbuf), non_const_data(archsizes), c_data(offsets), MPI_BYTE,
                          c_data(recvbuf), recvbuf.size(), MPI_BYTE,
                          root, MPI_Comm(comm)));
  // Unserialize
  if ( in_values != 0 && root == comm.rank()) {
    // Our own local values are already here: just copy them.
    std::copy(in_values + root * n, in_values + (root + 1) * n, out_values);
  } else {
    // Otherwise deserialize:
    packed_iarchive iarchv(comm, recvbuf);
    for (int i = 0; i < n; ++i) {
      iarchv >> out_values[i];
    }
  }
}

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatter_impl(const communicator& comm, const T* in_values, T* out_values, 
             int n, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  std::vector<int> archsizes;
  
  if (root == comm.rank()) {
    std::vector<int> nslots(comm.size(), n);
    fill_scatter_sendbuf(comm, in_values, c_data(nslots), (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, in_values, out_values, n, root);
}

template<typename T>
void
scatter_impl(const communicator& comm, T* out_values, int n, int root, 
             mpl::false_ is_mpi_type)
{ 
  scatter_impl(comm, (T const*)0, out_values, n, root, is_mpi_type);
}
} // end namespace detail

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T& out_value, int root)
{
  detail::scatter_impl(comm, in_values, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, T& out_value,
        int root)
{
  using detail::c_data;
  ::boost::mpi::scatter<T>(comm, c_data(in_values), out_value, root);
}

template<typename T>
void scatter(const communicator& comm, T& out_value, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, &out_value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const T* in_values, T* out_values, int n,
        int root)
{
  detail::scatter_impl(comm, in_values, out_values, n, root, is_mpi_datatype<T>());
}

template<typename T>
void
scatter(const communicator& comm, const std::vector<T>& in_values, 
        T* out_values, int n, int root)
{
  ::boost::mpi::scatter(comm, detail::c_data(in_values), out_values, n, root);
}

template<typename T>
void scatter(const communicator& comm, T* out_values, int n, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatter_impl(comm, out_values, n, root, is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTER_HPP

/* scatter.hpp
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
*/