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
uC+h+PtsRwklKskf3bDLsRAfP+9/P1gIQBcSOSUJDeMI2M7StBwPE/VegH1odBjFssc0YVTQGsxM5QQ6bJp0My6S/hXRSdy7JIL8EikXPRWrPbTM3eEAKPT84Virowy8k/khx4iwdR/eZbYcsHM08KSQNu09FZVtLQd/COVdqKmHUHpWgAMQLwh1g1brkS0iqa1cF65f2jBEVVvZN6MTADampKaCbGWrRhr6qS9Bzs7XNlbNXSfAKrAgRsTDJcXXb1I7yM130o91mtQ5miG9y/5Nh6+qs4/Qr6XQmtuhTmHlW6PIKvZGbJhg9QbleRWA0sFqoBKHS9ssNTTzLFRwr81zpE3yzmvpeojolCfX8U9O8B4dW1buKG35KuF/GMqpZvl44Hkzu6fFpzd/hk8hEibOwkIyjesxsbG4YSjkwRaN4aEEiJp3YdFphEPvIbcsHJJJtANWEsg/U73G9pLvtFeprP1VgFY/XxUZ1bW2DHMMAGPEYfmfdib6SsmTbEIXF3AM6cmloXrMY18RqxYOubnp6CyK5DEIZUoY/NB4C03HtQZ6Nir8o7PTiHS7zVXOC+idyGJhvR6Ztx5WFcRIQVDWpJu681lKvNXABQALJ/F2BYWxTbTTC3sJ+SW+C1w6xMie82mcu8Jzuv64cPXfl+/dufTOzqg+aeGin8x1Am1bRHx2lzLkLSl5YxLWbn8cwx0XL7PQA3p5YRjQ
*/