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
PaIaA7XrWwGOK6QbeBiw7wZftLaRht9j9H115p23o9TYevqR+fDKmRPNQE9u9TT8x2sLxeqPA0buqMi7P/xoCQ+i+ySFnaReHMmDsgm9XLsD2KCKYvECJyzV9BsZFLaFyBMfoHOdFfagfe/F2oXvu5AHe/UCYidQoCTqINFndJbyNZY3WHr4FQWjCVuTYB6mnRrhzq0uzSMeQHiEdTqVaH8Vcl7hZ4de9Ye1Qy8J82qHQ+31
*/