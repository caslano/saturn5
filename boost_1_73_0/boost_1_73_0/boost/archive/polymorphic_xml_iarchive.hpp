#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_iarchive :
    public detail::polymorphic_iarchive_route<xml_iarchive>
{
public:
    polymorphic_xml_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_iarchive>(is, flags)
    {}
    ~polymorphic_xml_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP


/* polymorphic_xml_iarchive.hpp
GroUOfCNuZBMyk5JDVsD6lIw8qBsPZ2HGchbjiCIz5sVuztdlFx6aYG76WQyVQHa6wJ5Qq2cq5WubRnPawaP89pyJE1r1nwOK9MWQW1fXYj5RDXBSFqpEKgdmtz0ZDmrbQMiEynzrKkbwrdx9EL2tDRVSfUXmjjKAJUU5SLtyADOQs1lfRytFIc/rD3OVA5FhA21uDi/uvvGZdDVeigN57Q0iGHlydbqYeVcrvtDruV0hrf/2rFzf/ubmOEgeIguYCgxMkOxM96JHmDLpyyFqRbHn05PTs7OTo4/c58MQExTECPIDmBCxqB7v8D+MQA+Pvt8xNlKHcHQj1vPwBzvWhphfKl1pDRj5el2ZQnUTM2VSN7weumuFEsiY1nKgqYh9JFcCJmIy1vKO6pvQP0kXn0wLTqZ+QDlsDWo32IqqNTGDeqRLAEZ7IotknrGp4Vmb5D+JhZH7GKLwX+jwCKtReDwCh3Fy9T/4vgMlvs0BO54CiFHAXvhx2Kez9Q8Ne4Fn3DCT5IfixW1j8oqX/boWKyswS1SKoYoubBkIJub54CbLNkkKR1EU7no44NljcVMZGqeS7J+WkEAOUallupE0WEO7+NZtJfFAB4ZwOPQPs3THJ2i8RKOzOGDj6AgYTkGOVE4SSWjH73yT7Zj
*/