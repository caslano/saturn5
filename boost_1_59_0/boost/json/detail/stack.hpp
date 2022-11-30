//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/json
//

#ifndef BOOST_JSON_DETAIL_STACK_HPP
#define BOOST_JSON_DETAIL_STACK_HPP

#include <boost/json/detail/config.hpp>
#include <boost/json/storage_ptr.hpp>
#include <cstring>

BOOST_JSON_NS_BEGIN
namespace detail {

class stack
{
    storage_ptr sp_;
    std::size_t cap_ = 0;
    std::size_t size_ = 0;
    char* buf_ = nullptr;

public:
    BOOST_JSON_DECL
    ~stack();

    bool
    empty() const noexcept
    {
        return size_ == 0;
    }

    void
    clear() noexcept
    {
        size_ = 0;
    }

    BOOST_JSON_DECL
    void
    reserve(std::size_t n);

    template<class T>
    void
    push(T const& t)
    {
        auto const n = sizeof(T);
        // If this assert goes off, it
        // means the calling code did not
        // reserve enough to prevent a
        // reallocation.
        //BOOST_ASSERT(cap_ >= size_ + n);
        reserve(size_ + n);
        std::memcpy(
            buf_ + size_, &t, n);
        size_ += n;
    }

    template<class T>
    void
    push_unchecked(T const& t)
    {
        auto const n = sizeof(T);
        BOOST_ASSERT(size_ + n <= cap_);
        std::memcpy(
            buf_ + size_, &t, n);
        size_ += n;
    }

    template<class T>
    void
    peek(T& t)
    {
        auto const n = sizeof(T);
        BOOST_ASSERT(size_ >= n);
        std::memcpy(&t,
            buf_ + size_ - n, n);
    }

    template<class T>
    void
    pop(T& t)
    {
        auto const n = sizeof(T);
        BOOST_ASSERT(size_ >= n);
        size_ -= n;
        std::memcpy(
            &t, buf_ + size_, n);
    }
};

} // detail
BOOST_JSON_NS_END

#endif

/* stack.hpp
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
*/