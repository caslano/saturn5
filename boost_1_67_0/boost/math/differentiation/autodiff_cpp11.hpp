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

#include <boost/mp11/integer_sequence.hpp>

namespace boost {
namespace math {
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
auto make_fvar_for_tuple(mp11::index_sequence<Is...>, RealType const& ca)
    -> decltype(make_fvar<RealType, zero<Is>::value..., Order>(ca)) {
  return make_fvar<RealType, zero<Is>::value..., Order>(ca);
}

template <typename RealType, size_t... Orders, size_t... Is, typename... RealTypes>
auto make_ftuple_impl(mp11::index_sequence<Is...>, RealTypes const&... ca)
    -> decltype(std::make_tuple(make_fvar_for_tuple<RealType, Orders>(mp11::make_index_sequence<Is>{},
                                                                      ca)...)) {
  return std::make_tuple(make_fvar_for_tuple<RealType, Orders>(mp11::make_index_sequence<Is>{}, ca)...);
}

}  // namespace detail

template <typename RealType, size_t... Orders, typename... RealTypes>
auto make_ftuple(RealTypes const&... ca)
    -> decltype(detail::make_ftuple_impl<RealType, Orders...>(mp11::index_sequence_for<RealTypes...>{},
                                                              ca...)) {
  static_assert(sizeof...(Orders) == sizeof...(RealTypes),
                "Number of Orders must match number of function parameters.");
  return detail::make_ftuple_impl<RealType, Orders...>(mp11::index_sequence_for<RealTypes...>{}, ca...);
}

}  // namespace autodiff_v1
}  // namespace differentiation
}  // namespace math
}  // namespace boost

/* autodiff_cpp11.hpp
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
*/