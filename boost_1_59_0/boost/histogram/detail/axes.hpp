// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_AXES_HPP
#define BOOST_HISTOGRAM_DETAIL_AXES_HPP

#include <array>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/priority.hpp>
#include <boost/histogram/detail/relaxed_tuple_size.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/detail/sub_array.hpp>
#include <boost/histogram/detail/try_cast.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/integer_sequence.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/tuple.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace boost {
namespace histogram {
namespace detail {

template <class T, class Unary>
void for_each_axis_impl(dynamic_size, T& t, Unary& p) {
  for (auto& a : t) axis::visit(p, a);
}

template <class N, class T, class Unary>
void for_each_axis_impl(N, T& t, Unary& p) {
  mp11::tuple_for_each(t, p);
}

// also matches const T and const Unary
template <class T, class Unary>
void for_each_axis(T&& t, Unary&& p) {
  for_each_axis_impl(relaxed_tuple_size(t), t, p);
}

// merge if a and b are discrete and growing
struct axis_merger {
  template <class T, class U>
  T operator()(const T& a, const U& u) {
    const T* bp = ptr_cast<T>(&u);
    if (!bp) BOOST_THROW_EXCEPTION(std::invalid_argument("axes not mergable"));
    using O = axis::traits::get_options<T>;
    constexpr bool discrete_and_growing =
        axis::traits::is_continuous<T>::value == false && O::test(axis::option::growth);
    return impl(mp11::mp_bool<discrete_and_growing>{}, a, *bp);
  }

  template <class T>
  T impl(std::false_type, const T& a, const T& b) {
    if (!relaxed_equal{}(a, b))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes not mergable"));
    return a;
  }

