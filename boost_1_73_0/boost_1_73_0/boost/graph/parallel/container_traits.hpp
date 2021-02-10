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
9zt1aC0nQhNPeeXK5iOjbrOKxBXWPAxQW9w1jJotUUCuuhg0TYeNto+3jcisKvONqsSLDW2v85XWavhJHpPI55SM/tQHFvf6b9vnvVNn2P3vq+5oTPG4CKh6j0uHcGtnx/CSV1E177SF/w9TrN27dywcZPdqGbqwi7qHutelxQ/0dECCTjnIDppzIc3chN5hCF/RMolafE78DTVD6Z7a/ek6yNI9Cn8mB6Ljhosot7xneGCCfTj4oHC0S3mC09+O3p9Y+T76r16Px5dHatg54g46uIf5dNSC/ZOcd1hUZ0A4qj4qezkc/PpOdRqYpPEI+9Yb8YsGbZIfmT1aRpGPWS3iT3fNwrKWc1feAejme3VoLj8ax9O6KXuDbY0HGtOePlRSACNP2NXVcs67fR0dvUy+++6kitfb55f9FqhXUx8VKmVPq4Op2T7nwo17hy3xGByqeN7qDlkFsRevxq+lHpB3Y4NOWHCUcNDx1ouIpqNGwZyR8lELG2yJg5LZ0PQRJMHcTe72eH+Kpgit/JULf/DvHHIqeKWYf8t3rxVRB2v4EeWaQZXCDWcoLG7w7JmemnL6X77pjBycFPjl8Mh5dtodiT/r3soQX8zrtRrMsHPkfH9QBehld6RaqQdChdrdkXN49EMtEHr/r6ON
*/