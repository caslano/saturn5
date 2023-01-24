#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_wiarchive :
    public detail::polymorphic_iarchive_route<xml_wiarchive>
{
public:
    polymorphic_xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_wiarchive>(is, flags)
    {}
    ~polymorphic_xml_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP


/* polymorphic_xml_wiarchive.hpp
I9mUiZ3Ph7+OUdi5QQ5PZff6ek/KxGMDdDeq9yQlJOesTD3YWDIk8aXzjTNJ5eJz+S+n0Ofyxw/irVrhSn4174dJS4jDrPqI+eUQEMMcdvp03lgBwpBxAjahML65HKhb/zxKh2jBMu34Hf4cEJoCRFzOP/+0Ho8PGVqBZfBRCNg9t9wpdfxVaChemw+jF+OS882ejQBphe+bt0LS21NH2VZHGQkoeT4gjL6eyN8DFK+t8YSE3TjR19LTWaqUS8V7ARZ9cqw7hfG3IVl0HDdpR3KtCf0Gk9tS486v43+AEti9DQGQ529oGbM3CH/CELYDR/XGNhyVQ1KZIvsuqGeFMrGg4VC9et3SySg5Q8/iwq3xWKpUOwONqqob8HO7Wndy3TTVHsaOd0aHvSde51MHEv/t16Aa3IBekZSysrogx4XeiokCXpddCC5cZDY1CZYrNalsfTkwXbVfUjvPAgjewV0BrVnjaqQGaeV7IF+YrCbwWYAREmY+FW+9DrCpNlUdAUYU9FPV9wh6BvhS7rLjpmrvyP75HDAmBiNuSq7YHsDpqahozlnVEe6Mc2zbfnE/fak9IsuRf667vZtqv6zaTwG+5bH08IEGYuhBt/UC9GZ9vdr3IB0SBDjrDn5XCqyuTrwPTTFsbnKfUYYE+OkBOZNBbgs5E/Q9EsorLE1GPlQkAvhASOD5z0Hwi28O+tFo0uN+kTa+jIZQkym3
*/