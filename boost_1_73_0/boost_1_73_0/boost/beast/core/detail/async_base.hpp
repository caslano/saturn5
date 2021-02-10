//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP
#define BOOST_BEAST_CORE_DETAIL_ASYNC_BASE_HPP

#include <boost/core/exchange.hpp>

namespace boost {
namespace beast {
namespace detail {

struct stable_base
{
    static
    void
    destroy_list(stable_base*& list)
    {
        while(list)
        {
            auto next = list->next_;
            list->destroy();
            list = next;
        }
    }

    stable_base* next_ = nullptr;

protected:
    stable_base() = default;
    virtual ~stable_base() = default;

    virtual void destroy() = 0;
};

} // detail
} // beast
} // boost

#endif

/* async_base.hpp
7rocM9h4A0hLjeqmOKLwE4VN7LoKRcWvemXg5+S+wN4iP3VSnt0EqEu90a33cqiksVSGv91y88XtuFxJhdmqe5OG+Ovm24RVh9RMmgMaIf8CUEsDBAoAAAAIAC1nSlKsyMLW3gQAAG4LAAAmAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9mdHBnZXRpbmZvLmNVVAUAAbZIJGCtVttu2zgQffdXDLxoamVVKcnTtrlgXdtJjbpSEDtbBJuFQEmUxS0tCiQVx738+w6pi522C7dAFSSShnNmzlwV//DXXT04hL1XZH8jvPBuEddS/EsT/X3tKPoM9Q+i7vG+z4kPW8jnyIH9kM8wsJCo8XJmnqNon6N7w8388Q3yPjKPKEGYQY5EuZFsmWsYjBw4fvnyD3gBJ0cnRy6MScEoh7mmRUzl0oWz1Er+zMnjo6fohQtUA+FeY2qRMwVKZHpNJAV85iyhhaIpEAUpVYlkMb6wAnROIWOcwii8vpsGVy6sc5bkxshGVKByUfEUcvJAQdKEsofaRkmkBpEhHI2nTGk0WGkmCg99U9BUrpSxYdwTrgSQB8I4idER0ZBrXapXvp9UkiN7PxWJ8pM2fC/Xqy6SOySxIhsQpQYtoFLUBaPpwkqkLDN3TAgKyyrm
*/