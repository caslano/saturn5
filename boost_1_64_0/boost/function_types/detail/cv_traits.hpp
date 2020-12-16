
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED
#define BOOST_FT_DETAIL_CV_TRAITS_HPP_INCLUDED

#include <cstddef>
#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, <= 0x582)
#   include <boost/type_traits/remove_cv.hpp>
#   include <boost/type_traits/remove_pointer.hpp>
#   include <boost/type_traits/remove_reference.hpp>
#endif

#include <boost/function_types/property_tags.hpp>

namespace boost { namespace function_types { namespace detail {

#if !BOOST_WORKAROUND(__BORLANDC__, <= 0x582)

template<typename T> struct cv_traits 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T &>     
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T *>    
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * const> 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * volatile> 
{ typedef non_cv tag; typedef T type; };
template<typename T> struct cv_traits<T * const volatile> 
{ typedef non_cv tag; typedef T type; };

template<typename T> struct cv_traits<T const> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const &>
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const *> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * const> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * volatile> 
{ typedef const_non_volatile tag; typedef T type; };
template<typename T> struct cv_traits<T const * const volatile> 
{ typedef const_non_volatile tag; typedef T type; };

template<typename T> struct cv_traits<T volatile>  
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile &>  
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile *> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * const> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * volatile> 
{ typedef volatile_non_const tag; typedef T type; };
template<typename T> struct cv_traits<T volatile * const volatile> 
{ typedef volatile_non_const tag; typedef T type; };

template<typename T> struct cv_traits<T const volatile>   
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile &>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile *>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * const>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * volatile>
{ typedef cv_qualified tag; typedef T type; };
template<typename T> struct cv_traits<T const volatile * const volatile>
{ typedef cv_qualified tag; typedef T type; };

#else
template<std::size_t> struct cv_tag_impl;

template<> struct cv_tag_impl<1> { typedef non_cv type;};
template<> struct cv_tag_impl<2> { typedef const_non_volatile type; };
template<> struct cv_tag_impl<3> { typedef volatile_non_const type; };
template<> struct cv_tag_impl<4> { typedef cv_qualified type; };

typedef char (& case_1)[1];
typedef char (& case_2)[2];
typedef char (& case_3)[3];
typedef char (& case_4)[4];

template<typename T> case_1 switch_cv(T *);
template<typename T> case_2 switch_cv(T const *);
template<typename T> case_3 switch_cv(T volatile *);
template<typename T> case_4 switch_cv(T const volatile *);

template<typename T> T                * ref_to_ptr(T &);
template<typename T> T const          * ref_to_ptr(T const &);
template<typename T> T volatile       * ref_to_ptr(T volatile &);
template<typename T> T const volatile * ref_to_ptr(T const volatile &);

template<typename T> T                * ref_to_ptr(T * const volatile &);

template<typename T>
struct cv_code
{
  static T _t;
  BOOST_STATIC_CONSTANT(std::size_t, value = 
      sizeof(::boost::function_types::detail::switch_cv(
         ::boost::function_types::detail::ref_to_ptr(_t) ) ));
};

template<typename T> struct cv_traits 
{
  typedef typename boost::function_types::detail::cv_tag_impl< 
    ::boost::function_types::detail::cv_code<T>::value >::type
  tag;

  // may require Boost.TypeTraits broken compiler specializations
  // to work
  typedef typename boost::remove_cv<
              typename boost::remove_pointer<
                  typename boost::remove_reference<T>::type 
              >::type 
          >::type type; 
};
#endif

} } } // namespace boost::function_types::detail

#endif
 

