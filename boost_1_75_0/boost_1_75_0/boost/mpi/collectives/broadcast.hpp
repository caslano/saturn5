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
b+p9fvLh6uMxru9DmzVel+ibH1EqZa5+iXGWNVCelAgxL8Ba1grjnvEAeVNYZcacHmfR5hiLXvMcAwg3pBnC3qjLqKzk3zjDNJv98pviPrrwUxSCfsv8E0ETIlYepshX1ZwteBXDVF1hrd1dj7UC0JcZd34H5cjP2LY1K5e0FpUgr3BriVJHmMsYKK2lxvAS5Mv/szhmM9YSnFTfccYls6eIz8VrzImQvs740jcDxyvYg3WHkzj3azQGIe6sbSWlhQUZWeqIMacScvCN2Zx/vs88mPl5bqq/S4yf2RkoHiWDZ2V8K4xrLw8Qn6vucqMUOb7aiHhNxRmb6Z/Coh2mjNIMs1lZv4g2lh5FXKa6it3KM4uKWzh7emteDZW9wlp9u8UdZg57JXO3xb5DLQ+gn8U+DTN82WbzlBasiVRFQI4MB+GCp17yaoTuwLpIVRja9y87eD5cL/FkNlRbSdzrLNl7qUhYJ8F5kGjjS9/n4224FlTUkM6uS5urjNe+9AXPOMxmx1yFD/Htnm5oRW732ax4MSjoVBRaBPv+qOqlGE7H33MJY3/9set1GLPbfxh7c67rVRizOu6DkfyZF1XcGnbmZsGHerOS/1DcYKA84Ds/Anr2lf3FtbX2nFprJca0aa6wHymUr1RwGs4azGYGLWdUvfA3EAxa/5+KKuq4QICGM6uRLH99oc1Sk1NXu0fpW0V/dssT+EZB8T0W
*/