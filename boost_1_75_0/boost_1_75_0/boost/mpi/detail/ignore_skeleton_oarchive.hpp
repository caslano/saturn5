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
dM8ns7bF6ukeptN+PlJZ8SQwpihv87pN0FBKiXfpZxid9ruP5g9tBwc2HeDbooMnrVsCtR+rOj6ebDLjDkaYbC9Tnin9sOh03eDZcN14c/BiCyChndduqbKsOq3qeUiHs5HwmeAzDdTGHaHxF295Ybf7qJvEjbVsk/VTzbEjrKCt1Wa54lTUGITV+qS+qKPA/Xnq3af3NaJckf7Rg8TsHGQfmVwH1yXfjGTCpPrvn5u00Y2UT+JTR0FnsfBlSMT3RrXwbsRUvA3YtB4Zf31uvweNoaWUN3Xpo1JUb8afSM+aUPdxVBQRPzeL4vy5DaCvqLTYpB5VNkz+sVkf86JfJmHKKZcZ97PNRYKX1A9HArgNpo1IfGmvbb0DnDWXvaRFkeR9+oN7R6ZgAFL1fSFa2/ixf2J6syX+KP6+4L02h9RTEc/2xUNGy4v1kSa8C8OnJoRu/IrE/WUA+xnBhggN/sVlJ25nTKdy51gnOwPIhLXqTSNuI9U1aRX5V2mxhh2jGpwbxw3AhpEJexXeV/y3zyi+332P6XzoxOgM6vywQbthasJ79qoq5Lo2Zns5shWXFDP0uykNvnS7NRW2q6a7d11TFQ5f9dtmQBLseQ5mNrZ4cog85xIHBv8GkQk1F97MjwcUfFla1UYaAvXsmxEt956a6Qm11MdYze+BDPIkSkdUIVCL/VV2XyMaxP1x9SIau3Cs7O2+QlcnmWA5
*/