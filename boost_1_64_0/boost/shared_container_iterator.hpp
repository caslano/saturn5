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
ZN/zDbgK9lhhOU674MItMeP4GBs1RQ3RluDHxJiDpOYfCZ+vbu4ainq6LhD4uBSse3k7SgQF3n6XAjDzyfUqw+nS8WRkB3L+w/Qb7gOzY9qNvVPUvs/rfKT+L0F3B9GEUIRqqg9i97MJU9lvwYOQabRsZvCplWx3XnS9VkAjijkwOpsI3UeLgOCMZfK7/Vzndm9/ShwmMuhnHSe2skijCKQHRUQMtQz/Ihjefj8tjP/i1HUX6SH1whn9IP/ypn3s+2dpH99XuAi36vEDcHzNpKFhfm9XtQb6pJ+5qqiqKAkousnc45Gd+EnTIwf3OWT+cvoQ1GVzi97KScrlvsy84fVBrHXDkWJSLDzWcclZ7fU1KvMduHhTD6yn5sTHazRpFNtQHQST0CfRx2zfLv2PB5bwXs4ct9iV5MjNyk2/4APn0ovXpGx4kuXM/bzkSfHOxpjF4mREQfz2PaDDeLyikZJPNac28F+PWAT1jnRb5RPvLMOIi1tiu7mIgK/LhhgunHIPkj6Gmu8QcayQx+g7cPAcJ3DWKfyerRyisgT2GDwAqmiBcFUvVhURPA==
*/