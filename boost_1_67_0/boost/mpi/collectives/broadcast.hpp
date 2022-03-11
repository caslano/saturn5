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