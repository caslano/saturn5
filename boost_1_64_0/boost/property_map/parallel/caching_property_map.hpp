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
ff4yyq2tf5l3nqB9qLSDlKW8bqzdB9PWXXquC85zPfMc118cn+W0/wnc/yz9LpPP/WzjOkinynW608O0f96fLnTQfvOlPEJ5DM9wPWblfNCfHNpzfOt5P2Ed7wMc4bqP6yJbqUHk+wLzBept0/K2ObyuwPFUX9Wua/L6SDbtv1Di+pqfy/WMI7Opp3Z/s5zn31w+N1SuSD3vv1Ww/0lcDxu09THlXkX9DpTy+tobtFsL58PJcaB8R5gPXuA4dxxgfm1TRO6XOR7U44iD47qa69gC3kfxMo7bmUdz/NVlzJ8Y73t/wvhTwPoHaLclvN/4Xsmzr3Cdlz0rjM9d6iTuZMm4rGE+EKzmdSiue7bTb657pLRlyfxluvj8C+OcjnnejnlSHuR1tMJs6k2/NliZb7tFrn0pjKPU6xzkeCDUL+c/0y3yeOP5HBLjWQXtbTP2F//TS0k/mcZ16eHpzN84jw7tvMHja+Pk+QY3x/EA8+uFWn7qYhyqpRxcd17qoX9s4vjM4nx/gXawkflUL+NrHOtf4jqM67EO7XnbGt5Xn0l/Z95dSD+6Qr/RreP9jLWMU2t4P4fybfEyftIOk2g/Jif97Umpn1bEONEjccqtPZ+pPX86jv6wiXlMIe1Jz/Gl/0SWM29Tabdcn3dwfdTPeNLB8V1TzvhWx+eoaPcHFjDfYPtTfsbx4v1FN+1/BvuZxHhyQHuukvPsnc885nlF+l/J50CK+dxRLNf7lGc37ee0jes45geHk9k++w9yHDte5304zuMknjcdtOPrP+J8z2b7vK4TfJXj1s7zEv3oEuOUjXYbrd3foZ17eZ49TX86eIDzV8B1jHbf5AL7c/H5lB6ujzif3giu01/jc4/VvL7LOBO9kZ+16wVPc93E6yqHaV/ntPv/Nt5H5n5Huvl80kw+f6Wdx3m/Z8sLPO9yXHW8j7P9E/Rn5qULr/J+Ae3/KvODres4viUSN85r18M/T/8vU0b8uJ/Hb9aea+R4bg7y+QnKvYbzvE2LTzyvnl3L5/Uz+Jy2tv5X6T+UP6Wd69IiiRe7N/B+A58zqljAOO/kc4Wv8jzzBv3gVeZNjJdJHK9X1tLfi0XPPW753qGtQ2q57slhfOJ8nm3lc4IJlFt7PnwO71fw81nI82DIjzh+lzg+a+iH1weZT3LdcWk2x//PnF8n4xrz9XPa84u/5/psI9ctL2r3bZg/jadfWhTe9+E66yzjBPsr5H0ERw/zrCI+50n/qOBzH1tLDNJfULt/wvsGfN79NJ+PO6xdxysT+w2ukO8jmd9sy+R8cBxnMA7O4Ph2UN/sVyl3KuPUAOXz8/nvTyrymesbA/3xwDrOE+f16gquY3i/aYt2n4L3F73ac4K0y1q3yHtCuz/IOLY9kuc7jquJ8fBCmaJMDo2T9ryw9nxmAZ+XGMfn0pjvRPI+VrCfz6VV8rrHj3WSt/L+5W3Oj2Em82sb46j2XFIer2cVMJ/VnvMy8LrEct7ne57tpFDeGvov48ElxvHTK7TnQBlHqIf6kiL13O9AI8dDpR0x/9U9xO+7GRepv4NxuWOZInJxXdhRqUg/2vOE6xmvaCcJHLeg9lz8ArGzbN5PDNI+bxbxuUG2d+Jp3p+k//Rrz1Hl08/n6Ph3OHzeS0/9+HzcpGc5noy/M1zMlxx8bpn61m7gPFDfw1wv6bS/v9H8aR0/f5zxjv2vot+cfYj9NvH5hS76wzieF+dwXaHdD5/J8yHz3dls7+YK1nM9q3I/7zrNTqVMeJrzxvP9Ee2+lnY/Qbt/X8LrdVzfnuN6pWONxMnaYq5He7keM3PeH2B8+yn7Zzw4zHXc9vmMd1mME5xHt4vxlvW3f8J8x8I=
*/