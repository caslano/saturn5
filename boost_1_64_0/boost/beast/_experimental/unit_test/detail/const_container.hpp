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
7HSx0vv+5OF44Ie242LFmNO/I6JaecR2iN4q2srVzEJfU1DH7ty38FedIqH9Cv6752h2nC+ncr2xlJSyRXj2uXowwLDbmLfr/53mSv738qZudgBYYqJfzxK1Tj7DMpq+WELOIA11M805uXIhDU1mJTZaAXs/G3kTS+ACBTzxQkfTAqhRiqPjcv4SGe9hda7JGLJKAOGBYOBAgwul+LiOiGzAYi677tD1Vpty71vOMgoRFt+lxrQVxyZGcEH3rpWesAeOo4bs4nujdxZdKNVAENdYeb+s/xcve0r2+0Vcqyocn9ndQkJ6PiKX0QDBZLtMablirwh2yRvxQJw5OXWN1uyANErbUpov8DXZ61qUBpoljiLgNKcQFegwfVhWoxhGkfsg9xgYzYJupR36Kq988UAR7mSXiaUc+TRly4wtxAKBrsVlVLk7/ilvGvBAj1BffP1j9tv/NRzlY2E20mYiixbP946hyDVuabXNpytsU+hT97yZeeKRfxooFbzpQPVRg22CxjOVmbTneogGRTGnKq4qAIsJ99qqgD2eSqPAS30xbTKTWoM92qRRuQ==
*/