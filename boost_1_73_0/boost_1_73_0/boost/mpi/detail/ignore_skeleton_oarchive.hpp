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
L3Rlc3RzL2RhdGEvdGVzdDE0NjVVVAUAAbZIJGClVm1v2zYQ7mcC/g8Hd0YbIw7tIB1W1wnmxnLixbUNSUnXtYXAyJTFViYFiYpjDPvvO1J+ydtaBxNgySLvHt49vOeojua5DlnOT0hHyEjh4ztfLlQ2zU/Iue9P7A0mY88njUYirsMiS0iHbo06tPQjL8Hj2Q3PGrmYctLJeJoscXrKNCuhaOugBYfNJowvSI9p3gY/Lvbh8C38USRm4jdoHbWP3rbR5OyDT0q4NpgQG7l9oRH7zsmpkppL3RhyOdNxG5qbEX+ZcuNwq2maMCHNhOShFkq2IUxUzgkGXIbUoasQMfLTRBj3MvLQvqBBueYJibVO0Xz9Ch3J5kjYhg+IVGYpgoXQMVwLybIlhGVMaE5Le8TDgZsT4nnD4NRx/aA/GDrHFrmcgE6o5nMmp+WabUpr5wg7mLRrhsDJ2PXpgtMFk5q2jn59A9sQEjWjhigzfBDihEmysQrldzNrZhpFmig2xSU3C70Edh1OX/AX0SwWpBOJhIOJ97j6wKl6Qmoxv/1szGvNJsefcfmKYzUENI6G1DV7CHzFMxEtwUQCLNI8Ax1zu50QsxyuOZdQzWOlq6RzY20RIM2UVqFKTohl9H6+6zKqkHOV6zY8oqdC
*/