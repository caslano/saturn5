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
MkD+6AkKOwf/ewIvZ8D/J+D/fPj/FPx/Fv7vgP8To0uFxRoDptclaVtpgpU9gUakZRno9YqO3kBHRSg+zHEPpwW1Qm1osVPJPnPmHPvPEm2b6n/Zb5sCrLBTtbWynx9vwMMMuA1tgX3p/OPa0y7LUXAcz6A9ZMwhpThxhva0F8ybE/7mzcsp9MLKO44w4EOsF+9EgjcTABKTD8m5ZiRk4KSn+J6yXWIPIElzl5Iz5Fh8ydAfnZ9EMVI+Zik67fMN4vrQN1bT4zKeV99AH33P/shooDv1Zk/C7xHxqjDQ65WWhpg5AWGsQxk+4skMIKO20lJzaj4AN36lqkdT2Q/08bK4d8bKelTCJuIOzuSjHq1X2ahDRoOtF5v6qdGQjZfd0LkJr+G1E2nISlvInNggeXlImByWyr7aRwTIIbwrttyShzebMzf98AcBlMr2YBWWm+f7Ijq6lHeHgtiguXiF6Mb286GS2nkX0OF5Bm8bVX6JCxVFDfPqVbxtqBZ+8ezcynV6VWUUVtEbHJc2pq8TlafBb6wlRHKemN6od3II0r5ONlKbmjit6B0ownZvThcXgDt34pXclbn1dHpyO2Y+ytXuZeduzP4lV/++/MhU7Z5z9nyu3/jumU7fW7J/JtWr6ZA/ur5eTeRvrsdRE+fGprJXPtSmbgOAvd1S2TMIYFP88TwLRSw+13+mnviUZsp7gfVrAU8XcJ6JTVr7
*/