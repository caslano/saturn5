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
CeoT6qmpcmJobOv+jF4Lwl/rCqW94tnQEMEMqpAVtiX2fwdcigaH9ZCrTtZK5KCFPCB0lS3pDRYPqEERu6hVRwL3ogCeqaYRMh8sV647+fhM0k20mpBX9BmnrhcES5hq8B8XSz9YLLzgKfCW3syf+/MpZbjpqbympPQ71FXRQy6sAFFY2m1LHA4HpTCwR5QwMqWyI8ZPA5cMWq2sylQdsm2yjkFIJftGHY1zvmkCFPAZf0XT1vhAW2n6/eawdZTsHPa13aQORbhbcPfm697/8w9QSwMECgAAAAgALWdKUjOIR4u4AQAA8gIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDVVVAUAAbZIJGCNUlFr2zAQfhf4P9w6+ubUdbowVoRZ2TJaKKsXuxuFUNCs8yIqS0ZSkoV1/31nOUv6MhgG3el09313n48H9KERHgvGlWktmSfcba2TvmCf6pJ9vq1qVt4tasaz4wvPxuTXUKHboJt4JZFxh73e0auPwaaTBVvMy9sHGFBgNjuHa7FBEBCEDwjWQFgp/4rgXlRwKYIYKP7aPSqRfdAKTdiTNfFyYCtYG/oDUsGAG9FhHGKkl8qBVj7AVoUVbFE5CREaGisxhbVX5gfEUYFnYzHwxnadMDKi
*/