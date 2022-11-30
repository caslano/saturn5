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

#ifndef BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP
#define BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP

#include <boost/config.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <utility>

namespace boost {

template<typename Func, typename Key, typename Ret = typename boost::result_of<const Func(const Key&)>::type>
class function_property_map: public put_get_helper<Ret, function_property_map<Func, Key, Ret> > {
  public:
  typedef Key key_type;
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

  function_property_map(Func f = Func()) : f(f) {}

  reference operator[](const Key& k) const {
    return f(k);
  }

  private:
  Func f;
};

template<typename Key, typename Func>
function_property_map<Func, Key>
make_function_property_map(const Func& f) {
  return function_property_map<Func, Key>(f);
}

template<typename Key, typename Ret, typename Func>
function_property_map<Func, Key, Ret>
make_function_property_map(const Func& f) {
  return function_property_map<Func, Key, Ret>(f);
}

} // boost

#endif /* BOOST_PROPERTY_MAP_FUNCTION_PROPERTY_MAP_HPP */

/* function_property_map.hpp
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
*/