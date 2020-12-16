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
oYk/PuOyYCiJB6zEnJh6hoKD9ueaNof3RaadRuKoLvYhnrPwoEOnW0H9qt9qwW+BYX8vnb8B4ku0+nZ5hP6/9biz6/9Zu98b6muL7H4fpsvVbO3l5kpoL5XuevzBlD5+QEZ5kK3NRBvsFuS7NrPzHXX+ydFLky4UTS789vj99AV3T0ymNtMLbWbqy7VJdJfrcHww1PXy903+Vu6BbY/Dp06I3q2O5AFrpu4X3doO2Laig+wu5d5SHgS7T/SV+2FHi/5xIuxB2Gmii5wDexh2nuggA7BHYJdJHrMVsMdg14hucoPoJLfCnpB8cydhd8GegT0Eexb2vOQ5uyg6yNuif3wu+seXonf8LHnxVFufwjaFfQ7rtvdvpr5tpMyFj5K58NG2flN+29U5F/1mB7mvI2xt2E6w9WE7iy5xOGwRbBfp526i4+wh+fl6iX5zAOxg2CGwo+Q+eW757UW9Ls89Q+qfKZ/rLFt/KL9psCNd9IfjRH84HrYQdoLoR0tEPzpVdLWTYEcU/LyHza0tlobvDazS8X1cqnVwoudDGecbbq26pi+l5+sJH6NxOPV8bYLper5ZW931fEmcF01fmpZvdDAjf5vo+ULw0QHnNuO+wqXZ5XE7sNXS8F2EvYvjtfKxDZpAHIu2cR2FEJIbch//l5plfgSfKuQNBBMY8+bFPoAnHRqCzTJ+wS1irbhkvewD6IjqfmqM4Xi37hR8Pq5EXms1Hj9+KDUe759RHugYh+ffuPH2HT1+7njt7aPTg662mFv0aeeTObvLG0/mXxzhPj7PvzjCyqMr30H5Tu4x0vPoNpbxWRPJ09wMtiVsU9grsBhDZY6tKtwTMJu8hZKz0HUcJDkKs8pNeJFjGUIIIYQQQv4oPhzNJP6fNGZGyZjJ/fr2Uon1QHejWVFNxxpofRzh+enx+uQJJZOMHPkghBBCCCGEEEKIN/wq/u9lDHXG7qA+1uxv+g0juzkA+qEf+qEfr/30NarBDxBZQc/D1jsuxoTEtHg0gG0fovGxpj+5Mm5Ok/dxlPYmZ/XTD/3QD/3Qz//thxBC/gd8OFrJ7+KcUTNml8yaMGVMn/69y12/16p9l9/FHPohhBBCCCGEEEJIbikv/q/q3Gi++mona4OFBYZmUGptMGyGkYFMrQN6Ut8aqa+vo75AbG3O60utfX6R+oan6pOMZgutBGfx/tiINhzWeQxy/gyEEEIIIYQQQvIXH47uEgP6Y8HicKIYmcyLkeavGOnUV5mwoT7FfYqtoFBiQp3HL0VtsS4xoce+CSGEEEIIIYQQUjmqFP9nsSZM35y3IIQQQgghhBDy9/Hh6OUe65qRVcF4NBI2I7+5Tu+1f0IIIYQQQgghhHgU/3O9mxBCCCGEEEII+Wf4RfxfFgyZibWJpBl2hv9VWJ/32j8hhBBCCCGEEEI8iv+zWP/32j8hhBBCCCGEEEIqjv+7usfnS01/zBGZZ78u75VfQgghhBBCCCGEZEfW8X8W6/L0K35lb/6dBYbmnr03f8JMLoyYqxeGo6WmtR8/IYQQQgghhBDiBb/Y/y8UDfhD5m++m++lb0IIIYQQQggh5Dt79/LrQhQHcPzUK4QFIhYW0ohYSJTrHSHxTBASQUSo9E47p+1EO1Mzp5RYWIhYWIiVhVhZiFhYCBYWllYiYiHBf2BpYenMnDO905IbxZSbfD/JzVz9zfzObx4dPfectvg1v9X/H2Hsu2THvm/btV/2x771V+nXvYZqhtJxTVNCMAYOAAAAAEAeppn/33ZU84/ep59XXgAAAAAAMJqR+/8jjP3nlXeVnVPwwa59uD+nQPZqsqMmzDyC3Npfa9ufLIjEtX778Rv6u5EM4yZkGDI=
*/