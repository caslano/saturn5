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
OGJq6nh5OT3uZ+fsdXhSb85UqTl1+h4wKujRqBsjqGf/6rAxLY/bdcXAmjAwVcqsk70F3/4/U4UmtA7fBcjXw58bdPMcvidzpkt08XUYjoGPiYzVy0Udaui/iSO+mziiIzJ9FRvMmSrqkPT7pgxVSDrOsjv8uUH3zoHhNslkqTmFXFSwuf9Ey9HwlDvNO+f5F3S3880OrMtXscGsqaIO7j5kitAEd+OkrV4fs/qLCp1ritgkkizmtCz6KnZLspjzZHEh9T+UxWGdRyDJ4rBPFoebsjipJIvDnix+NPn/UBaH9DI7kiwOaVn0VeyRZHHIk8WrJ/sfyuKTTYdB3Ot5aVqcgpie5PveUnEyqYt+0uuit4n/D7vowaaiTq4zg/waPcj3vaViQlf0a/Sgb/+LntBoNIZCjG+4+JBePkiSxYd8sviQTraUZPEhTxZfnPR/KIv36dxcSRbv07LoqziVJIv3ebLYb/0PZfEend8tvbrcw/e9peI0uqK/d7nH611W7w5N74JLH1DsC37+xd7lzuCySH6NvpPve0vF6XRFv0bf6Wl0oys0Go3TTCAwpNG1X9To2/Q6E9J48Ta+7y0Vp5fGi7d5Gn1vZ2g0evzjxZv0WiXSePEmvu8tFWeUxos3eRp9UDQ0Gj3+8eJ1er0bqY++ju97S8WZpT76Ok+jF5gQGo0efx99tV4zSeqjr+b73lJxVqmPvtrT6FIkNBrNfTTrco0nzHGlqSNHx8b2iQIB9r8fS+idRTj/9CMN1OAeYR5DrZnH0EDJa6aeNl5+nx8RCTruHkJ5DFSpSpWqdNctNs3UwU0AVpTHEGAFN8zHSxGvscjEvJSPVyfySsAxEa9O5tWSx1AL5jFUAWhnzraP9tE+2sc/c+D82ZI4f/bwLv74hGxqriwH+ivIY3kmNRKBwwv/mY1jSSmivQRjSpjxZERHtJckXBlwO4Brzo7E2ZFwZcDtAO5N3pUwKN+bonMwbHuAdrPyRehWMSqmSj+tcoSukaKMFFumOAbY2IhjbMQxNlIAh7svCWkYMu82gYcIk56RxKmJDpz0nAli7uxN3TDyWefWMXe+NJ1SawaNE74bNULhViOc6wTR24l715ymlhwKZPt4qRhFqJ95vxvCq8sXU47BCNzaEUFH3FtUwfa0eOpbJFOUkWLLFMcAGxtxjI04hkZ8QWG5QFBYjqfcHQ45d2CaHa0H5B5YHMZww87tMIZxH2iPl0V7vPD2rfZ4JrTHBbLHuWdSw6322A6FPc632uN8+MxM7ozeoWwqh/YY/vYNgdFYm+xxAexxF3zap4Ozt/KQ+j4rBRIOoPei6sbAwm2BqBXQLh1BXEUDVSUDVQWY45FlijJSbInivqttPlme80iaAapVDFCtksWsAgpvniaCMhFskTBMDQ9z8hP0W4l7N+iqJV8OJnhZVN+CClA/U+yGvq18NVhh7uC+Acatt6vUeiWOT2/CaqPzARudF2x0iQRpJhwlTMGWurFt21L/xgPt9Zpor/u2pPUOMoPdl8HAIPr4Y/Uo3t/U1CTQ6gwwAn3VVY/vKu/ahQpfne34BZ5J5cfgQPw4GFOAaA6NToXWojwbieirRTIUQ6PzYP3DJ23WH1UUMQgVX32fMvbyz6SGWvuDmdgrqVNb3YSxhpvaKuHKgNsiDr49iXNdwpUBtwN4a9LsQ62prQ9lMUDkyWzvMF41/O17MpI4uwNikluz0R/ylgKpI5d9OnCEO5B6aGNn4RnIpvrMw0Ot5uEhytq3oqkiJfVXOKm/QgGERRogjtAzoSRJndEPSZIDGzfkjP6KlHdfkXBLxBmUODsSZ0fCLQn3wChcGYIOZIfOmcpz/5xMF+ZMD1E=
*/