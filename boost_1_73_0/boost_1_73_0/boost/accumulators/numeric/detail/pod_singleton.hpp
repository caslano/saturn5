// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP
# define BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

namespace boost { namespace detail {

template<typename T>
struct pod_singleton
{
    static T instance;
};

template<typename T>
T pod_singleton<T>::instance;

}} // namespace boost::detail

#endif // BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

/* pod_singleton.hpp
E2bEj/THxva+fKQ8caa4vjvd379ffm6CK+/Lb5YwSJbwFVvjg79fYDWdUxPIqnXKzIcyLfT8mdFlOm7ew19UE/jvIsvwOurHLJsqNBb4GNuyX9iB4XBdCLPQFhVfcedPIC52ny/3H9+zq5YUavbspRCSFGO0yBf88whLYh+O3aZKsaUWPtha4U1s/BsgEclywYXXR+Bw6WsBw9CXgUK8bsgdbC5ETWjKRqMtanY9m6iJzU2MOLd+u5AW2NTCiqE=
*/