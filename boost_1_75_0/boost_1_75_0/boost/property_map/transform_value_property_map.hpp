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
JPTkldx6bvrhW2gVilb+Z50fmGaxvqq0rmKLGIWrjQf2XVywziZt194V3fz3eYFX+HnhL0XqNjLeoML6fuNVEW/2RzJVyv3Bu90CKkYqvNxkGyQ20fNxH7GKSjY88dtaTxC0aBL8N7fJTp9u+hcHg2eexaDWi8RyucOul/Z3i+1ujlWb0KVFGJzR5RDmmf5yuZ2enWr1n21niqD07SefiSAAMFX0cZFSTD5raWAiaO4nITbDtxBKKDw+x6uNVmuzwz9pKsfltrsHU9+arUzM0cLYi2B57d3wIVddDMr7fRranI4c3OiOIWsfJgyG+/PuI95mhoGWqmS/sIm49Xb6fLYhGCIBR8NB7+g0e319jF/g2NlnhtVWmWXNs1Fj+30xNjW+8BGa5VqtZUViThWud4rZnjFUxy0IA0FukfDIEwuttoibJHgTuW7c5hxH/qkQZ+lKa2jm0oTZRByy8OfQa5F3yDYGw9T2uOQF6izpa27tvIbI2sUkBdF/cJzmTCLlqVALgBhi2mUsZ1KAAjhdJrHNQRy2lpAzNcbPyZ5SB+t5DPs/bZHAOV0SA/QoOK61B15eZl+hK9ieUnzOgmzJG8VxSHcxbXWuJq258IrDxvY/9N2SB+av3qSK47NJSuNhYcCvb5Gl7+3wMqNgP3kbKFwL9bwe3QtTrBdrxCiw7WISxemkcPfoZHSfJRynWM8L1cH2DaIi0FQdhgIo
*/