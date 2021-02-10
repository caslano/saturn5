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
pu/XhtLqyrjJwI+7lShMiqF5ZfE8Xi+sPiw3zOfjwb24AHBvzuN4c1G28jysAZqvDn3wR6Nf22ZNS8yDNkXaoVhUqF5PJESK1UMmgc+IH5PwU7GFtSHurWw2gTSfn9J+VCDe4pjHalYXqYvajuneJwKq620tKi7vfh2YSPb77n5IN9INQStHNHntEf9C+wGFYdgbkEHzQKdBu0V7joVx5BuwQ6bVY868RlUttxYa6YlGDSPOaQ4XYcWaeZYLTnueA+3uYiG4zqQsYQosGDeqSPTM7O6uqEFywwAcBLlpVkDWzo326IV5ncMOt7fScCPzVvDTxIrIE4bHXhe2ShA7sq3XA4Z1eD2l6OZ8+PPrJSkvLGRpeahqEvSHtfCGhy515cuB1wDVmquB5aqNVcgtRmiKS7XDVaA+KsozobgrPxBMB+5NUtBXV2idadrITqKVrXk2X/+/zfR6LHKBTXUZXKssbYUxGAw1NlbXv+EkozF1rvT4qcnin9wujChzyy82PJrMlx0jbE9G56nb33mEI9EEsHb+1FiyVQF1vRsNr/bC7dQgDHaSkzR8TtNW/H47iRuJe4+yyqBAx9NuFa/S2IX97v6btjk8P0JSw6MtYdZS1SHuLfAQSgLxt0Zm0SRAhIXlSOmzsD5ksIFK
*/