// Copyright 2005 Douglas Gregor.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Message Passing Interface 1.1 -- Section 3. MPI Point-to-point
#ifndef BOOST_MPI_DETAIL_POINT_TO_POINT_HPP
#define BOOST_MPI_DETAIL_POINT_TO_POINT_HPP

// For (de-)serializing sends and receives
#include <boost/mpi/config.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>

namespace boost { namespace mpi {

class request;
class communicator;

namespace detail {

/** Sends a packed archive using MPI_Send. */
BOOST_MPI_DECL void
packed_archive_send(communicator const& comm, int dest, int tag,
                    const packed_oarchive& ar);

/** Sends a packed archive using MPI_Isend.
 *
 * This routine may split sends into multiple packets. The MPI_Request
 * for each packet will be placed into the out_requests array, up to
 * num_out_requests packets. The number of packets sent will be
 * returned from the function.
 */
BOOST_MPI_DECL request
packed_archive_isend(communicator const& comm, int dest, int tag,
                     const packed_oarchive& ar);

/**
 * \overload
 */
BOOST_MPI_DECL request
packed_archive_isend(communicator const& comm, int dest, int tag,
                     const packed_iarchive& ar);

/** Receives a packed archive using MPI_Recv. */
BOOST_MPI_DECL void
packed_archive_recv(communicator const& comm, int source, int tag, packed_iarchive& ar,
                    MPI_Status& status);

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_POINT_TO_POINT_HPP

/* point_to_point.hpp
TMMhmI6P4nB8HEfgIszA5ZiJ29CCOzAb30Y7lufLbRRG4DjshOPxQXwMzfg4jsU8nIATcClOxJU4BQtxKr6K0/E4zsAPcCZ+j7PQvzLtYayLszEE52AEzsP7cCH2w8U4EPNxIi7D6bgc1+IK3IpP4QFciYdxFZ7BNfg5FmBFzgmfwQZYiE3wWYzEDdgbN2ICbsIUfA4fwy04Ef+Ei3AbLsPtuA134qv4Mh7HV/Ar3IXf4W68
*/