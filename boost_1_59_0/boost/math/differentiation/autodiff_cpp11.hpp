//           Copyright Matthew Pulver 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//           https://www.boost.org/LICENSE_1_0.txt)

// Contributors:
//  * Kedar R. Bhat - C++11 compatibility.

// Notes:
//  * Any changes to this file should always be downstream from autodiff.cpp.
//    C++17 is a higher-level language and is easier to maintain. For example, a number of functions which are
//    lucidly read in autodiff.cpp are forced to be split into multiple structs/functions in this file for
//    C++11.
//  * Use of typename RootType and SizeType is a hack to prevent Visual Studio 2015 from compiling functions
//    that are never called, that would otherwise produce compiler errors. Also forces functions to be inline.

#ifndef BOOST_MATH_DIFFERENTIATION_AUTODIFF_HPP
#error \
    "Do not #include this file directly. This should only be #included by autodiff.hpp for C++11 compatibility."
#endif

#include <type_traits>
#include <boost/math/tools/mp.hpp>

namespace boost {
namespace math {

namespace mp = tools::meta_programming;

namespace differentiation {
inline namespace autodiff_v1 {
namespace detail {

template <typename RealType, size_t Order>
fvar<RealType, Order>::fvar(root_type const& ca, bool const is_variable) {
  fvar_cpp11(is_fvar<RealType>{}, ca, is_variable);
}

template <typename RealType, size_t Order>
template <typename RootType>
void fvar<RealType, Order>::fvar_cpp11(std::true_type, RootType const& ca, bool const is_variable) {
  v.front() = RealType(ca, is_variable);
  if (0 < Order)
    std::fill(v.begin() + 1, v.end(), static_cast<RealType>(0));
}

template <typename RealType, size_t Order>
template <typename RootType>
void fvar<RealType, Order>::fvar_cpp11(std::false_type, RootType const& ca, bool const is_variable) {
  v.front() = ca;
  if (0 < Order) {
    v[1] = static_cast<root_type>(static_cast<int>(is_variable));
    if (1 < Order)
      std::fill(v.begin() + 2, v.end(), static_cast<RealType>(0));
  }
}

template <typename RealType, size_t Order>
template <typename... Orders>
get_type_at<RealType, sizeof...(Orders)> fvar<RealType, Order>::at_cpp11(std::true_type,
                                                                         size_t order,
                                                                         Orders...) const {
  return v.at(order);
}

template <typename RealType, size_t Order>
template <typename... Orders>
get_type_at<RealType, sizeof...(Orders)> fvar<RealType, Order>::at_cpp11(std::false_type,
                                                                         size_t order,
                                                                         Orders... orders) const {
  return v.at(order).at(orders...);
}

// Can throw "std::out_of_range: array::at: __n (which is 7) >= _Nm (which is 7)"
template <typename RealType, size_t Order>
template <typename... Orders>
get_type_at<RealType, sizeof...(Orders)> fvar<RealType, Order>::at(size_t order, Orders... orders) const {
  return at_cpp11(std::integral_constant<bool, sizeof...(orders) == 0>{}, order, orders...);
}

template <typename T, typename... Ts>
constexpr T product(Ts...) {
  return static_cast<T>(1);
}

template <typename T, typename... Ts>
constexpr T product(T factor, Ts... factors) {
  return factor * product<T>(factors...);
}

// Can throw "std::out_of_range: array::at: __n (which is 7) >= _Nm (which is 7)"
template <typename RealType, size_t Order>
template <typename... Orders>
get_type_at<fvar<RealType, Order>, sizeof...(Orders)> fvar<RealType, Order>::derivative(
    Orders... orders) const {
  static_assert(sizeof...(Orders) <= depth,
                "Number of parameters to derivative(...) cannot exceed fvar::depth.");
  return at(static_cast<size_t>(orders)...) *
         product(boost::math::factorial<root_type>(static_cast<unsigned>(orders))...);
}

template <typename RootType, typename Func>
class Curry {
  Func const& f_;
  size_t const i_;

 public:
  template <typename SizeType>  // typename SizeType to force inline constructor.
  Curry(Func const& f, SizeType i) : f_(f), i_(static_cast<std::size_t>(i)) {}
  template <typename... Indices>
  RootType operator()(Indices... indices) const {
    using unsigned_t = typename std::make_unsigned<typename std::common_type<Indices>::type...>::type;
    return f_(i_, static_cast<unsigned_t>(indices)...);
  }
};

template <typename RealType, size_t Order>
template <typename Func, typename Fvar, typename... Fvars>
promote<fvar<RealType, Order>, Fvar, Fvars...> fvar<RealType, Order>::apply_coefficients(
    size_t const order,
    Func const& f,
    Fvar const& cr,
    Fvars&&... fvars) const {
  fvar<RealType, Order> const epsilon = fvar<RealType, Order>(*this).set_root(0);
  size_t i = order < order_sum ? order : order_sum;
  using return_type = promote<fvar<RealType, Order>, Fvar, Fvars...>;
  return_type accumulator = cr.apply_coefficients(
      order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...);
  while (i--)
    (accumulator *= epsilon) += cr.apply_coefficients(
        order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...);
  return accumulator;
}

template <typename RealType, size_t Order>
template <typename Func, typename Fvar, typename... Fvars>
promote<fvar<RealType, Order>, Fvar, Fvars...> fvar<RealType, Order>::apply_coefficients_nonhorner(
    size_t const order,
    Func const& f,
    Fvar const& cr,
    Fvars&&... fvars) const {
  fvar<RealType, Order> const epsilon = fvar<RealType, Order>(*this).set_root(0);
  fvar<RealType, Order> epsilon_i = fvar<RealType, Order>(1);  // epsilon to the power of i
  using return_type = promote<fvar<RealType, Order>, Fvar, Fvars...>;
  return_type accumulator = cr.apply_coefficients_nonhorner(
      order, Curry<typename return_type::root_type, Func>(f, 0), std::forward<Fvars>(fvars)...);
  size_t const i_max = order < order_sum ? order : order_sum;
  for (size_t i = 1; i <= i_max; ++i) {
    epsilon_i = epsilon_i.epsilon_multiply(i - 1, 0, epsilon, 1, 0);
    accumulator += epsilon_i.epsilon_multiply(
        i,
        0,
        cr.apply_coefficients_nonhorner(
            order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...),
        0,
        0);
  }
  return accumulator;
}

template <typename RealType, size_t Order>
template <typename Func, typename Fvar, typename... Fvars>
promote<fvar<RealType, Order>, Fvar, Fvars...> fvar<RealType, Order>::apply_derivatives(
    size_t const order,
    Func const& f,
    Fvar const& cr,
    Fvars&&... fvars) const {
  fvar<RealType, Order> const epsilon = fvar<RealType, Order>(*this).set_root(0);
  size_t i = order < order_sum ? order : order_sum;
  using return_type = promote<fvar<RealType, Order>, Fvar, Fvars...>;
  return_type accumulator =
      cr.apply_derivatives(
          order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...) /
      factorial<root_type>(static_cast<unsigned>(i));
  while (i--)
    (accumulator *= epsilon) +=
        cr.apply_derivatives(
            order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...) /
        factorial<root_type>(static_cast<unsigned>(i));
  return accumulator;
}

template <typename RealType, size_t Order>
template <typename Func, typename Fvar, typename... Fvars>
promote<fvar<RealType, Order>, Fvar, Fvars...> fvar<RealType, Order>::apply_derivatives_nonhorner(
    size_t const order,
    Func const& f,
    Fvar const& cr,
    Fvars&&... fvars) const {
  fvar<RealType, Order> const epsilon = fvar<RealType, Order>(*this).set_root(0);
  fvar<RealType, Order> epsilon_i = fvar<RealType, Order>(1);  // epsilon to the power of i
  using return_type = promote<fvar<RealType, Order>, Fvar, Fvars...>;
  return_type accumulator = cr.apply_derivatives_nonhorner(
      order, Curry<typename return_type::root_type, Func>(f, 0), std::forward<Fvars>(fvars)...);
  size_t const i_max = order < order_sum ? order : order_sum;
  for (size_t i = 1; i <= i_max; ++i) {
    epsilon_i = epsilon_i.epsilon_multiply(i - 1, 0, epsilon, 1, 0);
    accumulator += epsilon_i.epsilon_multiply(
        i,
        0,
        cr.apply_derivatives_nonhorner(
            order - i, Curry<typename return_type::root_type, Func>(f, i), std::forward<Fvars>(fvars)...) /
            factorial<root_type>(static_cast<unsigned>(i)),
        0,
        0);
  }
  return accumulator;
}

template <typename RealType, size_t Order>
template <typename SizeType>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply_cpp11(std::true_type,
                                                                    SizeType z0,
                                                                    size_t isum0,
                                                                    fvar<RealType, Order> const& cr,
                                                                    size_t z1,
                                                                    size_t isum1) const {
  size_t const m0 = order_sum + isum0 < Order + z0 ? Order + z0 - (order_sum + isum0) : 0;
  size_t const m1 = order_sum + isum1 < Order + z1 ? Order + z1 - (order_sum + isum1) : 0;
  size_t const i_max = m0 + m1 < Order ? Order - (m0 + m1) : 0;
  fvar<RealType, Order> retval = fvar<RealType, Order>();
  for (size_t i = 0, j = Order; i <= i_max; ++i, --j)
    retval.v[j] = epsilon_inner_product(z0, isum0, m0, cr, z1, isum1, m1, j);
  return retval;
}

template <typename RealType, size_t Order>
template <typename SizeType>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply_cpp11(std::false_type,
                                                                    SizeType z0,
                                                                    size_t isum0,
                                                                    fvar<RealType, Order> const& cr,
                                                                    size_t z1,
                                                                    size_t isum1) const {
  using ssize_t = typename std::make_signed<std::size_t>::type;
  RealType const zero(0);
  size_t const m0 = order_sum + isum0 < Order + z0 ? Order + z0 - (order_sum + isum0) : 0;
  size_t const m1 = order_sum + isum1 < Order + z1 ? Order + z1 - (order_sum + isum1) : 0;
  size_t const i_max = m0 + m1 < Order ? Order - (m0 + m1) : 0;
  fvar<RealType, Order> retval = fvar<RealType, Order>();
  for (size_t i = 0, j = Order; i <= i_max; ++i, --j)
    retval.v[j] = std::inner_product(
        v.cbegin() + ssize_t(m0), v.cend() - ssize_t(i + m1), cr.v.crbegin() + ssize_t(i + m0), zero);
  return retval;
}

template <typename RealType, size_t Order>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply(size_t z0,
                                                              size_t isum0,
                                                              fvar<RealType, Order> const& cr,
                                                              size_t z1,
                                                              size_t isum1) const {
  return epsilon_multiply_cpp11(is_fvar<RealType>{}, z0, isum0, cr, z1, isum1);
}

template <typename RealType, size_t Order>
template <typename SizeType>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply_cpp11(std::true_type,
                                                                    SizeType z0,
                                                                    size_t isum0,
                                                                    root_type const& ca) const {
  fvar<RealType, Order> retval(*this);
  size_t const m0 = order_sum + isum0 < Order + z0 ? Order + z0 - (order_sum + isum0) : 0;
  for (size_t i = m0; i <= Order; ++i)
    retval.v[i] = retval.v[i].epsilon_multiply(z0, isum0 + i, ca);
  return retval;
}

template <typename RealType, size_t Order>
template <typename SizeType>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply_cpp11(std::false_type,
                                                                    SizeType z0,
                                                                    size_t isum0,
                                                                    root_type const& ca) const {
  fvar<RealType, Order> retval(*this);
  size_t const m0 = order_sum + isum0 < Order + z0 ? Order + z0 - (order_sum + isum0) : 0;
  for (size_t i = m0; i <= Order; ++i)
    if (retval.v[i] != static_cast<RealType>(0))
      retval.v[i] *= ca;
  return retval;
}

template <typename RealType, size_t Order>
fvar<RealType, Order> fvar<RealType, Order>::epsilon_multiply(size_t z0,
                                                              size_t isum0,
                                                              root_type const& ca) const {
  return epsilon_multiply_cpp11(is_fvar<RealType>{}, z0, isum0, ca);
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::multiply_assign_by_root_type_cpp11(std::true_type,
                                                                                 bool is_root,
                                                                                 RootType const& ca) {
  auto itr = v.begin();
  itr->multiply_assign_by_root_type(is_root, ca);
  for (++itr; itr != v.end(); ++itr)
    itr->multiply_assign_by_root_type(false, ca);
  return *this;
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::multiply_assign_by_root_type_cpp11(std::false_type,
                                                                                 bool is_root,
                                                                                 RootType const& ca) {
  auto itr = v.begin();
  if (is_root || *itr != 0)
    *itr *= ca;  // Skip multiplication of 0 by ca=inf to avoid nan, except when is_root.
  for (++itr; itr != v.end(); ++itr)
    if (*itr != 0)
      *itr *= ca;
  return *this;
}

template <typename RealType, size_t Order>
fvar<RealType, Order>& fvar<RealType, Order>::multiply_assign_by_root_type(bool is_root,
                                                                           root_type const& ca) {
  return multiply_assign_by_root_type_cpp11(is_fvar<RealType>{}, is_root, ca);
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::negate_cpp11(std::true_type, RootType const&) {
  std::for_each(v.begin(), v.end(), [](RealType& r) { r.negate(); });
  return *this;
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::negate_cpp11(std::false_type, RootType const&) {
  std::for_each(v.begin(), v.end(), [](RealType& a) { a = -a; });
  return *this;
}

template <typename RealType, size_t Order>
fvar<RealType, Order>& fvar<RealType, Order>::negate() {
  return negate_cpp11(is_fvar<RealType>{}, static_cast<root_type>(*this));
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::set_root_cpp11(std::true_type, RootType const& root) {
  v.front().set_root(root);
  return *this;
}

template <typename RealType, size_t Order>
template <typename RootType>
fvar<RealType, Order>& fvar<RealType, Order>::set_root_cpp11(std::false_type, RootType const& root) {
  v.front() = root;
  return *this;
}

template <typename RealType, size_t Order>
fvar<RealType, Order>& fvar<RealType, Order>::set_root(root_type const& root) {
  return set_root_cpp11(is_fvar<RealType>{}, root);
}

template <typename RealType, size_t Order, size_t... Is>
auto make_fvar_for_tuple(mp::index_sequence<Is...>, RealType const& ca)
    -> decltype(make_fvar<RealType, zero<Is>::value..., Order>(ca)) {
  return make_fvar<RealType, zero<Is>::value..., Order>(ca);
}

template <typename RealType, size_t... Orders, size_t... Is, typename... RealTypes>
auto make_ftuple_impl(mp::index_sequence<Is...>, RealTypes const&... ca)
    -> decltype(std::make_tuple(make_fvar_for_tuple<RealType, Orders>(mp::make_index_sequence<Is>{},
                                                                      ca)...)) {
  return std::make_tuple(make_fvar_for_tuple<RealType, Orders>(mp::make_index_sequence<Is>{}, ca)...);
}

}  // namespace detail

template <typename RealType, size_t... Orders, typename... RealTypes>
auto make_ftuple(RealTypes const&... ca)
    -> decltype(detail::make_ftuple_impl<RealType, Orders...>(mp::index_sequence_for<RealTypes...>{},
                                                              ca...)) {
  static_assert(sizeof...(Orders) == sizeof...(RealTypes),
                "Number of Orders must match number of function parameters.");
  return detail::make_ftuple_impl<RealType, Orders...>(mp::index_sequence_for<RealTypes...>{}, ca...);
}

}  // namespace autodiff_v1
}  // namespace differentiation
}  // namespace math
}  // namespace boost

/* autodiff_cpp11.hpp
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
*/