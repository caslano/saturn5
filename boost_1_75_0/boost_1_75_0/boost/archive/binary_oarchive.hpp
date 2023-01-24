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
oOtyaZR+w7WvvJe4782n1W3eo63uHRuQw7dVlpyeDc0GvKHR51n85ijW5eujcOc16rx55c/+s+DTyoM3YFhTVRVxwAe2EvuX6wUEd4ecSvYU71iI739X27s3W8NoxAprWHLNoGKwiHngHRbxqbtbxK7ehfhEAYXnINm6/wnUTNv50DfauqdkDPMBgDzN1o1TXLi0hUiC5EuuPmjxenAGmg7re+MivLZrG1m8204g8TMA4DyLxm7fxv9m7J5qYez+4e+asXtKM3ZjctHYrfI3dm3gQfUo8rd1w4AtytfCyuUkBC8dQjo89GG/n427FG3cLM3GzfwfbNxTd7VxT/2qjXv2LhYuEKuZ4K7HYejixhrnpyZ80Em27cV8XF5kfg6eheT6W7UEGCVWuz3Usb+WrEjTXjJqm5dkgrCqtE2y5y5anmBY4gySUQv6LdOOIv5rbdiboo1tzSzRjPTjJTJqgdvgWp0hoxYXBxm1dXIPHzltNPoCmiptK2dzPFLmry+mThMKSttpXCt8hmwVPwSy54RlfQKV4UvkV1ITdFieRXG8BRJbgoZsmVhHj5IhW2ZlI96r17hGy/rpZkN2GL0Ep5HH0Mg39iBzto6suMtkztaAOYt5tABKjC3JndCC2hNvoDlL42xmqdxFqHYyZykB5iyOfs0s5YR7G+nr7bAaHDvxAYBhBvj5aENpTyXYe/lkzpIF+zXRhnAYxjMd
*/