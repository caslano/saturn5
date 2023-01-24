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
nvkkq/CvLfOoR6niTX+dlgk5hmQT+Ck9PlncUJNTg7mDHFNPr7Dc4ZWTkcviZhnlhcRkZK3rX9YGND1KPwvu1CyUUI2EXrIt7EpsB/55sey8KGzZ31m9K73KlW0bzIBl+Fokhs+KvUDFbAk/5SJ+j14qPl7TJig5ryDpN09rfxR/lNTVDvNmKYt/jIQ7T6RfG+WmVYwFyoNQSunhe9817ZGTnC7bZBQ0JrOH/G4UGmczJFiPGl0pcBClE1VdC4pBgoF/RcnJlmRAZXdQm8zje7Wv5AkGyoKv3c5f1M6KrGrKFjHNgbQj+Ge1jsqvt66FAhPMBKJ13VhchVk9TdFX6aDmR2R1PVH1Sp+uiVgs2OFJM8XnnLpLvDRqZWKGQR333iKl4PqSBjS/MnaXVzojlANkrjuBO80cqRqvZ6bc6YYpVD27HLniv0BxFItwVN6XZ6YAWkoc39J3/hVcYwnksE80bv+in/q9HlZ5ceGLuNAZ+pXK5ynDFA/2zxlL3EZoNPrNgifK+KTmkp1p6adtJz3oUgxfOxHsh7fo8EGdab2U9BY0f7x4OZa8myn5KS3llIbVdsp3ANzhNUA96rkZ0m6b6seRUDK7VMHB7BbovXnIwPr5TZIzjuATvV3yV180PupiHINTdQLdMk9tc2a1/J8e3XX5Y/j+iYaM0qOei6pTvN3fPy6+Kt8F8wctTlEMN6V6/8DJjuh6XWW0
*/