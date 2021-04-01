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
Y885P9TyR+RVo9dTtP9PYI1Kl5z20rEZXSwydbtXBrNLa48IvGzmeOyW8EZOROIsqwbEPAVvKxhxTpvnrN6zQiH+c3w9544X/0QfRHE+D+wqqAsAj4IFZ+yKveTov9sz22PZGWMMKpKLHhASAO+rtTdMtMzg6RuksrGg8gKE60TK01keBa5BlLASkDn9qkXNyKmNRuVhkfoOXAH2vSzSnj0YB9bSe9poIxee1qGsNgpQFRkfP2yrcJWZOZfgNewxo6f2p40+hlv0BEy3aBsE7DhJHJJO26qLtNR8AP6UZtpkIUHXZW+p0jK9jBu88i6ZvlMCeicJ6FADq8AuP/OXnuxZ9LiQQWxLiXSFAPenrymVYX01QYWoa+CmvP8FTQYgtgYa3lP+fr5xbcC4eYCiqGDn3QTKE0dxDEKERqwertyDchVJBOL51QqPfZKWFsB1uUuq82kdukCbKIK+5fgZujbrfNnak7c+GXVTAcxFGa4s3oq4KfMfWCOt0uqF2Ls+t+6IXhnp/Bs/aA4nueYSZnFyNlVqGSlFXgAjOYG7MXzVJH8NzoN8SNUd5w==
*/