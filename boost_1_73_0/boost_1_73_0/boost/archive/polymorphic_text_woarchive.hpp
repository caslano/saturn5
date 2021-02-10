#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_woarchive :
    public detail::polymorphic_oarchive_route<text_woarchive>
{
public:
    polymorphic_text_woarchive(std::wostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<text_woarchive>(os, flags)
    {}
    ~polymorphic_text_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_woarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP


/* polymorphic_text_woarchive.hpp
oc90yElxjF7FI8XYPz9RI/FmfnR8QIo6YAQXCppvXGkrFJsQ2lXqozfIm/k4QSeJbV07jy8SAXymfoabJERFZoArcriPRZIblJptC9cDQ6lC2+JYrSJyoI+Q93tvwLrC/O2oEhn48+iEMSX+ZKOqThkjtMnzGNHLiOFPMIX8XIJT9BvWbNPVpkGNwfF8o4TIO5rtoYKrqCyl9U9k8lQMri1wUm8kaA2S1iJgjY5M8gH4ocZGdKkiMKG8i9JOnYG5tRtqUhCdgWgmzeohxLoPwJ4egaeuE4Hjxt2DiHRduzXlYanlvBeqTKlINimB1ABs8WY6yQMknEvBivnnEbAW7Wfqvw7S0m5Xt06EhaQFEWyYsZbgj7jpA3WwdMZLzd/Dk3ZEK6Vk13kiJMBMbzvY7ZYbz5agaosXduwCslHi0SofWnQA0FF77worCWigBZRpPVNG421lDXE1nY6s5Fb6dP5zBsdGGNFF2H0E2tGLR93zWIkIet/Y1tXuIer572wstc1juKAGaLfdNgMgiRF+ZESScziLLqTcmsWy20J6cUKr326vFHlIfkqapacAg6exaaxNTmX3qXyhcB5YFwN37XJ2F+MxDe+gj93BPAfMBz7J6fv5YBoydYX/vXgsiQM3YzIW+wtpU2GsAwDq
*/