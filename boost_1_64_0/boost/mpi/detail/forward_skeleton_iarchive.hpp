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
Qf1CL+GWiDMocS5InAsSbom4C0bxyizvXhWScK+g//BuVzEJt4tOI06V41m8P/dle+/D1wX423cf3Iw8dXL3jc11qrVMDH0tdKfi8POgF8ZPUUaKZaDIcIEbkSnKSLEMlFaY5CEOqjMbxvmX6J2vAIJYXhICaFCjAE4XzkiPkKyUyjNHPe0a2HyyCk1JjDTNtYPm2gFzzShZfpmgTARbJJRklBqQCUommBooyCg1IBOUTDA1UJRRakAmKJlgamB4blgA/8Sju9bJDNVX5ezI23Tc3m3sr70N42yh5mUwqoo+/lg9OrB5V2XTAdoPbUXaGgzEf/ik95jRupln66vBxkP7PpPK63TgPLYGf/vyVt9mwbrZVP5MYPjK+/ChHz5k0/nEvZtP9mng3O7HEIEFh179nuhrTlbB2ap8P3wYvUqPHQc26Kr8Rw13eYPvYaz6jM9wP/gHDPd27/+a4b4nm74HdRv+9t3jGu57wHDPt8x/3HA3rVK6ROangOZnbdcqga7RAy2iT28xgCeSnRFt6Zx+xY+HYTaNMkUZKbZMKRlgbkSmKAPF2EjBAHMjMkUZKMZGigaYG5EpykAxNjJ80vtsCtbLPFdf/dRX0EzdpM3UTRwZfFNm0NrYb6bwiW6CG726Zmpic3eAa6XAmFBrbKW2CFopMGJnrjlN5ZVi0+jAd7BC03warPcAmamXs8+9WmdDBoYq17Rso5frl6sBYEVuEQfElzpPB14wGNGCPiLhyoDbIg6iL3EuSbgy4HYA/+3DojuzvXfisAj+9t3pDovuhGHROuEcFpWXA1vu+TPmors5oqfAnP4Y30yGeUJNpigjxZYpJQPMjcgUZaLIjfj82oMBvzZ9110NWtgCm1966x3h2NArZuDY0MSskb0XjKlNoCwHZS4oCSjfLgB+bSjPQTlzoZg6CMoWUFaEMjeUHihfQL03oMyxOPjIoXy5WEy9A2UIyp1QLoWSgXLNUjF1OpT9oWwGZUUoc0CxoHy2ZNt33j7ax7/xcOcPFp7Kmz+YKTB/YNP8wWzg7NjCNH+wrOvfLcHP/g4vP7ld/7qJCm16OU4yv0+H69nd6nWasfX6HNt/XnBS7HXU9rwO9txrrMa9g0xRRootUQKTFX+jdxcFgqe62Y8LdzCJO41T6im/K8TP7B3rn8J15nI9wjiTJVPsxrDRO3DWYEsOX6I+zKHRS3PWYOUWqYIL18Ee3vbnbrCHhCsDbgfw1mCPvG6oKjVUlXBlwO0Arif1eRIBpUrPR03Ik1S1BCfq8/r7nrA+PZqtqP3Nc1GoR7jY/hT9vT+5ksSCg9iYnnn6qR8kjyYBfkrmMEhgCm9yyi9bN+s5A/hFegx/AuMj7wmUeBqHWtdfs81omirp8EwYYzBFe87gTzzc+YKH48J8QUq5L5RnpJ6kZTG7fQiYe9XyAnhGehDeOWleQUWOnwT+4uzCaZZ/dmGmv8VJVZA4FyRcGXA7gHOHu1m06aTKJ05ePdp0UuUnclLd53VXBbBg92F3ZUN3dd8mzs0vkWHBHeZ7wYhYOqAG3xPwBRu8UuCLIqvrd0+lwD116n7rxRTO3pVbYpvQleYHtetNwi0RZ1DiXJQ4FyXcEnEXjMKV+QO8iskNuu47I1305m1LSbhvdBpxqhzP4v25E96WaWBDL9A6ngpeoAfOWq8lnqokhDtpgjIRLJkgoNqNLBOUiWDJhBaU5CCOy5m1uOgK5QIvxg+eO3JejpCMFMpPAdwqbpVWceNYtZeLyAb8QM2bHmWbCvlZg5HD7X3gAQ1He5/cFPxCni97dMNnUjntE8qh4MPfvpzVt3S2Nwe1oTIsXg4yOPgquKxzUTAKaUDW7OhgFzU=
*/