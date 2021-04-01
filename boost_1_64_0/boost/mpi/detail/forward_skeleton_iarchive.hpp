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
RLnH3Jmr0eBot46rsdDjJHcosPLarQ6wBZIoGHfjGHdNO0ycEAJajdQjZJ+WfOhD/FvQ/u+XfP9eL9l921MqXF6e0tG65cNrdYqy16Zbsyxq2+gBjbU/630micRKxYHi1bDMXGaOIwZfRF/HMo1nn/BemswqFMZJWgr0RuUO3BmthO+k9O0wdiRUccWJGXs08z0yJBu056C+LiBgWhjycDFdeZdctKCn0WLJeWP5QT/BC2Hr9yFWPKAVZd3iKPWP3H1Q7Uqm1Ez5IQn+fisN0iMGB61vbtzrTzVDrewrH3EK/rQq5hkp9jCUfjzEjTnlfndtXofa47ssJ04XgiW5a3q20LJx63pSD5RWKu/CQFcEz50yD6ImWO+aBxcuHwi3eOi4LaTX5reLc55sU9yByFxNSt4wSOd2ahEJpBRDoxtH9FJxBcwuWxTPGI1MgcD6E9wh8R07AwimEdZIk6u+TSMg1rJTr3K+QsPp0/jvY/tI+JhCDIQsQBpj6V6Y+fFh9EV3p35+DISQDmYlWpZ04Z+ix9pc1q7QXm77tEQqubKDjD9AReAzv3ymzw==
*/