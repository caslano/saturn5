// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/interface_oarchive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>

namespace boost { namespace mpi { namespace detail {

template<class Archive, class ImplementationArchive>
class forward_skeleton_oarchive 
  : public archive::detail::common_oarchive<Archive>
{
public:

    typedef ImplementationArchive implementation_archive_type;

    forward_skeleton_oarchive(implementation_archive_type& ar) 
      : archive::detail::common_oarchive<Archive>(archive::no_header),
        implementation_archive(ar)
    {
    }

#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class archive::detail::interface_oarchive<Archive>;
    friend class archive::save_access;
protected:
#endif

  template<class T>
  void save_override(T const& t)
  {
    archive::save(* this->This(), t);
  }

#define BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(T) \
    void save_override(T const & t)             \
    {                                           \
      implementation_archive << t;              \
    }

BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_optional_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::version_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_id_reference_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::object_id_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::object_reference_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::tracking_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(archive::class_name_type)
BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(serialization::collection_size_type)

    void save_override(std::string const & t)    
    {                                          
      save_override(serialization::collection_size_type(t.size()));       
    }


#undef BOOST_ARCHIVE_FORWARD_IMPLEMENTATION
protected:
    /// the actual archive used to serialize the information we actually want to store
    implementation_archive_type& implementation_archive;
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_SKELETON_OARCHIVE_HPP

/* forward_skeleton_oarchive.hpp
QBOkz+qxApWY4JbgWF32uW9/O1RB0I2gMg2Qsgp/VEa+IALQhKsTJeyXyep3j2iXJzTD71HipKsZjRa/uHZ8gcNDNR+f81pG4tat85qZTxXfFwEgtbvi5cRkWVp2y4yWbVqMJXWxVH7aONRpOOgjSpWkRhbxpYi8/nUg0ZW/Zz7Kymnpl8v7dZixCWUWtMcdfZeV3M3guctuCfkvkfW7NUyOLKCKNFyYeSdnsrkp6L+IsUvmzAS/VFd+1ntoXh+flBFH1R3kyls9P+mctaRiithai0ZxpquS+snBZJ0X2dTwjdQbKd/0Ujo45jmDmV6Tb71YR4uFR6Pu3jp1oL4+TtFqdDOsHRtc3Gq4A5OzuIeq+J1gHo4B2yLKG0MzvpJ9CzqbJFoB88PWFDkrGpE6OueSyhFH1xOfz3mEVZCYoYl6eD3h+8DGO5b2o+CrfjEh2G6LztF1xxBbpbFeILoNIv5qpgYhu3j85tWE097aob/z0yPpZH1/M0TJCgv7UuDcgL9235sH9FPVrtPt4pbdRlJYHCBGZ+9S9mdBaeN9Uvsl/yirPan/GufgZQ==
*/