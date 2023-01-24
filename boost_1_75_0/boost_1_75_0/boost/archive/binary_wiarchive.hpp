#ifndef BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP
#define BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <istream> // wistream
#include <boost/archive/binary_iarchive_impl.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost {
namespace archive {

class binary_wiarchive :
    public binary_iarchive_impl<
        binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
    >
{
public:
    binary_wiarchive(std::wistream & is, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(is, flags)
    {}
    binary_wiarchive(std::wstreambuf & bsb, unsigned int flags = 0) :
        binary_iarchive_impl<
            binary_wiarchive, std::wistream::char_type, std::wistream::traits_type
        >(bsb, flags)
    {}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::binary_wiarchive)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_BINARY_WIARCHIVE_HPP

/* binary_wiarchive.hpp
2JY3KcLM36ex62vxAgG8vsA5EMoqA7/5BlZrd0iypW/6WOzdyTKxxQPQPU/s0CgG2J1NfFOnPrtQGyBv24viuxrkahpNrD0styvr3VxzdCGd7rt0T4OamcGzd+jHRfvjuBQAT4PBW3dQaDAY/dp7Guh8NTv7ho7j1gadnexQM/jiBt9hKLmqXmV/fsPHsiMbqM+fT4oQO628F5nnDZ1tT71BbDvhK2VPvEHs+XQa+3KN/sR0CRRXBhN75kCSTX5DZ89+9gi2eGCeO4YXYVlUM01TN+AxqIxyUGt018STJ+kkuLiNydxc7z7fkHjBnwDDzzv1klC9JIPibYbZxsy2zc6MPO+2N3gDISXtNcVlxR1cFZoVV5FndpRGSHtrvAFKDZ7rBHBIVpylIS+Y4KWOyoCJkrNRAQcRB1WLibgayeXFqJ7vs7zmbp8v8HU7KAXkL6O5ZH0BcbNzCgXN+34mlD7SXJqpt/sMS/o3l4zXS97FkrbNJQ9ACd+OwOs79JN/T2L+hx2+OQwWvS7e1KjP4eEd+hwe2EFzOMFXyv66wzeHHfP0OaxWGn1zeBJjjxbv8JvDJ3f45rAOy/7W3mTwGjBWWUoYe82XYe4NgK0YjT1va2WMKa5GlsAIXmsy2H8BcV4L9ZREk3uMiXfrhezJKFfzTMoxltARr7FAVzHXxDJy0auY9FODWrSm073illyozUdQkxhLiLStFK92
*/