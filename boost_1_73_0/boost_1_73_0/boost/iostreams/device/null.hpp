// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Inspired by Daryle Walker's nullbuf from his More I/O submission.

#ifndef BOOST_IOSTREAMS_NULL_HPP_INCLUDED
#define BOOST_IOSTREAMS_NULL_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp> // openmode, streamsize.
#include <boost/iostreams/positioning.hpp>

namespace boost { namespace iostreams {

template<typename Ch, typename Mode>
class basic_null_device {
public:
    typedef Ch char_type;
    struct category
        : public Mode,
          public device_tag,
          public closable_tag
        { };
    std::streamsize read(Ch*, std::streamsize) { return -1; }
    std::streamsize write(const Ch*, std::streamsize n) { return n; }
    std::streampos seek( stream_offset, BOOST_IOS::seekdir,
                         BOOST_IOS::openmode = 
                             BOOST_IOS::in | BOOST_IOS::out ) 
    { return -1; }
    void close() { }
    void close(BOOST_IOS::openmode) { }
};

template<typename Ch>
struct basic_null_source : private basic_null_device<Ch, input> {
    typedef Ch          char_type;
    typedef source_tag  category;
    using basic_null_device<Ch, input>::read;
    using basic_null_device<Ch, input>::close;
};

typedef basic_null_source<char>     null_source;
typedef basic_null_source<wchar_t>  wnull_source;

template<typename Ch>
struct basic_null_sink : private basic_null_device<Ch, output> {
    typedef Ch        char_type;
    typedef sink_tag  category;
    using basic_null_device<Ch, output>::write;
    using basic_null_device<Ch, output>::close;
};

typedef basic_null_sink<char>     null_sink;
typedef basic_null_sink<wchar_t>  wnull_sink;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_NULL_HPP_INCLUDED

/* null.hpp
ZFkE3NpluVRRW//s/vrrYTP+6acmdbsYBEGTAiu6c+qSc1SrfDIQ2W+MnOPueedTzz+66p8d++Pri95hwVPOFLYfV5Oj085l79g/6x+NDtuGXUXMqQgtYmV6E4oCik/MjpzqC8kLinmupUG/GrkoPlxrvM19EN3MGl3Xd/AgkdQ8stoBQ0Mf93TxgZpf89vwa9OadbdM+NIM1YiBlzODejElJ6oWve45DnRZkHBX3+k/i9rFcNQf94cDH/d/76KHn8EYPnvcO5TZg0ihPpCo1iyeTgqLF5yFT/anIdgAiYM/4U5rYV0nysW7orH6eFqirPcf7I4QkyWfqhSwuOw9L0ZwU8wO3Lb7bpd68ApTgqWOQdpo4C0G9mZeLlcFCThtzbieyW0xz1x0Vd9NwouDL8wSpwi8y5eZNJmjYBZlPahrLVPSLzerxC1KpcvcLRQ5ahShTVIJRiBMjrk2qgRTcfbcAOEjPZ7N1uSpqGPi8mo0XuRcJ4hisgt+aRQHzn4UCUSQobAMx4gzDQgVtBGo0FpGrrb93W9h+5PB+udVv3vae46vOLimykKhW9qFHLaXYZSiDfBMtZHw/xl4FXkzsw7MzApYJ90VSoCkhRvOqXzPmXLNWr+nMl4mWxyEhmp1F3iqCLwqBaeofWe4
*/