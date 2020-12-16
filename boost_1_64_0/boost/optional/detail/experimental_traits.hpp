// Copyright (C) 2017 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_EXPERIMENTAL_TRAITS_04NOV2017_HPP
#define BOOST_OPTIONAL_DETAIL_EXPERIMENTAL_TRAITS_04NOV2017_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/predef.h>
#include <boost/type_traits.hpp>
  
// The condition to use POD implementation

#ifdef BOOST_OPTIONAL_CONFIG_NO_POD_SPEC
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif defined BOOST_OPTIONAL_CONFIG_NO_SPEC_FOR_TRIVIAL_TYPES
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_CONSTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_MOVE_ASSIGN
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_MOVE_CONSTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_COPY
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_ASSIGN
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_DESTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif BOOST_WORKAROUND(BOOST_GCC, < 50000)
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#endif

// GCC 5 or higher, or clang with libc++ or clang with libstdc++ 5 or higher
#if __cplusplus >= 201103L
#  if BOOST_WORKAROUND(BOOST_GCC, >= 50000)
#    define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#  elif (defined BOOST_CLANG)
#    if BOOST_LIB_STD_CXX > 0
#      define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#    elif BOOST_LIB_STD_GNU >= 441200023 && BOOST_LIB_STD_GNU != 450600023 && BOOST_LIB_STD_GNU != 450600026 && BOOST_LIB_STD_GNU != 460800003 && BOOST_LIB_STD_GNU != 450400026 && BOOST_LIB_STD_GNU != 460700026
#      define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#    endif
#  endif
#endif  


#ifndef BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#  define BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T) BOOST_HAS_TRIVIAL_CONSTRUCTOR(T)
#else
#  include <type_traits>
#  define BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T) std::is_trivially_default_constructible<T>::value
#endif
  
  
namespace boost { namespace optional_detail {
  
#ifndef BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
template <typename T>
struct is_type_trivially_copyable
  : boost::conditional<(boost::has_trivial_copy_constructor<T>::value &&
                        boost::has_trivial_move_constructor<T>::value &&
                        boost::has_trivial_destructor<T>::value &&
                        boost::has_trivial_move_assign<T>::value &&
                        boost::has_trivial_assign<T>::value),
                        boost::true_type, boost::false_type>::type
{};
#else
template <typename T>
struct is_type_trivially_copyable
: boost::conditional<(boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value),
                     boost::true_type, boost::false_type>::type
{};
#endif



#ifndef BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES  
template <typename T>
struct optional_uses_direct_storage_for_
  : boost::conditional< (is_type_trivially_copyable<T>::value && BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T)) ||
                        (boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value)
                      , boost::true_type, boost::false_type>::type
{};
#else
template <typename T>
struct optional_uses_direct_storage_for_
  : boost::conditional<(boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value)
                      , boost::true_type, boost::false_type>::type
{};
#endif


}} // boost::optional_detail

#endif

/* experimental_traits.hpp
O+uiJXUafYH+cbn2842vgHXaR3noM3F9dBxNQtf7ewWd80hy4tJuunA4oZx1E+dgK4eGB/afddN27ULz3+/qzNHHafvbKKNI976jKaOyMoaKUATm4/2121TbeR79otM/Ve8ATHSdLZk0ahg7NCekZ+i+Ts4d67LbbSdTUgutirYzd3pUh9k4UCYXdZgJ5lniaqfJVgndTgvLGeMntL9vQ1KtDq5ymTDG/Xwbo/2WkDrI27fkple2lMo76xri96x2+xqlUpzxRbhVE9UQ1RLVCTWGePdaIepbMfr+hre1e3XTXxpyEI4kUAeB5/8kVmHGE45Zg8jRbtfhymfFoW5CpaCqolboesBdQB4mIw/D2cv7iXvtL9C3NdFuetL2I8XMkfO/bJ/1k63foZt6H+IumxHaTUxQP6BPpbv2a7+l3U0jZbFWIed+3kD7ekafBpJvieg4BqWPD8hLX+2mZcDPW1qvWktUYF/Y7dosyZ6vzQJpUcnQY0xnn4VPu+uk06HN8rVxGUc7fie794Rf0nloZcUjV3WsiEB7Lqr9hwXKrYnWH8HdZstpf1e032z7G9KXW5bTzHqqhP+U9hel16XOML7dv0PO+9hzs2MiwmLsSn/zPTrxc26Hc3Zl7v1BZ1fETfxOJ9x5RWMiImPsKtcPt+FOJ9x5qfnDTRQ3g3fKd1Xs+ZU5pu76TnPe+FdK/Lgbob++Uu768e8JxD9/av74nXudq2FfHVVDVE1RqaKSUbW0EjcyZksOGrMFv4uepp4vcu65+FOBd8X1LTErnGtWzzGLzDWr65hZuWZ1HLNftgXMajtm3+ea1dIyiJluj/INPP2iVd6Fm/7Tyhiffv0xpp47u/YDWs4eQeeMkoxN8pzZlHGFe1y5erel/16R/X6HUJuxyXk2/7hSj0s9z0UX2GHObtWk/1uCMvekSBiEnGl1d40NxVzGhrJOHOhfLB3W01YLvRpoe83LxL97P4/uGuTdkXe8uea2577YCTrehq5+w/3dPrnzUbupQv8SHng+rdRm4YE8N9H6yfSMpb2/B+t+1mq3zRjthjlpd/vX+Usx/V+ed4bVtZvyVsHceZn480vby/2G43+7J0/kzFlnzrcfiXIO+l5ibr6S3G7z5dm9Vp18wCRgpW3mMvfBWYnUz478Mpc+hS9pDVO3rLjvXSqc+w0YvveckZVn7XWn1IdzrkGHOcfeYp3xPhOx4xrfepDxZ0Ed3hTb691s4116rBl4vj2h3a4IyEYfbR8n9o7+JivJLReunLllI1yHNdEeZYfj3hlTB9zq57J7fB6t3U+wR9ih1rXutE10rWNGavdqz03BPN9/eVKb32Kp71knudY4Q7X5DLsx0j/airCTXOvoT2u7RVZdqxCjnZLan7MOWlTbjbMLWrXtHvzvvrPzT1O27nvsnDJz33ko7ooF7s7ZofVHnLtW3eUSWONQz6i19G0bXwjcJ1ifl0EVw9QCcaW/vx+/rQ4/XfokW/Iw1C5jJdv97LC/XR9upd02zPOeoZo26/a35ZLk5Ndll2BV03bOvNkx32dV12u5Eft4Hrwga8a3qTXjCG1+AfNimDtrxoOcNWOxS33BuaPvNvfavQ5v/Quydt8kemz+tfuG2GXlhuvv4F67F/u1qB3af9DVMtqdoxKlfi458VEzbJQw377B7L3ceMJSnfSLXY7EERNZMRBmBQkva7+El31Iv3wYgxpKJkJCVPnE6n3TV/DfZr/r3ppX9f2jMSH6VUMhS4cn7jJxt8OEp19GRIcpN+Esp5Mx152Azn35M+UcwOfC0dIHx1/nu4bIvfNdQ+lf5Vs7rj4uyb02HtS2WUMKttNrrzVN2FbPonnfF59/ySQ=
*/