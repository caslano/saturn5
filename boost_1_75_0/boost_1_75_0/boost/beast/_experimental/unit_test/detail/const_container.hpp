//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_DETAIL_CONST_CONTAINER_HPP
#define BOOST_BEAST_UNIT_TEST_DETAIL_CONST_CONTAINER_HPP

namespace boost {
namespace beast {
namespace unit_test {
namespace detail {

/** Adapter to constrain a container interface.
    The interface allows for limited read only operations. Derived classes
    provide additional behavior.
*/
template<class Container>
class const_container
{
private:
    using cont_type = Container;

    cont_type m_cont;

protected:
    cont_type& cont()
    {
        return m_cont;
    }

    cont_type const& cont() const
    {
        return m_cont;
    }

public:
    using value_type = typename cont_type::value_type;
    using size_type = typename cont_type::size_type;
    using difference_type = typename cont_type::difference_type;
    using iterator = typename cont_type::const_iterator;
    using const_iterator = typename cont_type::const_iterator;

    /** Returns `true` if the container is empty. */
    bool
    empty() const
    {
        return m_cont.empty();
    }

    /** Returns the number of items in the container. */
    size_type
    size() const
    {
        return m_cont.size();
    }

    /** Returns forward iterators for traversal. */
    /** @{ */
    const_iterator
    begin() const
    {
        return m_cont.cbegin();
    }

    const_iterator
    cbegin() const
    {
        return m_cont.cbegin();
    }

    const_iterator
    end() const
    {
        return m_cont.cend();
    }

    const_iterator
    cend() const
    {
        return m_cont.cend();
    }
    /** @} */
};

} // detail
} // unit_test
} // beast
} // boost

#endif

/* const_container.hpp
uQyNgLEOUc25yYZS6Z2dyI8uUyvrjX50OOkywxlaWgrcK06GawCp5270X4dnG5vC+YpUmcuRUv7NyUvBhFJeFMio87YruvK2xEbnujzdzj9P+qg7mzunsHfEgV7ci0JzLwo5IWG26MAolGKZO1Bo6sCCK9vqgIdMH/+rmLrgMHUhEkeaH8w1eP/15ixBqdyZGD+FqHPQ9RRy2+BoU03JJA0WXFTtxlX17IlU1WPeDh4CnNjtgPklUxqIZJUato7fS2A6vyttiLfT6PoaX1/i6zN8DaUZ9oSeYFGaJ1ja2xMsSye+I7Q4G0InVOzDhC1q4iPfMPRVL8RlO5w/IOpFXQ1GjtN6kX0KBMAY5w5OWUiALo6H/cEzNo9cPvMXUo5cMuqeDIHdTGEI0Oxjl9hKlZA82RNK7J6Uwn5IEK9QvO0KXRendknN7yKOdcP/lQpJLhxVv8VR8NkstwwzggFGBmyCkLbl+SGXjeIZivqeymYMYSxOanu9dtHIk+KvY3kDR7SucwxvAJH7S9jilHJyJ32NCJo/o8ir9gSTBAp45jnU6Dttk7ffJjGscuwlD2KrK3o9SgouiaeOidOpr5w3Wxljz1M50EUZlo+q4eLOKMGeUhMYpJ+DU7kJhiE9WCW0CWdE8EXCzlJ0i2/pdqbY43XSPmHUTN5xy3iqBDoRNULO9+20y0q0WT2MlHGlesq4bErjJFMb3DoC0jg5
*/