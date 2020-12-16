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
nEWXMVnWBYzNiXWcEz1aeWwEQHcAsIXGaHTOkn2SxVv2X+nEVOHJ02WWHHJoLMZyjCfyuaHOlhvqsvtkMXNRjMAU/RfogPOQyliODd3ErzNOa4VflxHot2Vx/BrKgM5lAs07Wph1hcq8cPT+HnOT9f/6t8L23/UQtclWVBLKX3ufGqqOqMM+7X/9zRG/H0mNd/tbiFpYtA7Xegvkbu9iEaw4AG8g4EIFqOcIW4jGK25+75JSRrWXZPmLy1yTTzUuQV0ZF6dDwp0lHfLQLaRDspX+yhpjhRIzxo0jxqjIUy9CDrDnWtG/muo/NOPJe9GMwSViqLqIkPsYciZDqLsFnWF+h7Bvqf41F4Vu+1AJzge/6uNTtQSebX/wTIj4w36eB+p/pEL56p8loHxfRBFdvh6x7+gi5XfLS83VpzPlH/O5+uwysnMRqsjRvyLMYr4PmcB1hxTbL39iSe/qSwt51hDv+6ZPMViWSuUa7Gs/R6fdyxB9MNt59fz4NrneOIZNqh+YbzMtQ+QkqFXkF7TE9qW8TWe3mgVPnqzmZKz5CFTgtfmowGGiArsS7R2O9ZA3FRuGhbQA5JtTBLpjHdtWgozZvNf+lef/s+Pnqwl5u7n/mRDvODw1/riE+Orc1PjMhPi2XVPjt54l4vV2M7/qguPWqXJcOdbXIADT9StgL/lg8utDfO0j0lrn37MUIdqGM5UOy2pp3+nIyNRCOzS3ij00XYAIP+ihWur6fGiuDJGpBfbw6YwJljSEM2EMD3eyo/5u2uLHJFpPu4do3WB0IUs6NsgV32OJc9YJGlPes69Yn7Te60g+QrbjhTNFO9TWA33WI0i9n8vFqi/t60amF4KMx0pl2lwkfflaUBd6gzFo0E4n33LF3aZ4nfNxvLCEsonHI7FG9YWhQNm0hwBHIrcMEBZC79e5Bh0ekPI/dvcJ82DiCxU8FGw+pdIVdfgjS12BmI1myoLSFOE7osN2W4ziB5IfDmgNFKyNEsNM5h4A35Ct1jCo4NFi4GzhwxiRIxXH2gQitS6GMg61oNqliEMt2rIWSg85/Ioof5+aqYrsLjLMJB7lxpGoeZvSWMOPR+SJSuDsv1d9uzdLzPWuCaOQf5egtsTsOTS7JbZ3/bX5Mn3AVCxBRh2Q0Zo7ecn/m2q/x1idRVNVjaz7qf5oN9h6RC5TgStU+Y32zxe11eqhkyTNZAei53TjphWMHvpj1NVS9X0+OsMUBYOXEb2Bmmv48ejvCinsvOJJhaE+7FGgOSefuzkDBzVMvhUSQ7+fJyffo+CwShA9u7kj8L9bs7t4UkHIGZ1UgAXaHFlpwOJHaPUk97ey+6Aac5RsTISnT6I8ffxcXjgVIjqagKKmT+dCd8UmHlJ5qnyaBATPP8Hu37q7iiSx12CCrfJeIUkrx+OzuxcNz4BkKaeh9r18fDtqt3hqN+MT707xf2YUFi0AnQWo2s2enEaEZec05KyC13NEhfzViDfe7QftP7zotbVGfpXPxl9PFbOHuY3aJldVuUMHcJXPqSAyFEQmIUICIqvKl10GgVcf/7jVPTNO1KqyArEVsbqqjBMj72fDpm7lWSBBm940m/eqTTXvH9aoNgepUVC8PzwQq4fnLPei3G5Ved16rtWqDhONUy0rRsvYllHi0KpFOxdapmlMGw/7j0z/hD9r/+sjVxT3IhjF3+BepNmhE+heNDQDnathELw5jWIoNAfGAR94c8ofdFXAGgVhPRK9VabGohFj0UuoRtD0bbYx9QxxZePJbtIjpOx1p+z0MjEsPdjpgzgsvarK1LCUZSgIMSy9BERWVVn2/m+Xu+Pft69Okj/mB2nfBEZbOHH9+sfyhHvp6XLuzhw=
*/