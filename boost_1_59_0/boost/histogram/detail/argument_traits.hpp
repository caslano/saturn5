// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_ARGUMENT_TRAITS_HPP
#define BOOST_HISTOGRAM_DETAIL_ARGUMENT_TRAITS_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <tuple>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
struct is_weight_impl : mp11::mp_false {};

template <class T>
struct is_weight_impl<weight_type<T>> : mp11::mp_true {};

template <class T>
using is_weight = is_weight_impl<T>;

template <class T>
struct is_sample_impl : mp11::mp_false {};

template <class T>
struct is_sample_impl<sample_type<T>> : mp11::mp_true {};

template <class T>
using is_sample = is_sample_impl<T>;

template <int Idx, class L>
struct sample_args_impl {
  using type = mp11::mp_first<std::decay_t<mp11::mp_at_c<L, (Idx >= 0 ? Idx : 0)>>>;
};

template <class L>
struct sample_args_impl<-1, L> {
  using type = std::tuple<>;
};

template <std::size_t NArgs, std::size_t Start, int WeightPos, int SamplePos,
          class SampleArgs>
struct argument_traits_holder {
  using nargs = mp11::mp_size_t<NArgs>;
  using start = mp11::mp_size_t<Start>;
  using wpos = mp11::mp_int<WeightPos>;
  using spos = mp11::mp_int<SamplePos>;
  using sargs = SampleArgs;
};

template <class... Ts>
struct argument_traits_impl {
  using list_ = mp11::mp_list<Ts...>;
  static constexpr std::size_t size_ = sizeof...(Ts);
  static constexpr std::size_t weight_ = mp11::mp_find_if<list_, is_weight>::value;
  static constexpr std::size_t sample_ = mp11::mp_find_if<list_, is_sample>::value;
  static constexpr int spos_ = (sample_ < size_ ? static_cast<int>(sample_) : -1);
  static constexpr int wpos_ = (weight_ < size_ ? static_cast<int>(weight_) : -1);

  using type =
      argument_traits_holder<(size_ - (weight_ < size_) - (sample_ < size_)),
                             (weight_ < size_ && sample_ < size_ &&
                                      (weight_ + sample_ < 2)
                                  ? 2
                                  : ((weight_ == 0 || sample_ == 0) ? 1 : 0)),
                             wpos_, spos_, typename sample_args_impl<spos_, list_>::type>;
};

template <class... Ts>
using argument_traits = typename argument_traits_impl<Ts...>::type;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* argument_traits.hpp
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
*/