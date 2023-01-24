// (C) Copyright Ronald Garcia 2002. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

// See http://www.boost.org/libs/utility/shared_container_iterator.html for documentation.

#ifndef BOOST_SHARED_CONTAINER_ITERATOR_HPP
#define BOOST_SHARED_CONTAINER_ITERATOR_HPP

#include "boost/iterator_adaptors.hpp"
#include "boost/shared_ptr.hpp"
#include <utility>

namespace boost {
namespace iterators {

template <typename Container>
class shared_container_iterator : public iterator_adaptor<
                                    shared_container_iterator<Container>,
                                    typename Container::iterator> {

  typedef iterator_adaptor<
    shared_container_iterator<Container>,
    typename Container::iterator> super_t;

  typedef typename Container::iterator iterator_t;
  typedef boost::shared_ptr<Container> container_ref_t;

  container_ref_t container_ref;
public:
  shared_container_iterator() { }

  shared_container_iterator(iterator_t const& x,container_ref_t const& c) :
    super_t(x), container_ref(c) { }


};

template <typename Container>
inline shared_container_iterator<Container>
make_shared_container_iterator(typename Container::iterator iter,
                               boost::shared_ptr<Container> const& container) {
  typedef shared_container_iterator<Container> iterator;
  return iterator(iter,container);
}



template <typename Container>
inline std::pair<
  shared_container_iterator<Container>,
  shared_container_iterator<Container> >
make_shared_container_range(boost::shared_ptr<Container> const& container) {
  return
    std::make_pair(
      make_shared_container_iterator(container->begin(),container),
      make_shared_container_iterator(container->end(),container));
}

} // namespace iterators

using iterators::shared_container_iterator;
using iterators::make_shared_container_iterator;
using iterators::make_shared_container_range;

} // namespace boost

#endif

/* shared_container_iterator.hpp
fEsATIDmvjpYkO/zOu7DtIe+hibauD1F3VJw+TiaeW4PLoTJAG7+tixZM1iqQoPKClaXIvHcfVsorXsWD8mWs1JLD4Z5iR/7biNbeA+CUgP84V/xNkhT8ZDpA/orGDqwbm38Kx4YouL+OibR5dOubpBQZEVe2cpe3w3vIR5ctGF3lEVb3aIs2lMtyu4/GtJLG5uUBTugowl+XLfIzszVey3V4pkFKLlSbTXVpMG/DC8nEmdfFH5Cz1j1ELZZxfB7MgOy3nVsANohm7Bey7haNKx7EgWCWPfw9cgsv4ziQ+vvs8f/9QL5hl3Rtnn8a9mOgWdSpWp20yMrEsiC7/IdIsvfrYLET1Ri4uWs50d8i4O3fl/fd+OpODEt07rKteTEdNFLkLAxhTQIyJCL5x+KTT45AC09dwqS5P+DeubThjzc17L7WbrC9g2T+91i1WOifP22iiSAnDZFHHPdAht+nLEsBCU+Nu7vhlyQRBT0XvcqxKR5Z2jKQmKFUk/lmvCi3u7TzkR77MuFxsTxnsq8G1BoGYodr+iUP2o4683uhqKZz7Hu5zGnWP5rvz/RmpYhThuvOA0mS+DsF6fH1X2umC63CSHkomj9Jq16vYfNe3yz4s3EPWIz3jUYvV4d0GWi7zW/vyjU1GSqLPxgJRJq+xfS33n41xvXRop17nykIr0RBJuKTAFvOIXHIjPhQLFV/OMdRdJoFJReFGrv
*/