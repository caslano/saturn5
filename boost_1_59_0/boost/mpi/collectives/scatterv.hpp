// Copyright (C) 2011 Júlio Hoffimann.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.6. Scatterv
#ifndef BOOST_MPI_SCATTERV_HPP
#define BOOST_MPI_SCATTERV_HPP

#include <boost/scoped_array.hpp>
#include <boost/mpi/collectives/scatter.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/mpi/detail/antiques.hpp>

namespace boost { namespace mpi {

namespace detail {

//////////////////////////////////////////////
/// Implementation for MPI primitive types ///
//////////////////////////////////////////////

// We're scattering from the root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              const int* sizes, const int* displs, int root, mpl::true_)
{
  assert(!sizes || out_size == sizes[comm.rank()]);
  assert(bool(sizes) == bool(in_values));
  
  scoped_array<int> new_offsets_mem(make_offsets(comm, sizes, displs, root));
  if (new_offsets_mem) displs = new_offsets_mem.get();
  MPI_Datatype type = get_mpi_datatype<T>(*in_values);
  BOOST_MPI_CHECK_RESULT(MPI_Scatterv,
                         (const_cast<T*>(in_values), const_cast<int*>(sizes),
                          const_cast<int*>(displs), type,
                          out_values, out_size, type, root, comm));
}

// We're scattering from a non-root for a type that has an associated MPI
// datatype, so we'll use MPI_Scatterv to do all of the work.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int out_size, int root, 
              mpl::true_ is_mpi_type)
{
  scatterv_impl(comm, (T const*)0, out_values, out_size, 
                (const int*)0, (const int*)0, root, is_mpi_type);
}

//////////////////////////////////////////////////
/// Implementation for non MPI primitive types ///
//////////////////////////////////////////////////

// We're scattering from the root for a type that does not have an
// associated MPI datatype, so we'll need to serialize it.
template<typename T>
void
scatterv_impl(const communicator& comm, const T* in_values, T* out_values, int out_size,
              int const* sizes, int const* displs, int root, mpl::false_)
{
  packed_oarchive::buffer_type sendbuf;
  bool is_root = comm.rank() == root;
  int nproc = comm.size();
  std::vector<int> archsizes;
  if (is_root) {
    assert(out_size == sizes[comm.rank()]);
    archsizes.resize(nproc);
    std::vector<int> skipped;
    if (displs) {
      skipped.resize(nproc);
      offsets2skipped(sizes, displs, c_data(skipped), nproc);
      displs = c_data(skipped);
    }
    fill_scatter_sendbuf(comm, in_values, sizes, (int const*)0, sendbuf, archsizes);
  }
  dispatch_scatter_sendbuf(comm, sendbuf, archsizes, (T const*)0, out_values, out_size, root);
}

// We're scattering to a non-root for a type that does not have an
// associated MPI datatype. input data not needed.
// it.
template<typename T>
void
scatterv_impl(const communicator& comm, T* out_values, int n, int root, 
              mpl::false_ isnt_mpi_type)
{
  assert(root != comm.rank());
  scatterv_impl(comm, (T const*)0, out_values, n, (int const*)0, (int const*)0, root, isnt_mpi_type);
}

} // end namespace detail

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, out_size, c_data(sizes), c_data(displs), 
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values, 
         const std::vector<int>& sizes, const std::vector<int>& displs,
         T* out_values, int out_size, int root)
{
  using detail::c_data;
  ::boost::mpi::scatterv(comm, c_data(in_values), sizes, displs,
                         out_values, out_size, root);
}

template<typename T>
void scatterv(const communicator& comm, T* out_values, int out_size, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::scatterv_impl(comm, out_values, out_size, root, is_mpi_datatype<T>());
}

///////////////////////
// common use versions
///////////////////////
template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  using detail::c_data;
  detail::scatterv_impl(comm, in_values, out_values, sizes[comm.rank()], 
                        c_data(sizes), (int const*)0,
                        root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         const std::vector<int>& sizes, T* out_values, int root)
{
  ::boost::mpi::scatterv(comm, detail::c_data(in_values), sizes, out_values, root);
}

template<typename T>
void
scatterv(const communicator& comm, const T* in_values,
         T* out_values, int n, int root)
{
  detail::scatterv_impl(comm, in_values, out_values, n, (int const*)0, (int const*)0,
                root, is_mpi_datatype<T>());
}

template<typename T>
void
scatterv(const communicator& comm, const std::vector<T>& in_values,
         T* out_values, int out_size, int root)
{
  ::boost::mpi::scatterv(comm, detail::c_data(in_values), out_values, out_size, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_SCATTERV_HPP

/* scatterv.hpp
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
*/