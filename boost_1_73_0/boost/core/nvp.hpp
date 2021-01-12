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
m6d2cj2i58Z9jXV0mPpJi/Fj2y2tt73lN728oqTI8txzW4i7JnruxuXNd7e6jMPkO5JAwwmEUlqGLW++vc8IOd697X+UflXPr1wk7q/lena15bDbua5j2L72KmvFeJWo49UEDOmlrqRdSl84+Sfe06PPmLNUL0Gezq3T9mTM2uG9j5Xw6uS39kfLYae47eR7DyMcXUfujlulU3LK8ybGjl+7xd0pvvczDcO/fWibG7kFN/ju
*/