  template <class T>
  T impl(std::true_type, const T& a, const T& b) {
    if (relaxed_equal{}(axis::traits::metadata(a), axis::traits::metadata(b))) {
      auto r = a;
      if (axis::traits::is_ordered<T>::value) {
        r.update(b.value(0));
        r.update(b.value(b.size() - 1));
      } else
        for (auto&& v : b) r.update(v);
      return r;
    }
    return impl(std::false_type{}, a, b);
  }
};

// create empty dynamic axis which can store any axes types from the argument
template <class T>
auto make_empty_dynamic_axes(const T& axes) {
  return make_default(axes);
}

template <class... Ts>
auto make_empty_dynamic_axes(const std::tuple<Ts...>&) {
  using namespace ::boost::mp11;
  using L = mp_unique<axis::variant<Ts...>>;
  // return std::vector<axis::variant<Axis0, Axis1, ...>> or std::vector<Axis0>
  return std::vector<mp_if_c<(mp_size<L>::value == 1), mp_first<L>, L>>{};
}

template <class T, class Functor, std::size_t... Is>
auto axes_transform_impl(const T& t, Functor&& f, mp11::index_sequence<Is...>) {
  return std::make_tuple(f(Is, std::get<Is>(t))...);
}

// warning: sequential order of functor execution is platform-dependent!
template <class... Ts, class Functor>
auto axes_transform(const std::tuple<Ts...>& old_axes, Functor&& f) {
  return axes_transform_impl(old_axes, std::forward<Functor>(f),
                             mp11::make_index_sequence<sizeof...(Ts)>{});
}

// changing axes type is not supported
template <class T, class Functor>
T axes_transform(const T& old_axes, Functor&& f) {
  T axes = make_default(old_axes);
  axes.reserve(old_axes.size());
  for_each_axis(old_axes, [&](const auto& a) { axes.emplace_back(f(axes.size(), a)); });
  return axes;
}

template <class... Ts, class Binary, std::size_t... Is>
std::tuple<Ts...> axes_transform_impl(const std::tuple<Ts...>& lhs,
                                      const std::tuple<Ts...>& rhs, Binary&& bin,
                                      mp11::index_sequence<Is...>) {
  return std::make_tuple(bin(std::get<Is>(lhs), std::get<Is>(rhs))...);
}

template <class... Ts, class Binary>
std::tuple<Ts...> axes_transform(const std::tuple<Ts...>& lhs,
                                 const std::tuple<Ts...>& rhs, Binary&& bin) {
  return axes_transform_impl(lhs, rhs, bin, mp11::make_index_sequence<sizeof...(Ts)>{});
}

template <class T, class Binary>
T axes_transform(const T& lhs, const T& rhs, Binary&& bin) {
  T ax = make_default(lhs);
  ax.reserve(lhs.size());
  using std::begin;
  auto ir = begin(rhs);
  for (auto&& li : lhs) {
    axis::visit(
        [&](const auto& li) {
          axis::visit([&](const auto& ri) { ax.emplace_back(bin(li, ri)); }, *ir);
        },
        li);
    ++ir;
  }
  return ax;
}

template <class T>
unsigned axes_rank(const T& axes) {
  using std::begin;
  using std::end;
  return static_cast<unsigned>(std::distance(begin(axes), end(axes)));
}

template <class... Ts>
constexpr unsigned axes_rank(const std::tuple<Ts...>&) {
  return static_cast<unsigned>(sizeof...(Ts));
}

template <class T>
void throw_if_axes_is_too_large(const T& axes) {
  if (axes_rank(axes) > BOOST_HISTOGRAM_DETAIL_AXES_LIMIT)
    BOOST_THROW_EXCEPTION(
        std::invalid_argument("length of axis vector exceeds internal buffers, "
                              "recompile with "
                              "-DBOOST_HISTOGRAM_DETAIL_AXES_LIMIT=<new max size> "
                              "to increase internal buffers"));
}

// tuple is never too large because internal buffers adapt to size of tuple
template <class... Ts>
void throw_if_axes_is_too_large(const std::tuple<Ts...>&) {}

template <unsigned N, class... Ts>
decltype(auto) axis_get(std::tuple<Ts...>& axes) {
  return std::get<N>(axes);
}

template <unsigned N, class... Ts>
decltype(auto) axis_get(const std::tuple<Ts...>& axes) {
  return std::get<N>(axes);
}

template <unsigned N, class T>
decltype(auto) axis_get(T& axes) {
  return axes[N];
}

template <unsigned N, class T>
decltype(auto) axis_get(const T& axes) {
  return axes[N];
}

template <class... Ts>
auto axis_get(std::tuple<Ts...>& axes, const unsigned i) {
  constexpr auto S = sizeof...(Ts);
  using V = mp11::mp_unique<axis::variant<Ts*...>>;
  return mp11::mp_with_index<S>(i, [&axes](auto i) { return V(&std::get<i>(axes)); });
}

template <class... Ts>
auto axis_get(const std::tuple<Ts...>& axes, const unsigned i) {
  constexpr auto S = sizeof...(Ts);
  using V = mp11::mp_unique<axis::variant<const Ts*...>>;
  return mp11::mp_with_index<S>(i, [&axes](auto i) { return V(&std::get<i>(axes)); });
}

template <class T>
decltype(auto) axis_get(T& axes, const unsigned i) {
  return axes[i];
}

template <class T>
decltype(auto) axis_get(const T& axes, const unsigned i) {
  return axes[i];
}

template <class T, class U, std::size_t... Is>
bool axes_equal_impl(const T& t, const U& u, mp11::index_sequence<Is...>) noexcept {
  bool result = true;
  // operator folding emulation
  (void)std::initializer_list<bool>{
      (result &= relaxed_equal{}(std::get<Is>(t), std::get<Is>(u)))...};
  return result;
}

template <class... Ts, class... Us>
bool axes_equal_impl(const std::tuple<Ts...>& t, const std::tuple<Us...>& u) noexcept {
  return axes_equal_impl(
      t, u, mp11::make_index_sequence<std::min(sizeof...(Ts), sizeof...(Us))>{});
}

template <class... Ts, class U>
bool axes_equal_impl(const std::tuple<Ts...>& t, const U& u) noexcept {
  using std::begin;
  auto iu = begin(u);
  bool result = true;
  mp11::tuple_for_each(t, [&](const auto& ti) {
    axis::visit([&](const auto& ui) { result &= relaxed_equal{}(ti, ui); }, *iu);
    ++iu;
  });
  return result;
}

template <class T, class... Us>
bool axes_equal_impl(const T& t, const std::tuple<Us...>& u) noexcept {
  return axes_equal_impl(u, t);
}

template <class T, class U>
bool axes_equal_impl(const T& t, const U& u) noexcept {
  using std::begin;
  auto iu = begin(u);
  bool result = true;
  for (auto&& ti : t) {
    axis::visit(
        [&](const auto& ti) {
          axis::visit([&](const auto& ui) { result &= relaxed_equal{}(ti, ui); }, *iu);
        },
        ti);
    ++iu;
  }
  return result;
}

template <class T, class U>
bool axes_equal(const T& t, const U& u) noexcept {
  return axes_rank(t) == axes_rank(u) && axes_equal_impl(t, u);
}

// enable_if_t needed by msvc :(
template <class... Ts, class... Us>
std::enable_if_t<!(std::is_same<std::tuple<Ts...>, std::tuple<Us...>>::value)>
axes_assign(std::tuple<Ts...>&, const std::tuple<Us...>&) {
  BOOST_THROW_EXCEPTION(std::invalid_argument("cannot assign axes, types do not match"));
}

template <class... Ts>
void axes_assign(std::tuple<Ts...>& t, const std::tuple<Ts...>& u) {
  t = u;
}

template <class... Ts, class U>
void axes_assign(std::tuple<Ts...>& t, const U& u) {
  if (sizeof...(Ts) == detail::size(u)) {
    using std::begin;
    auto iu = begin(u);
    mp11::tuple_for_each(t, [&](auto& ti) {
      using T = std::decay_t<decltype(ti)>;
      ti = axis::get<T>(*iu);
      ++iu;
    });
    return;
  }
  BOOST_THROW_EXCEPTION(std::invalid_argument("cannot assign axes, sizes do not match"));
}

template <class T, class... Us>
void axes_assign(T& t, const std::tuple<Us...>& u) {
  // resize instead of reserve, because t may not be empty and we want exact capacity
  t.resize(sizeof...(Us));
  using std::begin;
  auto it = begin(t);
  mp11::tuple_for_each(u, [&](const auto& ui) { *it++ = ui; });
}

template <class T, class U>
void axes_assign(T& t, const U& u) {
  t.assign(u.begin(), u.end());
}

template <class Archive, class T>
void axes_serialize(Archive& ar, T& axes) {
  ar& make_nvp("axes", axes);
}

template <class Archive, class... Ts>
void axes_serialize(Archive& ar, std::tuple<Ts...>& axes) {
  // needed to keep serialization format backward compatible
  struct proxy {
    std::tuple<Ts...>& t;
    void serialize(Archive& ar, unsigned /* version */) {
      mp11::tuple_for_each(t, [&ar](auto& x) { ar& make_nvp("item", x); });
    }
  };
  proxy p{axes};
  ar& make_nvp("axes", p);
}

// total number of bins including *flow bins
template <class T>
std::size_t bincount(const T& axes) {
  std::size_t n = 1;
  for_each_axis(axes, [&n](const auto& a) {
    const auto old = n;
    const auto s = axis::traits::extent(a);
    n *= s;
    if (s > 0 && n < old) BOOST_THROW_EXCEPTION(std::overflow_error("bincount overflow"));
  });
  return n;
}

/** Initial offset for the linear index.

  This precomputes an offset for the global index so that axis index = -1 addresses the
  first entry in the storage. Example: one-dim. histogram. The offset is 1, stride is 1,
  and global_index = offset + axis_index * stride == 0 addresses the first element of
  the storage.

  Using the offset makes the hot inner loop that computes the global_index simpler and
  thus faster, because we do not have to branch for each axis to check whether it has
  an underflow bin.

  The offset is set to an invalid value when the histogram contains at least one growing
  axis, because this optimization then cannot be used. See detail/linearize.hpp, in this
  case linearize_growth is called.
*/
template <class T>
std::size_t offset(const T& axes) {
  std::size_t n = 0;
  auto stride = static_cast<std::size_t>(1);
  for_each_axis(axes, [&](const auto& a) {
    if (axis::traits::options(a) & axis::option::growth)
      n = invalid_index;
    else if (n != invalid_index && axis::traits::options(a) & axis::option::underflow)
      n += stride;
    stride *= axis::traits::extent(a);
  });
  return n;
}

// make default-constructed buffer (no initialization for POD types)
template <class T, class A>
auto make_stack_buffer(const A& a) {
  return sub_array<T, buffer_size<A>::value>(axes_rank(a));
}

// make buffer with elements initialized to v
template <class T, class A>
auto make_stack_buffer(const A& a, const T& t) {
  return sub_array<T, buffer_size<A>::value>(axes_rank(a), t);
}

template <class T>
using has_underflow =
    decltype(axis::traits::get_options<T>::test(axis::option::underflow));

template <class T>
using is_growing = decltype(axis::traits::get_options<T>::test(axis::option::growth));

template <class T>
using is_not_inclusive = mp11::mp_not<axis::traits::is_inclusive<T>>;

// for vector<T>
template <class T>
struct axis_types_impl {
  using type = mp11::mp_list<std::decay_t<T>>;
};

// for vector<variant<Ts...>>
template <class... Ts>
struct axis_types_impl<axis::variant<Ts...>> {
  using type = mp11::mp_list<std::decay_t<Ts>...>;
};

// for tuple<Ts...>
template <class... Ts>
struct axis_types_impl<std::tuple<Ts...>> {
  using type = mp11::mp_list<std::decay_t<Ts>...>;
};

template <class T>
using axis_types =
    typename axis_types_impl<mp11::mp_if<is_vector_like<T>, mp11::mp_first<T>, T>>::type;

template <template <class> class Trait, class Axes>
using has_special_axis = mp11::mp_any_of<axis_types<Axes>, Trait>;

template <class Axes>
using has_growing_axis = mp11::mp_any_of<axis_types<Axes>, is_growing>;

template <class Axes>
using has_non_inclusive_axis = mp11::mp_any_of<axis_types<Axes>, is_not_inclusive>;

template <class T>
constexpr std::size_t type_score() {
  return sizeof(T) *
         (std::is_integral<T>::value ? 1 : std::is_floating_point<T>::value ? 10 : 100);
}

// arbitrary ordering of types
template <class T, class U>
using type_less = mp11::mp_bool<(type_score<T>() < type_score<U>())>;

template <class Axes>
using value_types = mp11::mp_sort<
    mp11::mp_unique<mp11::mp_transform<axis::traits::value_type, axis_types<Axes>>>,
    type_less>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* axes.hpp
f0Qw+VwxmGiiDPCdWlz+9obg/o2lyldZ6fVD7RVopjZ0U5pDLuujdjhu/smuBQzLPutw2f0znWLoSg4R2uAPmlza4CcvJCUddRS8gWzzYPH4hlQ9Eo6+Oud2RBqp1NydDdBCOqMX934wZmGtolfYWgySrujtNt//zEjod3Jk5yvBA8jFO3QIY5sknNn1cffT1Q2eAP+jM8Tjr96DlNu09eqAWlgMnZd8liuFyBnGswl8LT5qmFPJvaiYOiuowR2q6YnNm1xXn8ordahvzqbR4sV8bVLb0SwzdFsD8cOGevzBHh8V9iOYuG4YG6k5wtG1637/B//Ay4CkA2rNVqyk6sE3eQRXZeLSZjz3prlXEfSZ5jpRmaNy1augiSmcsUxx0FYPzj+HIm4JQddPr9BsH+99gkArqbJWztxpUBhnXMR3ItHontCltvANtHKx2eEn2bt6dGx1t6pF+uwls9Md8/UcZlENnUDqKvZWCXvRmYzKED4fW8DyTnXZWQohn1SKrS0Lde9vz9mh+N4eLT1BpS93MLhwsvbesD2V5a8tLb5dvgbBtLJybPEpTqGhOef0vaNY0yunBdrygatpp2e1AIdSNeGrYMBQK7+ROVUI5ZGBUvIItbNSdLizmR9IVB2IfTbVxMYDIWySWEpRRQ91wcQpIxZbKed41AaXUGhnUTp/9V82G6Ec0D+EyBst/nc7ReEjjtyq/NTde/YuccaZR3BWNOOkW2i5k/hbFB5ynpQQ3Lly7s6HHPRo9gCMtJLOS6y5mqB2Mx/rk+mJbvUhVA1kPOl6I94KkSRiTlToI36npBlervM6XG3CGvEknu89ywCcnn0vcM9n19lWdnojfEZhRMZwuMvMfWXUueHDED07hzV3tN6irUC2GblXf92jfzFKvMNG4NbeZqZGpeZXqjHwcZM7a5MjZqwl7mzpzK3fZnU1X2AvBJdXztn29qlBWzWTyZsuSprRWLx8NvRJfdtfFrojYuRcU/SZLm8LOnNEDOy0Hl4yJOaldDOJetJmjndZNT+7S7ILmVMZab6NNgiegcMUQUqrTUtTVzRqHoCgFqPyUpwOMXh4bhBUShkk9EqLHBa7QzXlL57oJkHdijpptYFsThFhlver91va70lnGyGrfVfZa/94plJBBfz1/LrEreqUlB4F3wKQl6gD8MSpZLxDlOexQfh4k52vmnuJVurvxShmrMkQLdy6ipqH8UR5WZxbk8Q5pR0JgBbJwNVCne3oP0/SBzFBxc6iMyMVzWNx4Ey18hmeKQpIQhmQTXbpkje3raSfawKT/MueoHZNfOxIcCoTc/X0BcPB8DYdlEYcYQh+EG4Jvu4+vqKPS4ddhaPdjhWJ8Qicn+vzzFwPC4iR12IuPY/18OGWHZsTb4wcxZJqqInrxBpvzvw1x18LXE3o4HCBdfW7GPtKv6boCuG1u4IPwHf2ePa+KF1+HxXr1/9FFhiABm3V2k1Nn1mg30Ke3n005dZ0LTXYLH5mIHzNNL6w+gI69Ij8124icOz1uEbxTz7hSPaWasFUoDys4d8Ejs9E73E/dXKT6gQb5wSbeMEzyAkJCAOUEgRoESdSs6fvy4bbAfazY0AqoXoQ8jhKLL5evEA3QsvRBK/YBVjAwvd7UM3Jpj9It7pdgo8971UiiE679PG1qp4tSCD9O5dYSSh4GhONO9JvA3CPNWc0SplABHgrC7ynDoWz3inU9qpEwSdrJLPgHuRtHz/uZeYVo+R2LH1itiXrIeVGj8tvqPsjWOLZHldZ7DBSCHK9yhbVzbouuNlxkd0Q7gKCOnJ9uvuhXymQLRGpj9kI4wY0VKa0/pw0hBBnOXAyikb/PqEWGFUmjVPfPPCF+n/sAphXwfRF/4DaC/xhTZoIjoeT7Pb2KJABdLzmPlqKED2WWoXpkK1X3mv3DtQAFb8kQQhGlqDWEMI2u2sAUP8R5Nu78ruOEcebztEgHfxz4y9p74/d52c/aWZBnSalE1RgzgIRbN0KYCaiNWMD+BS+wGoLhkIAoIEDulVngvBGwAOmyvH+pzEEvObVlQaTGM7uDfbeQz1HCPekGlHH2BaHFOHbuyMw9vB+CLeHofLmUS/PKwoMRrhLs0bhrwMqvPOBT+/KUZ8BxCGRBs2tybQPeBJ61Ld3g64Pn9D+yeyuZEWh9RjxO5+wJwGDIE4G1kGUwINLuDgNN7VzGiCjethanU+lAfL2uRO0qh0ciCyEFWc9x9NA4joX8HaD94/KsiouraJ/aAjfzfAbviFAApgLOn86hK4/ol1UBMz639PLVSJnWc8JnrSISDqNQbzLfPoAuWoWsNZa9B3qC7j6IVapUIecf+19KlAn6JnanYlXYF8DEy0qJnZ+ofhhIVHCArARmzNqHglEU/1NiDLzm6u5eTbAsYDXby6AVDx/PDNASrwPLSf7/1e1DPl4eSsPP7/x2rKy1Zna4Q9AScSwbKgrRhNb6hcScwsqD3UCJuIHrKUu2Eh+E25Xx4lWyCg2thc9W81vAFWT91D2lIsKyPiT4sMnbGBCVb5o4SGhoXxRCi9dvWYzOellxUT23t4+fh+Sut1OZWc4mZ78lY/6eboR44y0/p3UWS9aWBS4YVtf4+S7NHJzGj6jWbHSxyYrX6FIr+3bUyZdFCNZs+6T3D2z7q+YdqXodusjm+iHNlX3J2w7skw7DdGtCiOb5ofXyoc22e5ZSyF+XLQOXUDXtIFmjNyL++3YuZruPyCzr/vvkNyrA05M3JjcrVFN4PseiLmne+ciW/v933w7E6Hp+flpPI3+YexpWnEhZBmIj63OER6kOyD0Yu7SKu7GKsL7rMjQLQ6LUaCbkZ1VSUtteL1Oc114drwwi5/mj8Oxd6AfjoSN8HEAUePEg/rlGxCL+iwRj4u5e+uF3vCWO94fNE704WEkZxzvmx3TixiapIEwPiAoKmL3gt21saFj9z33OqOf+fVJ1DSohxZ96HLwCqZ2ih9moh2mcuDSerL1uVTdiPDyQkupQrHlXV0DtIcxBEbpRFf79xEg52FH+CxEpfG4k7qu4N6xp+GXxlfxjtL/JvyrKMNih7uN6Yqogur0Yk99tasFHJ1CH4TwY04ytQpp0gqT9uQ+D6pSgxDYcJmr4/+bJNlzC8hHHo9WFY8qrMDOIaUZavxPar8yWs9kcrVs8WGwDd5WrVHzRYx2VdnD9jMFwrvrxLJ2ME0afXKD957qy4HZap+1WvvgffQcwacBqAL7XjTHU/Ktu8ypYLgXNAzvxfzYcaldRkmY5LDJgrF2GFol/PVOrIWzJ+DZDBQZ6+3VI1NqCUjq99rJ/BqovMN/BY77Rshja3L2J9k8pSrGPGzbrGlis4SS51gD7hE77nNdecPMpNnZArzpMGGxWfKpavYnhmsE2nJ96r099mWCeuFjDmzw11K9i37cz9aHUKRLMvpNIo3Do+40QeOI2V/0A9rbfB+DO2ewfyWs/n0k+KVZOybSh1wOmWxNmVwEzZG5wfFtzFJGmPuN6udbdIEoW/KxMVkGU65QugzMbU9km5bsZi61jWJruwlQkg7qP7L9ihMdWkQRkp6kSTMzuL3ywF4PtJmjDuaf9Ukihy6o6z5z93h8DcH9/YCCNJ5LOXly7q7ZlqF+qsIhl+SzIWGe8B38cyajA5l49ET3z8o1mzAXi4wnbwvgkNJH3ENTK7D5QBr32cR5PZvuJPhTK5SiHQNp/V9q1ByzxNbnCAFcx2DwRlzsLHHmPuVqtIulJd1oRPIP2Fs07Co76umldVYWg5Q4oCY2mfnfs0rhz2A7tfcDNe/4WHXeLCtGO19HsKhdu145MlXd6jg9jUHEtYv/Li9wMDK0Cbrx6PbaZD+etcl8RMgqMob9ts79i94SXdEVaHR6lu9qFxViXd9z0OGIfDVKA74BAAL/BP0J/hPyJ/RP2J/wPxF/Iv9E/Yn+E/Mn9k/cn/g/CX8S/yT9Sf6T8if1T9qf9D8ZfzL/ZP3J/pPzJ/dP3p/8PwV//vtT+KfoT/Gfkj+lf8r+lP+p+FP5p+pP9Z+aP7V/6v7U/2n40/in6U/zn5Y/rX/a/rT/6fjT+afrT/efnj+9f/r+9P8Z+DP4Z+jP8J+RP6N/xv6M/5n4M/ln6s/0n5k/s3/m/sz/Wfiz+Gfpz/KflT+rf9b+rP/Z+LP5Z+vP9p+dP7t/9v7s/zn4c/jn6M/xn5M/p3/O/pz/ufhz+efqz/Wfmz+3f+7+3P95+PP45+nP85+XP69/3v68//n48/nn68/3n58/v38AfwAAiOB/pv23Iol8Eb6oxK5dwZMj86I2gcy6/JXpD82c/yM09dYm6wiLigv1Y7Rs5crntmwdXHWNzxfv7I5r2vzUjDPgC43SgrfE7SrkgKhutWx0ktn8L9RYjuxM71vwgnDBqO1Rp1UE55CStnApo8JEm2wJD7Q+c3lUZIez0l8ZL96nuvaiQdQ7WF+2jy/8TXmSuBG1Qj93mj1LCC+Y+yOcWh+uW7jn2L5yxoTllqA50puyE2USKlty7cW3VSg7D5puVRw/qgc89KmyNHDeLUyo/NjQWJDfMD4Er1sYzf5CHFWVxFbUH/xrHR3fIRyjH+MQlkHvH6BR/LTR6dMloW87aO0Hc6W0uijNZ36eqWbKNDCsM+5cMzuPUjtELsadNpgcCzf0XjtOLt5gI1Du5X47ZK7W3nuzuBb0LM/dF0bu6P55MJkGHvWwN2X5/Ewli9iUImnZJRtMiOnRLOty/xQCU5CP1i1k7TOpNhx5zwqu4uscuHgqZDKWKns1FjYc9UgV8NGzmyJM/Ho5+BhMS64G+BjPLTH8P+pLVnl6sAjpkDT61sEtvbMg4REBRpICPCox7ng/16/kg+8yIt/PFQt87lnecLV0Q0bEhipagW1N03shhZpai5H3e/XRIQLNBh/0YlTUlo3YyeMzUkVnE8zQbmxzGX6qwZ5UtoV9Nc60NLjAriEW3f8BQIC/f/GowPfr7ekYT2HsXF1umuzxtZ7hcYhL/FX5H1H8rrfFLnN1/hGyS19NNnvVvS35HzmH2CkHoRjupthZ852O5l0J+HmEh4k9jF/PBRrDJ1TJYmdCDm1MdQdXumTb+9x0e9jB7QnZm/+FByjoTseLEUhbqBAqPqCGKLtPdTpC/qnUTHS8yd56iw4uWsjPJnZ+XZB8a34kosEKndhVlK435663RaFXKNqSqds1D1auc7RLCJ1VmLNmntOsfAFULmJiskWQoEcSKorV5xdAAsbKNSwS8gxrBX/qIH/XichC/y1JjpDCUcJQbmyUjtKbDo65gwK56Vi5rJqRqygTjK55Om7b36LTmVXUW9YDmnk4RJE1k6ZcY5ohjfaB7CpZLDncwCJbKMojzxDlwTxsNzwkzSLjFFlQm8BDd0g8fbS2C4MNFWpcYUVz8ri5aAci1K2zxBfIMzs/ZM0AK481NclURKczUK4fb+v56IchF2vR1b8LkNTBGFf9xVNw+F1YHeMWDlAeva1QD3HDBew9kQiv5TFuswivVTGuWw2vy/Wva7m2ziMSeWLI4zogAia7E7+ibRBXDxFffymRPu91yF6WVetfl8HXGMg1h2CA8MCunhhpTMQwuGd9fin/OD5VnhGYh3KWQlKIJ838utAUgoYwSyl/CPCtg/8FkDHPzFhAiXnwsdwENiQPgsmjnOWQdJ3ZtK8FTSFoCLOc8l9HvWLBoSKSAs+KyPhUeVJQrSIy8+tCG0o1S/t5piQcOaAheVJQjDfra0EbQrEDOw8tge7k4xZeq+C1zYzq20LfRQjin48xvraZX28oBsEsDLsfVeOryHSK5an6VnV+ArwaWJDTsB/AHSYphtDSOrDD4Wh0Am/ncQvLgYMNOIWXtrJOmqtL2OgruZwV6mnJP4LxwdkZ9dC8lnzZSQcCyC1h0uB1PHzEf9oRnP1rZjsdh3hwoObDGKu4gE/rlOHb5vDMD3AFGsjcJnhIBJZgIFPVgTdMPv4GrwpJcOCNk2HlBQAMpz1KlOygW3dgJxGjriMuvoNvdGtIUqz60MEJNfVZTgwgATJxN7t6AU/RufriLuLhaJqnallq4rbt3AT/TafFbkGQ/gvPk7L5eZKvhaKlGf5I/viacaZEvlbk6i9Q6//u60Zmudqmfj8R9aKdtS+gvh3qVRwxvCQ0REY95kylmT+pK7VLHqP9pbD/scjzKM7d/AsZpMepK2Y3ji4+Fio/1fANVED3IeH8/B6MY86qcsmhOQ2+Avhcx35V8GEiVHgOGZsVoPBf2JkNG7ExsynkeEibhVG4lsxtdFSrNRh36WwMu9cA+3hImR44Ep2dvyzaIEcwAhx8icparRS9VI6fCULfkpau8CnRTPgcKIqMisrxTFQ/gl/L5Ygbjz6C0k03KI6OCkk7+qTT13oveW6XtR9J2nxH4MWIqs2XMUPEr8ltC5S2KxV0ACj1VCi0fZXi3w1cI0dGaEdroF2PbPc4tEqprU7BMFNBqWeagr+1KgmDxqvvJRLxSQgs/GTgPL3MFPg6fJl6hFgjtV+qtOzsqJR8Ld/lN3XLFyFRVAwadxW0aSGd6My27FhVrsFl7y+8Mjb6rGq+1t9eldWysyY8u3E89Fj+qUZYlELRYwU96AGQ3TGeeoybgsDnevbK2dBjagH1WCH2WNF27LEll+Y65mp9yDiWoT4N23IYmuumasJp2s/l+GnaXLn9UvwpaQPxkdDqZYFd2vVy5Gp+xvRTCbrlWkmbKU2ukyJp0euk+MjJ34hI0Yvj7uhKWVskae4AcPrIGMoPUHriGbVsSaeLxD83ZoBRN/kyORLmOdK1nuh0Ob60lr201UOZ4FcdDpXR0awA5IOej4/ntV/Da49erE2XoxUytDV6qdmWKimeqU2XJvuhOXKcRs90KVohtc9V2iuUtqDSNh1vnpT2KuVJ55RdvtYEzsHLpcD10HFHKL53aQPIVW/Rvi0wEPmhVilD5padkVHQ/zXanp5KxcFCW3EUyUS0yM80pfRKJSJrVXLpAiX8ff4/kq3hUFShRDmUOPYujiG5fY7SVqW0LVY0VQZgkIHlAKz4dbyOLEsd27GEh1cxGrJjHXkagT4NQWrzJW2apA0GBrSfSb7WmTDq4udpompVttT9bDe01mNWrYiavwc1tDUQPVR2ekUuhsmlY8iGhT+TqqIzccAuweFLQ1c19DKbt8+z6FvCyK1LIWnhiiFUxIHxRPmGkI6T+EE5vwl4tELcpUQmhq6DrXyoDv+UwZ/GaaGiqcJFwmmfDBrWcUo1Wz8LmgpICE+YHDQ5wzR9/8KCsJoOUK5xWh1iCtkp5P8wofHMje5Q4VTuFpNLKMKXF10J3nTiKDrH9LU+RObudMr/pnHK/2G5aHy4RL8E0tRcvN3Jd4bPaN5C8JUVCtSEO3eVbZ6qe9X8TIcnG/AUdrcB7xwdXoDg+QDeGJSssE1e34cJ7inzab4rp6/HMoXnSbL70PiWvtEVKjBwIyHx0U8QoYi1ccJGjn2DN448UMUbtNU6hPyp3OungPATgiCqjXjZjZm6q80JoTzIyg4FErYM9Zm6n80RTM0U/jTtrnrhF3ZhQ/FuVlSZ67h5+ybLtachz986ZJQ1Hy4AYT7iJf8wIL4rvhZUKGA/QqvAAcl3Sw13nVKUmym0
*/