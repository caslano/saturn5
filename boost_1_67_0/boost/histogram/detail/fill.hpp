// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_FILL_HPP
#define BOOST_HISTOGRAM_DETAIL_FILL_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/config/workaround.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/argument_traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/tuple_slice.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/tuple.hpp>
#include <boost/mp11/utility.hpp>
#include <mutex>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class U>
struct sample_args_passed_vs_expected;

template <class... Passed, class... Expected>
struct sample_args_passed_vs_expected<std::tuple<Passed...>, std::tuple<Expected...>> {
  static_assert(!(sizeof...(Expected) > 0 && sizeof...(Passed) == 0),
                "error: accumulator requires samples, but sample argument is missing");
  static_assert(
      !(sizeof...(Passed) > 0 && sizeof...(Expected) == 0),
      "error: accumulator does not accept samples, but sample argument is passed");
  static_assert(sizeof...(Passed) == sizeof...(Expected),
                "error: numbers of passed and expected sample arguments differ");
  static_assert(
      std::is_convertible<std::tuple<Passed...>, std::tuple<Expected...>>::value,
      "error: sample argument(s) not convertible to accumulator argument(s)");
};

template <class A>
struct storage_grower {
  const A& axes_;
  struct {
    axis::index_type idx, old_extent;
    std::size_t new_stride;
  } data_[buffer_size<A>::value];
  std::size_t new_size_;

  storage_grower(const A& axes) noexcept : axes_(axes) {}

  void from_shifts(const axis::index_type* shifts) noexcept {
    auto dit = data_;
    std::size_t s = 1;
    for_each_axis(axes_, [&](const auto& a) {
      const auto n = axis::traits::extent(a);
      *dit++ = {0, n - std::abs(*shifts++), s};
      s *= n;
    });
    new_size_ = s;
  }

  // must be extents before any shifts were applied
  void from_extents(const axis::index_type* old_extents) noexcept {
    auto dit = data_;
    std::size_t s = 1;
    for_each_axis(axes_, [&](const auto& a) {
      const auto n = axis::traits::extent(a);
      *dit++ = {0, *old_extents++, s};
      s *= n;
    });
    new_size_ = s;
  }

  template <class S>
  void apply(S& storage, const axis::index_type* shifts) {
    auto new_storage = make_default(storage);
    new_storage.reset(new_size_);
    const auto dlast = data_ + axes_rank(axes_) - 1;
    for (const auto& x : storage) {
      auto ns = new_storage.begin();
      auto sit = shifts;
      auto dit = data_;
      for_each_axis(axes_, [&](const auto& a) {
        using opt = axis::traits::get_options<std::decay_t<decltype(a)>>;
        if (opt::test(axis::option::underflow)) {
          if (dit->idx == 0) {
            // axis has underflow and we are in the underflow bin:
            // keep storage pointer unchanged
            ++dit;
            ++sit;
            return;
          }
        }
        if (opt::test(axis::option::overflow)) {
          if (dit->idx == dit->old_extent - 1) {
            // axis has overflow and we are in the overflow bin:
            // move storage pointer to corresponding overflow bin position
            ns += (axis::traits::extent(a) - 1) * dit->new_stride;
            ++dit;
            ++sit;
            return;
          }
        }
        // we are in a normal bin:
        // move storage pointer to index position; apply positive shifts if any
        ns += (dit->idx + (*sit >= 0 ? *sit : 0)) * dit->new_stride;
        ++dit;
        ++sit;
      });
      // assign old value to new location
      *ns = x;
      // advance multi-dimensional index
      dit = data_;
      ++dit->idx;
      while (dit != dlast && dit->idx == dit->old_extent) {
        dit->idx = 0;
        ++(++dit)->idx;
      }
    }
    storage = std::move(new_storage);
  }
};

template <class T, class... Us>
auto fill_storage_element_impl(priority<2>, T&& t, const Us&... args) noexcept
    -> decltype(t(args...), void()) {
  t(args...);
}

template <class T, class U>
auto fill_storage_element_impl(priority<1>, T&& t, const weight_type<U>& w) noexcept
    -> decltype(t += w, void()) {
  t += w;
}

