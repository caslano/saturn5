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
DqbeLsu3RlXrpS31N9IDHjIDi6SwxLcXhQd9QEdvNS+2aeNHm7HVQ0NrUv9pT33aa62tZt4S1wVZsRWUBQJPi7v72ZXNO56YIvZpXd6EkIcIr8aYAcA6ahTzTTtvbNsw8WKvUqkcicvbFwAL/Iwrn8m7tjMyRyMCVKTfoiMZwFxFvbg04C5Y3oq5IIU5pZkNXW6l+FEs6UOp5Z6LtzimVHtYopEzfUWXGYuNjrau9fwHXV8ZREbRzubj/VSEB9w9yWaI4AuCL6vKY+yJiT4sQ970hnddljSaG5H6xDIPodoPusn8L0cyxZEHpvQ2wtt4Xnj/L25Cz2aaCF92Ba3Y84rWQ+xUQOIkdcFrzsoB4nAf/mfyjypeRdPJov9Qa7Rk7IgCQ1pLxd1b/MS/WXT4KnIfW96nHf7M2UejpXk5eekv4/e5xApfosuO2t3Z1JTRY8/FXeA/5OsmWST4IFHqC885CVaNbQrRFDjMTJAKuM2O0pIDz6LzYC7FKOHNDD70GvBmKaWQ5kSeh4bHmehx9v1wfLXNwIh3GTEPc8LxltLbpZeutW08wKGtDA==
*/