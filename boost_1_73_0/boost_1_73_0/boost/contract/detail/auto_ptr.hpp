
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
VWp77Jl5fvPsOMsO9H/ZYzk6HPz0ic0b44Ptzmkq+H80Ua87xPEDND90XGL7hlQDePJ6iHvwJq8H6BqvuM11qvtx/IZ0Sw1S/w208zLWXbQ0nq3/kFdbwW5zBd1hDw6Oj/+APXi3f3Bkw4iUjBYQKlquqLi14TQ1lr9zcn/vSHpmA1VACudZwChnEiTP1B0RFLBfsISWkqZAJKRUJoKtcMBKUDmFjBUUhsF04fkfbLjLWZK3cba8BpnzukghJxsKgiaUbZowFREKeIYRMH7KpMKYtWK8dDA9BUXFWrZhNAhSSA5kQ1hBVpiOKMiVquSfg0FSiwJ3Mkh5IgfJjgonV+sXu1ogmjXZAq8UKA61pDbo9Tasecoy3SJFaKzqVcFkbj/BwoRlOuACJC2KNhy6MiqbLVAIW7ZsvRIqRM+UbiQvpc52l/P1s4VIaxsoq0WJ6ZAWXJdyJN6GukypMOsNEbssLcuG8p+U7Al7CrxEVNBxQ/DCDqyIZNKGGy+6DOYR3LizmetHCwguwPUXbbwrzx+hNhhmFUDvK0ElohDA1lXBaPos+S896ZYTXcJwPpsE0ygeXs79q3jsj+KLuT+MvMCHQ+gcHMM/dakV/r4DnYKttATgyDk8cvbRoEcxJXIbS6p0sfFFXUkMHV6C
*/