// fallback for arithmetic types and accumulators that do not handle the weight
template <class T, class U>
auto fill_storage_element_impl(priority<0>, T&& t, const weight_type<U>& w) noexcept
    -> decltype(t += w.value, void()) {
  t += w.value;
}

template <class T>
auto fill_storage_element_impl(priority<1>, T&& t) noexcept -> decltype(++t, void()) {
  ++t;
}

template <class T, class... Us>
void fill_storage_element(T&& t, const Us&... args) noexcept {
  fill_storage_element_impl(priority<2>{}, std::forward<T>(t), args...);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IW, class IS, class T, class U>
void fill_storage_2(IW, IS, T&& t, U&& u) noexcept {
  mp11::tuple_apply(
      [&](const auto&... args) {
        fill_storage_element(std::forward<T>(t), std::get<IW::value>(u), args...);
      },
      std::get<IS::value>(u).value);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IS, class T, class U>
void fill_storage_2(mp11::mp_int<-1>, IS, T&& t, const U& u) noexcept {
  mp11::tuple_apply(
      [&](const auto&... args) { fill_storage_element(std::forward<T>(t), args...); },
      std::get<IS::value>(u).value);
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class IW, class T, class U>
void fill_storage_2(IW, mp11::mp_int<-1>, T&& t, const U& u) noexcept {
  fill_storage_element(std::forward<T>(t), std::get<IW::value>(u));
}

// t may be a proxy and then it is an rvalue reference, not an lvalue reference
template <class T, class U>
void fill_storage_2(mp11::mp_int<-1>, mp11::mp_int<-1>, T&& t, const U&) noexcept {
  fill_storage_element(std::forward<T>(t));
}

template <class IW, class IS, class Storage, class Index, class Args>
auto fill_storage(IW, IS, Storage& s, const Index idx, const Args& a) noexcept {
  if (is_valid(idx)) {
    BOOST_ASSERT(idx < s.size());
    fill_storage_2(IW{}, IS{}, s[idx], a);
    return s.begin() + idx;
  }
  return s.end();
}

template <int S, int N>
struct linearize_args {
  template <class Index, class A, class Args>
  static void impl(mp11::mp_int<N>, Index&, const std::size_t, A&, const Args&) {}

  template <int I, class Index, class A, class Args>
  static void impl(mp11::mp_int<I>, Index& o, const std::size_t s, A& ax,
                   const Args& args) {
    const auto e = linearize(o, s, axis_get<I>(ax), std::get<(S + I)>(args));
    impl(mp11::mp_int<(I + 1)>{}, o, s * e, ax, args);
  }

  template <class Index, class A, class Args>
  static void apply(Index& o, A& ax, const Args& args) {
    impl(mp11::mp_int<0>{}, o, 1, ax, args);
  }
};

template <int S>
struct linearize_args<S, 1> {
  template <class Index, class A, class Args>
  static void apply(Index& o, A& ax, const Args& args) {
    linearize(o, 1, axis_get<0>(ax), std::get<S>(args));
  }
};

template <class A>
constexpr unsigned min(const unsigned n) noexcept {
  constexpr unsigned a = static_cast<unsigned>(buffer_size<A>::value);
  return a < n ? a : n;
}

// not growing
template <class ArgTraits, class Storage, class Axes, class Args>
auto fill_2(ArgTraits, mp11::mp_false, const std::size_t offset, Storage& st,
            const Axes& axes, const Args& args) {
  mp11::mp_if<has_non_inclusive_axis<Axes>, optional_index, std::size_t> idx{offset};
  linearize_args<ArgTraits::start::value, min<Axes>(ArgTraits::nargs::value)>::apply(
      idx, axes, args);
  return fill_storage(typename ArgTraits::wpos{}, typename ArgTraits::spos{}, st, idx,
                      args);
}

// at least one axis is growing
template <class ArgTraits, class Storage, class Axes, class Args>
auto fill_2(ArgTraits, mp11::mp_true, const std::size_t, Storage& st, Axes& axes,
            const Args& args) {
  std::array<axis::index_type, ArgTraits::nargs::value> shifts;
  // offset must be zero for linearize_growth
  mp11::mp_if<has_non_inclusive_axis<Axes>, optional_index, std::size_t> idx{0};
  std::size_t stride = 1;
  bool update_needed = false;
  mp11::mp_for_each<mp11::mp_iota_c<min<Axes>(ArgTraits::nargs::value)>>([&](auto i) {
    auto& ax = axis_get<i>(axes);
    const auto extent = linearize_growth(idx, shifts[i], stride, ax,
                                         std::get<(ArgTraits::start::value + i)>(args));
    update_needed |= shifts[i] != 0;
    stride *= extent;
  });
  if (update_needed) {
    storage_grower<Axes> g(axes);
    g.from_shifts(shifts.data());
    g.apply(st, shifts.data());
  }
  return fill_storage(typename ArgTraits::wpos{}, typename ArgTraits::spos{}, st, idx,
                      args);
}

// pack original args tuple into another tuple (which is unpacked later)
template <int Start, int Size, class IW, class IS, class Args>
decltype(auto) pack_args(IW, IS, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IW::value>(args),
                         std::get<IS::value>(args));
}

template <int Start, int Size, class IW, class Args>
decltype(auto) pack_args(IW, mp11::mp_int<-1>, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IW::value>(args));
}

template <int Start, int Size, class IS, class Args>
decltype(auto) pack_args(mp11::mp_int<-1>, IS, const Args& args) noexcept {
  return std::make_tuple(tuple_slice<Start, Size>(args), std::get<IS::value>(args));
}

template <int Start, int Size, class Args>
decltype(auto) pack_args(mp11::mp_int<-1>, mp11::mp_int<-1>, const Args& args) noexcept {
  return std::make_tuple(args);
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 0)
#pragma warning(disable : 4702) // fixing warning would reduce code readability a lot
#endif

template <class ArgTraits, class S, class A, class Args>
auto fill(std::true_type, ArgTraits, const std::size_t offset, S& storage, A& axes,
          const Args& args) -> typename S::iterator {
  using growing = has_growing_axis<A>;

  // Sometimes we need to pack the tuple into another tuple:
  // - histogram contains one axis which accepts tuple
  // - user passes tuple to fill(...)
  // Tuple is normally unpacked and arguments are processed, this causes pos::nargs > 1.
  // Now we pack tuple into another tuple so that original tuple is send to axis.
  // Notes:
  // - has nice side-effect of making histogram::operator(1, 2) work as well
  // - cannot detect call signature of axis at compile-time in all configurations
  //   (axis::variant provides generic call interface and hides concrete
  //   interface), so we throw at runtime if incompatible argument is passed (e.g.
  //   3d tuple)

  if (axes_rank(axes) == ArgTraits::nargs::value)
    return fill_2(ArgTraits{}, growing{}, offset, storage, axes, args);
  else if (axes_rank(axes) == 1 &&
           axis::traits::rank(axis_get<0>(axes)) == ArgTraits::nargs::value)
    return fill_2(
        argument_traits_holder<
            1, 0, (ArgTraits::wpos::value >= 0 ? 1 : -1),
            (ArgTraits::spos::value >= 0 ? (ArgTraits::wpos::value >= 0 ? 2 : 1) : -1),
            typename ArgTraits::sargs>{},
        growing{}, offset, storage, axes,
        pack_args<ArgTraits::start::value, ArgTraits::nargs::value>(
            typename ArgTraits::wpos{}, typename ArgTraits::spos{}, args));
  return (BOOST_THROW_EXCEPTION(
              std::invalid_argument("number of arguments != histogram rank")),
          storage.end());
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 0)
#pragma warning(default : 4702)
#endif

// empty implementation for bad arguments to stop compiler from showing internals
template <class ArgTraits, class S, class A, class Args>
auto fill(std::false_type, ArgTraits, const std::size_t, S& storage, A&, const Args&) ->
    typename S::iterator {
  return storage.end();
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* fill.hpp
GSU6hbcii2pMcW39ga2Zd0AL51B9A4W9u7WmmFDLmlF49Mek+mb1dGB2jkI1kYi8SNJDeTnXd/av2nFshFfpBpXigxzUFrlhm4ZhkW2pbDS52op01oc+xchP8O1giUinhnUvcFSYqWWKRw4HDLl3wDPZW/aOo5qF3nSpqrdu0WmHdDZmE+BKqKWY+fe6kNB/57LlXxj92gPbVoAmeer2X0g2PQXZhQckaa+mHFykXmWHVpQiiiEt5N003FtlhUA32jPPjs0WXbSghPZXHFkS5tSoNJRgE5Uo1XtMTiwxQ8QKINNFpkiOZh6a+xtzGAbLqWvykn7iDic7PLwAPJAqDgOnocPZ+8EYf8OZUH0DNnHEj2yTxIxzR0sM/MT9h3Fv3AoNzsa1qulnEckQELeiX3yBO0brrrvVFdTlz/gRTeRMQ2M27BsCCtFHE3aDz1UXL+oixdqEQ7LrGBGzpTptQrdtvLC9+0yF8z5/sNSTFlzncnqvJVaW066Twx7Bd2W4Kl0se/tRYyUH6vLHTFhxvvxMydI59HXMwO7Yn6/Lrlfn6G7tONHjuFY+a9rOSvDF8FDXMhs3fjJuYen4ayvz87nZSW92Ej4EOxwnuwA4QCRs0YhymQaG+eRPGd2z9It5Fffrzls20phc2u6uyZX5/eLrCP5DKWcn7GDB8qBA1T/6wYDXbAmHt0o37PRJfR7AuLKds2zWwY5U7r9Pe7oeJHQpd3vml5SMz3y5b6Aqz57oLlYAsKtieSEigFbYySC+r6YcCFDXoIOyPUsYhnrOY3O3Ot4Ip7zGB33L01I7BjTxwYr5Lox/egCLVsMgnpaEP41+4RPu02rlIy5i2ih1sK2+WcN7FfMRNczYiwFgCjvBqabZll7FteVKWs7ybqk7zQkHqMxUPDRV5NOT3zNLeq682NVpHsBCbvaa+ry1PIGGwOQK9qlZX3aLhyYLdfL0P7oUpr7KJpqWPKY+Tqk9vZ8/wwrgrlZS+jrrU8lU/pciE7tGBFQ3a3ayS1KMeUcMSa6g6/y25RwvRkLXZlleN/GHncStXVnfTbxxNlV1I0CPIOMEnPxQ+UjFGEVao8ZkR4PTnTBESTrALJ6iaMdd9gDTyzz0aZNj4eGEsay3WL+TpjS9hSqsyobCMB3gflxHrIrc81Rbue0b43GYREwYIajcXfg8oKDPCF2Hnf+pLIhLm2AhK5LE/7f+VTlRoJ66t5zJ26rgPyLxArhmOu/XGThfxPHV4gaVAwmPLgvFYKZls8DOcszksTmp+Ugs6/mvF+Qf8vMkzDbkNemGlgIB3ldzWZ12IDnCClGcdPkIEeJQgoPSLBbGoppMwy3YlvV1/srzTuNRAjf4VXG1paZXm5iHal5YEOFD2qKIctb3HAznFR7o7m+nHly9bW4loWcsXZlm0g6vG9RKiwq7ScpJ5fDpaM5hotOofDDZ7KP0bWeionYf2CO4pVF8nPeZYjt8pWkW+FLod+QDm3jWINCP6BnkMvVteRbI8KM9wwyJV8YQO11/Bq+iANpJSYJINxLjAwY1vKE5HhZP2kOvqfCSHWVxU6iVqc80szObDr77fcMdigCKO5ItmFVSq4FA/HnSMG0tVLr6egzWpaSPyGWGz7huwXXtV41e39KoCY09R3ZoP1Dy1qaeEwFQykTSFnyZGMxKNZq33nX8mdfpASEbZ6Izf3m2Hwjn0cdJ9N30se2yKaKTQd4MfZ5YYRzIo8lEbU1AkFUeHLfcYa/+GvIfbEyljoauV31e3p0L2O9eWhIxN1nN8v4f29CMRtEfO76Oa5tUXgmtH8/kx/IKmRbh5p6nK8WANgfggcGRx4SyRcLP/PAjSapNS2nt8gZvaKj/vvV7daI7iB4tMkIEG38HiEuAM7Fq6ZlU5Q/LX2ahVC1JsWei0wNY9no06wr1E1vsLdO0vhrBT9Kww0bpoecOTVLnpW9a9hLa9P4qsiJEp1UF+u9CwEnEn9/xSPqjDEfQ70ze0Qu+YkNcsRgdROLwY5+aevcGG5lc74iDgOJ2dbEOlVnv44WlFdXiwRPmNN7IotCMq1iZjbE8XKN9haiCFZ1ywWPiNhc94gLfhQ1rmggSnIQt99B1sVd0MEqxv6nYQeYev8Q0WseWTI1hhtNdxzMs+jgT7UeCqxMqn1VJEzPFR/+Q0bBwqPWxyGP5NahBHQ46FWuKe9N4prQf1CqjX0GPWSC21sGxhdfwdv31onmJFJ1SfQTsrKBDdRa4LvF5Qk+QiSUQkHXzDVU4GlEhursCb+CNBdqccymHenyqfCCmuYclnfSQreYxG/9uP2dsmT03T1P9vQOXhOOJdgUmgkmv19nDhBU4L3FpsAtLmTT6VArevvj7UbMZ8LoAguA2ZmJT34pOFSNyqswJV6LdenRa9tDDGOWSTP2+eTulMECWiiXuEzVhezsYoyF/mMAuQYuWcyq1nvG68a16djgGKII9WkbFFVPZJR72fb3vsD9pH+eOc2HAZAolhl2N57HHIqCx6HgZKH0efQj6YMvo/8S1HNIS9giN3Z3aSJ1xTBuOsJOAaVFUUOpQwdghEmvdXS1NLRLEoh5dZBExu6y2YKfMhDQ2w6u65VvvFw+s06MBJ25ozfiTefqjC1gy3KDXrNabJAfNuxbBLj8Xrq/m4AvR67V9b5kGogs8SDc3i3ZqcpZ1YoPMULAv50tOfit9w3KhUk2vc/nC6a+Shyg+KgHSRz92aC0w9nl5s1/gOUOgExOHthnoyQVjeFhEBtaAybWELAytaj3QAiFdew5dv4kC4IjoJcoq40DZQ51Jryy6pODLVC8U/eWvZZywUN0TM4oMaUTLsQkDPCNv4ysjlXGq0p25FHdSQmPq/A3PIGJfA0Vu4XDYX8cN/HJdgODT8Ti3KVGXu5krXIt+DVMYcZnm99Rb/84Wx/reaQgFS7b5zCZHENQv9mbKSXRAQL1Aoe69lCqkZWKx/3BC8Hj7DVLSrHQB8GiQHIIIxzwFVVGmtLdQ8usUFVforhJK6vTLfTohtoa4sK/LEr/8AldI08OrVEvwJsBFUOUB/ATa7jVezYn3yA7A7pSpCw3yU37en6m71bbPb2IE73xdb8A1ntYe7ZuSJkJzbbHV0NUIl3G+KrTsnayoGJ7XICeM7xbv0HfH4Pe2ggjfYG+q/RzeFyOsZ5JdXy7PBBC0CKjjG3AqaX9DspS4K8QvbVMspmS3W6GhCKRi0TknfdjIDj2618lRqh2RReNebJDPjIjF+s5lhDBoH4oP3C4h3QyA+FXSQCQL5jGVBHxDSLZdtR642e5x35qABomL8ez81oF8B/3z1gKqsfz0sqkpDxGJH1v4oRVBJB4goPxLeDZKEmtVWcboYeFJWIgxkvTvdQFyvfsmn76Yvq9obkBZgi9XFr2sEZLZhZiNdcDbTP4ykXr54LfpLE1g7RPXs9Si5mKRRDjmoGsBucvkmyI2+FNMDdwgkXj5tBQLqCHiBvzPIaYxa7KVxqm+hUqbUCVMkjHA9FVsqx2HDAsEKNksX2qVqHxzw6Fdmec7B8jt/MOBAvyc4IIRipaH7tnrPJKnDJiaDQVMkkUjNwmTx1UdRo8PRx/JaPjLh7xYG2cP50t5FwLiCDKjhP7kcilTphxMKR/AULHXvaeCibH9o/FBh+bv0DQI2aAzUuzbmqBYIPX4oHf2hjdgXxmhGteW1/S2crmHznkPCjPcwUVe0Jzo+D+SrYl9I0yEaBYPUqcN24m3LVkbTjyq36GDvKQjHmZP8Gi9+CbfyAip/ByS2eq2Y8TRyzjgb/EaFLoFQYR4b6ee4b2Zeg9145bqwzO7yZ1B4Fr0VIpxLhY1b54ybTiAR+Rh0LIwCFjpH2T0qXZaTGeEaI/bm19P2YCmCtGWHTmLgEQQSSSR252eGr/GvUbB4tTRXNwnKaRXw3cqwXhk5V0Yr68XLOfV58lVEHnxZguRsduQFEbnu6K5MSibk0CVvkqDJq0WPuZhhVsjYMDUleFWQyepDXqVp70X6BdzKRqae/I86iraI2sQRDWFdFsd9QvMsU2otF7N1ZYJCkcjzdokDC3Few5C+O6+dutVGvF/aMCk++JAqlh8cFXpLUXFOQAzbAlm+VeatmeSBakUiLzEyvTGvpOS7Ck+3ZTh3Yi26QfziX69tdeTfurg2WUYJxBDe1rAMunhbS8fCckcMU7rn9DNnx+SSQ8XEoAxMSFRUppDzTtNSFFUyhOtextZerDfh6DbSil7OZHbo4qCLSsLtAS5aCXDqJEt2HY9P15eywmiArj6Le86kQjwQxWOj8pHRpa86Wd30ylDYaBtVmnOHNE2405NaYHwSOgnfmpa7R5W7X1uNoSWVYYGg9YFNw2wrIFwdOBAfb2QA6QBn85nUq880wlcb1HK2FZpIr8Wm/REIni0naiPgw3XlAxXUAbFNoLuzZLeUNMvq083dmUKfgEpkBjfAhPtBHRZhHIZrq9n1ru3KfY9FuiG9PDJobWDgTlEtzB/tH+XD6vooCRMdMftUzW9VmBracXmCrIlw2SXCvvHgEqxwGG/ZSAUuvLPspH3FBXtWXxGyWph5c0ZXQBcnzBcr0Lt3NLG0Mcr9h6eY7NfqfuGxOrrqDBabSU4ewPn29dbKwX3Qh38+dae1p7vssqPJKfvQ+RtJpG+GmkTl4bnf6MONwHJZIkD/oAx51ZEJ/MGEuxcAPt6Dedx5f9l9aSwhRXyxKtNU0/Cvhgo63tn1a3Lptlhn0PSqzmsizzW3skmgll2+bldTQjrCIH9tLRvLWdN8DhNEA6TiXeDFmrW55GBOJVgc6dZAvJS+7S5toFFlw5kDNYvZ/p3npHrueG/twM3cJqgnrLybW6qAm+e/8QPng8Tem5sRPFXdGuKrOv8ST8ELIbtOlNF8Xb6FSwuPVT6Q6bt3FfNAxqGhUeRO4z8C0SWARZJifT6clsEsHaaw4bDsym1e+rkikDet5WmlY7pHsQqBuoHNHVTmf9NRUqsymKVcfaMm88Sn6oFfSPh6C3HbnTCiFmQz3yZUvcf5wX1rKd8XErxxq58PLIz50fcer1weMUkdIIBGCzvgi6KYpViNppKJEJERh4KyJ1KETtTDiK79RCwEOqVy9e8kAiR4psoJ3VjEh0goWmDzzplW7iEYW8fOrX7sge1QKoWxg/XWQrSUuy91hAAA+2kawBwu4b1BRGf6ZW5YXHZECNvya98haQamH61WWgxOAazo6hv65fwenmn9pzZV+LziK+VtCo+bOeKfI0pDGEEqIp+rnq55wUm4LxsAjLyWOh03S8f3vvrxwz+WTZciZImGKNEHtouXeU01iIjY8j/YEGiWzvKlU1tkUHY4lveKW0/sBZN9iVdPvVRfY8IPt1Kthtbs8oIhwNd70sqgVJ7FgxmFmlow6ymrpjYaPGPkCq4hrrYfRnWTJEWJLZo/rjz5O1CAeMbATiO4NU+OFl8Eq8MXw/5tQnMhaJ7wmKElDpT2RaM2zJGag2PC2xjnBoztWD78n5BtWvm/8I72udoVq9R0ubcp1Ea6LkLcyYqWrpVUCWzGAcQ0KSfKgzrgJbd3CyRElMQCqSN6UdNes99JIyE6yKVaeP7ZY7IE3u4jIkug/qqdCWGIbBCDGo32K0F17rXOT941TRY04m/BKUAqUPQF808Jajhw8hQH5HVRI0uCvCsXjyDCCHJHpQ2ObXh09GEC++BIXcuFFTK8lkzpNevXN60vonSj+1Rhue7g1DohKRIcViYc0Du/JQ8pCj3wn91nWY052EBOuvowdigHKsY+fYCxMx/6GqlJbB9bAQdaHyGWJdMEnDHZqtrP4vJ+U8EPftYI3l9jYPPaJPJx4gALGlUPDBgb74jNLlNFk1ErZNy2BJFv/2hQ1KEPM1xF6rYwsu3JnKlhmrQ2OOeDRx0DRvdS/AMDdjtmBRG9Qo6spTSjI7vYQGdlErcKbrQYWXWqZBS7yRS2FIdrLlXeYpMl8jMXcsUnBYUXb72wWkU3TbVBDb7OYhfA2d7kU7BLfAw8ARB80gaHIHUWGqxKcXoUwSnYlJxD/aFB4AVFJ1LL84kJ7TOyto6vwNDOaBWedLcQt++gUFtom7mf4Kk2rqmuGnXClIR6NLUp0KsPiG0TT83OO7+v4jEQIgHn+p1p1OyHEJ7cbYreDxs75bMNG+49Hf8bovGMNRgmJWFxmFF06EnyJuPoqoKfpoDeaz92qUn1JiEJIzr+hJrahIgBNT7T5em4f77s9VecQIhA5Em/TMWqitywczKHPCA9aPfrADdW96z8jpCvwNqPDwpwIG2mpmrkIDhyRf4cSfMUedn5gnuoIEV/ePGy2R3pLUv8EIfBhPWfaY0ksbklci02Zf5qFQondhd8elO3Z+2iAxIMdfOKXgEeVPqs3YApTzTR8RrMGZBb5oW15XvqCZ00oG/uT9jNUPFUZ7ID2wWFHe2Kf3bLkbbC1JqxTS/BpK1dNkvPgGWN9/1xBj+6Yx42ziVa4GZUFQwCP/b77VA1KQ3lATyOvUzK+du+urktuiD3ngaBrgVtkqCRHCqtHKB75stmupAgwOGPl8bYooygGoQGd1+MxE2b3rWFBaRtYL5AB1y4+3JYyzd9Zl9Lu8LwVwYTIxW0uUkbB+62IcVJnRbydw2DL5ib1cRX4ltDd8ghvy7VhDsFDSTDwnK+tzpuQ0XJPTst0e2I1yCgFUQyGGVW4JVco4quVczrc3yVQ8eUJgeTnAF6gQ4PlldVT6VZRxh3YbIuud9zTc6Rc1bcg9cRnXlI2/33B8nP3BUYkMwX4oSVQBmKmQbqDvt2/ayo9E8b3K6Ya1ZQF+qUvGpmeENndJFBnXgafqgyRYt6HeXE7fxP1A+eGwHcYf7Rk/uLdcg4eS6hobJQRTqGq8mDdXjS0vpJAfK7J1/IIhY0eA1ESU9jfwEWsofyylIcs+JnAhL1DKi+Moi9hnaalh8nN6qFl4D010zDnNUrxVxl1Qo6k7KJqZ/EGfdI1ZAMrBVQE1dJCuls2tk65uqre5jzO4yV97ZnXJx6Q0tDnHUS1OAkuErJ2WeUTQgypH1j3fl/NZOkkrxEXFIKR6j18lAUBEi1oyxZz+rXsDvj0Nn9HQKXT2GF0t89aS58GXummsdKsYb7Ctxs+dxkOByP22u5ggr3sfOitBJUgwsKNNtclmPB24EGGUK3QujFEWENWzzt6rRX3mgHcFfdvE6drdbQH9F+B5RGa0+AkKoOOUYoos+QV93eE0YTiY29reac+BcNQX0gA4lPY0Oxsde7Z+yWyqXxws8w0rI/jpVwDZUrgnT10uwTpa/ch60jmD2ECShdlbvz6soliRcBRz03ug4F9htcyQCs8NscNCgc8J41zZdNbByOpSsfi8uOnooWW4ZJrVjIa8il+lCyeXxlbZBGZq0yKye5R/ABISM48JFII40h6LEmCyt1ACDqfj1Cp5A9oty41PHmMp4y7OEHqS+fB9GEk1XIYht9KG3K+XdCn0GZCcyIXS6Zgs1ueI7UppnIPXXltijdi/+uZtZlKRvO2HeWJuE2hVjpuHbUYz8YpalX3QL/WjX4GndVLq5bFxM7c6FqIzgz/PBRS6eA7CJfRcQTj2INw98PDid4CFLF+iCpAJO15/zCtbkRRvE7/WgvS64qs0UyFDHqtdyNzxPHvp+01rSlIJrXcZ5crWtl3Nf851aHJs3idXifOPvON+dyf1bi1G9Bg+i0EqSzEtUuV/B/0YO9SWLqfCwLGoPN5l/0tNu0QOWXpFWfeb/UR0Pmz8i2MJkvZ2Fq8VL+khyQELKALkSKNpxmZmjS/Sr0jQ/JqYx4maals7JqpQRKzxs+4fEFnkUi8Oz6V7yy73FKrUBlquqltyS6hg8t0x8tQ+489Ui8TXTDHAq0d6kHyPP5Uv+o1aumaaIOuMvlI+Xm4Ilgp3Srky6nO7SPZcUzM+Gq9Hxrei+6J2frTuoxT7DHRSx+VipgHxLnu8uqJEHCFgdPR2W2wlM8mJK9XUG9GRbRSZmVXSxqvkzYH3LoLks5QVBNbrkcfG5GXg5+YxtO03YCYvqS7na4SpE+1Q2yKYFbiSNS4vO3LWbWD5gC60PRgYGyJveUmg26klSsh/yhoXV/PdaIXSzwmXFZnaLoKvR06HqF8KaNucH6XqymjUNCPSzWZwfY10JsrKn/lupuGZa63CYDOSa0InpfmUxZd20TLnnNRLBSJg3lbcA37tsRsbSe3XzfwcbHe8bqS5RL9UPNmvj1n3Vo8TcEVDFw+S9JT8k6AvDglFOxsxhO7CtTjoWCa0iSCzmPHWBORBLxglBtZhiYd8tgAa72F5+FOkg1mKjjktLoKhZX5CiMYtxaveq800WnWzXT/kHfL0m9gy1TqTtabtvDzgtLqb+xsqdTwAKLPXTTUdnn1kgVtpvmm2x58wbRFwNl31Ah02iFiA6BdqWFlxpiTLbN9T6XXIBEEG8V4VACrh+us0iqenGvV4Sw+wFzm9Rt18jZrxKEHr7gVaxB4rLqkh5JJsigpu69jYTb6nbsdDlUbt2URprr4Ea7Tg8Vx4Vplf/lcrP1q7+lYbJh2rKBuh7HRfcaF8irCCRqNNjvTE3fxF3egemlGTrIeAxypmQjI3+qqk5a8/23FyWJpovher6kobD1C0dHHwVoNFk+spknRy0u9L1sUbCEanccUVuBZqi+KddxSIM2ZePyJlLh2efcYPwBF4gxAid9vyqSDfGM/RjentgRTrmpatKfU/kvx5QLC2WrIKTa8aeV/hn5UqZl4xDyY/jXRArYTnIEmfrYM6yoc31GwE3R5Kn4WZrXTuLGnkQJCVY0frCKRJtxJS5n6/8DWIb22M9qnivjblpIliLgqmwAb40pREmRyjaMpk3XI5X1s6sMEtCaMpj9GXAyqHq5Tg8m/kaBq9yyPBqO0x04QTINwZvJv1uMoYusY9XLxBSFhHVQLXeA5CkIGlGIRC+19anf0ZR7BtYjIdCJOOPxgjg5zazV63WjT8GH+zrKVRDTQX6giL5JlunuJmLFwPnnF6pa5ZO2Xcc7L4XpQ9uudMlOAISdu+rulv8kBtoD7kLZ387WEAqK3MLorCKOwQkPb64l/sBsYaQvNB+FRXxTRfCGVCUKTFrWTv4X55RR/yl4xf30pp6UkBLO8m5jNbxGLcRPxZ0Q0ZIoi9eT2lZBAwpTrw=
*/