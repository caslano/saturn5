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
k/xxpas/8I3JQtFo1mXxcH1SZAhcAr83GmJ+o8ind+ZLOL9PuMmR3moMQy9z16qGhIKO1fv5Z/rmqr8sNYlZLqvMAUxVuUIzA0gMRsar+L9YfJ3V+PObZdGmIT3LrPZmFKCK75OQZWW1KPzptVihwUqa3LOMnQA3pZFF166OwHKzBH/tEqsyK3sLWwtbrG/MxAsG/qPXhseS1VwdTJwELrs+yHt4ZqXWILkGbvH2Qko1+Sj0O/vzM84l1pAA3e4g0b9GXHc9qHQKL+t+vFn0/fXKiLcKq+q92kBDLcvGc8+kkGcDsg6iyyEpz5aHG6p15roD2bqXZB0EK+5y5ZP5a0HHr+xApgsLYXIfHOoweRMgdJvCrckSou7Ti2Xx4NelnpwOWfyPf/tE9eu9Wn9K9QdPhe3CskyqYIZs/KAe11uauu758FXhXU5+tW4Bs7W4f7BrJW6l+IrtQ3kviBG5+NIAXZNVp5c0l9drCltYnRGJ7nC1J2otdo3W4Mztb3PTLnEucz4uLe6fiSrGL7TfaLHe9BvQ6Eh+8wLSL9efLXUkayDfH9gZWs0KIsEqMpzAg438aJ35uZReEsYgdlMYDwarpwikueVoYrquG3GI+R754f+db7sKaoPLAgBcSoEFChQrFAvuzo+7u7u7uwQLEChWXIoUC+7w41AcWpziFHd394RkZVYedmdn7su59+E+nvmO4N2fcbJYnS7T
*/