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
                         out_values, detail::c_data(sizes), detail::c_data(displs),
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
  ::boost::mpi::gatherv(comm, detail::c_data(in_values), in_values.size(), out_values, sizes, displs, root);
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
  detail::gatherv_impl(comm, detail::c_data(in_values), in_values.size(), root, is_mpi_datatype<T>());
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
  ::boost::mpi::gatherv(comm, detail::c_data(in_values), in_values.size(), out_values, sizes, root);
}

} } // end namespace boost::mpi

#endif // BOOST_MPI_GATHERV_HPP

/* gatherv.hpp
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
*/