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
7d9GP/6j/RHHOc5+5xecjzt/45zi8mHEW+la5/ogxru/uGqRlymedZ6r9G36NF+Vr8V3E/rGDP9X/O8K7gr+IHQ0tDH86fCXwg+HfxA+P1Ia0SPhSDSyKBKP3IL4qQPcQt+Y6AO1WqvWo/Xar8Xocb/9UfuT9r/YGx0tjjbHGscjjscchxzPOJ53/MEx4viL42+OfzoKnSc7nc4AaqvRtc19K5Ufeu5uzy89G73v9H7Be4/3
*/