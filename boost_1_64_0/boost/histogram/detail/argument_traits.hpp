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
vC/SSecJPsALuIE8Ynsw6S47eFuTZCfOxU5cf4Br1uFSsWGeBUqBwZFUOHC9JHDQPnu0c/HMJL4dYYcjbU/DPZY8irYh+mJgELAyKLS9c1oLAoBnNrwYtG6sc8y6a1hifW80kwIpzVHoyU6VJj/sXEoCQXoxZ9J0bPzOQXwN5/jjxa/m+N29jxf/G47/RmFi/IBf5/d2iVpIGFK52EujgCqxETp2bdb5vV1gHKuvYlLgVXlCu0TPwcjXPCN97RUJ+S+d/bR5Xl/ND4HGfT6co7TNvJpUPtQ32Nh/NiPDFbmUT0097FG2FN0il0Dh9EwRv8vtmV5T5NE/zIB6M2aiZ7MV8A61WfENZPUQvnPl7yntVUPVbrfVdSV5UcfVXdniCml43VHbuX2WZ9C+46Z3iS1lJ06/7E/x/h0WPRP/Pv+P8e/Fz8a/j0+AfychvvTP8e85Ce9aQv7LEuI/in/XKD8mqFWlibO7GS++6z2uP4YclT7YYXqOF2OPnx7tl+lHdpie40XX46cnfMnz+B2m53ix/prjpreo9KsGdZge8Wj/8dOjf432d5we8Wj/8dODHoz2d5we8Wj/8dOD3oz2d5we8Wj/2OOmB30Z7b+sw/SIR/uPm56W85pGdVxweYfpNdW+mzvOn9NedKL8XSoPt/qK4f069pbA+SX6/7jcWLwpek70/xEfn5MY313FK3pMiN83WMUreouP3xgfb0mMXxwfvygx/sH4+PmJ7Zuh4lV/J7Zfxav+TGx/fDzjT7H/iVXx7F/hT8WXHhufExufnRiv8Kf8n4yJj1f4M/2fHBtviY1fFhPfUf0HZh8Tvyg2/exj08+Pa39ivMKvan9ivMKvav8x8YZV9PlVVaJWGX3heOL12lefi14rcbYYdIGhAIDBfY+aYu6oRyBLfKbi3Ccq3caFyZdF95W2nqF26HAPvr3Gw4NoZLFpu2dMtD6RMfAz9Fg1F0sDrRzTvA91NBrVGX7B9p0jl4E1KQzpEh94TlhrGMGcYeqTehlYqJkBFJT0j/qAajzSJk9gc8VXAnG+Gpf2K+MW32CKuItLyf5sKU3a115RghxUepdY2MfcFKstDFzuqjsPNh36SAfkd7sop7J5NW34whV25mQumAujcp9hM0yLN3H0YJtsYq+aEtXEmWhidWFUzYM1/YOjDPPnP54tBaQUnHZxz7lUlBxtk8YstZeLCjyzZwfuRL9oRvVkT5yDSrLLMXuzhRZh7KUCpd/VV9HZuTVVscVvLCAt0dYi0goOsTACP7eRSKuzbwf64LWXYH1GUrvpY0evdEDY00m9Il5Npb83dzZPt9elTJkgnYE8pIhjiFZKbkQflqNEl6Mks4DxR1Ze2o0qGpYxfahF519imOBNlplFZmazG34L7W+v6Wnoiucs95NdTY1DbkeKNYeATr47oatWobJkJWI4KJwYHdKrf2RmurjiSmOZh/J5m2UWVk9jkfnllWoRee91CNLGqHy4c3efJa89Ura0oCifsPDiLIuSXEBJvDFJcsSGErX7x+W4ANGAFRqV1ZxplvV32H9CmxzTGKvZGLc2Ia4xrc8BGEeUB5iacHdkplu8nRxdGABtp39s+Qv7BLC+yGpdiTOB0ff01sXmu0/0vJCoZ/Uo87QCbBpKw1+hTgGFnZ9GsTXJ9DfVYfpSrxkKXLDRUAnwX3ObTxRhGJAGibYBHNCFdAoWKa44Vtyw3xhkdeGaUTJlTs1doMDv5xsHpcdeeHobAPJ+1ac8bO/v2edZ5WmkHUgaK+VQVWzBSzG+Rfi68C2hu93xzcbXTcoCfHPwJU1yX+0Oq+rj+2iATEMF286Lu6eqqGlgpRsO/WcpyJpvMtgriWA=
*/