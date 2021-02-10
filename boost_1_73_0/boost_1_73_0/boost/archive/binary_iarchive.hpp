#ifndef BOOST_ARCHIVE_BINARY_IARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from binary_iarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE binary_iarchive :
    public binary_iarchive_impl<
        boost::archive::binary_iarchive,
        std::istream::char_type,
        std::istream::traits_type
    >{
public:
    binary_iarchive(std::istream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(is, flags)
    {
        init(flags);
    }
    binary_iarchive(std::streambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_iarchive, std::istream::char_type, std::istream::traits_type
        >(bsb, flags)
    {
        init(flags);
    }
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_iarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::archive::binary_iarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_IARCHIVE_HPP

/* binary_iarchive.hpp
9AF8moTouIFiGa/NhHgN8IYRgqSnH2LI6Hu674kUQ8rkMHIgahmh4wA8YcCtKxEvrRDqN13EnQ53Xt15m6feiMbE1fM1QkN605jNiga9RlyJa/Frwb9DPea+NJvWyxMFrHOTgQJKVymtgaDIy6GyY/e/D3fiSC1Dy6TYz51o2dhotMHts6MAU8VjT490x0v4sKWrbfKWjhYTkDUYFm4Oqm4h5wXa0wE4pAeeXWrvoDdz7b0vDEVVDzehPODRvN+CIaKK9Y83e+vzji/845/f1ldebYSHYO4h1D6iTMI9MUEAIS7ogwNqAoAEC8n/aik0CnEf+4umLeVU1JAMIYNUTaZqg8WgYq22+tMYcx1mkom449XgUD24eADN9g9yFMA9o/jaqDvhgUe6IbjsuSdXLtqT4U2p4X5xXq46EVt9xljYgHkaen9UkQfx2Mn93gSaWorOsblJ2OeWR02MgTYdk5gZbn0ihIC2U40uIBmYazEcqeIF2bpYTQSWKjmNnAqyaXvRsi5CQ6ASolvV7cq8wZslN86qL/99//j5/W9vfv7Px2dzEeXlSEQz5J28zRC3Yzn5V03pf+JgqtCcqIVH1bQmJgfZRRuz6E3+hVnsUemyItSDfhRM3LyBYakPITlYRnJUzF4bssRoCLak
*/