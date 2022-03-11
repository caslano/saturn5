// Copyright (C) 2011 Júlio Hoffimann.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.5. Gatherv
#ifndef BOOST_MPI_GATHERV_HPP
#define BOOST_MPI_GATHERV_HPP

#include <vector>

#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/detail/point_to_point.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/detail/offsets.hpp>
#include <boost/assert.hpp>
#include <boost/scoped_array.hpp>

namespace boost { namespace mpi {

namespace detail {
  // We're gathering at the root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gatherv to do all of the work.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, 
               T* out_values, const int* sizes, const int* displs, int root, mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                           (const_cast<T*>(in_values), in_size, type,
                            out_values, const_cast<int*>(sizes), const_cast<int*>(displs),
                            type, root, comm));
  }

  // We're gathering from a non-root for a type that has an associated MPI
  // datatype, so we'll use MPI_Gatherv to do all of the work.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, int root, 
              mpl::true_)
  {
    MPI_Datatype type = get_mpi_datatype<T>(*in_values);
    BOOST_MPI_CHECK_RESULT(MPI_Gatherv,
                           (const_cast<T*>(in_values), in_size, type,
                            0, 0, 0, type, root, comm));
  }

  // We're gathering at the root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it. Unfortunately, this means that we cannot use MPI_Gatherv, so
  // we'll just have all of the non-root nodes send individual
  // messages to the root.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, 
               T* out_values, const int* sizes, const int* displs, int root, mpl::false_)
  {
    // convert displacement to offsets to skip
    scoped_array<int> skipped(make_skipped_slots(comm, sizes, displs, root));
    gather_impl(comm, in_values, in_size, out_values, sizes, skipped.get(), root, mpl::false_());
  }

  // We're gathering at a non-root for a type that does not have an
  // associated MPI datatype, so we'll need to serialize
  // it.
  template<typename T>
  void
  gatherv_impl(const communicator& comm, const T* in_values, int in_size, int root, 
              mpl::false_)
  {
    gather_impl(comm, in_values, in_size, (T*)0,(int const*)0,(int const*)0, root,
                mpl::false_());
  }
} // end namespace detail

template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root)
{
  if (comm.rank() == root)
    detail::gatherv_impl(comm, in_values, in_size,
                         out_values, &sizes[0], &displs[0],
                         root, is_mpi_datatype<T>());
  else
    detail::gatherv_impl(comm, in_values, in_size, root, is_mpi_datatype<T>());
}

template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, const std::vector<int>& displs,
        int root)
{
  ::boost::mpi::gatherv(comm, &in_values[0], in_values.size(), out_values, sizes, displs, root);
}

template<typename T>
void gatherv(const communicator& comm, const T* in_values, int in_size, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gatherv_impl(comm, in_values, in_size, root, is_mpi_datatype<T>());
}

template<typename T>
void gatherv(const communicator& comm, const std::vector<T>& in_values, int root)
{
  BOOST_ASSERT(comm.rank() != root);
  detail::gatherv_impl(comm, &in_values[0], in_values.size(), root, is_mpi_datatype<T>());
}

///////////////////////
// common use versions
///////////////////////
template<typename T>
void
gatherv(const communicator& comm, const T* in_values, int in_size,
        T* out_values, const std::vector<int>& sizes, int root)
{
  int nprocs = comm.size();

  std::vector<int> displs( nprocs );
  for (int rank = 0, aux = 0; rank < nprocs; ++rank) {
    displs[rank] = aux;
    aux += sizes[rank];
  }
  ::boost::mpi::gatherv(comm, in_values, in_size, out_values, sizes, displs, root);
}

template<typename T>
void
gatherv(const communicator& comm, const std::vector<T>& in_values,
        T* out_values, const std::vector<int>& sizes, int root)
{
  ::boost::mpi::gatherv(comm, &in_values[0], in_values.size(), out_values, sizes, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_GATHERV_HPP

/* gatherv.hpp
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
*/