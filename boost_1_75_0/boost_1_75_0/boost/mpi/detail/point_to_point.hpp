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
pIb3gj7vmTHsu2P04D/r7a2LIDpv5m5klxC0E0+InwrPY+Cl49cRhPnfuQ1EvRmkxPmbptnf/B9uM/w3t7k4ebj+HktZejta//OS3c/R9dzI0YNsGBjS/eYvoW/Qr2YVtaS/lCuEmly9VX8DwhV5k2yARyCrNf1WeInc0g8Vkkf3l9k0NFvBlF3OBgJj36ofRVq2nWeNhhlnSlzpXiYw2/JUwGSvDnMl9/l0+5mMPHMjmaZMz6IoSHJrJ3k3De9h1f3lYvH15f4Ucv58CmBrfx12F3nAz97B1kJZz6kpRZF1/BHukxCBJyO2tbG3Z8MecBMGNWjHeQP5adv3U4Kwz9sMa/5NS59UAXYF2kekuDDU0rfN7wwwRN6xoun5v1x9OdyEmlNsIutv3KegeCkUc2ZduZLkO2GMdUQXcLW3GuibudRkHrfp+JZ8r1ltOCLNh26bxyphOzPXxhallf7BSB8AkOOImqExLhOwoXTJ2O7F/VjhL9J0fBuwJTqVDPQJrhLdaOetr3ZekGb3vN/Dd0E7/IEguCLef2q7BDEsfQykEXGHe1MgNLd8Q2Dn59bbOkfP4ZvornnR70kO+8FoV7VVTLDHdfS6PAC43/cL0KkVtrz+59Q1mLeZqpH3SmkrYXqyr2oyH4V/spIIJ0x8VZELDa5ZBOvJ3u3lfgo6Unuy8ndbWz6YNIW/ysLaN10QhtGGUbctiPEKC0QA
*/