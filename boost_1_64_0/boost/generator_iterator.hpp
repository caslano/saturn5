// (C) Copyright Jens Maurer 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Revision History:

// 15 Nov 2001   Jens Maurer
//      created.

//  See http://www.boost.org/libs/utility/iterator_adaptors.htm for documentation.

#ifndef BOOST_ITERATOR_ADAPTOR_GENERATOR_ITERATOR_HPP
#define BOOST_ITERATOR_ADAPTOR_GENERATOR_ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <boost/ref.hpp>

namespace boost {
namespace iterators {

template<class Generator>
class generator_iterator
  : public iterator_facade<
        generator_iterator<Generator>
      , typename Generator::result_type
      , single_pass_traversal_tag
      , typename Generator::result_type const&
    >
{
    typedef iterator_facade<
        generator_iterator<Generator>
      , typename Generator::result_type
      , single_pass_traversal_tag
      , typename Generator::result_type const&
    > super_t;

 public:
    generator_iterator() {}
    generator_iterator(Generator* g) : m_g(g), m_value((*m_g)()) {}

    void increment()
    {
        m_value = (*m_g)();
    }

    const typename Generator::result_type&
    dereference() const
    {
        return m_value;
    }

    bool equal(generator_iterator const& y) const
    {
        return this->m_g == y.m_g && this->m_value == y.m_value;
    }

 private:
    Generator* m_g;
    typename Generator::result_type m_value;
};

template<class Generator>
struct generator_iterator_generator
{
  typedef generator_iterator<Generator> type;
};

template <class Generator>
inline generator_iterator<Generator>
make_generator_iterator(Generator & gen)
{
  typedef generator_iterator<Generator> result_t;
  return result_t(&gen);
}

} // namespace iterators

using iterators::generator_iterator;
using iterators::generator_iterator_generator;
using iterators::make_generator_iterator;

} // namespace boost

#endif // BOOST_ITERATOR_ADAPTOR_GENERATOR_ITERATOR_HPP

/* generator_iterator.hpp
81/H8wulGY2x6u1+FZcvZ+FGVES8BQb0ARi11rOYIMBLYcoXVt7He+aZteZIsp/gj8CRUO20A/w2FDcxTPzdWOp9wHRBr8UrDSfMVzmGj7m2/NQQFRCqk2BRpXO7U9o09Qs7djpinEynLpuk5ovJRxZfQtod7FZs0wyUG8sjOsq9/bF5bheFm0UEZrgaILveW/riT/2hbLrJ437nUlKME9Q+ZTI1txA83qfRtd49S/eGn26GIthZb0O/f8WEY1E2gvaDMogrE2eiKj8+UWxDNlDLTTq5ahZLOIHAsvWkyLs5m79rTbLddn00dsS/NqRGK/GqD5xsvWPsdWz5oLWuWwZ5twDetanl5X7r50ZjVAY53Thn29lBACXQxJ32xJaExBD/O5bniL5AVdkGA/2TxzLsNRN/fz/WR1LRv8no5UUpDhxRQtE0KNAnlUrT6kTpS7ifYMxE4I6n2RT29D8Ri8uY543FuZCpJgQZRND5OAQErBw5DR+bx4wNtOi+0A8bYNhtEk625k/nYs6RYvxM1qNYl/PVdYIg7KnsWgmy3NuBD/JVt+9CXQ4PpA==
*/