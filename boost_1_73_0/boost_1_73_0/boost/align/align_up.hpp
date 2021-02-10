/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_UP_HPP
#define BOOST_ALIGN_ALIGN_UP_HPP

#include <boost/align/detail/align_up.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_up(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T((value + (T(alignment) - 1)) & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_up.hpp
c4MtFBCgK3BcGHA+FdRhW5oU97/66kuSjtvCeI3S16uyaSlyi5RIm3XPVOZ6cHAB0bGx7cocL/k8L+Hwg6GmKa9vuiC64wUHggiV9XVV/sMItsthE5hmPpkAISgv9LmYbwCGinXZUgIErhUUhtrVVK5kawT24VjnRRrsDAKrrkZbOD5+mNGKBif6iJqioJALUWU0YFePGKJgLMGNahmlC9WSoG20q1ItXCn9ARWYJ4K8fUcrgIfM4LfIGt8cvn1/eBruixKkimpOTyry+4ERx9gmluiM5YE18uzKVoT01tfcI5RgkhqIQ/LH4/x7XVZKr2e82APSjBvyFyKtXI+85aeJkMCvSPOjHokRGIcHydReltOd1YtRWPjG6paryVy0gHsQI1XlWqO1k6uVYxY1mqSAXHJ3UitCNQ5HJYRqcmtUh/gY8BaRfWqDy5vpDWMXjQ734LQHIR3m5vyT0jncJsx5ox+oWavISVTbYo5xSCTpn4BBDXNi5YjcwIUl0Sl7kiiRWiUUDe2F4Nyu+DwDHWRXIoEErPeouboJrgOqUaWGJw/DC2BawkAFcbJdNWoGIcniS5pWOWjr0qkMhJPhw2rPQegfPbEVbjRERHNkMmb6ThV8CCCy6AV5htx42qqN+MzzWxoVK3fZ+hHU
*/