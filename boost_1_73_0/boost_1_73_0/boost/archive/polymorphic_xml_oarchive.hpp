#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_oarchive :
    public detail::polymorphic_oarchive_route<xml_oarchive>
{
public:
    polymorphic_xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_oarchive>(os, flags)
    {}
    ~polymorphic_xml_oarchive(){}
};
} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_OARCHIVE_HPP


/* polymorphic_xml_oarchive.hpp
K3vnooDftdMly98RaPa8rjNwkq1MYJDqHoFIBpKDxRbhOST6FcqThTdASuzr3oZtN006HEETmVDpSsDH6fr0gz94S9rUMXj22DxcVbGfUuV63lj0Rg4wrc5rk8ZEmK4wM711ji0MgxhnskinqMEy5uNMjDorW8aJhg8JOth7fnOZTecjFSWyTt5uojOMpigAXgq0QeZEz2RGpbpFOi++oldd39z/8fX6+j+X3wTRSx/TLAlnBa21XFuS1kc3pFjUeM+V/j2Glbpkuue05cur6nvHXlxexaPvjfTJfMznVMzv1IaOlqWi+Bq3oGCBPq9mrqJ+7JbZy2Rn6hbb5tTM9/z55fz2H7kzXnTRGj3vnW0pYwl9qXnxkClDKuOp5fTwLhm3g0v09Hfy9i9dvbq8uxdfbyJP0j1KqjQOB6w/nbshvOnQjKic0iMUxd2MWcPwoB9EvpOLmbqh1CQ5TPtFmuWbRkp57M511PR0oRMSBJGyLpnQUT2j/L07VbIm+FFACoIKDqsQjJxVItyEz1U9+JffLUwothBd/npx/Rqjb8+hj7SVk3YRmkgywjApUMJCguUIZ0qpfB+yt9rwqFfaF73txmGNFyyqAba6MLZDDn+ILvavoWNlbzeKHHDJeH2gXgqFHIeOwEuSe+h1
*/