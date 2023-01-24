// (C) Copyright Jeremy Siek, 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/property_map for documentation.

#ifndef BOOST_PROPERTY_MAP_ITERATOR_HPP
#define BOOST_PROPERTY_MAP_ITERATOR_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {

  //======================================================================
  // property iterator, generalized from ideas by Francois Faure

  namespace detail {

    template <class Iterator, class LvaluePropertyMap>
    class lvalue_pmap_iter
      : public iterator_adaptor< lvalue_pmap_iter< Iterator, LvaluePropertyMap >,
                                 Iterator,
                                 typename property_traits<LvaluePropertyMap>::value_type,
                                 use_default,
                                 typename property_traits<LvaluePropertyMap>::reference>
    {
      friend class boost::iterator_core_access;

      typedef iterator_adaptor< lvalue_pmap_iter< Iterator, LvaluePropertyMap >,
                                Iterator,
                                typename property_traits<LvaluePropertyMap>::value_type,
                                use_default,
                                typename property_traits<LvaluePropertyMap>::reference> super_t;

    public:
      lvalue_pmap_iter() { }
      lvalue_pmap_iter(Iterator const&     it,
                       LvaluePropertyMap m)
        : super_t(it),
          m_map(m) {}

    private:
      typename super_t::reference
      dereference() const
      {
        return m_map[*(this->base_reference())];
      }

      LvaluePropertyMap m_map;
    };

    template <class Iterator, class ReadablePropertyMap>
    class readable_pmap_iter :
      public iterator_adaptor< readable_pmap_iter< Iterator, ReadablePropertyMap >,
                               Iterator,
                               typename property_traits<ReadablePropertyMap>::value_type,
                               use_default,
                               typename property_traits<ReadablePropertyMap>::value_type>


    {
      friend class boost::iterator_core_access;

      typedef iterator_adaptor< readable_pmap_iter< Iterator, ReadablePropertyMap >,
                                Iterator,
                                typename property_traits<ReadablePropertyMap>::value_type,
                                use_default,
                                typename property_traits<ReadablePropertyMap>::value_type> super_t;

    public:
      readable_pmap_iter() { }
      readable_pmap_iter(Iterator const&     it,
                         ReadablePropertyMap m)
        : super_t(it),
          m_map(m) {}

    private:
      typename super_t::reference
      dereference() const
      {
        return get(m_map, *(this->base_reference()));
      }

      ReadablePropertyMap m_map;
    };


  } // namespace detail

  template <class PropertyMap, class Iterator>
  struct property_map_iterator_generator :
    mpl::if_< is_same< typename property_traits<PropertyMap>::category, lvalue_property_map_tag>,
              detail::lvalue_pmap_iter<Iterator, PropertyMap>,
              detail::readable_pmap_iter<Iterator, PropertyMap> >
  {};

  template <class PropertyMap, class Iterator>
  typename property_map_iterator_generator<PropertyMap, Iterator>::type
  make_property_map_iterator(PropertyMap pmap, Iterator iter)
  {
    typedef typename property_map_iterator_generator<PropertyMap, 
      Iterator>::type Iter;
    return Iter(iter, pmap);
  }

} // namespace boost

#endif // BOOST_PROPERTY_MAP_ITERATOR_HPP


/* property_map_iterator.hpp
WaJgVc4BxVsggTmV2Unpv8byqnaM93VQWkqISnu5cHkkTR7iiDCsYFmrG4zhQR6f3leNOZlVT0cPioJgnRV/iK75CaVLJwMFjtIBaAiY9i4tWapybaEWVVI0T4HZSjro87aoJHwpTMX+8MrSqM/NxoB71DmWi+ARgTW1QVkwZK01gPLlkrzcfl4T5hsQTK/hb5g5aTipYwwy/MA8xWb+ZoURmATyvfcrEb5fTKOIwRwrnonFQfIKdFKgxhTpSTsXp5CK6YXUKaH3hSUDyr6LiQFWffUnQW7vaCULUY2TAgv17b/fEJruhVSsYpuAuztrAY4mLs1qLIJDb4uILn7IIv4rNaKF0959oxpcmB+WrqTEwHDEv92tmVLAhZABBO8DyTDE59UUHth1r/Gyc2qcXLtt8LQJl7l1/Lc/3WidBrqg1y9wCbU68+Jk6ljkTmpwz5bz30oiTNHcU2nD5jim1N1WghMgZbUvHfFmJ3pWXGJXyCJq9sdsYI8ffSW8SMqSWlFsZzP6bEumSK8O2nj9omaFJ5eYFJRIyNORPcxYpu9auipmZmTy4Wh+rofKRXzbQFMjGFEgfls57IHqHaHxQgrL2mkDI6jJlt+UXpuu33aslzWK66/6H1hHwsGKm0S3gegXas5vJLVRo3+T7njNdnJXTATbR9vJJPugy9hTguH3YoB/jCN+NaDhGfNB1yT7XupOAxc2mO3uXFLk
*/