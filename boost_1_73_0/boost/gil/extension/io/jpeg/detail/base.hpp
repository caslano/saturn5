//
// Copyright 2010 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>

#include <csetjmp>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4324) //structure was padded due to __declspec(align())
#endif

class jpeg_io_base
{

protected:

    jpeg_error_mgr _jerr;
    jmp_buf        _mark;
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* base.hpp
Y984CHHcSNgk+ImNtg736fqK9cITsKOpi9FmD+Ft08paoIuY49an4HvOgQ0j+NHDECMX4CewPlmO+fIo7OHrH/v4YYhZFkv5HLkI8eY+6NOGDWz4FMSa+2Iefx7jNhuxIHxV57uQw1hRdhH0+/AtEWMsEH83YOxPeEf8vvMXEBf9B/YGNn4pYo9fNzWwS9HmN08W+AsxB49tgu4+Bl8AmqtKmC+L4QNuxFxDrHw7Ykj3XIzh
*/