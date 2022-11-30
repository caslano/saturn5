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
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
*/