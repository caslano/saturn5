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
ZpM1hWWcY6CKW2WVhK2ZaC+52jg2tVbiVwRCxxrHO/YivnP90PHqd0DGQHVZtHy5S/509buD/qaheyatQsV6wH1gT9iL0Duz5fF3eyyj7tHIsQxb/6mi/7D1gETPaWFjCVp3rvFy0YlrnLFAXuPPsPdLv+6L5FcfYQ+ka0VnD/UOezhE2YOKa157L6ztRbawamrxUaVa578omQTTOCPxTb5fDOOMxrzKy6Re2l9Z8mNB31ddrY6mcUbSMI2ZGsfTtWxTtvtpUMf0bfvca8Prc+cbJTMDPwcBbWNfb0LfL/aUI2sY93HZmNWCjR32WHQ2RtsF7clyj5fpNlKyyS6/LGnO8TKtYxkHd43DOW0xWwq7UGzxMsLLlKv2Mbct2susWqodXwraoqy72ugb7iIVZ76VQkoTrbYmO5V0ZT1Yvfa30U6RNdmOlENs514l04/vL+JNtkoa0dsqsiY7M9mklk2TdC21HlqhUycqzm1Kbpbl579DLZ97rVhdjxeVXBa16KLt8Cu1bxB72qm1lQ+I59qGMX7CwcSEYsu9tnJIZiQyH9gy8Qla5muXzERk+mYi02GWlvk+JMPvODv/DOIRtklz27h5TLj949rGtU+fl5SNa1vRdt5Rr9PstnPdxiY7l3Hhpu15VHtLbXlSxt0Iq8ir6HGTPU91rinJb+O1lbgmO1Ttp6+XJUomxWTHOn6S/l6PZw3HNWm6fZwDPfk3pPut7OtMRovf5RnWo1T1cPmE0uUN01WDrF29mAynwAXw9Rx+h+lq/JTS4spSy+STmKZfyL3uTSU/Ny6ki6fV70yTLknbfY7JswFp3UBaH6vjJ8SlSVrvq98zbc98vt6+PX2h9ds7PWnvP9IXsA70mXQu+cj9UK9prfKpI59v1fHJcV0ln6/U71+4451g3cqd5BWruz4P71Z5XeEr8vXX68d/8oTyb0idRmkfj32VXKK/vfWez3AtokzGZzZVplrK9BvH2af1uJbfSOs5W/eqPGfjByhAu7bXfgwvV/sv8dvPexdxrM5a5TNd35z5LwnmX8xulf988t9GpbNDXGiO5GhVn20lH+556vhyck4h/1TrbEqiZHXdeR50lomSUC7j9ZOymJ8LHPN/ViqZ04z3eXN80WfIp7IqQ3/T/CHim+8LaeLfcZU6nux7lNw+t7ob5hWZyjCpeHyhSkeXoUyVob3BJ50pPvW3faVJm9xNmySo+GO1TbRRv5NUejmO9HIkPcNa63p+UrqKOwifsR193XynWtf5XrQu9HeyfvP31+3Y5elGH8Y14t+uKvz9QN+zNlFtPt7X3tpP2duCyHcG/Wzwvcp7gW8Auhhu3RxhNyYfqoPVsenG88t1LdX32z+UDj7yL2Lu1KP+bNJiv65XL329t+Q6mSX+Ojuq8u2Bnk/2JftrrCv9o6y2cUG9pOn4PZVe5kk9j0jXelH7l7E/i/trAfegt5K4fnPSJQZmn57Yrk2ib2sWdkfatLZ7msQJdJI10hNm/5AYlxK53rrI5SD3rZ1229l1rjXgtcyoUFpJp1Y1lU4FMp+q/E49xiWjy7SgUaZ/YlyniDJ1F7nEZPZlQv+pbRMCCXsllCRs28afGOCQ8Z7WVPs98hR6xuNVNqnvz7nrbj9n+XOTQ/o6ZZ27XKF2WILMNuQXd8qkNv645IR8CpXatrFM23JsO8KzXYJlel3dGYsrKx3n8MCn5P1U26ha81gf76uOJ+n309Ei7ywH82qlHIPXuxztWijHL0+Gl2MzJd9RlWMY+dCUap7fJAz+DCLcScglzx6EnoRcwvaEfqF98nsHQug5ZIbZT+xwksI2dlHvxKmqFPEptJk8Dxr9VrrmCKrnAJn3K+8=
*/