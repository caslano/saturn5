// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARRAY_WRAPPER_HPP
#define BOOST_HISTOGRAM_DETAIL_ARRAY_WRAPPER_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/utility.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class = decltype(&T::template save_array<int>)>
struct has_save_array_impl;

template <class T, class = decltype(&T::template load_array<int>)>
struct has_load_array_impl;

template <class T>
using has_array_optimization = mp11::mp_or<mp11::mp_valid<has_save_array_impl, T>,
                                           mp11::mp_valid<has_load_array_impl, T>>;

template <class T>
struct array_wrapper {
  using pointer = T*;

  pointer ptr;
  std::size_t size;

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    static_if_c<(has_array_optimization<Archive>::value &&
                 std::is_trivially_copyable<T>::value)>(
        [this](auto& ar) {
          // cannot use and therefore bypass save_array / load_array interface, because
          // it requires exact type boost::serialization::array_wrapper<T>
          static_if_c<Archive::is_loading::value>(
              [this](auto& ar) { ar.load_binary(this->ptr, sizeof(T) * this->size); },
              [this](auto& ar) { ar.save_binary(this->ptr, sizeof(T) * this->size); },
              ar);
        },
        [this](auto& ar) {
          for (auto&& x : boost::histogram::detail::make_span(this->ptr, this->size))
            ar& make_nvp("item", x);
        },
        ar);
  }
};

template <class T>
auto make_array_wrapper(T* t, std::size_t s) {
  return array_wrapper<T>{t, s};
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* array_wrapper.hpp
tF25q5PUFk9xBER353w6GRIQ1tqb6E9X7Ukzi2mtZPFGe5Mj7Pr4LFiLUC11sKIRxELLsQFdgmXfT5Fdldhqo78fXq4ouoiMrtycl5nhba33GxmOJ2dnlG0Z5VQC+HJY84zjnH7AOf0wPqfVrAyP5hQeiWxoIzAAh7RoFOBGC3cnaQfe3r2uG+8fJfnFK+er7ZxvQudQDp0DvBWb+PyRwucvzpWIiuBqzGFJRrQXfiGxUNfKVQD5TOWtxdEIrhZXtrdhsFXgL0WIUvnwVeHBA5AdxTqVLPFIGAzbjZr0GIjN+Lqu2lPRXmu9NcJORApp5/fbbI0fESUDlYH0HdiS2AbTTUKY2F9AiPp1ZYxh/KPSqrE0UoRRwfZPSWz/ZFdywnRjWPTsL9Gyq86u7w539lWLaz/lsUBlV/rEihLTLpoPLoJMkuhAwYE2ZDegkiPl1atg4WvN+ucwMqv7SmTua/0d2JHWaEZ/o/U+ClgahW+dgwAvThWNkwUCI1XO+XPRDLQ23+cVbZfII3x6u1/06G2xSMmmv3e4OKdEncjYpO0wc7yDa7AhT9WgH/LHrPou8hhB7BmHQOTGu+ipcpt1vWhA4+k8F5/9hNYs/DUU/xW8jTD0iaiJhppw2iL5R2zqZdgrzjpbjEYGqNO9l6o6rYnLrptnHz1TWOuPsYFPdGY4VHYZk4Vm3gt7F/oVx6bwwau89PAvvAjMp+lgEpLTIU3pm8At/FKnS6rNoYhiwSe7G6g2VVFtVRDg4saLucfVTaHdASvFLrchaSBvKwLBcdw0o0O5SdfHoEJ0KDtMhJGn44kLeOEMo521A3ycyQOXKmEkT+ulCvb5RW4WqPOQ8hKN9CXSlxGQIrI+aeN2+qmheH/7MnOynHUYZNI3Zhxu6YEWnRc7Dj1sWGDsDueAkFOg4cwKd0NoVrXQ93KjwnbCNNA1GjW7kS6r0a3o2TOqIrc7xO+GqsPkxeES0byPSPsr5YR7QhiaZ9iLML52HMLE6mMXqVViC9k/YAiiLQCOgWoEFE7NZsjS9RXEAP4p90H//3Nqn6Vf5fOfhbH2RBNpE24qTdFTqT+Vi3MMiIs0PSl2CtbuloLq1BxzegVtTaT7j3iB99WmwFy3BWbM9yeZnD28WjwKgVgKe4h60IwaEn7KW00T87gkEpWbK1mSppssrgwHDtid36GLGiJ5DdPOzXDpt7lby5LkJDrNRVMyDUvNgaNTC56gJuWkIA+B4dBV+3W0hNYeNk5DCTRHeC4/Oox0e9jwKdlM92xMuq14lsBI17rSqkrG1Ms3j9gzECJkzqRG/a7VmIIz63oF5uLuWHe1uB9aHUCQGLWLK+CmqWqGVR5+nHCxaVv1mjVqP+cT7UXG6i0wJ9siLywkR8RFoj/K4FMMfJxBdE1jPk7DjzBjWlz0H2aaOOVT+Az4bLpITaQ95C2aN3RDWgljB0zYH5mRLfpCetb2xXLPIpEv50tlqPcWagpQSOt5Y6XxoqNQrbovUO4KyLnxFCwR5eXiecN84raLTAs6uq+i9R2ipUOqJK71r8BZtcNmD6QoUrOexXyudZLsAtq3rU8zcc+G15kWE/c5jPte1cJ9fizuHcA9mC9WBoFDPeuu46S0TbwlAt5nOCtb3slE596YW9CLZDPdcsmijMloMuBIrlK6WGU3o59FNBH1XOSN4uOEsktylFA2FQTIN6bvq0h31U3WrFjHc0EtfQwzxwURDJZe5iLxlvAYrhIysvnFNXnAFq2KyatjG5bQVAIzaRSCOJpYSqvF2yyQFZPzEfZC0FtbZ2J4msLwz1ipJBWRL0NuJktmaZKST4eIMbjPKpCDG/u14pwMV01uhutCfPfgeVc=
*/