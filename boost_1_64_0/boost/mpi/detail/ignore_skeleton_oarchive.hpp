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
2PlXS9GW6xFHL36RuH/3D8LnRT5bWyjfiIjL92mIlucBrkn0Cn3m3ea2fVbqsVkcCbP2CTX1qJell3Po7VhJvNCJDoT0SLyqCSp/V7m307jXqSOohiZL+0xxGW0qSKqAYv4m8vRK9xiOIV2YSpfOIhG+fYjtelrrdR3zGvNODmbgT9+TS0HLEVzqSoQExaODi/jWhsaRSE4+M6aUkG6B09gpisu6J3Z2XrMtkePCVUdexzQlEGYSt7Qu2+Gg76b77YhGqfawtakO7e0wYB23fSy83hDa4wH1N5LTcH/Pc2sUaX3pevoozaHrPnUjbx2C0cMnPAJpUn/iB7uV98s+hnPUbyQsUAdd2xYetcSukEac4G/pR0YoOk9JX/E7NIy7y8tYqlN3pCykoMFTSgWEuPbAX2J3/B/WYALFcGoO9KXyYVNMPkicqVTzkvGMCYb7AkqGvCDnDscbvU1g24AsHBEEZLKXtkEuIsR6bAEwiMmIFm5/Ixd9H6w0rBp8RmWp1b+8vyI2fbg7O9E999UzoT6rWdsuolINekFERcMwMUskJt/WitgK/P3bjw==
*/