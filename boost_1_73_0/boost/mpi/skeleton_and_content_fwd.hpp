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
lVl+U6yCYRiIzbARNsdm2ALbYkvsiHdjIrbDRdgBl+AfcB1G4tPYCYuwMx7EbvgmRks5A8q5+oVR91LORoS/nG/1Yr4g7I0h2AfvxL7YAmOxOw5AKw7EGTgI5+NgXIYP4gp8GHfgUKmPR/AQDsOjGI8n0CT1ZMYSTJX8puFt5C0dG+BwvAMzsA1mYn/MwnFoxQ2YjZvRhlsxF9/AMXgCx+MHmCfryS3n6vPFJO2SlkSG1Mtk
*/