//          Copyright Alain Miniussi 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Authors: Alain Miniussi

#ifndef BOOST_MPI_ANTIQUES_HPP
#define BOOST_MPI_ANTIQUES_HPP

#include <vector>

// Support for some obsolette compilers

namespace boost { namespace mpi {
namespace detail {
  // Some old gnu compiler have no support for vector<>::data
  // Use this in the mean time, the cumbersome syntax should 
  // serve as an incentive to get rid of this when those compilers 
  // are dropped.
  template <typename T, typename A>
  T* c_data(std::vector<T,A>& v) { return v.empty() ? static_cast<T*>(0) : &(v[0]); }

  template <typename T, typename A>
  T const* c_data(std::vector<T,A> const& v) { return v.empty() ? static_cast<T const*>(0) : &(v[0]); }

  // Some old MPI implementation (OpenMPI 1.6 for example) have non 
  // conforming API w.r.t. constness.
  // We choose to fix this trhough this converter in order to 
  // explain/remember why we're doing this and remove it easilly 
  // when support for those MPI is dropped.
  // The fix is as specific (un templatized, for one) as possible 
  // in order to encourage it usage for the probleme at hand.
  // Problematic API include MPI_Send
  inline
  void *unconst(void const* addr) { return const_cast<void*>(addr); }

} } }

#endif

/* antiques.hpp
dbwEva25wWpL5V636khX1+vWqrB6tyPSqM36ajjBh1AAmO7YyvbTg+5F7niUMgeS7ux3Xc5pjp2QD/jhga58mmvj+Fy8ERJNWmQptRyQB+txyLgV/9ZVxGThOSwtaXy40FSuGXrFge8bvkFjIfszEqI5iAjWzYz5JpUmLkN4Mos9qZD85MF+jtwY2Zy670xYYeKE/8n/xGO6JQNhLIlgYsSjVfruS8mnegPx4SqV7q0TSjinls2NkuEB1dpPioA8ogjlYN2pgPwNJyElYNNkzqspJXyZBXW/lWeOXYjslz9sP4C/F9QSBERb3ECvzhUURgLFRgJOobfY6SSkWU8pAIWX/5L5CmyjfJnhG3GND4q6vLyJZWpjoc2cpvYnDTe8LEZSmpybn165BFKzYf6EB1Usf/t3XCkKSHCSeGv7zAiFTxRTikvpARnGjfa4wPagps4E1ZwPr27w22fakiSPy0EQcYRDKdrIo9k2ONnGCBlM844333cKSq6adhiqqxxY1Gei0L6fD97Np1wgD6w3p6jy9v3LhFgdr1Qhi328pd0qOgvaGIqsTmI0zw==
*/