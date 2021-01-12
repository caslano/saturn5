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
oy9IJwrlEh94r7RTVrMskwjDhID/HrcXsLaT1CPN5C63bl+2V4lERR6Tf20e0D9PncEZ1eA6rVCdk7MraPy5TjtQR5LmCJzDQB2elVq+DnaqyO5wowsAzE25nUTW5nZHAdgSZ1hgH4fqnHZG71X/B7f0z1OHrNqoHurcMpwQyyP1C874DeuKyAcO43Fq92BVh8BYCKqCEsLkV6XV+kWt2XDaIAzLOVz4KfrhSY/bFFcPbVpu
*/