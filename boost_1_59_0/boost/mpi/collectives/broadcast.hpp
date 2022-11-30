// Copyright (C) 2005, 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 4.4. Broadcast
#ifndef BOOST_MPI_BROADCAST_HPP
#define BOOST_MPI_BROADCAST_HPP

#include <boost/mpi/collectives_fwd.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/communicator.hpp>

namespace boost { namespace mpi {

/************************************************************************
 * Specializations                                                      *
 ************************************************************************/

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<const packed_oarchive>(const communicator& comm,
                                 const packed_oarchive& oa,
                                 int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<packed_oarchive>(const communicator& comm, packed_oarchive& oa,
                           int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<packed_iarchive>(const communicator& comm, packed_iarchive& ia,
                           int root);

/**
 * INTERNAL ONLY
 */
template<>
BOOST_MPI_DECL void
broadcast<const packed_skeleton_oarchive>(const communicator& comm,
                                          const packed_skeleton_oarchive& oa,
                                          int root);

/**
 * INTERNAL ONLY
 */
template<>
void
broadcast<packed_skeleton_oarchive>(const communicator& comm,
                                    packed_skeleton_oarchive& oa, int root);

/**
 * INTERNAL ONLY
 */
template<>
void
broadcast<packed_skeleton_iarchive>(const communicator& comm,
                                    packed_skeleton_iarchive& ia, int root);

/**
 * INTERNAL ONLY
 */
template<>
void broadcast<content>(const communicator& comm, content& c, int root);

/**
 * INTERNAL ONLY
 */
template<>
void broadcast<const content>(const communicator& comm, const content& c,
                              int root);

/************************************************************************
 * broadcast() implementation                                           *
 ************************************************************************/
namespace detail {
  // We're sending a type that has an associated MPI datatype, so
  // we'll use MPI_Bcast to do all of the work.
  template<typename T>
  void 
  broadcast_impl(const communicator& comm, T* values, int n, int root, 
                 mpl::true_)
  {
    BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                           (values, n,
                            boost::mpi::get_mpi_datatype<T>(*values),
                            root, MPI_Comm(comm)));
  }

  // We're sending a type that does not have an associated MPI
  // datatype, so we'll need to serialize it.
  template<typename T>
  void
  broadcast_impl(const communicator& comm, T* values, int n, int root, 
                 mpl::false_ non_mpi_datatype)
  {
    // Implementation proposed by Lorenz Hübschle-Schneider
    if (comm.rank() == root) {
      packed_oarchive oa(comm);
      for (int i = 0; i < n; ++i) {
        oa << values[i];
      }
      std::size_t asize = oa.size();
      broadcast(comm, asize, root);
      void const* aptr = oa.address();
      BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                             (const_cast<void*>(aptr), asize,
                              MPI_BYTE,
                              root, MPI_Comm(comm)));
    } else {
      packed_iarchive ia(comm);
      std::size_t asize;
      broadcast(comm, asize, root);
      ia.resize(asize);
      void* aptr = ia.address();
      BOOST_MPI_CHECK_RESULT(MPI_Bcast,
                             (aptr, asize,
                              MPI_BYTE,
                              root, MPI_Comm(comm)));
      for (int i = 0; i < n; ++i)
        ia >> values[i];
    }
  }
} // end namespace detail

template<typename T>
void broadcast(const communicator& comm, T& value, int root)
{
  detail::broadcast_impl(comm, &value, 1, root, is_mpi_datatype<T>());
}

template<typename T>
void broadcast(const communicator& comm, T* values, int n, int root)
{
  detail::broadcast_impl(comm, values, n, root, is_mpi_datatype<T>());
}

} } // end namespace boost::mpi

// If the user has already included skeleton_and_content.hpp, include
// the code to broadcast skeletons and content.
#ifdef BOOST_MPI_SKELETON_AND_CONTENT_HPP
#  include <boost/mpi/detail/broadcast_sc.hpp>
#endif

#endif // BOOST_MPI_BROADCAST_HPP

/* broadcast.hpp
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
*/