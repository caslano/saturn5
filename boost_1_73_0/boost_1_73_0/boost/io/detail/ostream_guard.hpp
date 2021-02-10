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
xVhYGQTITnguRqWSXJzPfsVNeI2ZoeFRlTAFV1hiJDTztLc+1Tk8cR0btlhmAlpwdiQnn5u8DRoIQZfw3bCji5is73Tfnvs6gvs24L5O6rhPsB2/bLcxoQkSeymJzSeut6UnQSWCSlJEJQR25gcjOaOWE06oJVXhx1fGF+l/HaultAyVZD2fV2U4pkgbjoC33Bx6wH4kRhBT0wvifCMuWtarlbCdGYzcRajphcg3J4DE9SIMLyjIhYO9w5WXNaJNi0Fy5ZpMNl36XUKnI7Bz9/7lCwMQidfIGULyEoLgzU98nSuYeX+PzzjEFsIQYiE25QifmoXYST+apsd+NL0SfrTwo4UfLfxoTlH2B/vRszGIZOesZFkNQ0Amv5C5E9i7NWpa/dbq0MFnGZZaVWo1PdO7WQTa/bxoJ1aauAe6HW/ZW7XSJDBPYF66Me/5YR+OfTwRPN1m8HQdp06EVrcSWpUmti+LMKsIs2YwzDp73kXQSDo86M2d5J82NsA/g4gNw2LDML/TlDfaMMwxE/ESy8nIhOblQesMz2/EVuF0e+kbBXH4DF3z4njzBne7OCTxM52KSPORc55OnItPpWTJZU9N6GjaZZ/Yo8cZfQlvXZzxE467cNy3u+OEz3MqAut2GJkQECYgLIMQJg4q
*/