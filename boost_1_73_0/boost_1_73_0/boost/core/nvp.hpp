/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#include <boost/core/addressof.hpp>
#include <boost/config.hpp>

namespace boost {
namespace serialization {

template<class T>
class nvp {
public:
    nvp(const char* n, T& v) BOOST_NOEXCEPT
        : n_(n)
        , v_(boost::addressof(v)) { }

    const char* name() const BOOST_NOEXCEPT {
        return n_;
    }

    T& value() const BOOST_NOEXCEPT {
        return *v_;
    }

    const T& const_value() const BOOST_NOEXCEPT {
        return *v_;
    }

private:
    const char* n_;
    T* v_;
};

template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) BOOST_NOEXCEPT
{
    return nvp<T>(n, v);
}

} /* serialization */

using serialization::nvp;
using serialization::make_nvp;

} /* boost */

#define BOOST_NVP(v) boost::make_nvp(BOOST_STRINGIZE(v), v)

#endif

/* nvp.hpp
Y46J25hj4jbmmLiNJUzSxhwTtzHHxG3MMXEbcwxyPjRhJvXhiQ3Cv88IasgyY8iHX58/alhSQ+6UlI9MWueihjNqmJhq+eadO991Uf8sKR9vXyOk/75cvfqqpHy8fR0k6X2V3/LOmS7qI0n5yKQuF3Uwo0rt+6c8/bW5IvFM56jA+WS8qJGMGmP9+prOqHFRJwfOx486hFFHWr/1Y756kYtaFzgfP+pQRh1h/T7cveZBF3Vn4Hz8qMMYdaz1m/A=
*/