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