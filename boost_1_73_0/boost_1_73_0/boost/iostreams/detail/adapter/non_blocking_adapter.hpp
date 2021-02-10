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
r3Ce/Ymp0ri1hrJ+TniNYz20yvpBodWeCluMgMBhX4IXFJ47tU7FIww/HL3H71Cjn3AWb8PR/j8fDGM+LnVxwurg1F7wGuch/OBhw878VH2yCJoE4IrVadmIdiARM36D86Pjk8Hh4CHPizbvRbfbvWxTBe8oshKrjKFN+NGktnzCo0bS16BGatOMismj+09D1fCrByfRfmkSCNVAauN/UEsDBAoAAAAIAC1nSlLqGj/B6AQAAGEKAAAjAAkAY3VybC1tYXN0ZXIvc2NyaXB0cy9jb250cmlidXRvcnMuc2hVVAUAAbZIJGCtVe9v2zYQ/a6/4qaksJ1KVpJ9KOAmWY0kW4IWThEnCIK6cWmJsrhJpEZScbym//seJTmxh3XBgMo/RB3v3j3y3lFbP0UzISOTeVs7P+7ytujFa1r/prhwdwEftfqdx/bfnafTR2o+CJrg/kKKiJ4jHqc9ejHikbp1xLTNceDG0+kLaSaOmPuLXOBk6oaweFuIO1blUot5Zql73KP93b2fw/3d/d2ATpgUPKex5XLG9Tygg6S2vMvYw0Pf8KOAuCWW92uYq0wYMiq1C6Y5YZyLmEvDE2KGEm5iLWZ4EJJsxikVOafji4+356PfAlpkIkZlaakqMpmq8oQyds9J85iL+wai
*/