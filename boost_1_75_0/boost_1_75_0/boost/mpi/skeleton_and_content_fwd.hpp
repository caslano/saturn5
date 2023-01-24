// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor

/** @file skeleton_and_content_fwd.hpp
 *
 *  This header contains all of the forward declarations required to
 *  use transmit skeletons of data structures and the content of data
 *  structures separately. To actually transmit skeletons or content,
 *  include the header @c boost/mpi/skeleton_and_content.hpp.
 */

#ifndef BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

namespace boost { namespace mpi {

template <class T> struct skeleton_proxy;
template <class T> const skeleton_proxy<T> skeleton(T& x);
class content;
template <class T> const content get_content(const T& x);
class packed_skeleton_iarchive;
class packed_skeleton_oarchive;

} } // end namespace boost::mpi

#endif // BOOST_MPI_SKELETON_AND_CONTENT_FWD_HPP

/* skeleton_and_content_fwd.hpp
mLNxliqNYJ6Ggwn+K2n4XEmkX67EMom2AGkEcRPioq+NC2GD0ywH2jB4dVx+H/RJQ/Aq2otuiAuddhpDZNJJ1s/IvPb5pGHgaaDNhvBWraQxi6cxRPkbCnLzarafNEZlGkggiLnlxzsNxB5MWsmdxmwWeyPjkeO+qJKGxk8aEzKN5QHTMAZIQ8PKPi7SGLtIObRBIg2jVIgjAXjlm4aWjdwkdEAZc6ehvjqq/HQyjYNBvp5EGroAaYSx2B1C1nMvkoZRpmEIFu7l00wD7z+XUhoO8m9Q8cpfjVTJOPdLT5WqRqTUTSjzrSfdqghmKxe8HWDqNLy1Ar+TzX/bpdPgtNOIZDEVohxnPNKY5ZNGq0zjjEwjRtWYpkpjbVwUG6twf0/VBgeCRDvfL9kYoyqqup3rmCd9ddycaacxLMvhkGnofdLwrxPXxs2ddhpjshxDMo2iAOXQM0+6IS562mlMStkd1wjZtfuk4V9frY2bN+00ooNFOaLlAOaRAOVI9yrH6rj5004jXsqqXqYxOO36WDDtNNJlOYpkGqMByuHdP66Oi5l2Gsr7BHaZxuS0y7Fw2mnYZDlaZRrLVc1UXY5yr3IY4hZNOw28jwC5GtIKuUrzSSOQXC2edhoOWY6zshzlAcrhPZYwxMXyNKaj2wdlOaLDhPsBnzSMAfrzJWz5TtKpIWKsqKTh74WUEZlGmnQc8Ekj3W//sTZuKSut
*/