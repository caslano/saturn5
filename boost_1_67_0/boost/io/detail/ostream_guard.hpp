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
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
*/