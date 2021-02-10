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
lAu6QBtqIDem0i+Hw7RWAjMfZjLVw3Rb+iA3RVfFHDMo6AZkZcBIqDXzwOI8KGTGlzZiK3CzqheC69x7SAWNymwoFWgmBEohjTPdpswg7jrjWRRUmC03NmhZaut0k8viDyC2EEWWtSrRBluAmExigz2oy4ypBtsUvXXoutm09h9H8pBrBrLETMDxYwhjBxZUc+3BVTg7m17O4MqPIn8ym8P0FPzJHLXeh5MxnjdHJwXstlJMo7MCXlSCs6wx/H8LDZ/CTG1s1UuODbMFCr7QOj+2UVG1Qcy0TBl2pWTtVNxwIXDUkMCa+s/Dt3F8dkxOp5eTMQrqjTaswNHS/9DbEsLJ6PxyHJBxGCHtdywvU1FnaMpxNo38g4Ux8qP5DqNTh5IWrNezxZCKmtzd59VxBnm/Q3Zkd9di4n8IYtjq24gMvtwn2u9BMxJuPItwPGJwnvzYA7sf/jJ3tppkjfOJN4zg1EAUvAs+g/P1oG3wdWLgy9FW6FMQxeF00m4mjjs47CeOY63twJUrt2VHwcW5PwpQZXCIqOuvifPlyCLBSZLnDsCOns11Ty73qMxKvI6urbo9EfcU+3VB0+90xc7wigkWGwxUZb5a6f628c3vJG8AKNUiCEWIe84X1rtn/zGj4ONlGAVj8smP4r8O
*/