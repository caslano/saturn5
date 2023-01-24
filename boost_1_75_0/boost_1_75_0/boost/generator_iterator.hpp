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
RTEpnIMOPC4+zK8fpxZW8nQGfhuLjdfHHz/u5o+iBrRi58wC5fID7EfE0pR+NaIDcjQe7yhYeJsNvJP1jM1rexgKEyIf/5Ap1J/rLTC0lw+qspW6i7YKPPpqkeUwX33tLBDjsftvZPUcLooaek+HoyyA6GM67QH/N2q9cUSBKZqZh6bNRGkQFfNVcazhb9VUK4SSIiOHaD04WkityuPn+DJU13slz96vIuqKM2HKHg4tqXcA6oyDiKFQn6gnoRUxsPP5e/yscaj8LU/iM2UQuE5H3vQhnUF96NSLPTvyg/Oo5HxcZ43yv6L7PddOq49VbOHeczegzPOKhXHNpNz5X42SI6X5I/2PQWm14o2jobfMW0O/KMo9HIBDZlTCTAQI/7y9Z7GliuFd75JfSUetA7EPavwbxl1rgo9/tsjDGlbZQzdZUtMe9HLCa55MLjpA2KO///HuNK70eSb1bC3jjxpkMmwt6cbNJ9DuP1S3lt6LULY3Lq7UmmSsuPrinNT2EoyIm59iviR8U4AdL9zPu3kTZXQ7Jopb896l0LWeueML0SkTGriXft3x2zfGZgU42rs3LD7f/dED3QjbeRIC2kUjjq4T/Y0fjhrJvifcnF3X3VHc+LPuVI7o74RFXNjP774gbcbMJe+rhY78WR2ZDF81XX1uiGGSm3+WWFfVMYL8oRjRZtrS3B56Vsab3xpd2ZglbmOzOZ0CGZk/
*/