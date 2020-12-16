#ifndef BOOST_ARCHIVE_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <boost/config.hpp>
#include <boost/archive/binary_oarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE binary_oarchive :
    public binary_oarchive_impl<
        binary_oarchive, std::ostream::char_type, std::ostream::traits_type
    >
{
public:
    binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_oarchive, std::ostream::char_type, std::ostream::traits_type
        >(os, flags)
    {
        init(flags);
    }
    binary_oarchive(std::streambuf & bsb, unsigned int flags = 0) :
        binary_oarchive_impl<
            binary_oarchive, std::ostream::char_type, std::ostream::traits_type
        >(bsb, flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::binary_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_OARCHIVE_HPP

/* binary_oarchive.hpp
k5pMna1NngdGqi5uUhbhnYrWMUiPgcEg2NnjEx1Z1+G/Zo6s/mULMRgdAtAOCISmIpFN+TEg6o+YF1KJCGxWXjXXLaTerPTfgR+B/jXp6xBz2HfJsF/dYwz7qP7gPkxzFxPCJxATTYhN+vX7ZGKOgisQIfzdLQ275M/i+XSZEvA/3DfPb/Gx8l+DIUgUUo/OrsdBaY8cM/d3BQs/RcjAQ2vR5gdGrjnR+qmt9A3lLoTtKsv/QHHb9NewvDy/vsKSv+dA+fzXLPlTgFLKyf8s+S9TefvxKyitFi3rKRB7yeGWu2sp7q4UdXdll8TcO9CdFyNn45nd/JIC/zQ94hxEFMbN6xUDqUpMIGESp2TVCsqH4ZcmsAx2tAJ62JNTz2LfLcFafqbMxeY+Gtu4phHVKue4OSq8ZIP+k3FdJPI96+hSk1NkdIQ0E7NLIu5t8LE6/Uu+ApWjreRBTuzOPY/MHXfW3x20a2py56yqEwNGRQWBwgnQmDgUl3+yXnYg8t6rPo6UOiZb6ugqdbREHZ7wr+LmVQgkXMdJWVXMGcoQmMMZOZdohRIZOkvihSV7yNT5NwlpVYZ/KxMCIBO7myQSAfJuu4XUk7Xd2km3VpSu6cRpPwG6UVnBtwDmuOpLuUGK6Qa5Niu3N3D/VX/Va4CBz2TSv/2lYQ7/iOyzTl8CX6dENO9jSntH0ccolH02zAdiejqbN2WIHDdZDz9snsFxHm13fpbCVycEX23eFS3uE/6hv7O7WPl40jdFKzTVFvWTNuaCNYKqG4Bbws4V/D0DZekY3xQjnC+Qb6GyKJ9bzhG8HPtkgu94RI49qAHdsUlkH6JWciNucn3ep8atxY4t2u6SefmRb9YsQ3h97itcGkMBT0GLIHcikjWd/Hp8mhNFj6C79e/5eikp6vJ7kQc/+UmVHaEcWHc9ps7SmnStiOOv7iVvBS9+IhL2q4LRI4n9Jum7l46S0oc9FMZRPS8tcTowTMz+/K+jDZv2qetRs4hpoyBUQ+ajZ5yUqWfGoBRU/FhPa7HsC3hJa6nafBspwpVODZPHMhgNvKsz47n4pNPRmsT+WQNQE56ss1ql56ZHoHIfWtbrcJs1qJEnT3ObNVSbO0E4+rsDNgyJ7Qj2MIhnUtKm8ix0qwo+sD5ZNimoM8CBosoAtpMgFqNEBjtimfCxvHJdg1VUirF/+Vgpxu4hJ0VyrjFb2HpK7i84URxf3/AHWtal9ictU5Hi9D7Cqy3OrfXYVeZZb4W5/etXsqdvIhL9IYvHi2a7FBPYhzQkr18m+oQkpyHiO2cRHysvEsXbhV6p2JTWNSXzfa71VjLj15aQPxC0w/XrG7/AcakaxmQ6dh2kd5cuVvqq4uu+JkBFfjfJwTgFlGY8/DBkYy6FcQY1dZ+TKPJS/p5dpoP7OA4G4k/LHXO6aDLlTkhO9V2RkdvHSRvsbHGQgJ+DXFBk4h1RrwGxlMgAaC93R+uMC24hpbR2kGiCcB1+Klh4rxjHTNiJjTU7ImiM9hIrXyXjgqLjsmcDS3uvEwFi50UkQBR9VWy3zSvltWfrPuwysfYE4SGTK2wOUsQlRnApaGYfYF1O4qn8Y8n+aYcgwCfmFAcwzcooVBDrtF1ECL4EQvATvd/nmHxKN4FyBegOC1BrANHW/9MK0JV3ENAj3NpdppvBu/n3w1yPlG8p5fWj4I6U+xDvimjlPuRPK8o8STVBQhn3Ib2j+BW3YIVMyNJv+CRPBhVFk/jhN8x37Dr3r0Kgv/EHc7D5s+hS/ms6bS/ze0fp38+W+X2qbD6VL/P+CxpR3qNv/ky9/458rzjE+68BX+kyA36jM5T+k9+o/84dCj4+VP0rAK/ieRjwd4c=
*/