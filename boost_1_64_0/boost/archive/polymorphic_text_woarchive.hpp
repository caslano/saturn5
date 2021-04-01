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
5RUrrt3GDAcGTgPphD9p3t6imKrkm+4Xx5c295CL1P9fslyhMBdQUZNJvb1aFx2TleX4GesrPkOUJprqjm87P9HiPdJfhsiGt95T4hKuySn+OadZmnORBUbYT2J9YY+xU7W2Ld02LBSS/VW+3l3xml5DgxFMg3llQWHswhGlYvzbuT1b1S9YiUtULLVardR6jfkcJfmZTze1wI6yonbUCnINVuPHtCquFSq7jkJ8SMXQGvobTuvnD/1Vd0z1n8AeZ834oqHQw19TEvG2gct2iJw8llTb9qlNjL3CJUswpeBOPJPwElM8IQIGhtZubFVQAeh4YsA3tX7LNupMgpGVhrVugPma2Wpu4jV0yOevyMPtBxdrDnePNJTw34YZVDYBvdd0rFQJKAev1dNEtlR7Q080PZ504WlH1DfKcgEMvxyqMPf10RVKmbHwWWcMtpR/Wc3jUeHckottGISdJjlFcu2879mpC/H6sRgx6AqnexPqghGtyCQB+Flm5vlcLVHyRDpQdcrB0XHcSFQFiFsLYaRnXyijdw3McRWwfz4eTJ+oZa6CoqxZ6ieLDg==
*/