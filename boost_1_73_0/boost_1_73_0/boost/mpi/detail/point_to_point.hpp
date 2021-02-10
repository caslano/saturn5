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
NPDDejEJR2NECp1YrnMSdJ36rOWe2TZaMPnEpK34hiHbhreS7dL94W0ukLshmnQRz5FOuEIGAlI8pwyVDCXkidVmIikykGBIaSK1ZYVGGH6q2O2EYhukBVozJJkuZA7bMmF5LV8BQDHTChEUcam0hQGzkPyZaC7yTm0g5TlDO6JAlw1gjvZoylmuK+xWhbXVbLZqOpzWRQtdNVtoIkoU8yxjcIIAfEZFvgEsXwvjjYgQlWTXsGouOmjMqRRKRNoOgoVzfdFsWD2RazBjh/sd6wAJ37ST6Cz9GdGESMX0DVfC/vTp+ie7dRIesTzWSQe1rxrWw8ODbdyC55wSzV68CtP5OFxOwnuMe9hcMdz7ZtEbxLGP6XULr5b9eD+h+HgNrvA6xnuznDXHcG6GZ6UHp3zsx94t9ku8mHkh9n08M/vbGV6Yl16MV6X3iHtXmMzgPrjHv2AvxcMVHsVegYeAosTKPF9jb4eHY7yaedzsN9gT5tyfnq+um5uG1TimQC50FSnJSAoRjBliHPbyDFLxFDDrPfpLOVPvTUBBw/cnzjFnLl/lzGWzacDkMaSkZJCUoAGOvphNCSSPKhVNAeQ/mDWXhsRbnpM03X+sq4+r3zL5isLLQ/7ThNHt/wXwLyiA/24+veQQ7A7j4D3q
*/