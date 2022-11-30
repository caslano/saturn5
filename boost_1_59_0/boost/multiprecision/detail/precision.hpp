///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_PRECISION_HPP
#define BOOST_MP_PRECISION_HPP

#include <boost/multiprecision/traits/is_variable_precision.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/digits.hpp>
#include <boost/multiprecision/detail/assert.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class B, boost::multiprecision::expression_template_option ET>
inline constexpr unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>&, const std::integral_constant<int, 0>&)
{
   return std::numeric_limits<boost::multiprecision::number<B, ET> >::digits10;
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>& val, const std::integral_constant<int, 1>&)
{
   //
   // We have an arbitrary precision integer, take it's "precision" as the
   // location of the most-significant-bit less the location of the
   // least-significant-bit, ie the number of bits required to represent the
   // the value assuming we will have an exponent to shift things by:
   //
   return static_cast<unsigned>(val.is_zero() ? 1 : 1 + digits2_2_10(msb(abs(val)) - lsb(abs(val)) + 1));
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>& val, const std::integral_constant<int, 2>&)
{
   //
   // We have an arbitrary precision rational, take it's "precision" as the
   // the larger of the "precision" of numerator and denominator:
   //
   return (std::max)(current_precision_of_last_chance_imp(numerator(val), std::integral_constant<int, 1>()), current_precision_of_last_chance_imp(denominator(val), std::integral_constant<int, 1>()));
}

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& n, const std::integral_constant<bool, true>&)
{
   return n.precision();
}
template <class B, boost::multiprecision::expression_template_option ET>
inline constexpr unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& val, const std::integral_constant<bool, false>&)
{
   using tag = std::integral_constant<int,
                                      std::numeric_limits<boost::multiprecision::number<B, ET> >::is_specialized &&
                                              std::numeric_limits<boost::multiprecision::number<B, ET> >::is_integer &&
                                              std::numeric_limits<boost::multiprecision::number<B, ET> >::is_exact &&
                                              !std::numeric_limits<boost::multiprecision::number<B, ET> >::is_modulo
                                          ? 1
                                      : boost::multiprecision::number_category<boost::multiprecision::number<B, ET> >::value == boost::multiprecision::number_kind_rational ? 2
                                                                                                                                                                            : 0>;
   return current_precision_of_last_chance_imp(val, tag());
}

template <class R, class Terminal>
inline constexpr unsigned current_precision_of_terminal(const Terminal&)
{
   return (R::thread_default_variable_precision_options() >= variable_precision_options::preserve_all_precision) 
      ? (std::numeric_limits<Terminal>::min_exponent ? std::numeric_limits<Terminal>::digits10 : 1 + std::numeric_limits<Terminal>::digits10) : 0;
}
template <class R, class Terminal>
inline constexpr unsigned current_precision_of(const Terminal& r)
{
   return current_precision_of_terminal<R>(R::canonical_value(r));
}
template <class R>
inline constexpr unsigned current_precision_of(const float&)
{
   using list = typename R::backend_type::float_types;
   using first_float = typename std::tuple_element<0, list>::type;

   return (R::thread_default_variable_precision_options() >= variable_precision_options::preserve_all_precision) ? std::numeric_limits<first_float>::digits10 : 0;
}

template <class R, class Terminal, std::size_t N>
inline constexpr unsigned current_precision_of(const Terminal (&)[N])
{ // For string literals:
   return 0;
}

template <class R, class B, boost::multiprecision::expression_template_option ET>
inline constexpr unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& n, const std::true_type&)
{
   return std::is_same<R, boost::multiprecision::number<B, ET> >::value 
      || (std::is_same<typename R::value_type, boost::multiprecision::number<B, ET> >::value && (R::thread_default_variable_precision_options() >= variable_precision_options::preserve_component_precision))
      || (R::thread_default_variable_precision_options() >= variable_precision_options::preserve_all_precision) 
      ? current_precision_of_imp(n, boost::multiprecision::detail::is_variable_precision<boost::multiprecision::number<B, ET> >()) : 0;
}
template <class R, class B, boost::multiprecision::expression_template_option ET>
inline constexpr unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& n, const std::false_type&)
{
   return std::is_same<R, boost::multiprecision::number<B, ET> >::value 
      || std::is_same<typename R::value_type, boost::multiprecision::number<B, ET> >::value
      ? current_precision_of_imp(n, boost::multiprecision::detail::is_variable_precision<boost::multiprecision::number<B, ET> >()) : 0;
}

