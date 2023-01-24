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
r4tXhnyYOXrb4m2TbZkrWynVeclXswkCVMtCowmsu8gxNjnZ/ybryV/a+TlGKPIxls3kZ3xiAadiSt3QVKQBfDiZNuVFIYQaBtLMdYCUlUxSBOp/KIpllvIWFKoT4U8sDRgvMpPETk1l+GYyxxFAMjWcEgCf8p3GrG3etk/euLw37ykPvWKQbHs5OWDit3+2uC50mGtPCLvDwOzFR4Q5DjZXq0mR2v+8LPPZi7y8ITJ9pvgm/ulOQYrCm6NJus5j17Sgnfp48Oknz0J/E85uwJ9La6ofYAzRXZTtZKZRIizGFa3RJyi/cL/aAAK9l76tU1sAKAqiY4QaNLlEu3x9+fKS9/JPl+9qyF5qo1y03DbxcnEXcRxws7E80cSVxoH5az30m2y5FIeYD0pnfJg/5D5QLuK+wHgMevOV8j0aLVY2DhF6WBAjUzbwRwzGUCDJawz5TuFBwVeRCy4fUr+98CJ/j55ZvL3O4oyDOJA0mYmUjvCaUZHW0wIvqJjKI/m+4t9jf8AtDqJ6je1cbUR9RfsVjQeDKjbnI+eCHEEqrhTRYiBmyweilhecOvAb9ccrNsmxyeNZKinHIlcqegF4VJJUu+BkgS5LipD5alpttDe0ZjyOyiUaYDX6MlygSWgSCDpqPZikYgNx90bDM8W325r4stxa3ZJ52gqMQG7COWLAkhZg6tEPs+PbmcLskbyb0w5L19ks6trZVs4/
*/