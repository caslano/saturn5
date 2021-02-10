//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_READ_SIZE_HELPER_HPP
#define BOOST_BEAST_READ_SIZE_HELPER_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {

/** Returns a natural read size.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @note If the buffer is already at its maximum size, zero
    is returned.
*/
template<class DynamicBuffer>
std::size_t
read_size(DynamicBuffer& buffer, std::size_t max_size);

/** Returns a natural read size or throw if the buffer is full.

    This function inspects the capacity, size, and maximum
    size of the dynamic buffer. Then it computes a natural
    read size given the passed-in upper limit. It favors
    a read size that does not require a reallocation, subject
    to a reasonable minimum to avoid tiny reads.

    @param buffer The dynamic buffer to inspect.

    @param max_size An upper limit on the returned value.

    @throws std::length_error if `max_size > 0` and the buffer
    is full.
*/
template<class DynamicBuffer>
std::size_t
read_size_or_throw(DynamicBuffer& buffer,
    std::size_t max_size);

} // beast
} // boost

#include <boost/beast/core/impl/read_size.hpp>

#endif

/* read_size.hpp
cjgGrWDhzB33L3ruW+eMRe8OgFc575zBRI3f9C4uqky9ckBQ79WFIyDB1Jk7cvoTIt18Exh9SAS0XHTU+NLpu/TF+YsD2nujDx1IQPWHg7HzX1fYhIfqrPe299oZq1ZdAgRrUwgQd/9q5Lwl+sD2+OrVeOJOriaOej0cnpF01dgZvXP7zvhEXQxJ3ufqauwwYWe9SY/RAwqEgx3E1NXYZTG5g4kzGl1dTtzhoK3eDN9DCqC0h9NnLM/hgHgWK3CGow8EmuTBEu+o928crI9IhGBvMuqRYMaTkdufVLcB5WQ4YuZKftXAeX3hvnYGfYc2DAnQe3fstKEjd0wbXEYOxQPtFfNOigFt+NowzA5rULnnqnf2ziX6zX6ofewaE2Hx9d8Y6RcGXi2BUv33FRIlhYUph+qfu790fyZXi8if6czhzuG+enHmjPsvOTHbZMGpzRYE3hQe7plUaKMIZS5OZ+SWKJbYXV8cWlCHOzvfI7NEKwTVF1kehEl3/rK2lOK0rM2QimbqvTv48dnO90qVe9bZYY44xbsQKMJZHSbYqgPVaRoznsoaMX5If3hdx6sFKjSqXqjQutbqtx2l+ueTD5fO9WA4cNSpOuqUS+fuBS0dV5b6VBmeqmc7Dyc7O2ADocpADLzc2yF4TSz0
*/