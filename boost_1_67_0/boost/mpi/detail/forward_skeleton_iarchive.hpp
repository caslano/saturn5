// (C) Copyright 2005 Matthias Troyer 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_FORWARD_SKELETON_IARCHIVE_HPP
#define BOOST_MPI_DETAIL_FORWARD_SKELETON_IARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/iserializer.hpp>
#include <boost/archive/detail/interface_iarchive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/collection_size_type.hpp>

namespace boost { namespace mpi { namespace detail {

template<class Archive, class ImplementationArchive>
class forward_skeleton_iarchive 
  : public archive::detail::common_iarchive<Archive>
{
public:

    typedef ImplementationArchive implementation_archive_type;

    forward_skeleton_iarchive(implementation_archive_type& ar) 
      : archive::detail::common_iarchive<Archive>(archive::no_header),
        implementation_archive(ar)
    {
    }

#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
    friend class archive::detail::interface_iarchive<Archive>;
    friend class archive::load_access;
protected:
#endif

  template<class T>
  void load_override(T & t)
  {
    archive::load(* this->This(), t);
  }

#define BOOST_ARCHIVE_FORWARD_IMPLEMENTATION(T) \
    void load_override(T & t)                   \
    {                                           \
      implementation_archive >> t;              \
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

    void load_override(std::string & s)    
    {                            
      serialization::collection_size_type length(s.size());              
      load_override(length);       
      s.resize(length);
    }

#undef BOOST_ARCHIVE_FORWARD_IMPLEMENTATION
protected:
    /// the actual archive used to serialize the information we actually want to store
    implementation_archive_type& implementation_archive;
};


} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_FORWARD_SKELETON_IARCHIVE_HPP

/* forward_skeleton_iarchive.hpp
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
*/