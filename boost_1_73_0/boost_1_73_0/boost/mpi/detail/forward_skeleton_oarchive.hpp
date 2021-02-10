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
H5EvP6RMkKWwjAuT+ViS/r1j+0HJ8cKcn1cYGpPND6ZsvqPMmTmDHNMW0zl7hyZL2IS2A4aXnrgJHqMMRNEvFOF+38JEimqe75eQRVurkGKTAvi4tcE7KKzgG6UWBjGQzXcUZAXVtY1urxPYlbZ0XFr9sVPHI6CvQ+xe1S9MvmzBWbFgS8EEUiF0lYDKMrwiRphxRTIz2bZn1QWmRKkgp6G/qcOjZcbiaCNQ6+r7TPBTZgvzk+0bXkGfy29qxFPki4uLP5CpZWEe/02vSbTVKrmvUGFC8AwWgldFVIINYQ965CtjwG6kguG59WWpW6KAtA1yv0E/q8HrJo0LNUpFjg0UFCMWvQ2W9AEBtxggomh33318A2ow9Xs6uJM+PGutz1BNVRW1WETaI2EMpQEXeQ/CD4zqIsDtcw5D2gZKH3AP3D8u77pshQp1cUCkGX3cr1cTRCUH5GGtSCeme8knYF/bEX58up7yV3su9sjLzqhzYAUcxS+imkWHUEjDtEBazzQ2y4C2u9GO79RqctyyYD2YDTTUXO5dr15WlxPRG2I5yWbVGbjBwpe+OOISfbYDdx1GB5AwqBqnjegRnQsDXBxqmN9M5cxHZc6ny8z1EfI0jXB1iJM/TBCCQadqmJ275fPdego6ErOeFiPh
*/