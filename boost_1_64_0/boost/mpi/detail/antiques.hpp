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
SP+n+6OQvpsrEuk/e5zbbADsrkr/tqGhaif8BcMPFoAm5x6e770M7FqvDNlyCH0o7YV0V/HXIwvHi8dnW9qJMopDxTvcwTzw8r0tWLAHEoO528xZG2hChQxuqIqTWAGD1md0oLs+0Oz6ZdT1YarrE9zUxC4XIiA9UuP8M6R7BVI5Q2qEm97CFNgrtOhG6D0EcFgByMktDwDdhVrtVn/QIHQOqqXnoyuSFChC+8kIvSUQsLuwffSRZk99xkm/p00usSG6UzQHO7Fa8BgPo4hcTO5JKGwFqxfM3aOPlYKl4FLAuHCK3IjgZQx0TdgxP0Wdqdw91qsClwBjjm2cFtVGG9VGF8Rx9EWZZkErzd02mUO8gHbuQwQYvTKS4gNyZ3sY3y9rY+HeWxxHhzKNA/nqLhw4C57medo/3kRox74gER8FyukbIjK66pOj8PGiR/k0XIwv9juDeU/BIKHqUwz3m/XUP9KZmxY1xr6q5ghFq6omfo37uwKM/tbyY/CFUoP0UIofsKgvXE2JXOcbf7+Oy15sloXtZ0znsqRB5SU32I+hlPCxKfqhjd00fype7o1OdCxo6HVYP0SnuLHgTrVQUGlDznhvoIuIAJbxAzVMilo8UiGepM+TdmVJDtzP3ON8q/OVdG99SWUskAycKWMLp0pomc3b/hlPbP///Bt/1H1MH3u7JQY0WCdEONzo8mkv5PoaUUqXVdCpfLExGAswP4kcvF0+m07fo+PfbiV5n8P5DPqm3gTyZ+4DcqpcPvocD3IN5D5Yjui+L/RoLICrEmwAP8PMWC17oGBHUwnhLyId8oU2gojA8TAYG8gwb7wzE6U8vZ0CHKdTJysw3gqX4HNkmrzkl4ffgUNtaIRufnFG2B0BdqzueIHf05Df8wF5x8LGd99jON1mP7b7/QkK37h3SjSlG0TdfKDXxWx6qLPKCEvGLU/Hfh+y8KfsKcEfB0YyMNaKPOJzZjZhhgVx6tV0udmkJZjnCz3ouHR9W6PWYhIUDrWV5fFVLT2WeMUwnpjIHehLvXBmW6R5tG5ynCtn+daJG2Vyo+0/npT5BJQzt1SsvnkLT+K+5eTWF3YhXMx35RTUQ8cE8UB12tbLrVbxNpIK0FssAbHW/4mW9fc8swOBs2PtnaxAP7P7sfcXrX9va5ylXBRHb267oxmaOb5RZP/1OMoX9ooqrqWYa2y7Wjz+8uPGNXAbJPXCEZOEreNrI3sBHr7SUsgex0Udp2hs2ppnKQmy3eQdMJ1WKR1SnJEwAEVo4NWBubGgZqGyXzotTnqsMt4A+OeBvtK1ElVarm+/Nt1rWaNJR6oWE01Np2WsRjySjM4e6Xj0jkWCnrYGzYS5sxQ9Lp0Ap0OK8xIXns5dzcmrBuRGuONd2GKK2SIgd984ehy6y7G7eiJ11/FsSFtzEyZJWYTtXpvbIAlQqaDBCStbV6HXj9BIOI1BCLC4sNWu3IbU0IC0F/Iair+6gr4mhzKhNsgELqGv3lAqFw4UeuBrG47NBoO4Pq8B4+8U1NKy1VahxWjstUuuugdvj7e4ZUzF4T5pJZe4TTGKnHWJqINbCXwqlfkZih6qi1D0AK9okNau+OtsSuuHaa2V4jkp2rcBrpdmtpKe6yrw6lOAF0YOcuSwiKs/aA2t4jUtTBXDoXet8FBhPBGKvxpZOEdOCVvaORhPs6ACUkDDmoEHC0CScICusmG6yqKNKXUg7MhEcNPitRCa5oLBvH2QBhwIwd5JIzsRLlKAZXC//dy80FwON9y2xtT7+dJ2A6SboPiOXMGkvB2cgBJk5QDdTA5cn7d3LdxMdl6fu2+tmzSYu+ut3QJYJ8Df3MeAf6yEUYZrApENQOdEN4w=
*/