/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_OSTREAM_PUT_HPP
#define BOOST_IO_OSTREAM_PUT_HPP

#include <boost/io/detail/buffer_fill.hpp>
#include <boost/io/detail/ostream_guard.hpp>

namespace boost {
namespace io {

template<class charT, class traits>
inline std::basic_ostream<charT, traits>&
ostream_put(std::basic_ostream<charT, traits>& os, const charT* data,
    std::size_t size)
{
    typedef std::basic_ostream<charT, traits> stream;
    detail::ostream_guard<charT, traits> guard(os);
    typename stream::sentry entry(os);
    if (entry) {
        std::basic_streambuf<charT, traits>& buf = *os.rdbuf();
        std::size_t width = static_cast<std::size_t>(os.width());
        if (width <= size) {
            if (static_cast<std::size_t>(buf.sputn(data, size)) != size) {
                return os;
            }
        } else if ((os.flags() & stream::adjustfield) == stream::left) {
            if (static_cast<std::size_t>(buf.sputn(data, size)) != size ||
                !detail::buffer_fill(buf, os.fill(), width - size)) {
                return os;
            }
        } else if (!detail::buffer_fill(buf, os.fill(), width - size) ||
            static_cast<std::size_t>(buf.sputn(data, size)) != size) {
            return os;
        }
        os.width(0);
    }
    guard.release();
    return os;
}

} /* io */
} /* boost */

#endif

/* ostream_put.hpp
fPkt9vLdK9eHQj5VftUO5W6S7ezAd42sr0P9+uT6UMinyq/Fodwi2e8/sucrlP2efCr5CuT6IF9cG/nlk69/G/29T8Gn6ndrFXyq/rRBwadqv00OfEDGDOUcMcAA8skxQ/sytmMKsD8QxHQgh3RDmC6N6YbJdmM6lVwTpfx9DvlPZv5nM/9zpHR1DulmMt0spsuU7eUg1/2yvT62z7+e+f+a+f9GtpdDuv1M9yjTHZDtxXT922gvPge+QkmOWgc5llOOFZSjRErX6JDuMqarYDqvKRffewI8ju0EpOBTtZMMB743ZLs58OXIdrPlA8p2M/gU+p9C/QcBk4GnSukaHNKNYLqRTDdK9kcznXM70T6xz38q85/G/DOkdKkO6eYy3Tymmy/b30zn3E7yVfkHxYx+hPn/Vm73DumeYLqDTPek3H+a6ZzbSYOCT9VOmhzkKKUcqylHmVwfx+3TrWe6Kqa7nOl85ngFbM10cgzpu5huBzAaeDewN3An0MOY8gMYU34gY9EPZiz6M3h+Is+fBfwJcApwF3Aejxv316mUf6/i/vo7vL++FpjAGOF9gVuBqcDvA8cBa4BTgbcBpzP2/wxgNfB84A+AlwJvBBYAbwKWM93VTHcN023i3gJbgduBN/L4TeS/l/x7eDxFf4bEep0JoCyQF1QD2gc6AjoBSsWawFkgPe7wlIGdtSwQ4w/bxh6eq4g/3Lo/OAZxcPxha+zhIyBVzGF1vOHgGMNtxxd2E1uYcYXlmMJyPGE5ljBiCMvxg9Wxg/esi0bsYEvMYMYLRrqYzowZHBwvWB0rWI4TPPBRyIT8933XOUZwdI4cG9g5LnAjfjeD3kK+G2BXxgVmPOCTMYBTcpEO5434v1Mgy2aX8X9fg85SDGBl/N8s5FcOUscAtsT+ZdxfM+Yv4/0qYv06xPmNB29wrN9W2MEpvm+NGdPXGs83dn10yDF924rnWweS4vcqY/fKcXt343sp2vNW0G7QIVAzSI8TMwm0FOQD7QQdBDWD4p9AHwHKBXlB20B7QEdAraCBBxGTF7QUVAWqBu0GHQS9BdKeBA8oA1QE2gzaBToIehcU8xTsBJoLKgVVg+pAh0GtoNSnEUcYtBRUBdoG2gM6DDoBSjmE86B8kA+0E3QQ9C4o9hnIDloC8oK2gepAh0DNoNhnEW8YlAXygmpAe579asYV/lfH/1tZUVxQVJm3vqRMDwAYXvy/QVpMwpvxGvqKrLyZ0xcsmDF95rl5mQsvmJd9/kKNMezu82jcb1/sUSQ+fahrIqgXbhZa/irG8GdmX5SVe35e7tzszOmz8gohfhm20dOXoXIfvSHR3K9c/d6J+US5fk+B/Iw9t5H/5ITjIj32AEsOnNe0lLH35DWvcZA7/j2V3LAOKiCvpAh2hMya7TtPpo+S+Jap3hmBz51ecYZeILwb4Hsx/kbe0Mmsi8PUqSvIwLfhB+kqnVbgrUrh2oqK4jIv9HIhx+QEkQ++NyYF2nJLZ9qQCWJBvWHLDJtyQ6n/DJd2sqv/2ZQ5b3CgzJujzfEB831pAmTOUsiMN08lFNqVzMjDfM/UW7w7puPbvPvOCkNHYy9QlINjLIe6Z9nUV24Xc4zD3zZ0fqQvV+kOtVcxXsLJd5b6Qfzm+7e1It1AhS2Yp/Q+eLuL92HUk+8NWRb0uYL6JA0N1KeV+mRQn2mgnXocSDt9GOPA0EdjGYnU516Rbqw2StqT8554d7Lrcj5COfsGyVnHhmlk0Bt0AwpsUcmp9+lCWIvd1f1kiD4UbNtjNrat78ZxJ9p2BqgfeOLfV8m8tixvTVlhMW2bKGQWB0zbJot0X9eGowyrHsyX78ffE21Hb3zqdkPeNus=
*/