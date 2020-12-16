// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED     

#include <boost/config.hpp> // BOOST_STATIC_CONSTANT.
#include <boost/iostreams/detail/template_params.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
 
// 
// Macro name: BOOST_IOSTREAMS_BOOL_TRAIT_DEF
// Description: Used to generate the traits classes is_istream, is_ostream,
//      etc.
//
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
# define BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait)
#else
# define BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait) BOOST_PP_CAT(trait, _impl_):: 
#endif
#define BOOST_IOSTREAMS_BOOL_TRAIT_DEF(trait, type, arity) \
    namespace BOOST_PP_CAT(trait, _impl_) { \
      BOOST_IOSTREAMS_TEMPLATE_PARAMS(arity, T) \
      type_traits::yes_type helper \
          (const volatile type BOOST_IOSTREAMS_TEMPLATE_ARGS(arity, T)*); \
      type_traits::no_type helper(...); \
      template<typename T> \
      struct impl { \
           BOOST_STATIC_CONSTANT(bool, value = \
           (sizeof(BOOST_IOSTREAMS_TRAIT_NAMESPACE(trait) \
              helper(static_cast<T*>(0))) == \
                sizeof(type_traits::yes_type))); \
      }; \
    } \
    template<typename T> \
    struct trait \
        : mpl::bool_<BOOST_PP_CAT(trait, _impl_)::impl<T>::value> \
    { BOOST_MPL_AUX_LAMBDA_SUPPORT(1, trait, (T)) }; \
    /**/

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BOOL_TRAIT_DEF_HPP_INCLUDED

/* bool_trait_def.hpp
Fu6E6+Eu+Du4Gz4BX4R74UvwdfgKfA/uge/DYvgxfBV+Dl+Df4dvQC9pexvWge/C5nAfHAD3w9HwQzgGfgTHwY/hJfAAnAEPwlnibue/yFnDC7c73zaDGyT/y6U+rpb6WAE7wlWwJ7wW9oWFcCi8Ho6Aq+FYuEbq4yapj5thFlwLc+HdcA68FV4Hb4cb4Z1wk5zfAu+Cj8lv5/mQLum+2PB8GI8/D7xE0j0BdoLpokdTRd8nwfHyW56HsjaRe9DwPMyS5042rAVzYQM4W/RjHmwE58K2MA92FHdH/9dL/E8a9P9S/EXDy2FreAVsD6+TeBbBMXAxzIZL4Dy4FF4Kl8ObYQG8B66A98OVcBNcBber+KQcnTVtsL2hHJ9Wl0TPYRR8FsbAXdL/eA42hC/AVHGX76jLOjHqTOLVv6N+p5TjXTAGboCnwt/BNvBB2AM+BM+Cm2AveB88B94PLxB/GeJvivibCjfCy+Ef4W/F353i7y7xdxROc9ZewSmSzhpwvKTzXvTC5kbYxA4PW8KtsDXcBLvALbCHuPcU93RxzxT3o5BniawBUuud1PXs8jsp1zuTdNWAPWEz2Fvqvw8cAPtKv6Y/PB8OgJNgBpwGM2EBnA5XwMHwBnguvEPc18Mh0i4NhQ+L+2Y4Aj4OR8Kd4r4bng/3wFHwPXHfB8fCT2Aa/EzcP4fj4TfwYnhS3P8B06HPY/+W57+zfgbmSfmHQ8pQHfTFVXnMgi1gNkyDOXC8/M6V30dhrrPuA86T+KJhhvP9fokvDTaF4yTei2AfOB6eDafA/nACnAEnwllwEsyGmXCu+HP6lZbUaz1Dv/Jx6Vduh6fAJ6DoH/P6ofXvZQn3KmwC34At4XuwNXwbdoHvwh7i3lPc08U9U9yPwm4emSeWOXWup9LYBtrH+/jzwv1yn38o5dOE+moFP5Zy+avE/ymcDw/DhfBzuAR+CdfBo3AT/BruhifgB/A7+An8Hn4Lf4B2/+pHWBdaXO806IXNoB/2guFwMIyE6bAGnA9j4OWwJlwC4+BaWAveA+vAP8FEuAvWhXthMnwL1oN/gw3gCdgQWhREI+iDTaCqZ4/Mmcq8cYqHc3Y9S/l9Ke3ZcdgUfiP9hBPSbp1FOzAEfs/vi+APcAL8h7RXP8LF0IO/NdAr/Si/9PfD4FYYCZ+AUXAXjIMvw3j4N1gLfgkT4DFYT/r99WFz2AC2gY1gN9gYjoRtYTZsD1fATnAzPBM+CnvA52FP+CI8C+6BzeAXsAWsSbm0hK1hK6ef78zbgYGG+7yHPGfOgmfC3rAv7AP7wV7wHPl9FKbbUhTYbkTB0RJfa7nPU0V/O8BesCMcAztJO9JN2pEucCbsCnOVu1zHmRuCMwzXaSDXOU3akxS5XmM4FDaFI2ELOAo2g1NgczhNuTvth8xVwBsN7cdWaQf+BG+Aj2jh0st5718o4S6HcfAKCVfojP3CGyRcHFwi4dARVR8tYBJsI/3eM2AX2Faex+3gEJgKh8P28lzqCkfBTqLnnWGWuGfDDnAl7AKvF/f1YaTbtk+ain1EGMpe6Wpky6Ky9krTfhtos3QWvwsRk+3Sd77k78XYm0QcO6aHj/itnotD2zNNXxzapmkB5zYgLyOOfdOTizl3VYmd0xRY1tYpxN2xd5p/VaDN03X83oK8gZxAui3BH+LYQm3wd7+yh9oHTuP3kiX4vdZnHUJ0+6gbcc/Fj24n1c8LexFMWEo8uPWE6YhuNzWf36uRYPup9+G2Cu6CwXZUD+Gm21JNPULa7bDLSm2qriUtO5CY63yufdV0zveE+bAQSe9F3DAFP4cIs2tZqd3V5OWltle78XcaIjZYGaQjfkS3xbqd38U=
*/