/* cv_traits.hpp
e8J2aVHUS66fGQKv+Rf/836JXXmWHC/r/Pp0XTjv2Px6ne/nB18Yf8J4SWGhhOe3d106H8Vd5+f7J+uDwF9tWZpbun4/DiyY/xjHpeNPNb8+XP+z+Cctil/son4vE/hGth8c+0P8ZRyWzhdWp7ntiAEAlpiXMte/d7z5rT/pz+drQy0VZQCw3jz7EZn9iALoSRhuFTHUUFTXllXfq6Yiqzp/XhC0d7E0cwL4UbaTM3Y+6vy97OKwsOzwvWwL8/3K75LVlJXXVtRU0dJWkTfU3r8XfrR3OmprBj/KppbGToYu7vYAAADmR81sjmh7Ovyrxff+lFQUVRVUFH70r6Opq/ij/b8IgKmrk5sZAJgYO/9rc3unI99HYmpvbmzqYu/0Iy4asy6qKc76qAUA4GZs42omaDd7VXPEcL6fH/UOP653FtQfnb0UPWp61MXGU172e797/tDzd/3z4sjYxWyPmScAAMCiHme3M9TQVNGV1Vbco3jg712fOdttFjT996/rTC3NTK1nN1xaiRjAGgDYRTi28KfpfZakFL2yy3q1MTHVXUl/Wg4qcvhfiJgL/jfClk1Q+rGzfYjv4nOkL/34REjfKhE1RoyNN1tfbtl9huHqCXSlMmr6gOjGwasWupfs+HZ/YzjogWhyNCnVBiXKG1b648ifT8fJi4gImMXKdPls6Goer9rR4UoR19oWb3iZ4uLE6vrn3vyVlf0SGhM1bXHNHdSZhyy+rknOMyIKXjMusbs683q9xjOenkG3lKgRAUYi7w/Ocp2mZ22bEF6682hHhA3PJUi52cAYMKUlwfbm0gk5KfnygvD9JrH50UpM1y4XaTELEQfVnqXrHd9nx/Fyx7pdPPlM4bWHiNCvNWDcwoB0kpzJSc4yWHIEsdS9TEmnYx7auc/lid3xY0M3hd6oKy81v2sJ89tW83WtG7lR1/i7iScJA24humvptZeYX4yMjEupWF5T7AJ7t0eC64RI/ektXZpycH+fL2k756odSLxuD2tJs5r9ucfPyPKPJsUrUe30FDnftNMldLXozTdEjdgIBxvTAfOrb5mlQz6/1duV97604fyPgz82sLr+2Po6tbz8WoC/8lcrUJVklcK8q3orL/Se/7akvxh5Uar7nULyqmeBo5RhlNQ++9a/dyK1yB0Wz1ffFSHjIory9q4PpBN/xQqc3HbqxVS2FAlqp+4EU3I7Pj9rc5fsvKXaK/MTd5u5TorHLGPiCH7Vev7ujwn59kmtZ+2656XRVFl/7a9G4/gz/Wy1o3YWlq7G+1zHrbZmli0d34vc93ZKcWXoppEdPa+t3Mf/WreYkugzKX3ScHKv+Dd7pi+HduHDu7S5Ni77MuXts19tRdeDcPYBTWXXLxFdlY0kN7YcWLnWgP7trmHpj44nw3ZOniF5+MNffN27NaupKVAC7fI/+wsAQA8AdggAA1jiwpcMXg8854sn1ZfxPSdR9jDBO8Fhz+Wh+yvgcKcyRdWRNV1RtaJ5vEM3O2ZGKLrRB4ikuxVskVQCX96fvH75jdFHvoju3fuTwP6CVorA1ZdPyovpfI2vb+15trHQSncTAAantJwTRy58WrM/+clGCsYWUpz76sJ4MhDiqU7boM3zff51hHjORJwIgKW0DOM11/K2sNA0tbKcNNPu4ZbhsT6S+lnTxEJQcWz/BvCwtyggZzodn/lM22SyiyI9aGRrUedUhgjplzsfkjuurUvZGrvtQ/3unpxVbocGxUSLvhiI8okMUmYoNnAyvKX8EsDwVeaPR7MMypjbMRb1cTdvXFwqHxgI1zrkjmNCY5zf87eq+5n+2p/5L0PF667m7l5Xam5La/5WntWRZ28YwgYZSFmJI3k=
*/