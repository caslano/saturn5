//  Copyright (C) 2009 Trustees of Indiana University
//  Authors: Jeremiah Willcock, Andrew Lumsdaine

// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/property_map for documentation.

#ifndef BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP
#define BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP

#include <boost/smart_ptr/shared_array.hpp>
#include <boost/property_map/property_map.hpp>

namespace boost {

template <class T, class IndexMap>
class shared_array_property_map
  : public boost::put_get_helper<T&, shared_array_property_map<T, IndexMap> >
{
  public:
  typedef typename property_traits<IndexMap>::key_type key_type;
  typedef T value_type;
  typedef T& reference;
  typedef boost::lvalue_property_map_tag category;

  inline shared_array_property_map(): data(), index() {}

  explicit inline shared_array_property_map(
    size_t n,
    const IndexMap& _id = IndexMap())
  : data(new T[n]), index(_id) {}

  inline T& operator[](key_type v) const {
    return data[get(index, v)];
  }

  private:
  boost::shared_array<T> data;
  IndexMap index;
};

template <class T, class IndexMap>
shared_array_property_map<T, IndexMap>
make_shared_array_property_map(size_t n, const T&, const IndexMap& index) {
  return shared_array_property_map<T, IndexMap>(n, index);
}

} // end namespace boost

#endif // BOOST_SHARED_ARRAY_PROPERTY_MAP_HPP

/* shared_array_property_map.hpp
/S4YHFF3h0xfyZwLEuzJZHQEOHwJaqVtWe3/sgLFzOwDHF5AdEe/s4rExiuSlDI/IAulRj9LSaT4R7o9Q+wJhoLZoeqyv30fM29cSStOfhiIkql1YvHnqjzkSDvuL0IvhCfr0JTkTyeWY0bN0WhIV5iG1uUTgimztl2DdN73va1X+XSUczGaRmwQ6c9LG6LHqrALYwQ0CTTcScDcNyB70sZKM8bXU+5vXiAbFO/9bVjPEA5zopOijQ+pwhq5sYEv1puYL7uQRjccp4g05qiVnSK8u2aWKkFBev77LQ7fvQWV3FBmoyeGvPXoq0LR+/BxSwT6RtQMReuFHB1VmlBdaNWcRhvQNBVyBYj8FFG1bGuozQllWyUtwlsZTckiN3Tu84a5qRnc6cSRb3KkuMRV1U48GxMSj5zemDMOnY4ezjtakN29Xe1WClXYlXrAu7zuJWv8IMLI6/TJYYHRxBvjC8S7UoitS958RFWG7ig45ziZ37T5OJet2t6hgliPWM5GpOMRuprcjm1D2hGt3ChD+OsI6vu8UQaKI/7YWmAPYu2AAxrJBvgeQQXpYReE84XQbviBCExD4j+Z0ixHymoAD2EoRhTiyOUJqfZwgdK2pMhrr+IJYWjkEXQp7uT2jpZZ3FaAHMGiyCB570xDrSebjIwdHDPx/gfScjfCSp8Y/li9J3DapqL9gq1L3GDOn/ZuhX+LUXcp1Yi0xqwV
*/