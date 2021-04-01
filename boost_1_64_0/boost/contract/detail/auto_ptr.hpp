
#ifndef BOOST_CONTRACT_DETAIL_AUTO_PTR_HPP_
#define BOOST_CONTRACT_DETAIL_AUTO_PTR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/operator_safe_bool.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/config.hpp>

namespace boost { namespace contract { namespace detail {

// Using this instead of std::auto_ptr because std::auto_ptr will be removed in
// C++17 (this library always uses release() to avoid ownership issues).
template<typename T>
class auto_ptr { // Copyable (using default copy operations).
public:
    explicit auto_ptr(T* ptr = 0) : ptr_(ptr) {}

    ~auto_ptr() BOOST_NOEXCEPT_IF(false) { delete ptr_; }

    T* release() {
        T* ptr = ptr_;
        ptr_ = 0;
        return ptr;
    }

    T& operator*() {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }
    
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(ptr_);
        return *ptr_;
    }

    T* operator->() { return ptr_; }
    T const* operator->() const { return ptr_; }

    BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(auto_ptr<T>, !!ptr_)

private:
    T* ptr_;
};

} } } // namespace

#endif // #include guard


/* auto_ptr.hpp
+eoCKYDxi/8fvLt++7p7LnsEujY3pZ5n2Ar/Fb3buqfUgs0fRIGXVBVYAt0wGgXZEvEcEgUAnc7H2L8CTqThjibDBzH3CtS7DFetidr4aHHwfeTYQlNkCbBV5uS0J+46EukYDMFKZmCDqX0ekXhnU+a8wPaqixz4uGLOPKrfN0Gl4Ur6WzifJLI9aFu4+MpNGK0roEuFlmQSfEO+wD1a+z5UxpCQ1tsxh9MmVuaXuo4hwkzwidLW01wM5XRQc9dFSFLuohP1+1YOKtfAJ3/z9ZZtCxqW/NNONAz04wvnMRgSSMx569lw2OlUggQMVubbKL/NK5nBZipfA8bhI4z0WapJnhchMrAEQcmD9oUGJI/N52vtHy4kYmLgWriFLe+ptzRzsROuplY31MBPR5YZqGs/2wPOzYQ4tztk53C2FGoExsdShTiIyoUvv2qDFyYWk0s5v1cwbnx1DzSfPZHzn0wgNuqxRCtdDrQ655fSVf1QFF5f165Bywt0izgbN+I/feivz5YHAKlpUEg96osnEyHNIzThbryUnvH3goZEKdUZjmRJKbyXYWFTLw==
*/