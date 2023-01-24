
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
bNvlNwfkdOhJhF1Fw6ccZgqShOjypwyXuotz5w1VtlS+Y/d+Mlx4I8Y2X3o/o9c2FZfKuEapviuxGMPKja71B4Gu4qntSRKZGhoFycJtGnYfcnKPeExOkkmFvq0RdHxJ126S5Jj+UTWzuOtzx0WqrGNlEOp4ddzKcV4jQ+DT8wflTSShUbb05iLmlL3nKR1TLIT1bzRixgSkz5OvOd5LVNY7E8F1aKB14wVtu7fsMpr92AH14iAyck7CSllhEeeKzfTBmG3UzmskxOnXSJwOuBsvccKL2Esm0JO4e405swgjfVjyIuv9PW7O5vup6+MuOx+MPMF3dMNt5rOMz2wHzLQ+T7vUFW2nWHvBgzVUIxycF6VE369dMFE8eLxG+fHC0LkkpxMGXgdnbmVTjWFYePU469cF1zhJDJ6f3D81UTynxbND2kBSk+9ye1uvidxsEjZsS8q6vXP3iVq6JK2261x/YmZ+yDshZWVZmNJbh+SDPU9+9duda/SP6Gy+0u/PWUPYMPWhlg7SFJJlosXPXdt96MraDWGY4vsBycav8o0GZHUIzDeRYzDW015Cn55M2g3rpDUfL18m2F/AyGB+OubgozArgvSPo8U6t7kn975tWtzudmyTxDuB4Tn1Fk1KqW3CejupSKWqk2ejiHWoo2wDLJiEnxJ5h8nGOxFJLciIRp2mmkk/qY0JpXDmJh9JzlRS2/MmSSJns5dU
*/