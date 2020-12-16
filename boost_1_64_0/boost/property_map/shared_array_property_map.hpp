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
nwEAAAAA8J+YZv5/2PWV186+AeA33qOfZ24AAAAAAPBrfqv/P8JYeTpWf92u/SYdK1d6lNzzHWU+9z7XGmZq7pX22L208wz2p8dO9jwl8j9ua2z7+2eJxJWB7y1wOp2KutwZy/kzdby1dahMHc1K3Wvpa0lP/ZBiDMckz9x70/20Gzzr72coG14U76X5uIxK8nkZ8S5XHBVfDBX9z1bVqZ3Pff832hrdOSJR/bHGwE9Kqnf9mvICP/9zkl6nX2xNd/o1eb6n4htNZSzXRnqv68wViVs/1JF/Den5mWOnHZUHavCclndFpmdIOdWWHMNx2WprumdrOvWzmnwnDINLFelf9MLAb0tf5V7XDlvXdvsH5xv9uhpSpbX9pLBxXEvpvf+Fre1uZo6bp/Jvf6bmTu8F3+aLRLN/3HQT5m45lvOXZ+50Hz8tEIn32c9UUmHQqncq0Rj2Mf1sp5Ydpjk29NlO3bD/tHbCxsXc61mZ/j9g6/Gn6tGnPf/7Sf/+v1Aknky1XxnXdZfW8NXW8GhqbmqnUhnPeUhr6C0SiQc/1FBjXizwH5hm/n+kXC/I3AlGHp/PKy8AAAAAABjNyP3/Ef4OSF7ykpe85P03edNxmHSo5f7A/J16O3BlPA6TW/vkJe/Mzmvnv9lx9tcD45i1oJ08g0SuzyEAAPIwzfz/SIWe3/jD7+jPMzcAAAAAAPg1v9X/H+Hv1+Qm97/ODQAAAACYdv5//EEgf/Q9/XnlBQAAAAAAoxm5/8+4KwAAAAAAM8408/+7ymt56vKffUd/nrkBAAAAAMCv+a3+P3MAAAAAAACYUebon6W2/7+2eMTzz8uwuHb0fv7ewq4lonbJFft3lIOO9KOgG9ak+TVqrat2vZa7bqI0UdpQX3cx2rhhYls/1tu+dV3UdELprgtlSzqRtGsI2ZNxPldeLNttTu0rnwyCVlQ+ekL/OrG5NLGhtHFLHKl6fvlgEKnT27eWe/qnpXeldOD0AdFxq3+zqLLT6UTpaqU4ea3tiuJ6P2gFjaC43pXVbqO4PupWo8uRku0dtUC325LF9UFH7QhlXf/SVTsGssT7qa0QW5cUxCIhFgvxWX/XkJ4KMVlSsqeS2LYl6WNCK4gksrrtm+1mxds9mS0mPxbEbiF2l0LXUY7ZbvsyET/2SmizRMmLI6u3mJg+/8n6ep04tmFDrd4QWja208T2HT+5+vS+PYOx3QOxPQOx/dnYmcHtDmZih4ZyHsnGhnIeG4jtG4idzMaG2judiR0baq+cjQ1tN5mJnbTbLbIxNxuz2wkba5pYo+650erLJrZ7vzk3nSRmz5C2MtPek9OFfmx11IsXSfz1LBN/mo1fuXLFrTYG6r161sRVbbU+dIP7ci0TOzO0n9enYifT7ebb2M1MLN1ut43dNrFeUk/PxI7Z2FsTk2Y/7XYFcy0Wy4Wpa3GjienDksQmz2VimwavYZWNbTaxp56JPb6QiW01z4vZ8fPi9lwx/51Zp2SLWa63e/h86nkxWySR5PHJFUJc04/rePx4NYpMrjlxrs48ETaT7faW9J0hqAkAAABgxrD9y7i/mfQ7xV29nCOyTD/U9lZ0/zLpZ4pPenlPLzOSfqdZLX69nbzuFi/0sqeXffZ1uH3t/LouktfUoqmXG/Syz7zGFgAAAACA7+ydf1hUWRnH78DMLqy6waabblq4i4ouuOCCYmHOMCCDzsCoaLgLCyNzcUZnYGBmFDcsaHHDwsLSDVssLS0sLSy3Rws3KC180sLCFnahsLSwsLC0tLT6Du/3Kmy//ij/6Hm8z372OHPuPed9z3nf977n3sud+9v97b/eOj8drrxVubNFHNgXrkwc9Vm5v93f7m8=
*/