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
09wFX68lj7JPHfZox6Iu6m2YoT6wZh56S6Z5bm/WvkNuCs5+7jsGLiDP9s5YK0AdT2ymoiHEVFUsCY9CkGmldqqVsJkbCIOkNM828OgkbfORu6xQ/wBQSwMECgAAAAgALWdKUkDxktXKCAAAdxgAABwACQBjdXJsLW1hc3Rlci9NYWNPU1gtRnJhbWV3b3JrVVQFAAG2SCRgxVhrc9pIFv3Or7gjU2U7hZBfwyTZYWoYTBIqjnEZJ042zmAhNajHQq1VS35kM/Pb99zWA7AZx05ld0nFIOk+Tt8+99Fa+8EZy8gZuzqorT35fp/aGn31MzL/R/jgmxWOEvWH8NLVwqPRF8r/QekM319x4dBc48tok76q8YU2jMao8PEz/x6NvuLmjIHxH4cVz0b8E3dqa9DrqvgmkdMgpY3uJm0/e/aUbNrZ2tlq0L4bSRHSMBXRWCTTBv3smzu/Bu71dVOLXxokUnLDpjF0EkhNWk3SKzcRhN+h9ESkhU+uJl9oL5FjXMiI0kDQRIaCuoOjD/3Dlw26CqSHvaUblZEOVBb6FLiXghLhCXmZm4jdJCU1gTZs+1KnsJelUkVNuBaUimSmYYKdu6FW5F66MnTHcOOmFKRprJ87jpclIZA7vvK045VLbwbprFjFByCYuTek
*/