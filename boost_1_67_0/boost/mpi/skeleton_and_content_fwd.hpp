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
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
*/