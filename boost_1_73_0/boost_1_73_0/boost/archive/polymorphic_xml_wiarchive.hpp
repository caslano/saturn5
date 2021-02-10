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
k74q9aiwpFod/WTB4k6QVGXH8LSPtkZEWSzydSKKxZhten8ns0HsX9LwYhlQnOSbQ8x8/PoRwxeOtRshNxgYCSSfapBfndvaBrmypMLYujbDUIRZcnvTAYVwnUa+ySJc9JBxJ7eUUly75seiGVvjrjw1trFFHO70dPliu4tfx3AAUPUoJr87GGAccH0pORn3SGBgSlWJPWl7FE+xwSIKZvuNDndhE2+Ak+SAtyZ+a/JpZ+wS/Qhitvd/UEsDBAoAAAAIAC1nSlL63WBNXQgAAFATAAAZAAkAY3VybC1tYXN0ZXIvZG9jcy9IVFRQMi5tZFVUBQABtkgkYK1YYW/bOBL9zl9B7JdNitjJtnvoIsB9SNvsboDUMWp3e4viENMSZfFCiTqSiuN/f2+Gkiy77uIOuABBHIkczryZeW/o35fL+eVruTWxlFnrrfj70Y8QX39PaxaNzv55VsbYhOvLy+12O/VFNtG5ic5Pnd9c4l/6ffu3n6+m8SWei6+0+LXUL41Vptb5fneuaqPttFQvL9OgL3nd5bkQ71pjc9l47fW/WxNM1EFMvv0RUk5kveFt/Pmh0fVicX8hrVl7HYK9kO+cN/WGH84Wiwv5W90u7/G3WuucP2ydLfBaOi8XWanqWlvYkgkLJWu9lbp2
*/