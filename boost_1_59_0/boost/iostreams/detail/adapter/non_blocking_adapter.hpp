// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED

#include <boost/iostreams/detail/ios.hpp>  // streamsize, seekdir, openmode.
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/write.hpp>

namespace boost { namespace iostreams {

template<typename Device>
class non_blocking_adapter {
public:
    typedef typename char_type_of<Device>::type char_type;
    struct category
        : mode_of<Device>::type, device_tag
        { };
    explicit non_blocking_adapter(Device& dev) : device_(dev) { }
    std::streamsize read(char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = iostreams::read(device_, s + result, n - result);
            if (amt == -1)
                break;
            result += amt;
        }
        return result != 0 ? result : -1;
    }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        std::streamsize result = 0;
        while (result < n) {
            std::streamsize amt = 
                iostreams::write(device_, s + result, n - result);
            // write errors, like EOF on read, need to be handled.
            if (amt == -1)
                break;
            result += amt;
        }
        return result;    
    }
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way,
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out )
    { return iostreams::seek(device_, off, way, which); }
public:
    non_blocking_adapter& operator=(const non_blocking_adapter&);
    Device& device_;
};

} } // End namespace iostreams.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_NON_BLOCKING_ADAPTER_HPP_INCLUDED

/* non_blocking_adapter.hpp
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
*/