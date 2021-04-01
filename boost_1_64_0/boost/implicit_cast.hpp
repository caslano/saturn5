// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_IMPLICIT_CAST_DWA200356_HPP
#define BOOST_IMPLICIT_CAST_DWA200356_HPP

namespace boost {

namespace detail {

template<class T> struct icast_identity
{
    typedef T type;
};

} // namespace detail

// implementation originally suggested by C. Green in
// http://lists.boost.org/MailArchives/boost/msg00886.php

// The use of identity creates a non-deduced form, so that the
// explicit template argument must be supplied
template <typename T>
inline T implicit_cast (typename boost::detail::icast_identity<T>::type x) {
    return x;
}

} // namespace boost


#endif // BOOST_IMPLICIT_CAST_DWA200356_HPP

/* implicit_cast.hpp
bdBCEgsKpeMfpn8AMb0+IIzgcenbawtpMMUpGMpSqfiP0r1qi92MzSjFsfMDEtpvCUzN8/D8KY8CSWwb/yN8vj8B3yj4FExAsMAbAriX/dHtS34DVuDAYPpQWyePnk0PG7bvuIi6icVdoVSGS9+RU1hfd8rmxbc27o0RGnHxj5xKcyXmkxIjuYx/7u/ppCngd1KXtq07+Fm/iRtAIilw2C3tTboJUGbhN5m+gesyBhGP8czqhY2GSQoFXQF4x/Vkg6Avu1rOFZosNJXhsNOcMsCNinMONRTSXsH1GebEx90wBALuVk7d5vTbhaem9CVL2hpMuVOhcez1nEX/OaZ+Frd2HI4L6tseK+vbZeGkibd3AGOWj2htq66SbifZY2R8TGslvB/FuhKYq7Vvg1HglXQN+Q4wa41zpUASQV8H+J+MGMQITf8x+qT1mrsFnDfWubQTKljso8n9cgmZKMJUhlbyB9FPCqs8WA9P2wbSNCx6/QQKxTg8C4b5p2z9Fxtik984Cd6KkQxp6jFjbqMjQcg2brJBCpB8qYximfcOQPOo2lQFL/0CNnhoMA==
*/