template <class R, class B, boost::multiprecision::expression_template_option ET>
inline constexpr unsigned current_precision_of(const boost::multiprecision::number<B, ET>& n)
{
   return current_precision_of_imp<R>(n, boost::multiprecision::detail::is_variable_precision<R>());
}

template <class R, class tag, class Arg1>
inline constexpr unsigned current_precision_of(const expression<tag, Arg1, void, void, void>& expr)
{
   return current_precision_of<R>(expr.left_ref());
}

template <class R, class Arg1>
inline constexpr unsigned current_precision_of(const expression<terminal, Arg1, void, void, void>& expr)
{
   return current_precision_of<R>(expr.value());
}

template <class R, class tag, class Arg1, class Arg2>
inline constexpr unsigned current_precision_of(const expression<tag, Arg1, Arg2, void, void>& expr)
{
   return (std::max)(current_precision_of<R>(expr.left_ref()), current_precision_of<R>(expr.right_ref()));
}

template <class R, class tag, class Arg1, class Arg2, class Arg3>
inline constexpr unsigned current_precision_of(const expression<tag, Arg1, Arg2, Arg3, void>& expr)
{
   return (std::max)((std::max)(current_precision_of<R>(expr.left_ref()), current_precision_of<R>(expr.right_ref())), current_precision_of<R>(expr.middle_ref()));
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4130)
#endif

template <class R, bool = boost::multiprecision::detail::is_variable_precision<R>::value>
struct scoped_default_precision
{
   template <class T>
   constexpr scoped_default_precision(const T&) {}
   template <class T, class U>
   constexpr scoped_default_precision(const T&, const U&) {}
   template <class T, class U, class V>
   constexpr scoped_default_precision(const T&, const U&, const V&) {}

   //
   // This function is never called: in C++17 it won't be compiled either:
   //
   unsigned precision() const
   {
      BOOST_MP_ASSERT("This function should never be called!!" == nullptr);
      return 0;
   }
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class R>
struct scoped_default_precision<R, true>
{
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a)
   {
      init(has_uniform_precision() ? R::thread_default_precision() : (std::max)(R::thread_default_precision(), current_precision_of<R>(a)));
   }
   template <class T, class U>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b)
   {
      init(has_uniform_precision() ? R::thread_default_precision() : (std::max)(R::thread_default_precision(), (std::max)(current_precision_of<R>(a), current_precision_of<R>(b))));
   }
   template <class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b, const V& c)
   {
      init(has_uniform_precision() ? R::thread_default_precision() : (std::max)((std::max)(current_precision_of<R>(a), current_precision_of<R>(b)), (std::max)(R::thread_default_precision(), current_precision_of<R>(c))));
   }
   ~scoped_default_precision()
   {
      if(m_new_prec != m_old_prec)
         R::thread_default_precision(m_old_prec);
   }
   BOOST_MP_CXX14_CONSTEXPR unsigned precision() const
   {
      return m_new_prec;
   }

   static constexpr bool has_uniform_precision()
   {
      return R::thread_default_variable_precision_options() <= boost::multiprecision::variable_precision_options::assume_uniform_precision;
   }

 private:
   BOOST_MP_CXX14_CONSTEXPR void init(unsigned p)
   {
      m_old_prec = R::thread_default_precision();
      if (p && (p != m_old_prec))
      {
         R::thread_default_precision(p);
         m_new_prec = p;
      }
      else
         m_new_prec = m_old_prec;
   }
   unsigned m_old_prec, m_new_prec;
};

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T*, const std::integral_constant<bool, false>&) {}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj, const std::integral_constant<bool, true>&)
{
   if (obj->precision() != T::thread_default_precision())
   {
      obj->precision(T::thread_default_precision());
   }
}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj)
{
   maybe_promote_precision(obj, std::integral_constant<bool, boost::multiprecision::detail::is_variable_precision<T>::value>());
}

