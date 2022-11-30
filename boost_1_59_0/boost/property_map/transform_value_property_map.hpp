//
//=======================================================================
// Author: Philipp Moeller
//
// Copyright 2012, Philipp Moeller
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
//

#ifndef BOOST_PROPERTY_MAP_TRANSFORM_VALUE_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_TRANSFORM_VALUE_PROPERTY_MAP_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <utility>

namespace boost {

template<typename Func, typename PM, typename Ret = typename boost::result_of<const Func(typename property_traits<PM>::reference)>::type>
class transform_value_property_map: public put_get_helper<Ret, transform_value_property_map<Func, PM, Ret> > {
  public:
  typedef typename property_traits<PM>::key_type key_type;
  typedef Ret reference;
  typedef typename boost::remove_cv<typename boost::remove_reference<Ret>::type>::type value_type;

  typedef typename boost::mpl::if_<
                     boost::mpl::and_<
                       boost::is_reference<Ret>,
                       boost::mpl::not_<boost::is_const<Ret> >
                     >,
                     boost::lvalue_property_map_tag,
                     boost::readable_property_map_tag>::type
    category;

  transform_value_property_map(Func f, PM pm) : f(f), pm(pm) {}

  reference operator[](const key_type& k) const {
    return f(get(pm, k));
  }

  private:
  Func f;
  PM pm;
};

template<typename PM, typename Func>
transform_value_property_map<Func, PM>
make_transform_value_property_map(const Func& f, const PM& pm) {
  return transform_value_property_map<Func, PM>(f, pm);
}

template<typename Ret, typename PM, typename Func>
transform_value_property_map<Func, PM, Ret>
make_transform_value_property_map(const Func& f, const PM& pm) {
  return transform_value_property_map<Func, PM, Ret>(f, pm);
}

} // boost

#endif /* BOOST_PROPERTY_MAP_TRANSFORM_VALUE_PROPERTY_MAP_HPP */

/* transform_value_property_map.hpp
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
*/