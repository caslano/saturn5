/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CODEGEAR_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_codegear.hpp
5QOXnUr1N+mwImCCK9a0+lTQDlhmQqaCuiWG105QL1IsheRG2RIWHDP35Ew5srzPQQlb4NbwVHBv2i/225UaqjUNvu4INSLvFwu0ztTDgb4R4WMAFQolDvWMdFGPxIdV2Atn8Fa7N8VjDxONOVcUV4YC7Tghq5w1FRxeAbfMbygDO0apTp0KO0i8uiqio1mdeX6CMLBbgjXsfC96p7cuPXvaxNIxS4hpahwX8DUIzFChYI2QUEgHgY2vZmIkHCwcHwrEgs1ql6HM0A85QgEJ9TrnNjVBoQ53W5qbo7w47HPd3C0BaOPzuUAGvAEbh5k7B4CeMd85JbA2L794QW1EMK1UWBGjJDDbSB71sSg6KNIwY0UaeitEG1tjn7HoRNzlEv+VGRuSl2OrhySc2J+7MksciG9UwUxV3IPyIkKRgqy164ForlfHVow0+YfG5eCJWtFueowmDKlyyxyOz51UaawEbd8teBOW3qGAbZNpoW0lSlqtSACjrlGIoiOrsUO6SL2fFkAzbcjg1HyUoIqBuhYOURIOHSbHAtTTzapPw20Xc4S5bvVM6tSEVp/0UPOdx8WbcrmjxlcdMmwEvobLHobVfTRyvqMDNUJIy/jLXCPh/q5KrlTqehZy6ahqlbx+z+vURwi5gCNxteZSjMDKjvCBl49zKWPliLpKiuQEcjpaCVgrvkZiTfr+ScBakkBc2fLSWhvmkpU92s27
*/