#ifndef BOOST_NO_CXX17_IF_CONSTEXPR
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) \
   if                                               \
   constexpr(boost::multiprecision::detail::is_variable_precision<T>::value)
#else
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) if (boost::multiprecision::detail::is_variable_precision<T>::value)
#endif

template <class T, bool = boost::multiprecision::detail::is_variable_precision<T>::value>
struct scoped_target_precision
{
   variable_precision_options opts;
   scoped_target_precision() : opts(T::thread_default_variable_precision_options())
   {
      T::thread_default_variable_precision_options(variable_precision_options::preserve_target_precision);
   }
   ~scoped_target_precision()
   {
      T::thread_default_variable_precision_options(opts);
   }
};
template <class T>
struct scoped_target_precision<T, false> {};

template <class T, bool = boost::multiprecision::detail::is_variable_precision<T>::value>
struct scoped_source_precision
{
   variable_precision_options opts;
   scoped_source_precision() : opts(T::thread_default_variable_precision_options())
   {
      T::thread_default_variable_precision_options(variable_precision_options::preserve_source_precision);
   }
   ~scoped_source_precision()
   {
      T::thread_default_variable_precision_options(opts);
   }
};
template <class T>
struct scoped_source_precision<T, false> {};

template <class T, bool = boost::multiprecision::detail::is_variable_precision<T>::value>
struct scoped_precision_options
{
   unsigned saved_digits;
   boost::multiprecision::variable_precision_options saved_options;

   scoped_precision_options(unsigned digits) 
      : saved_digits(T::thread_default_precision()), saved_options(T::thread_default_variable_precision_options())
   {
      T::thread_default_precision(digits);
   }
   scoped_precision_options(unsigned digits, variable_precision_options opts)
      : saved_digits(T::thread_default_precision()), saved_options(T::thread_default_variable_precision_options())
   {
      T::thread_default_precision(digits);
      T::thread_default_variable_precision_options(opts);
   }
   template <class U>
   scoped_precision_options(const U& u)
      : saved_digits(T::thread_default_precision()), saved_options(T::thread_default_variable_precision_options())
   {
      T::thread_default_precision(u.precision());
      T::thread_default_variable_precision_options(U::thread_default_variable_precision_options());
   }
   ~scoped_precision_options()
   {
      T::thread_default_variable_precision_options(saved_options);
      T::thread_default_precision(saved_digits);
   }
};

