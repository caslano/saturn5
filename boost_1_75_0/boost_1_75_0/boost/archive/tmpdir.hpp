#ifndef BOOST_ARCHIVE_TMPDIR_HPP
#define BOOST_ARCHIVE_TMPDIR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// tmpdir.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstdlib> // getenv
#include <cstddef> // NULL
//#include <boost/assert.hpp>

#include <boost/config.hpp>
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std {
    using ::getenv;
}
#endif

namespace boost {
namespace archive {

inline const char * tmpdir(){
    const char *dirname;
    dirname = std::getenv("TMP");
    if(NULL == dirname)
        dirname = std::getenv("TMPDIR");
    if(NULL == dirname)
        dirname = std::getenv("TEMP");
    if(NULL == dirname){
        //BOOST_ASSERT(false); // no temp directory found
        dirname = ".";
    }
    return dirname;
}

} // archive
} // boost

#endif // BOOST_ARCHIVE_TMPDIR_HPP

/* tmpdir.hpp
nWUAYEUL9DAYg9PYMKA+lb/fvlELMaFkXOIj2gt5TGumI3ekEIS/I4ZHmuGWZnqGt8FoHHwI/Ai54P8AG9PK1r6rSUUHKGGdNILr5+sEp7O/vS8Irge16n3UZpiRyrzfkHXAl8J2xY7pldmpIl10i6RGn+h+1E5QvLO54qFYQXEMIvDMb77/DuC2LrMyyq3isQyXFjeqvnRXSNvCZ2XSc/1WGGWg6UReV09imFWNZtfjKFBTFX7ZOj6eBvvEBjHPr/wNLcmwuArpKeNNcH1msMNUGcXiqzpQT174I+21XD5crt8qL7n23NOgpqbiKfTd+N5d3U1fG5zrRfdFuemDAJy1zfc00JdHc5Ioeg+F73kSYOpurFHpylFFjLQZt2Paehsm148A8IbE7sYWknME4JjBDgxFJy2S0u9RektvfGo9gncl8uAfez3GZDjqUM1yO4dqAmtabSu5Jr8BKiF2JD7udttD6MnCGxijY27ST4Ywe6Q6POfPQWEs6jF8IJI4l8JEQLkAZ2MdK5s0gh5Tqrlz09jCUfhxIFa7thM0Uo7ZAfaCczekPVaTN8I92+SZHqKEnqsOClt6OESxhAQmzfWMbYDdwbEFKsWOlFzFO/HTXPbehuZH8O7gSgudw+eDodDBguW2SXI0ztjEnUiMcznooc4mekwF65b6fBBKZqidDQB8Hct5L6pafJeqJr+qWM6v7WggvY4dQNKh
*/