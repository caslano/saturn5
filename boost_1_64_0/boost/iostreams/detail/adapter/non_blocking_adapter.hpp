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
X6GGTuxIotbTbUYn4/rlsd1ab48MibJEfZTURKbvPN0db2TYDSMJLmvWNqGA2qHAyOClFPzFNUqilCKTUDyuRf8AO8Ueb5cezRSmL1ErPAyaiemltqazgkwI4KQdp/6hlxHHPO68T6E8hXMfLb602dsa/Jiau86Z066mVugs6WrkWGTbPPSASdZQ0ge44OH3b3K8ZK7xUKtweY4Y56LSGWX6x6MDoZ447+Yhsb5KqnxZWicd4Kqv7ZFLl/1a66nuxLV2AwKkdUKwO3iWjEAjcwwGSjiXqVgrmcZhNIKey61BBya41UkkyszOD57m5h+M1CXbKxb+AqhRV+Zslhf2X5prQwiAaz9+2pIAWvBRyDQjZZdP+V23w35W1m6y6UfqmRY74txSDd67wWgjPZT8SJPFvOHtS3l5UWDDRuDlFgY2gPjZF64EZEK8cfCmu1MaZeL/cFnSNADLskpu+5OCLJ2Ac9oBdL63FFu4uyNR3XdwWKZeS0oMOVhB6zM6p56TwrOlr09pZxYBs2q2PfFNxmxx6nJGFaJ8zka8In8IsHDSFzBQuny9duUdQg==
*/