// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_CACHING_PROPERTY_MAP_HPP
#define BOOST_PARALLEL_CACHING_PROPERTY_MAP_HPP

#include <boost/property_map/property_map.hpp>

namespace boost { 

// This probably doesn't belong here
template<typename Key, typename Value>
inline void local_put(dummy_property_map, const Key&, const Value&) {}

namespace parallel {

/** Property map that caches values placed in it but does not
 * broadcast values to remote processors.  This class template is
 * meant as an adaptor for @ref distributed_property_map that
 * suppresses communication in the event of a remote @c put operation
 * by mapping it to a local @c put operation.
 *
 * @todo Find a better name for @ref caching_property_map
 */
template<typename PropertyMap>
class caching_property_map
{
public:
  typedef typename property_traits<PropertyMap>::key_type   key_type;
  typedef typename property_traits<PropertyMap>::value_type value_type;
  typedef typename property_traits<PropertyMap>::reference  reference;
  typedef typename property_traits<PropertyMap>::category   category;

  explicit caching_property_map(const PropertyMap& property_map)
    : property_map(property_map) {}

  PropertyMap&        base()       { return property_map; }
  const PropertyMap&  base() const { return property_map; }

  template<typename Reduce>
  void set_reduce(const Reduce& reduce)
  { property_map.set_reduce(reduce); }

  void reset() { property_map.reset(); }

#if 0
  reference operator[](const key_type& key) const
  {
    return property_map[key];
  }
#endif

private:
  PropertyMap property_map;
};

template<typename PropertyMap, typename Key>
inline typename caching_property_map<PropertyMap>::value_type
get(const caching_property_map<PropertyMap>& pm, const Key& key)
{ return get(pm.base(), key); }

template<typename PropertyMap, typename Key, typename Value>
inline void
local_put(const caching_property_map<PropertyMap>& pm, const Key& key,
          const Value& value)
{ local_put(pm.base(), key, value); }

template<typename PropertyMap, typename Key, typename Value>
inline void
cache(const caching_property_map<PropertyMap>& pm, const Key& key,
      const Value& value)
{ cache(pm.base(), key, value); }

template<typename PropertyMap, typename Key, typename Value>
inline void
put(const caching_property_map<PropertyMap>& pm, const Key& key,
    const Value& value)
{ local_put(pm.base(), key, value); }

template<typename PropertyMap>
inline caching_property_map<PropertyMap>
make_caching_property_map(const PropertyMap& pm)
{ return caching_property_map<PropertyMap>(pm); }

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_CACHING_PROPERTY_MAP_HPP

/* caching_property_map.hpp
6odznxtLnWXhl45XCImCcfD0Fs+S/hXPBsOyTwxzj0ISKCUzlGsVwABEXsdtpAfEZpHpUfD1nR/0PZe7kSk82fTJRwMCpar74zNHkfv7mIh/9k3h+vsmuhSuyMLIgEHbAT/2e17o+Lvx7xyFytK3Wd69j0bp3OLvWx+8ii+5Im7n8s39428lDji1mrMha2p5b9uUISi7uxxoDHZO7ckBqCSRy0M1MnO74uN+A/Dc5Kvrt0L75RKHSmJzxIDy6LWodS7zkMtQjSgPTnNVA1xzuyQRKxc6cSuvynC8VuLQtY31ikCN7fbJUi8Ua5HLRdt/ku543MF2skIt6v0I4CJst2DWbufOLhDD3IGuTu4qSllVLmkVisNKWbm22tc7P7yudyqZ2AWDZCzxMi/ihyKCYWkmxF9z/Y6qO3oT0ORkD0fpsj3DqULuDfmzHW8NVbMjj0dXoDy/rNq6ZkNv021YlR+jqvcxzjtB+CGAqi3mftatHAUqkuBahaSX/T/hKtiFDFKYTULAZgNczsBn+22D7t6Tum2aNLdqY5ktoscqY5iNZUwN5AWIa5Ebfw2+u2LclZMpzc/MHq5YcKxBChvakxbrP05EwOZmz38CKkzaTB6tI3PcKZUXG/CwBp0apAkXJk0yHDYJNjrMgbjbmefG80fl1t6DvBXjiDQ2NcubZkuBthXy6NVBJxdOmZb0S62sgtHquZF9Hbj5JJja
*/