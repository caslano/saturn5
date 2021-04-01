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
uFrNfk6hJvdZ5r27MBGtELMIkN6QUp+gBjl/HJL8aPjNZJefLriXNnBLVnKSXPV/Lyo15r1D+NwRLopw/mIAC23Z4QjBawoLvALVy9QIDgM1LXc/LBo3v1spEuUJNFFKoJMsp9YXWniR/f1INBM/8l9E8MbMDbMHrfXxVt3wEf76QzPms7NXds8/6HQCAx6KZPaZXqw21dtsZRuBHiLTOCRIRAwI0J3EirssnTjyJIFinLZpvoX6AMrFSsbw5O/cl259qqv8BDF7hOq3hA+hc3LTeHheOmGh5XZf4600rR1yt8vDXT0UBcg5Mq5JsPMsjv9m/ZCP3tVVAIyNKHVK7TCxRE7b7lbTKKEMGPdK3wzuGpouqHVGQT8JiTb/7fZJ9vyIoXDKYpy7whik2fghbWqiqGOyvIIotZ8fKcEHPdPo+HYCMgW6NRpd7y4KxyUOKh8LrGt/SN3OteISOjJ2QFpI+mbIX7IpUEcChZ/Kfwituq35cnXSykB2eT9mUTf/afDR/tQ7tfvmLKZexK5S1YKOpkdLRkmksVeT40WdU8hJRmUOdgf09H927A==
*/