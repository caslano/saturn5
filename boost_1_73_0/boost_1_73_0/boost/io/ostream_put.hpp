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
aFQB2Z8iNKa34alOoGJwrrbFhAKTtZEQAc3Wts/g/Onafaj4bL5lrlEpdpZqVer5uGwQ4nhDcPaaaUmW10JNts15NtJ9WnKB3DvlUM8t+z/i6XZXT6e/5Rz79kX9vIJEIR3Ml3ejP1VsrXSNMi6GDz1M9HdFxiON0KRD6F+xivqXGRxCvVAtK9+yNk4qtqRtUyiNeuQGcr2aKmrP/FfrV/WkPSjoKMgkZpVCPqYfXWyCbJLAaNMiMQflSsCM4peqZoasa+SFs0oSp1WT7GCuU3S6elMzOK1e0e9dv4JuQE5xapRxMXzoYQLySQqhSYfQv2IV3FyCCtWy8i1r4+TnkTRKox65gahTU/uRyp1FrUYZF9unBib6p7eMRxqhSYfQvwIVrPtxbf2qnrR+BR0F546aGyufj+lHF5vg/NFxK5XVIjEH5UrAc0jhPVXADFnXyAufRzpvo/9+P/5/iqBziVmlkI/nVwub4HySwGjTIjEHjhLh/9Kz3zmOM7ImEcn/HLcu+n+b6uOG4SKWa3Na6bRfAFBLAwQKAAAACAAtZ0pSwbhVe34HAABIjwAAMQAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM3L2xpYi9saWJjdXJsLnRtcGxVVAUAAbZIJGDt
*/