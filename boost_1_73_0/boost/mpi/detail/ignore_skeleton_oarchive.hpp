// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_IGNORE_SKELETON_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_IGNORE_SKELETON_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/item_version_type.hpp>

namespace boost { namespace mpi { namespace detail {

template<class Archive>
class ignore_skeleton_oarchive 
  : public archive::detail::common_oarchive<Archive>
{
public:
    ignore_skeleton_oarchive()
      : archive::detail::common_oarchive<Archive>(archive::no_header)
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

#define BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(T) \
    void save_override(T const &)              \
    {}

BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::class_id_optional_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::version_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::library_version_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::class_id_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::class_id_reference_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::object_id_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::object_reference_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::tracking_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(archive::class_name_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(serialization::collection_size_type)
BOOST_ARCHIVE_IGNORE_IMPLEMENTATION(serialization::item_version_type)

    void save_override(std::string const & s)       
    {
      if (s.size())
        save_override(serialization::make_array(s.data(),s.size()));
    }

#undef BOOST_ARCHIVE_IGNORE_IMPLEMENTATION
};


} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_IGNORE_SKELETON_OARCHIVE_HPP

/* ignore_skeleton_oarchive.hpp
fJLIW6je25Mh71HyIe9xLD9Nkz/Xa1ZeWxHk2M42WbZ7zMOjc5zLXMnflfTyuc70Gknvk3SBpOvM8/x7si69bJ7n8kokXSjpWvM9/x4n6Y2StunSGyT9nKQ/lPQWSUcv8Ewv0qU/0qUbL/RMR0l6m6s8kt4u6dWSfsm1PEkXSbrfImd6t6SzSWuXP5e09v1HdfNf0M1fa7Hn/A+Q1s6fQ1o7/wLd/Pcs8Zz/j0s85x+9xHP+
*/