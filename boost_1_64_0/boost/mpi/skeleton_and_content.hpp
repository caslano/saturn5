// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file skeleton_and_content.hpp
 *
 *  This header provides facilities that allow the structure of data
 *  types (called the "skeleton") to be transmitted and received
 *  separately from the content stored in those data types. These
 *  facilities are useful when the data in a stable data structure
 *  (e.g., a mesh or a graph) will need to be transmitted
 *  repeatedly. In this case, transmitting the skeleton only once
 *  saves both communication effort (it need not be sent again) and
 *  local computation (serialization need only be performed once for
 *  the content).
 */
#ifndef BOOST_MPI_SKELETON_AND_CONTENT_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_HPP

#include <boost/mpi/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/mpi/skeleton_and_content_types.hpp>

namespace boost { namespace mpi {

namespace detail {
  typedef boost::mpi::detail::forward_skeleton_oarchive<boost::mpi::packed_skeleton_oarchive,boost::mpi::packed_oarchive> type1;
  typedef boost::mpi::detail::forward_skeleton_iarchive<boost::mpi::packed_skeleton_iarchive,boost::mpi::packed_iarchive> type2;
}


} } // end namespace boost::mpi

#include <boost/mpi/detail/content_oarchive.hpp>

// For any headers that have provided declarations based on forward
// declarations of the contents of this header, include definitions
// for those declarations. This means that the inclusion of
// skeleton_and_content.hpp enables the use of skeleton/content
// transmission throughout the library.
#ifdef BOOST_MPI_BROADCAST_HPP
#  include <boost/mpi/detail/broadcast_sc.hpp>
#endif

#ifdef BOOST_MPI_COMMUNICATOR_HPP
#  include <boost/mpi/detail/communicator_sc.hpp>
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_skeleton_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_skeleton_iarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::type1)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::type2)

BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_skeleton_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_skeleton_iarchive)

#endif // BOOST_MPI_SKELETON_AND_CONTENT_HPP

/* skeleton_and_content.hpp
FPEfTLmoWgu935zi3Fb3CPiuJ0foTDsjjW7V3SVki8/xMeWiVggoAlXVSPQiYgA04NSA2rQEDrmB8ak+2Izu6Vm34d4GBXMzjrkjGlVhhAneLAUm7RjkUA2DridRqV2pfLYDEhjrpStsHsbrGOd5xkfUYNOGDBB301BSSpDalSaY0G/1dw4MHUDcsYyz/ftNV9z5RExm704YQl4Zq4La55dKnv0NPFdx3IS8/Fazp/IwBLLaaiE5RK7Dq8YN/YgVJnpRG1MCNc+OogOxSfg8iykOeZPyufXM3bO072EB0wpPuEryXqkZpwHpHpOU4Og2sqpiD3eRL4ChAFu/UX8yD/ww3b+5CEDXzF7fVGaBDcqU0JFp/wVLy5mcW5vA8tvROxvDb6lcgzMCp1EP6CYxpq6xQZCkuuX6/dVcErKxHxBs9myfPAKhvaUK7Qane/P3uYdEGH+8LcBuifqUR8kiil05nKpvPhS9XgpVYF1Nnsw+Rjw6ezLk7cKAe/gBK8aS9HghgWrapxvFYa1tJRhDd1tutm6KjB9hpCEfeogVZJejm2SvV9ZVyU+mLg==
*/