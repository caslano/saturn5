#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_oarchive :
    public detail::polymorphic_oarchive_route<binary_oarchive>
{
public:
    polymorphic_binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<binary_oarchive>(os, flags)
    {}
    ~polymorphic_binary_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP


/* polymorphic_binary_oarchive.hpp
M1v7Nz+MEsvUgB35QzcANqOgsAQ9PDmkwLMIA5WFnfqHJereMqXoe7NSJUMgx8tZ8NthY1UuZXlFVBK9GzwcPxwH8NqAfwEuR7bpCiySovzkoi3gM1oIYlOcS54+C945ay1WDTvlOxAm4lrol//c/JyYMkb/q4SrTpNZ/SoIBvr/C402CXxeBW+D3+PVzzdLPa5dfqja0xO3iyE9B0VaAhIFvrXVCgP9Qzm4+0KXDFtC/HhY7tPbQA03mcLjn4ra3aANYxuIJznaauki0GUuzrqqtPQRmJWvkfx79HFV2ZI4iuL9O1WovYM99MPH9IgRKwfsnWa/mhFBB9YFN06k1xCFxDcW/d9RSBd4zpfjKxwV82qeAQZqTOiXUtcgCd+fNyTRzLdn7PouNO1IyMrqGQGW3ZnHwTaFHYXG3gls3jL0HTceaEX9EYEht4leurt6WZrmp4BO4VxTag5AdFC/6widLcSOvQ7FCaIGy3+VBztGTOPpDjfUrag5EGWvRWgRZJrv61BUNFnuzf6RYYFb/tebyu7ueq9LvkzshEYyaAxRuBp8JnEpAtr8dg==
*/