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