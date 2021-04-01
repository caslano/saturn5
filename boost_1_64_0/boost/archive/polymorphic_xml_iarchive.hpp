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
6gsHuHMdhHzEn7WiLDtbNJ1EIhWGcXscG1swOCEGJ+LI1LWGRVd7ixJ8uK+ilaQds1hSV+oOjGAqFjUgdtDFETzBWUFOj7yhdBe+zI6fjx6isHmpXWAV+Jtx7jRdqMtzIIMLnFKzC20ufLfAgAlklZqjbyZfaHYyqGx6wuom4G8bR2cPH4jJ/WEJYCyT2VxVhjyaY7fFLinB8MzhcJRFuIrviVKWooIKhVqvo/R2EBpl4GtEQnIbOCnE7fl17fyO00iL/USxLc4fX+xdpSqI3yPE5PWLr4GSVaR1PSWC8X+2UHfnDvQudiL0nj89VNd4lzeZGpIPSgzZNomT2fmDJjrWqvSM2JOsvDK7pEZLo4i6NpRMcm3+75Bif0S7T+C+PMiiyAknMoZyhD+VZ6Fo7vaDoCxSaZlDGwH7SveU0zv6Eqdl4Dl0AWVmxlOPCQ7M/YTAxOTUat7Uzi1+yMQxHR45CwEPaP6K2i9bvnFcVQc6YvPsvKPeOyDA8lAeCLzrVHsu0aR68gKO2nCxJuZ4f7NDrvRDNsOGmU3An2HIiFTWNdTa/3whb/zeEA==
*/