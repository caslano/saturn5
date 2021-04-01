// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

//
// This file contains traits that describe 
//
#ifndef BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP
#define BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

namespace boost { namespace graph { namespace parallel {

template<typename T>
struct process_group_type
{
  typedef typename T::process_group_type type;
};

template<typename T>
inline typename process_group_type<T>::type
process_group(const T& x)
{ return x.process_group(); }

// Helper function that algorithms should use to get the process group
// out of a container.
template<typename Container>
inline typename process_group_type<Container>::type
process_group_adl(const Container& container)
{
  return process_group(container);
}


} } } // end namespace boost::graph::parallel 

#endif // BOOST_GRAPH_PARALLEL_CONTAINER_TRAITS_HPP

/* container_traits.hpp
mu0iA+OLR0CKoCgT29dHVZJc3IzEmN8un2dyBcSgCDGvgAF5Jp580VTYLjp+Etoc3UB2/aC0Rci8EgOpVAnKNmphORq4XCqVaVrMcY72bgqj7owqTNNTajgDFf2Uvz3P/uIbYmKfpGiL3pGNJJB9D3/6bQrrNEqa0SuvUFIsL4wTtpP4dIn4mfHx+SVDTrl8zVXBihoqgk8mG1EPj2yOlqSnEMbcsx4b9N2xZYnlFTwkFVJU8ATomJR16f6Nfe6o6qtHr/UwQuZGMcLZhbR0rF56dRA825T2+peNPKucV9P5X9jGNqoOO+HgusCVimOY0Lj2lZiiFj8FW/PZso2rISSmLfRatshhSc562HZs52iQeBi2KD+RzeIt178mMfiwLtK2TQnwntuo0DilB0QbnYqhCGJ72+3+CBoCvl1G8GQ/FTJRtQ0lHbbxD8CtknvOCWxKGNikPUNKD8wPBvSDrAWNix7jq0ZtRP0i7LfBcusJLw/tmmMOX5xK/rKw27wgDdZvuZQE5ADIu8KZ7HReAO3VqDnX1T7E/bhSR2+8ZtekQvr5JARBgfUubQ==
*/