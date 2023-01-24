// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_AT_HPP
#define BOOST_HISTOGRAM_DETAIL_AT_HPP

#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class A, class... Us>
optional_index at(const A& axes, const std::tuple<Us...>& args) noexcept {
  optional_index idx{0}; // offset not used by linearize_index
  mp11::mp_for_each<mp11::mp_iota_c<sizeof...(Us)>>(
      [&, stride = static_cast<std::size_t>(1)](auto i) mutable {
        stride *= linearize_index(idx, stride, axis_get<i>(axes),
                                  static_cast<axis::index_type>(std::get<i>(args)));
      });
  return idx;
}

template <class A, class U>
optional_index at(const A& axes, const U& args) noexcept {
  optional_index idx{0};
  using std::begin;
  for_each_axis(axes, [&, it = begin(args),
                       stride = static_cast<std::size_t>(1)](const auto& a) mutable {
    stride *= linearize_index(idx, stride, a, static_cast<axis::index_type>(*it++));
  });
  return idx;
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* at.hpp
QDZFo6t6KjbLCbjaLNjOJSjYLljvNRnosjUK6m7ZJtFIulVB74yvfKa0/0iGPH8kQynejPG3VoHp/5IMa7MH1Z4lw9Eve8+/ip9B6xqMFrFZxRTb4tJHi4d7hTAGpPDErH9ICf16z1ICQ/L+H8nQn0ez7olfc91Q5nHka9Y5RZ/ha97dSsmyiiQBenHkL192O3HUMr98UtXBLX53tWVz5/TuI36MFS0nyJRbo6sfPtHZWaknLPjEReFmUoYEL7+oom2EjBdg1evK8sP8Mozs7K4MwePpouOeT4vIGVc7G+1eQwRXwNoDBtAC/+Fzh/RA2Iz3KRWJbTnyjs/oykCQD1ZPLlrsbRMDNwPenOkJx3qz+jb7aTUGtDv8rijQjry8hg1piarDvn+6d+MZDLRYJQPKdyV2LbvQlWX9vsvAvLu+Hy/qseJXHla4DWzyaPJpQWh4PSTvU5sUao1eyrVp25GKmIr8GaGa0uK6/Et5kN0Xz01dYzJnsgvdTY8e303f7UbFBlVIMzpovAd1869NrVzkwxdt3IqUD7QMZmuKp89UAkoTgl4QuTHJVPnqRZGHmeojvPrI2Ljn9BUpTjoaVWdE3BEWqkR818SWeD0LrtyrkE7LCjpi0mg06q0F8oAmyV+d4hOkkVKo49aAu4Xmddx/owk8z2hC7DOaUDErROTEh3z5ae60i2HFTip4S0SZnTQcmwI9BPfQ35gd
*/