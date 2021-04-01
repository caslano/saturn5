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
E5t53BG6Y5Wj8cCihCIODOevynn/JTXLR79OZ8MIBXFe3Pn7+tvlsgLpGxKuRsDx+HiabRGdKETJy3iPVe8lIBpJ5Fj/L39dPzLJxSxy6nIZP3CrbFy5vKLBa6wcPQl1NNzW9J5tH257KG9oHg7cAThW4ACer0kuI307at7fDboqosJItdwFZRNFbYG/FHRBwlMCu9YaVFCTzImMkRiIPr0nzBlopvDWLYaoQX1q33xIbHm89nsJyI3SrFHMSvn3+hSS9n85aYc2IytbnEFD//3siU4yjI1oxOwaM6gmpdwu0SfzcuE3lnuIQMuxdkeartmaPgyXQVnbQT2MVFVlBWmiV3c1vng8CR6Rw6ScsmRrSrbDFNADOoUUI1Xj6yECme2lJT+GrQa8uP3iW8F0RhE01AECsg4DbW7ov2vqXS0T2icJyrrakZevSM5Dw1dO1+xierWtc8bQqcimly6RPy7xjIuEOvCX5TXtHhKKogIoMLUW/4ydehS0CxOZZfK4u7PrDSJ4PsHS54xafi58dLg1prFA1CD/FHjTovvJlkDiO9a64Mis3oBphw==
*/