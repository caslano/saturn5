/*
Copyright 2018 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_EXCHANGE_HPP
#define BOOST_CORE_EXCHANGE_HPP

#include <boost/config.hpp>
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <boost/config/workaround.hpp>
#include <utility>
#endif

namespace boost {

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T, class U>
inline T exchange(T& t, const U& u)
{
    T v = t;
    t = u;
    return v;
}
#else
#if BOOST_WORKAROUND(BOOST_MSVC, < 1800)
template<class T, class U>
inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#else
template<class T, class U = T>
BOOST_CXX14_CONSTEXPR inline T exchange(T& t, U&& u)
{
    T v = std::move(t);
    t = std::forward<U>(u);
    return v;
}
#endif
#endif

} /* boost */

#endif

/* exchange.hpp
WjGa++83s0taL3aRfKgMW/Jy5/2ZZ0bB7QDO/rGXF5A6+Oortb8pvvC9F5o36g+emecF0vQLuB8UvMX3bzA1hJ3Ul/QUvknqC5xYqbSz9Y4+p+k3mLslJ+nPkIRvU/qIJ06yk79Q9UMj7koDJxen8PLHH3+AF/Dq/NW5D5dMCl5BbLhc8+bOh3e5PfmlZJ8/B5r/7AM3wKrgQGFSCg1aFWbLGg74uRIZl5rnwDTkXGeNWOM/QoIpORSi4nARzVfj2a8+bEuRlZ2eB9WCLlVb5VCyew4Nz7i4d2pq1hhQBWpA/bnQBnW2RigZoHkOhjcb3akhJ1ilFbB7Jiq2RnPMQGlMrd8Oh1nbVBjJMFeZHmZ9KoLSbI6iWqE3G/YAqjZgFLSa+0D3fdioXBT0jinCw7pdV0KX/s4tNCjzoWpA86rq1KGo4NqFwCHusuXTTajRe2HoTSupydq2VJuDi5jWTlHRNhLNYVrwXq4w8T60MueNvW8T0VvpsmxT/pWS7XzPQUn0CgajGMbxANZMC+3DzTi5jpYJ3IwWi9EsWUF0BaPZqtP3YTy7RGwItNoA/1w3XKMXDYhNXQmeHxj/RzvdC5JruFguJtE8SS+WcRJNF+FvyzBO4DUMXr6B/7YSwf3y+wEMKrGm6sOb4PWb
*/