//          Copyright Alain Miniussi 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Authors: Alain Miniussi

#ifndef BOOST_MPI_OFFSETS_HPP
#define BOOST_MPI_OFFSETS_HPP

#include <vector>
#include <boost/mpi/config.hpp>
#include <boost/mpi/communicator.hpp>

namespace boost { namespace mpi {
namespace detail {

// Convert a sequence of sizes [S0..Sn] to a sequence displacement 
// [O0..On] where O[0] = 0 and O[k+1] = O[k]+S[k].
void BOOST_MPI_DECL sizes2offsets(int const* sizes, int* offsets, int n);

// Same as size2offset(sizes.data(), offsets.data(), sizes.size())
void BOOST_MPI_DECL sizes2offsets(std::vector<int> const& sizes, std::vector<int>& offsets);

// Given a sequence of sizes (typically the number of records dispatched
// to each process in a scater) and a sequence of displacements (typically the
// slot index at with those record starts), convert the later to a number 
// of skipped slots.
void offsets2skipped(int const* sizes, int const* offsets, int* skipped, int n);

// Reconstruct offsets from sizes assuming no padding.
// Only takes place if on the root process and if 
// displs are not already provided.
// If memory was allocated, returns a pointer to it
// otherwise null.
int* make_offsets(communicator const& comm, int const* sizes, int const* displs, int root = -1);

// Reconstruct skip slots from sizes and offsets.
// Only takes place if on the root process and if 
// displs are provided.
// If memory was allocated, returns a pointer to it
// otherwise null.
int* make_skipped_slots(communicator const& comm, int const* sizes, int const* displs, int root = -1);

}
}}// end namespace boost::mpi

#endif // BOOST_MPI_OFFSETS_HPP

/* offsets.hpp
VimbT7NP3+BieQmTySuYwdbZ5xGkMW4LsdIBnIV6B33FkP35qs9eImy1MVDJDYJ1ENZF1RbZO2LwBEPwAZj4XBiNNg58is7ZE0pZGZt9acpAWFljNx4BxQqShBKSwqOMmCjtA7wopTYE2HJ6SQW8rwBRuLqWVnUtzzk//nidL2bZ+TH1yq7nCy5jxLqJPDp+h3TQqHx89uZvCOKz70XmwJgm+YpelztQMkqQZURPoyO0ayJBAnxHtHAUKhePmNh0uWm7j+h10+oLG2m0gnttFYlcQssKCAWmGRmxkhGKtTdQSEvqW0UitaUpu+0yV+phfPL658l/nuy2a7t6HK8eh9Dq9N9GnzMho11HjyvQe+cLp0jftxR+4orGu+gKZ1J2k0/nNIazu9qtw4hl7/McSNJ3+EPWjcFTEpOiy8sRax/dsIYRa9/U3vnj5svNbDEivAOG4L/1FPzwLX4BUEsDBAoAAAAIAC1nSlL/1bIfqAEAAD0DAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTQ5VVQFAAG2SCRgpVNNT+MwEL1byn8YdcUNsMrHAeSNFkERPTU0AYRUIXljh1g4dmS7LRHsf99x0lLtAQm0J8943pt5niezIH0ouZcpYcpUFo8X2a2t
*/