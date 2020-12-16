#ifndef BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_iarchive;
} // namespace detail

/////////////////////////////////////////////////////////////////////////
// class basic_xml_iarchive - read serialized objects from a input text stream
template<class Archive>
class BOOST_SYMBOL_VISIBLE basic_xml_iarchive :
    public detail::common_iarchive<Archive>
{
    unsigned int depth;
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_iarchive<Archive>;
#endif
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_start(const char *name);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_end(const char *name);

    // Anything not an attribute and not a name-value pair is an
    // should be trapped here.
    template<class T>
    void load_override(T & t)
    {
        // If your program fails to compile here, its most likely due to
        // not specifying an nvp wrapper around the variable to
        // be serialized.
        BOOST_MPL_ASSERT((serialization::is_wrapper< T >));
        this->detail_common_iarchive::load_override(t);
    }

    // Anything not an attribute - see below - should be a name value
    // pair and be processed here
    typedef detail::common_iarchive<Archive> detail_common_iarchive;
    template<class T>
    void load_override(
        const boost::serialization::nvp< T > & t
    ){
        this->This()->load_start(t.name());
        this->detail_common_iarchive::load_override(t.value());
        this->This()->load_end(t.name());
    }

    // specific overrides for attributes - handle as
    // primitives. These are not name-value pairs
    // so they have to be intercepted here and passed on to load.
    // although the class_id is included in the xml text file in order
    // to make the file self describing, it isn't used when loading
    // an xml archive.  So we can skip it here.  Note: we MUST override
    // it otherwise it will be loaded as a normal primitive w/o tag and
    // leaving the archive in an undetermined state
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(class_id_type & t);
    void load_override(class_id_optional_type & /* t */){}
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(object_id_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(version_type & t);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL void
    load_override(tracking_type & t);
    // class_name_type can't be handled here as it depends upon the
    // char type used by the stream.  So require the derived implementation
    // handle this.
    // void load_override(class_name_type & t);

    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    basic_xml_iarchive(unsigned int flags);
    BOOST_ARCHIVE_OR_WARCHIVE_DECL
    ~basic_xml_iarchive();
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_XML_IARCHIVE_HPP

/* basic_xml_iarchive.hpp
wu+qydNoJjVMK+G3VHOmUd/7s8JQ36pAwvxxRDZTSMoj3mFHMsI3kFvuSQcEb/wjhXyZTwdIbpcoGoBn2MYJXZytoVrC9pYA0QCCVE846rpD1UWyHNQfXuKBxUn4hkBCP5URXuiZOaELyKnJDzHP1U0I1K0YnP7IjxiZ8nzeVWxd3SsjohzA4/e3oBWt3s2TIxuNriIkufOulPJPMRrbSCz9R1f6zflhXnOtYaK7VExK9W/b8rpN1Ry8fS5yuaCkabrvxmxeVVXUsqswPejVpE08ucq6x6ZIto5E685ni9lC/T08Y3HIp7vwJkFBYPQV4WJwdRl7AUQ0PP1DldKQU5YXkXsabBrZR5mC+D6Jd8keAoO2WT9cB3j+uPLQ7AEEwBlspgXsBX0VgW1QYKkWsHtKgb1MYK+dtTTaFrBAs0VXqrJNeTO/QmKYNiqpH5L8U+hbCn17jb7Fhpk+n6PP/tfFO/u1H6s/uHptFM/WyaPV1qJF63s8tL4vI61vGMEIk1qJ7A+ykDVaDHkmyDn8oDKT9y3jcE5uhHBVC5cKHrBU0MO2gklSwT1SwRqq4GJUwD2I7RTuiyJe1T+E6kjBz8vZ+BNJuIPIRGGBXOgZKtn0KBP0Y1b0NEAoC2A1BKyqJXc058ZQhn4nvv8sB2g/86Po31aGfsygCkr/ZNPh4sD57X8N+EqtDPi2oBvPG19dYrj3llJw5ADRC0XWmMmGDz/S12kG7jkTLhr+cEeGb+xhZRG+sILjI6eKGY28jYQMTB9tloG4+oC95bajcKQcLfwImGKCQBzKHNHA0nuisLgnuxUnkOOl4b4kTESAQHIvdpEyJAYq0Z/ALyDHTO2HDO1AhvZDpnbAI7b8h2R79KvI2+MMdol+Dnc7+RJjE3hfdTYt0kBdjHD5Yfo0Csbvh4BPLYUTpPDHVHgJFa5gKUwPBYleLuzR/uryorA88g8GAhcTgEfkeWMDzT7wHlVzP1s9bCO4ji0EXZPfhAyJKNtYJcUT9hdBVxVJyknlpEmyBLQj9aeJsM5RKTTh+XK3UKltwIOc9jqnvcNAlO+g3CmnZYVyOHM6VljSfzxSzDXONGoc4VT9WKXnKIKCFJR4EuvSPHhwPpQjpjMoSzOagxlp5857V8a+BTQMO7bUu2CrcqWH2H9AIgEWRnOXIMfiqY2jKitjalHLEJc/wpszjAiau1xCa39zANIe2QyYaTSs/wXUh9LdC6wNbPBXVj+04JYJLAus5M1lbiT92xO0x0j95A2gdgQL5ro2IZW+kP+0lBSR1dbKTua17oMxxrJ056Fm7DrlftKBpDtaXHnslMHuj+GFrlEJC/0E1Bjdi9gcKDP/ZXUZvScBPxbHkJB1Im6sl/TDrERz1t/MBHpFgGZagNYw0CJZahVLQK+PVeRQYHWJKMV5gmNxaM4YQmB86wOcxPzCEPdginFnNjFDmuhgNrHV/7yZeZdk1gxm6j2rMz1rViS0ufr5O+C7//SP8n9/qYGv60YZ/v+LbfG1hBKWmOYe9n/flIty8KFT6dp+6Hcx3s0MM/BujzCFd1uHKbwb94Oc6rpI4GOp3FW6tYNAvArneknnXd/3vYFlBzsd0L8mcDCqPZTYOLBC28asClxAtuW0kkzteCYdlIN4L7JgyO+jeMfPwl7RXwQhoFUOYkhxTe/VRjN6vc+VqZ0rjZvnSeHBVPimNuVws0drZqDXu1HTQYU2HU0EIQbogItO2sHGgjYPcNI2QmWfq6SdQiT7qui3JgbdcL0qFDMOsUhOxI2WYEhGNcOP01xmjYMtIWMef7HwfYhJiW4QPhzDDYwZ6xFvhkAgU48BPWHWAqvcHNKZNMhfBf3Lmfci06M=
*/