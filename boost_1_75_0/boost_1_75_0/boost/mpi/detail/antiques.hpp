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
ad1neUHe4eINNS+2an3szi3KPnfVCjEcv3dyZyUoM3vu2a0dX3amvB4njjzqIlI0+O7rfU8V8gl8bhExk+P48Nvzre6hRH7NVGHpdv/9C5jTvAhCKrld3WEkAwxUuYRaGVySdiayGNthDOx0wUaKwmEZRK3+GI+4WIX+D2BnKzaOT5TtHu8XEpsdiXkqxb9ayqG4AXgVJm6r97oNebMnGkBceuB2XktDnjbfvEBdibF6rGbaHmTKW2TSMb2GvRwRcM1gUCg6szx1WDXcUCeCa/FNX1mzoXC15s9akkCpR7pPLTgXatzk0tQ5XVmTpfgQnIfRt5t29M0xs/iyDEI9sqPqaCbb2GHn0MrpcmRqb9J02bHQOlX8MDjGmkpt4Vx6RS+YZeCfhMsUV9cbmliCJ3a1bQBOoVDgBqwjxujnheQcZ0ZNs1voL36eOn4uEzUWj7pj1T6/+fbROG+rGq2P9k2O1SD+uVd6fzehhTM+mc3XviC2rmqk5dBd/7tlUPniK8AzRJf9bal7HkTv5y3GgWBn3hnLEwIQlT/ycOfCzjHukhrPCeBQO++vlxu8k9AFPLDjvxwutXPhCuYn1/wIkGKbnSTlhhmpa8bAx82+7FtZcM3lZ4uRXBi4HhvFukGtZs0yxt2it7y4R5Njc0IqCg9dwezm7K4xJ0CSLOJic5msKaLn+/4ksX/EUu/Oqa0nmcbjjE9DMhmzW89M
*/