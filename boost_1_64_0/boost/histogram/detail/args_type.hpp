// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_ARGS_TYPE_HPP

#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct args_type_impl {
  using T::ERROR_this_should_never_be_instantiated_please_write_an_issue;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...)> {
  using type = std::tuple<Ts...>;
};

#if __cpp_noexcept_function_type >= 201510
template <class R, class T, class... Ts>
struct args_type_impl<R (T::*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class T, class... Ts>
struct args_type_impl<R (T ::*)(Ts...) const noexcept> {
  using type = std::tuple<Ts...>;
};

template <class R, class... Ts>
struct args_type_impl<R (*)(Ts...) noexcept> {
  using type = std::tuple<Ts...>;
};
#endif

template <class FunctionPointer>
using args_type = typename args_type_impl<FunctionPointer>::type;

template <class T, std::size_t N = 0>
using arg_type = std::tuple_element_t<N, args_type<T>>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* args_type.hpp
zT7ex30MJ+ZivI86IjLTJX58rmHAFTiUWZfhF++MNyar8BWBQ72gf1B9nuUXl5cTVURPSEpn8JXqrEre4Yg67nwuiidlBznyI2WdP8IDb/qRiNJU2BHjozI7i0VyOIZ7Kq/F1Nd+ngjnoElGlhtQEWkaXzbY3ED6i8W0zNvg51Da3anwipBP9rdwLiIrOvZpO8yhz3KLF2g+vdIBrA+hueQm4nJe8bJbaTt8yvVfWRW3u8grSi9XM89AbjfuZvdBmsvIlL42+Sw7Hw28h6kxC4AusowpJhITV2EqCmeCQt2oAZ1FKkUAHoOz3KQHmWTUv5vfWKmz9iU55i1b7KfuWsSCFbInOwVewoziaWval0S2X9intbg6fj2e74t/X+1NsN8aH//+6bj4d5GQ34WD4t+/6e3APmvraHBuex77p5J0tLwrMzDe8rSbx98egDghFzBPYl7q6EQnz7e4iLuuR+yZPE5SWIi+HmlcllBjFct7KMo50xe9EM/Q0+aIt4YyvYR7iRYX05KZG4SWC3n5ZBwjzNGm/pYv0biLzj+UmdOuL+7o3tSz1ZILuqakTMOc4+Rm5Zj2+WuscZqRebm8GZ6PrdfVvUx7VuzpXCJrdZM2X8oDWWXRZV3NZTLSIXqOVSJHbs1gGThEpdiBZSduI5EqcU4XLJkSnGY/lTr7hOty87zl7drjXEDNNJJ/rjARxZZbIlxMVovE30AFWIt3eFgRHnEHG/lls+9dleXtyHJATJY0K4qHTybLuI9GUjSvEsUSpzqMWgKh4DhTkFyb/pzgH0lX8I7jwavz3T4GqRIZPuksOLAqsqCRHpwVexNVuZCuv39GdJmRo/1EtVr55splJqj6Vvys1EDQoGMQ5Aac9vix6Q8Dp37xCyf72EIuCn/jPVLamQM3U/rKkz+loD7y/Bnr5aCrGHC1ccopER8wQ/1jHyn2ESWoA5iK0DqCn2fAP3SS8GMN+B99Bjyfl7M0HZO+q5H+4dj0mGcOnBXdEKgTIpDBJ0R5yn0796TPn6L9Rj6PJOT/iBH+c5n/gM7R/O88lfzHnhVT/26ymPTBP6SfZLiSUMX1k2DHzxP4IbgkCdd0wv6uGH1sf3McvuKOC4z9iT5xULR3b9xRTKdWuvBFxeYlxQ3FnWp6NkxO0t4B+XpFeCQone/ver3OTidQ2LSmux5aae9sWd++0F5SX97ZCj9asKvZSad34Eam11GLhQ0JaarO4icXbslZfpIKdi+ZOe5rstayLzi9iYT29EcKlvv19vUR7EKm3j27IGKptVb6agagluwXdGTULDMZx7lQzdcXbJnTg/cjFpb3s+qr1x/AFcr19osGbZi9e2X55RELXRx0Ujr/+PpwbWAWF/HsQwkesi9qKlgJi8wLyD55W5KxWpw12rMq0G53PhCytcP7GIIttr2DPpmNatV2QQOOWurMdmjk6d1oybfIlq4FWZBWBobAbt6YwJJkSk/uQ341Ci9h+y+zfHwHVglyE+pZhQyOKZ0UbqjBumNqYF9pH2hBxqd0i/TxPso/5m3lcv/SLX1e5ymfcIEIkdyhhjHWhamVTHIHPLv4Fu8r5frLULM2c6POqhKvqenTWR9CLFrhmncgEoE13nfIoT2chWLfsfcq257A9qNw7WZrxfXey2puD6yQJFzNXnnzKuPQWjsN5472YgV275OUJSBUoU0otKBKjEeh7IaTF3h58w5SIdMnz9tJv/pqumop1Np53vsRG2oQsmzC3+UW3AwovVKl6Mvrr7bS0/CkwEpbffdwkVpkpTeZl3Z6xXe78ySGOI4J7XTUdx++EDWpT7FhZTN80Fbnoq9DfCe3lNR7ZPd2Y3OKMbryTYNdh+w=
*/