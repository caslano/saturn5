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
k6tKq6rrdTYh1LpdFTU1tXbdTouurqFGV12jMxWW6PaQsG6IigpfI+N4M6H0d9/Pv+pexTx8b869Jzhmciyu3lUFupJmUTZj+UHB7MDPk7IU2hgLXhURpBUfDlUGo6XBv9KuHEVyHUkacPlhwSqyKqwCnj8i6j/rh+7AGaV//W9DXX3dLibTRIZafDOWTv9vqLNYa3fJPDikH4ePv0w285v5zfxmfjO/md/Mb+Y385v5zfxmfjO/D+0Pt7wcjDXp5P00o8/9NHEPrCgAvcoPHfeWvIguOqawA5TQ+bvdLs77GWtW3ffxvt1TUJJTGszEhaEwOVvP4DGK3zVeKRXiz+jOE/Z35Y/Kx/MUxdxz9Uoyw2TWk/8WMueDxL22E2R0lJ8DZHAPKZ/SHCATM4uxRjJnyKTPZqyTjFbDmFXDn1BhBoq4lcwFMuV4UoZMfDhjB8lMkCmNYGyQzPJIyguZs2RyKUN9ZKLnMGYnM0ombS5N38mEEp+qyJzCugOV5xCZSTLb5zM2RGbNAuIbmXNkimIYO04mdiFj+8mMkTEtwl0qxiIXM2YjY6RynV4seELRM+sqyidzf59axevf9X1Qh3UW93fkUsFDlzt9s9nu79A4xhdUXN9riLer3d/6zcTfue7v5uvFPTzlG8jYv+57LeWn/Aa3HPhcsVP9YpH1YIH4GVRuCAtZC/UKA/rquKBpp6GXaJRY5JNGDE9j
*/