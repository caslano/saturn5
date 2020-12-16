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
97f72/3t/nZ/u7/d3+5v97f72/3t/vZ/v/0N22ORT10dfLeiGKcoitemU8bh+92r9IoO5QG3ojyN8rjXMPI5oVQ+L/ykMvK548e6kbI2HMejtL0k3wdflP2vtMvnI32y34l8OX6LW+qT/FLuy5R6w3jpd+Eb8nnXBSnX/CFMvsfx81BO+aAcd2Gc7D8pVvZzd4WJ3LmUu1z2M3nk+2nPyeeKlXLcngj2p4bLfsXyOWGD7L/DKuNhmiD1aoL0c3y57Ne7S8op2aLn4Sa9tL9W+t98WY7bWmGQfl6nXpAjAmVmHvtLkv2O/FTqN3N8N78aLvvz83SrlNtnUc/3GZQwlKc4ThM2yfeF6wxKeGh83pDjOzwiz+0Y2S/olv3WbJP6RZznbd+S9mdTruk79FLvxxijvLlbkXF/TRlp31AaLvuxvdNzpDzIdrca9NLejzn/HMdIzsvscmnvFOdtj0vqgxzPq5XyOErtT+T4Lb/QSf82Kb2xclz2Axx3zldCa/jIuGRm0H4+xXbnSZm9QfSdMT5c+n9OPh+p5zxclXZXrZHvp6wTeSf0Sb2Oem6lvAdojydOyPf7qHf0Efnce14n7fXIuJ3axn5nyPeXZkrZT3km0M8Kn5Pvl9M+t39B2tt1guNWJvtFzpbvr8yQsrZI5DlNvztI+w92Uw7Nb9bKfrc5z9spz+UBjjPlPGCR/s4zDkx7VZFxeL98nsFxD9J+tztErnMb6O8eylks5Sr63eXn6Bf0l4NxOrEn6mOiPEmfkP0vLQyX/Tmue6jncc7v9B9wfsqlfAWDPR+l48+0d9rRDNSjSsnm5yQeN+1lKa+/Rfrbx3aP9Mh+2ay/zXFTKX9SE+NhnuiR0Eh5uX+mKvttC0h57gP8zPZndNDfOS8VyfJ9Le3JVKIoWSi9tMeUUsrxLO14A+Uclv13z+Bxz1Aem7Tv0Eu5db3U36YdqxvDRS7Kk7RAyhTGLe8btMsoke/KZkXGk/N1ezP1/xb1oB9dcRqUyFDcYLuzaR+69aJPP487rsWVxxlfnVLfQf36HSLHHu6vLlVEnuelPKv1T787zM8nWCYwPhx5jf08wflkvKzgOHgp/xHWn2Y5nfFJN4fxhPGuP0X0Okg7dawSeR3dHBfqu4N2eIV272a8X8XzZHQL4xj1PFtEeVfopZ3PS/22B+XztHNhSnjo80Vp/zrjgoH995bSb38m9bZaqS/czHml3U4vk/II/Sqa5yuvVRF74Lgdr5H9LrXSXunPtS8p0m+v9JNQSD9+SS96x/J89yTPpzPDpJ1YyuWV/a/2y2fTONoN5bdxPqITpL6X8dxQalAMoe9nc3yXUd4tImfwfbQXv6KEhcbzYyLPtvfSnugX0wKKzONG5gesP0B/THmZ8nDcDTlSX0H9CjPYP8/Tjmd1Eic5z1t2S3lqp5QnnhW5rrP/3ZyXLas4z92Mv4ynV7I5vhznNYyTW8ukzP4k85ffSztTLuqk/Drj5DwplzOfmvQEy3zOk0p7oB9sjWJew7ij1vG8V8F4tUb8Mml+uOjJ88AM5jWzX+N8M14sYnw4x3hT2CvnvxnMm7YzTzu9Qspo5l9B5jfntDxngOd/h/QfPYHx6nnGJfa7Zw/l5/zfXs28Zjz1pLyvPMl86RTP87WSR0Vy3jIx/oZQO6ocvyeb4884209/u9AtZRLtb9s2+pGTdrReyg7KdfWTisin+QHn9fJ6fnZLmfAp2T+S9jdlLe21mvGY/nT5x5zPldST4zib8aSjVvY3ZNI//dQ/kuPM448vpfy7OH4n5fjljB+11GNHOdtjPDo1S+qjH+B8LgiX9uiHhZyHIOPjQY7bBMaP7eukfIVx5axZJ3Y=
*/