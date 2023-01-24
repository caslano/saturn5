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
CXpIXn1FvZ3LFrxUkDUj6OK693E5v86NPcBeVPRnj4dPk6pS9N4yKW+cnSjTVVaeFHx/S55QAm2930xJaaK86dG9hn1lRsrBJSBF/4ESlfuTVTTXS0d/kcHMueqCWtXvoWC5AH+oapptoaODf7HinNdYfjiLeFrviLgHQ1Rdvj9/qED67SLSvFkshkgc7d06d268LkE99OSP6Q0n37+PCRV7QQ3TXAv2x2cV31u8d2HejDr33GsFDgnIef4AJ/2JH7uGTsSWsNbhjzZTwAv9POOaIMLmr+PrLGNdClZpEtdTywwF54XHouoqquuzyFn0wNSPFGv6K59TtwkVVX1e/5oD5iEH+8zOtFBpDrhP6+EQ6V4gp4o8Z0mpijcu7muIvCyQxfjVZ1g7E3Qhw35Am5QZ685DgAs+4Mk5NGFgKqmA+HfibxWOWQt6mKK3cZX0a9r2ytfFeGiwNM2JtWe+3Gy9NSG5u0qvg1sdNwjIY48uww1JgAjUMq9Oo8ENeRKzvLRr6ByXR4ChzODWICXUgOQaFE1xULLMEqB8ZSz7iAXH6VLspuBK23mc4op+vEKlQLynQDiTeyXEIyecLp+FxdvIRFNhuL2Ar/Ub4hk8zgQ+/94Di1FwiJXvDXALGfrJlF5P6YkFOBt76KcZWApXlZMIaY73h/EKsZHsJqqcZDgN+dcoPS7MmbYKNAxnOI5zHRJzx3rLADm1yPOf
*/