template <class T>
struct scoped_precision_options<T, false>
{
   scoped_precision_options(unsigned) {}
   scoped_precision_options(unsigned, variable_precision_options) {}
   template <class U>
   scoped_precision_options(const U&) {}
   ~scoped_precision_options() {}
};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* precision.hpp
uVnxRlATEbFFxZk0iJj3OlnPue198F9yYA+0m5CRZRKz6KJ0rfjQSPevaIdUxBFjsNaMnfPli/7ZFcK7VIaoo2Wm3/AWCZ2cSRnT2X2AYtM8BYerMriVeg0odbL41/DM953iz1EZH5k9xcxj3Rz77nBUs519RU7SDaP9jOdP0NN+uTjuny6i+iBs3xpkYOu+LZrvt46i/TD/HPuGX6ykrsraJzdTjvfO4WpKNb38Jvxqe6H+XnLj/bxu/+Z+1Tpi/npy+//y3J+/7xI1PvQSf48nfVg1MvRdrisc2Q+BxYP7vFDjvpE+9ELrQW8aW+pNTopd5PK+tPUDxebtTaxOvi0ZNjr0N97sju3IU1jIF+C1G53ERyMDnSajejcZLv/C8V6w254Y9snRHuzkHkH/gsOQteBpfoodIFRwDNtcea91HGXGqXOVYqryc5OMuFqMGbv7ZD3mWSKJOQ/vk8WG1QEK4D4+9aPH3rdj1xk7LJhArUupAyM7AMq2D5JoRpUMKMNkmQSnX1lFkaQSNvrzMtgE0t/zwgg564RLH1WxvFjek86lG5FiKlTVS/Dy6lktMxp2a+q/zGx1HWeqSa+lkTiQG/4LiyV+vxUn0Jfc2ZD7PGm0/4112mc5L9ZcogVcftXpzHgKYG2hMlMwLlOoF0ETF5D39QXbKf5kHOSPInzLWs0+hhIOOZm73mOZSyAaXyT+spHTlWba6Jg2g8asz15Ww2RlBR1OxFRsKTajKv4R1z/w9rHwFSlthsPKqHObY08tWFp/+8B97eTZviBryfFcWxWuturWbr2Ehl/nFZBU/xlH/0wpGW8Nq78t7fuYH4OoRGKp30oS6hyOE+LaHri0FEOUrk38l3wLwgm/Lcf3eqscUou6062bRksXM0E6CX3XKJsd7WVtN5n+xfzeTNQXw5vNrTTgw8jiW5v8nksXdbG4XDSGmjZmY2a4E1DDXCbGOiVCKHSEMLKUwhxBYwusFoFgj1A9uI7cKbb2nx3Ez2w5uHyI5N1pJXis/BFQS174K8iZgkr0mh6rlJFX5NfYU/5+hUv6Nhno880NrbZlPUuDanvhiWH2tlSMHIt7r/M2fv736AOrCux/rEh+sOEAYPPoYO1SCWMJGzNChd+ne6cPUS9XY7z5W0O0wyJzDfjqr6QAdka1RBA6rU/v8247bJtqyti+O3Lwdg2r6t3yOkMP1FW9N5DKbdgj3uNB3PH6E5+fWoyW/qmXGdJHvTpwx0ZnGre77f7boDaixybA10arEbpX0wLfivBZ4nSXDLzanzVb/8WB5gpcNfd0+MdKT8xBWQCY4Sx/gfsmgf5sbmE7nbjqAd7ovfQAwNSOHjN7lL+0GbED/fLgW2cMihj6aCeY2XY6i8Q/yn0SP052PcMzho9iNZ7ssF7ksrRPxQbn90EaImdmNDWz8uHtjxehP2kv0rbz3ukGlKwoQuQy+aLPWxJMZ/13zPfCTnK2mLY5i2LtX44lcybofmfVZQH9yHYBELxPcp3gW9/iIGrI9IpFug4776mO898yf3xtD+loF/pG/6jMRMj73P4EkWHbsiUeZDMedHNsInFrM1IQWvMG0Relm3zl1qX1SSonjD7Qyj8VJ8o3F1tY6Kg9miGVruA3vvm04guvLhL+gU4XW+BtSrxvPjCN+0k+KpovV6S+ss1R7ou6s5+8Uw5Udn2v9+1JSUDWw8PXMEicDWy/FVo9hmE0Z7Gu9V9T8nlsNCQfzdqklKbQ5D3ZmbOPcZpwG7GS+9RcpesI31/B9If0r+IQHbVIIHL+XBs36eNZ08TDml6gol2NTBI3zTc8H6rR7iwDjoezD/fopZxurwOcdTu9QF1YFilLs/3ZAa583Q9qX6OkKVs3VZlznOfkS8Md+cOnqy/mJ26rhUe2jTSy+BzvGoG80w4hj5izWlXAbM7knlviRcfYyf6M/eOPFCEPl7KOnc4NWBC0NyjvO5Y1M7nX7amKrD7p7nxWVcDay5azd6gXBF0twaAYYlhmLxw5lF4nH7iGKO6VkwnTXPQiLwfeuAbhEThF3y/sj9i56pUKEA+X6T2GlokhxA4phnohI7A5bfhL0t0EYzM0mVMfVGPg4IHIIFr8e3RjYHXdDAsOlvvTXCmTUFRjWUTjwhoEedYPc9kCq4Yl7JP5zAY9l2h0Yk5UC14beXOlShxzOfCK7i8MYmJmrLXNIZWYYJWQQFsqLLzRiFGUa33H9ssUu8b6eW4clfW3FWrD3Xl8oEfzlaNT6s21w0m/ljnDHbfZRr6kFY4xXpMAwKY3DLNLQlaZF/WS+UM1Qh5a81ylALxcjtQBQ4vv7YGhe2ruVztSKY8BmoquJ99QJ7b3yHQmmPP7tTjSavOkM3/+52oxTJaGWn/3sU1zuhKRpx3hGwnctgnLaEwMOqjHzBRTSGlmeri0/QvvBABNm1+ju6TfAeSfPnsfpWHNB5lMvFeNLF9rwlM2Z4HNMe3OIExstdKGc5PMfDhPoD52pWwS5HNUV/ioIKBRAf97Ob2oI6UYdMVTm70mSSDDbtwsbPKEW7goio1jVofCMC8cUOBzF3e4cI2oOtL48E/m99OdtN2RntA5CKwuCG7sk50ye5LpFPENadbXyYlWe5NOXfkP+EPvJ/PMhVgmz318m6iJFqKtl8Iphdd/x1T6kwAELPvTQtUlSktZxRlvkobgZ6AV5p0Qp0mC0W7JoSuJlz3RVBdnwG6gP+3qQH5kQrJbCBQAljS4wD2V95cKt8PU9GBbjP8ML+1HQvKNtFZBuDZ/sWXW++wH595UFcJiMiM4PWz+xU2d5G9Q6lPw3YM+Ilzd+7aoUdMQsDD8++xNOl31ryWNE3N+eA1SSRSbo+oSJ6kCOVUGuvQMPDPqjMvg89CKfGJDRM8Rxur70D7TzyBVzqwEwj16YrlTGmzERAnY1DruAhnpO7QNKag0p88re9a4s1aD8dBa5u9e7f8nhhvdhsHFbttS8pR74ohSZFSGUgNUkHab70mfO1lsprmAKBYSPM/kt7AauMCBS4ZMZxSQ+nt0eQJU/LQNxqFVOTXw7wSwLnLqH21IKUyOglvE/lzXBljpgTDfP1gdn2tPxorSQQRPSHy+9SDMAivQPGPQKyH9SlValGzKAa5SE2J68ABUeeZwK+dBODw488+A0ORoPILkZT7QDbx6IG4rLkOQk1aixfLk/SCI8xhK16LT07Pa+KhXYLE2eEVWHuOq5ch4s9wWjMx6bbNX8ApfZpVvUqz0CPGKHu3HNbn3Oyw1C7HzW4EaoNHMH836u/ngQwac0uAy9PWi5rBoaZpx5PCPlYlGLBdmQmGwz3vZ6Er0fMG4aJqchVhF/mCeEDdggyj8C9/AMmguUTcLIe79ZfiD8Kj/MN0mdkcptYbb+P3zN8I+MxymTzWGfBNFRGOG14pJpXeMcBru3oLSNpgIFFwyqeDPDOJVeZSmXwdPoOWSR12Nj9HhCsvPLWm+u1luxPISj+Mqzdx5B9MZY1kkdmpAP8hRRiN2h9Lx1RZB0FdR1jTXCjnXMCbtuZ2wVobeAiCiTwZTSgDSJMaRr+R+aSyu5WBFFjbkSLgh2jb1/v2ieQVdTc80OAfNv7KVsIOXcAOriHirynDd7avb9mziwR4xj66KNEGmDHiJzu/r+0PAVgdyzfG5NSep5UG6IFQK7QosNWqRPM+A+7G455bThFUE+Bo4h0PdVg7FzFFSNEn0kJTUgnTJf3bQuLV9snJ6Sd7cfai8fvJQLTG15HjQ5HKHNGQOBQu+qM6bZeu7DqmWhdOpSTXpPFnM5LJ4XNuy3HPYHMIV6zBOBwj6v8UqffTRXDH/+mxUpQAiHiUWoW5JaOr2fB8bHf9gKuVn4QCXOFIk5YoGizdUAoNmBIR+00wd8unKxz+7OFhjkHisOMYWgvvT7n3gxv+2g0TvskfsgL1khX6h8rb6srmtpeprNVE79m4y9VMWtubBesVaKfVKuPgWeH3KD0YGebLPje1osRvgNceyWhx8m63ZgC9BVRXJKOgm5F8MTpAuaZV8GzJt+NX11oxnHkbLzRvftHr4RE7LYU2QOiV02KHv4MqxZg9Y0p9Ch9SukjvN6mCx1IpwJ0CJzhhDh+r/fuhcOQ8K9UA7/Mp/a5d8rwYidGIiAKd/CnFeUwv/knaff97Ffv835+tRxsgYjwsltFb3KdeHyD8Gn6AOC2xYBZcNvQa/Cc/GzOoOmL81/1YPR5OHFVIIrVuCLe3l96GLfekL+NL76nDFhh1uesG2tGUGQ5Fk0IyQtYHLoEQ26pGUZ7smAO29I0p01KlPCxCy0jMWMSEENzIXA+GLeMwOuRm9gzpILja6/mprZqLHjkSxoLoWdQDGflihB3fFcHdpXzuIkWpmRBjc3SKn9cuT3OvWG8WIVwdozdpa81VpO366IBqzy54r9B7RuOHpZbfa/hQr/lBD5727Cgdwmawf1UguY/MffEVqP7FGBwMSK5vkJwH3GrnhAK2EGxRSV1ydL+5FG+22aPms4JsWXpdrHWqDjhYPXoPDqoFKDXxjyl6XFqeA8Wgd2JIjbHKTfLgNFJviG3MwMHKMor3MPnFxEAG3XGztiQTi0gLfPFBYRe1ZfoJB2Nxrwf6TCvk6K55hJcFJSRMXvouXdfJ/E+dBazcs/8GUvvKdvYGR2vQN/ZPYAstPRcQbHsJJejOEYFM8wJXakgyn40cvGUpluIcgwR1cve0fOkxzC0DkDbKDJxGhZ4jA6VCKo0cmocYXRC8Bggu7djFYWeCGeiz3gxaohYdGNrC4IZTQpsbggU1OWrhlhIC+SOUvd6BU5i9f/u/gDaZ0Na1eLjzVQWVootXgPasZ2abIDi34kxw7P06wrRdElKk1Wkc3eqw04pbeMD9BZkLdUDnrsnB3+78DKaCszHq5cbCJ80A7Ghfq1lwf25EYhXFrE2qlB/LjKz+7IIl/wr25IXUpEj9rUcESL3IzO2rjp+evAEHOSg8kTKiU7ukOMUMSMfNmUYpuMIMJh0oHIC9DsSSk5uwDyD5iJIRKhBYvzuzaYxt0RYMbLZpBYzaQwBzQDKdjAwEyEKquKvzU8Aas1GmxxlD0dvL9ApRtEAPTrvr9w/9JDgYMq5UgBzJSqsmAUuFTqwWCVhKYjAawqI1E9kNRrkmAbuLD+FZLrHVjOt705SEFsqBXDfeFFquKvKLYeoqkHX/aDDs3etnapK5Veh2BS0SFlycQQ1D1PEXV9xMPOjKIt9hsRi6bnVpeU3EEtM9qYaycRce1gZLQhypj+DxV+4QYkYQGB4TmEswqvkD5Obul3765vBX+S6aFwFOAkUQTTI+7iDvoYYcv7rCQOb8tSe+ckdT1vrA1SZbFncFX4wGrgh/R8/6vM/wbw2cuYEOhnsEqJCga5spLq5jgZm5PPlXsQrV5H+zndcZqcUSUXR4YW5N+ox9wD+0XH5MtcwieuzpLEiBhOxbd6LhHUPzFuZUYu+XRNIE9beni8z0gFHvt+5t1UMIw5fN7R3KJ6eBDy9l8GoecNA0H+864bFtGFL/6rM6DdNAVw2M9aHs8uJxmzLz58CQB4jMG9F5WW/nbimkHir+whOS+uM5t9tnXn4HxzaPtE5ONKLA21zwgY/dUlh2lC9p+QOp78/UUSuOTPfKOxZXqKH+Wrtz0hAIeB2Hec52umKsCpEVH6dlJN7HC9O1CaftGs+bCvAdK2fWtRvVZahdN2bsGcUhShsVuqxykdU76kOEsfa9X6noG6cvdopX67bRyO2EvdfnGoR/+ewbNS9vEV6ZGQPZChClxbcpXj6l30GSn32RE2Tvn1tnqksVsUjfo+q22fsMtZmNN0vqLqfmeufm+aEOb4M1VT/IndPp7eBz+2kTSZRe4IucvRESayi8VqkvGu0vsZiMjJPcoI6dfuip6kizh+kgLLG5ZtEIbGCNTha45I1f6qREMY5ccIldu41ZuOxXTBV5My32UzKDDaknDfjUvE4C7iEH2RLbfbaZK937G5ISrukYr4wD8UDWmQJelYFeA8m+ky/lQTl+0LLz+lyyr+OExm6b9msvQ2TNSdaFTcYHbONrjNVARWJch3X3VGe8HHLWqn0NHcStBddvx5vmPiW5zovOuijPQNyMCWCsRdXQVS5G0x0cQ4WxAEtl/nove+OX4FDm98ImHyfjFeDVpvVO0ZOp+SyheqphODCGt6VY/iPS6nqIBPfRNJUB32AgzULMExi5ZbzCJ5UwZORG/JckgEl+F2Rj2d1lxJanNayINgqyz3qaRbl1F10pFl1C+EfoXg6Xfk85C4EdmKehRkoE9Emnfi8Ci/z2yDPSUSR66Ixt5MnTtpQxwcRy+0F6MVUhabEVYWuymBf/dYknIRPNPIuiCNKoYb4QGPg+CNMB5I0MclAG+NjqweIwGhGSkBkSklwHQqgEguODzp+yUCaXBtBdCo2Vs+SuQCBp/lxlym1ZJw/dqfvJ+OJAHg+i5I+Zd9tYzJCdNAOJjsjUwZIqHHPJPEIF48kJZbs/zCuX+9mZlUMxmRVBiK8b9pirW/SdXRRCkmw9cry/4LMl/vnNTvxhfPG6d8j/Obgavja2grsUK83mf68MlCvezG/9I8SRr7/disZ/eYcogandXgGU+5XLCXr3geUOe8/FlMydZlPYpm2BV28YQWLpe3oDhOiqhf3bYH1TbHu4JkTPGXgfqY2EYqbzNtOF0HA4kyemSRAZ2aMjzhla/zHP6zjSmW/8jGc7XwlW+0YsuhtXxZu55sOlLTuVPl2seo2WWckmcTOJhAD70hAE+3CkA1GFeZaa/uWmop991Iationt0RTWCuIpHQCY916LEmqHKewcqY9XFEXutCDy3q7u63ZH104gTn/KnpX9GuOJcR5XZBTQrBxSS2W1q5ossfT/1PesrvoE6KHyf1tEJ2IaRvZQ0q26LwLlmx3DfIMhy7v152yUOY6ZhBYevjU4MbeB2KaJZEOSp8fKry+h5eWmDkrMByhHokg41ZeAeTpPFW7We8p/RzjdMTkiFNf+HHjV7bEy0xmPP/vrfDE+kwL9UR/HWJU8qS0eOSDjw5xuqdFUHX+w2bGHErFL1TXN5JNlGLN4lygenrv4S2LEgCPSpxa4WkmlCCuyW9gfSk0EfQxskZrW+3iZ8rFrZ7DmB5E7Ni3cfBKhA5UUVyJM4T3Q5unqwJGUwq1Qyg84RZTWnIN1P1ZHW8zRspcgWPDIW12lhT5Onz8HYvdbFr+g3WDH3utMn3ZWCbvT+LoilCdypyDNO89jLdodXn45Mv+0K+Z1jui7f/yYHhj4mFplb0ObXZgx11CtTlv1Z7gg754tjpTYPF77xPPG8Bfeorf1jmgq5FqWJzo9aN2awJ1r4n5w5MJe8JQ1HHrRL6r+8mFN8T7HTutDqHmRWyAtKlsqcn10BifuCqG6lpKQJfIEfy93p+Y/0VKWO9orlcqHpZhBNlXMt4YvUPiV8bonkvyEPAFBIwck5UTYuN8DbJX2Ct+UCXA8a3uWIB9vaby2FJ3cR9s6e03ySai9JWAEnbz5sQnk/+3aNBxU+ZYGOtxPiUsHcs9NGo7oup7uwxzIPZ7nnQN2Rdv2iqJAYT/hHMKfeGI2O0jBkVJarRU4+F5bFUI92o98l8X9jATG7poBd
*/