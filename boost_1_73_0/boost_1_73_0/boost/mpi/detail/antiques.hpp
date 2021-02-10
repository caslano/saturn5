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
fgBQSwMECgAAAAgALWdKUgdjMY8wAgAAqwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDU1VVQFAAG2SCRgZVNha9swEP0u8H84XAJbmKY4TbtFuIGSZU23tAmpVzYYA8U+xyaOZGSlrf/9JNtJBvtgizs/vbv37hwarEwsKpyQMJepsscO61elk2pC5lG0al5wN4tIqdVbTTLRniE740LWXiUX5AKeUL+gplWeIAk1lkUNUuzxxg9GV1e+BSfCCJAqzjDe3fg1Vn5biQUfAxgOBrD8Tr4IgxyiA36AwRge1Yv9EAwgGPHRmFvI3UNE2kIcnAJaNQFLxQ7JQtjEg0ryNMekYwku4dtBOnrLMuTB4Mgyi8SWgz8MBsMrmsSf6OV4dD0cjT/75DaOsTR0LeQWKw6b2lYiUyUNSkMXKLcm43DtMhJjkyvJIS5UhSdMVJfo+nszLDP7gnw9SFnTDIXtaiP0zj2E0FQpaj10vjgvG886M6dF7ohaM+MmsJBW7IRkxpT2wjEMnc+T08DgNUMJq/Xy5y9YaWVUrApAKTYFJvZWCw5jtd8LmbRknLHefPkU3a94z9GsluuIubkBpd3gaXmkonPwI+u9VBya2VrSE1uYojAHjXY7jvtyzlhcJ6UR
*/