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
O8qry+vJg+W1w8rzq/OL85vyC3sWgRPABeAMcAU4BVwCzgHXgJPAxbFMfas63rlit37RS5V83tW0IzbXFOGRLG2VjNrJxW17zwahb1l4RdPCG5TueMJhWfTj6ns/3VaENzPdawAOqu6q9nEVTO3y66BjxdOhE+ZD5iPm0+LD6ku+K75LPnQdqu5KCJIJxAAGAaWBPUB6YD4QBIQD3wMTgcfhVwqo+AX6ZvpzeZR8tPxU3DaAWUTDs+BeYZZgOb6fXlk+Pa6O0ga4JbQlxuNsfjY4Eb9JTy8vFxdNRSbB42KOfHU0eyWH7r86hMB9Ltv611BrK2t5azVryLUSo29OICdNJzcnJSe7yvz5xaOKuMkA0xjrODnN8v3YfupZan6AskS6T134vPqs+vKkXE46uYgIm53d/X7v5FB+mfEy9Sr1cuVR3Ok8muJu+s7tLup25HbkrvTW4SHmQflh7IH9ofwh1t/q6dOTyZPak/OTwpP109cn7yeZJ3MJ0d9AYj+2q5+Ir/fcD9zwahSoaSAyNpmKVULHY9Sz7PzrdPUuiH1AP044VjgOl5JCTMDd/nphsHoSBBroj1OmzBDrt9d/5CBzs6aajP0aNk5wOiEaHesuX5E/qL770UtL2D5WTj4xf3Fyy9pDiFJl4Dtognub1DNaSI4KFOsyEAya6lqqc5h0qHZobrgW8MuoZm9jh5b/KS8rby0vGZubW5ib
*/