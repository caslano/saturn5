/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_OSTREAM_GUARD_HPP
#define BOOST_IO_DETAIL_OSTREAM_GUARD_HPP

#include <boost/config.hpp>
#include <iosfwd>

namespace boost {
namespace io {
namespace detail {

template<class Char, class Traits>
class ostream_guard {
public:
    explicit ostream_guard(std::basic_ostream<Char, Traits>& os) BOOST_NOEXCEPT
        : os_(&os) { }

    ~ostream_guard() BOOST_NOEXCEPT_IF(false) {
        if (os_) {
            os_->setstate(std::basic_ostream<Char, Traits>::badbit);
        }
    }

    void release() BOOST_NOEXCEPT {
        os_ = 0;
    }

private:
    ostream_guard(const ostream_guard&);
    ostream_guard& operator=(const ostream_guard&);

    std::basic_ostream<Char, Traits>* os_;
};

} /* detail */
} /* io */
} /* boost */

#endif

/* ostream_guard.hpp
avXxqTWNfNw2FHbtNQgpYVdAnVIbuanLT8Wm1zh5yTyOx6FH3dLQZc29scKiTf0wyE373kFpnCRizSGWDorNVu761fPlm5hVWSMYttf8Bur+USxD2U6fhPDMPnAwkkwnXjCV9EIO+JOXkx7ywTbCMk5dKcUTIJrQlZkxr2UJMCulnQ/IZyK+Ruu8SxyEsxUMB98TBhYdfElu6aKO/DG/xUpAKzzBIHM42WNpulLa07FGNGwZO+9UWDli/+Djv3mx6ZO31MuDcXKEfZAOeynx9VHJtbZ32N9Xzu4cKd+6vBN82tPtzm11e/UDPNTJWXkW6Sla0mxkLCMB+jZh73YtflZ9vNhbPxVsgaFFATLoOk2aIWgqm8MjVdV8TjseATu9ZOQ7m5ZOt3x6b9vr4VFe32eXVSxb6sZQV+0mGhILT7579F9WLE0+tmbA9ccDrtqknvBYhaZ77XQ/IV9V9vhaRWI7/UYWi3qY+H0j+B2EVk2imCBWTSLc7TTxaFk8MNSmQ9OVnZVjJMB/FZvbNuKV9VK2TOxJVXvLtxEbLq1XCiGhNORoQc2oSlM6tckCmH0DPfcssTwJzfM7Te4hg7YNrgb85HnWfbTJ6nK9ibMKWAmsTqgovZ/pSjSkfN6O6ZhOk9hZ0RtaS4cfeOvqlYOYwq+K8bH4gdZug642uW3CpYuPTcdr7fWZ1GueUMzr73y0ig0/8HdSl6O40HG0
*/