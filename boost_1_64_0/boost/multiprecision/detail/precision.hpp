///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_PRECISION_HPP
#define BOOST_MP_PRECISION_HPP

#include <boost/multiprecision/traits/is_variable_precision.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/digits.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>&, const mpl::false_&)
{
   return std::numeric_limits<boost::multiprecision::number<B, ET> >::digits10;
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>& val, const mpl::true_&)
{
   //
   // We have an arbitrary precision integer, take it's "precision" as the
   // location of the most-significant-bit less the location of the
   // least-significant-bit, ie the number of bits required to represent the
   // the value assuming we will have an exponent to shift things by:
   //
   return val.is_zero() ? 1 : digits2_2_10(msb(abs(val)) - lsb(abs(val)) + 1);
}

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& n, const mpl::true_&)
{
   return n.precision();
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& val, const mpl::false_&)
{
   return current_precision_of_last_chance_imp(val,
                                               mpl::bool_ <
                                                       std::numeric_limits<boost::multiprecision::number<B, ET> >::is_specialized &&
                                                   std::numeric_limits<boost::multiprecision::number<B, ET> >::is_integer && std::numeric_limits<boost::multiprecision::number<B, ET> >::is_exact && !std::numeric_limits<boost::multiprecision::number<B, ET> >::is_modulo > ());
}

template <class Terminal>
inline BOOST_CONSTEXPR unsigned current_precision_of(const Terminal&)
{
   return std::numeric_limits<Terminal>::digits10;
}

template <class Terminal, std::size_t N>
inline BOOST_CONSTEXPR unsigned current_precision_of(const Terminal (&)[N])
{ // For string literals:
   return 0;
}

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of(const boost::multiprecision::number<B, ET>& n)
{
   return current_precision_of_imp(n, boost::multiprecision::detail::is_variable_precision<boost::multiprecision::number<B, ET> >());
}

template <class tag, class Arg1>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, void, void, void>& expr)
{
   return current_precision_of(expr.left_ref());
}

template <class Arg1>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<terminal, Arg1, void, void, void>& expr)
{
   return current_precision_of(expr.value());
}

template <class tag, class Arg1, class Arg2>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, Arg2, void, void>& expr)
{
   return (std::max)(current_precision_of(expr.left_ref()), current_precision_of(expr.right_ref()));
}

template <class tag, class Arg1, class Arg2, class Arg3>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, Arg2, Arg3, void>& expr)
{
   return (std::max)((std::max)(current_precision_of(expr.left_ref()), current_precision_of(expr.right_ref())), current_precision_of(expr.middle_ref()));
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4130)
#endif

template <class R, bool = boost::multiprecision::detail::is_variable_precision<R>::value>
struct scoped_default_precision
{
   template <class T>
   BOOST_CONSTEXPR scoped_default_precision(const T&) {}
   template <class T, class U>
   BOOST_CONSTEXPR scoped_default_precision(const T&, const U&) {}
   template <class T, class U, class V>
   BOOST_CONSTEXPR scoped_default_precision(const T&, const U&, const V&) {}

   //
   // This function is never called: in C++17 it won't be compiled either:
   //
   unsigned precision() const
   {
      BOOST_ASSERT("This function should never be called!!" == 0);
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
      init(current_precision_of(a));
   }
   template <class T, class U>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b)
   {
      init((std::max)(current_precision_of(a), current_precision_of(b)));
   }
   template <class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b, const V& c)
   {
      init((std::max)((std::max)(current_precision_of(a), current_precision_of(b)), current_precision_of(c)));
   }
   ~scoped_default_precision()
   {
      if(m_new_prec != m_old_prec)
         R::default_precision(m_old_prec);
   }
   BOOST_MP_CXX14_CONSTEXPR unsigned precision() const
   {
      return m_new_prec;
   }

 private:
   BOOST_MP_CXX14_CONSTEXPR void init(unsigned p)
   {
      m_old_prec = R::default_precision();
      if (p && (p != m_old_prec))
      {
         R::default_precision(p);
         m_new_prec = p;
      }
      else
         m_new_prec = m_old_prec;
   }
   unsigned m_old_prec, m_new_prec;
};

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T*, const mpl::false_&) {}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj, const mpl::true_&)
{
   if (obj->precision() != T::default_precision())
   {
      obj->precision(T::default_precision());
   }
}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj)
{
   maybe_promote_precision(obj, mpl::bool_<boost::multiprecision::detail::is_variable_precision<T>::value>());
}

#ifndef BOOST_NO_CXX17_IF_CONSTEXPR
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) \
   if                                               \
   constexpr(boost::multiprecision::detail::is_variable_precision<T>::value)
#else
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) if (boost::multiprecision::detail::is_variable_precision<T>::value)
#endif

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* precision.hpp
rRkuLiunfHB8Pq7n3/wjOqvLGKUW3nfGerWrV+/kYNPTYxTCTMy+redH988ffaZeUj3sbuRgH+t1IvGSa1oo7U3zZrmTyHee2nE32ZgsUr0d27u7vb21dkYl0/nt29/v5G/LpBRlXLYxh89gj1G/U8KFdkEEQz7TLkxbVJXS5366D/tYr5eJjjQFKjM2QxtyNnx/xDJZxkIVxroCLIhl2PfLnnCCU+/qtm+LjKJqrOQhXthPBpwgaI459TB7kL6rw/klGi9S2OJZInUnP35wBDDdt/pvBpwSkqOqYJyrNQ58d+G2cyVbo7NZjjNghfvpHwNWKqwUanMH1ue4uj/pPfN94/u1E9Qrs6aFRhzo3ah6CC84bqOIGG/eVzd7vfcEKaiRydXttD+pdH31/gEnGtHO4/2YqIvPxQynIBxbKM1ct89dOK1gnE+OOCIEZ73BOHM+5xjHWW6oEZUPnFgwztcGHBeaOYfp2+321s05n2/jduOBZx1V5QOnFozz/RGn+BhtzBhnzucnCMf7ZpQg5ap/1JzPzwcclYsQwfoeZ3d7zuc3CMcxxk0ofNU/n53z+dOI402WRliMM+fzd4STaZGKl7jkkzfw+deA42liWYmeT43DNefz3PcPPrkySumXfM428Lnx/gFHquictRhnzQfy3/Z629zUpm5H908Ey2bfWru9bCBcOKVtMKTsF8mtslIMMdpQnVhLSC4z84F89fTkM3d3pvCTsHBDjCuMk7xXyUlDziFMIMY5HXCEFsEXI8jx5o9kiF3V63FONFcuiezqZrpfnzxPF26Cdau/OhJmueN/4eiz9TeH948f9HZ2P0L4nngVtWJy/QZ6/WfyAzV9q6C6SJJLq4m9tip1MZwqg/yL/4H6U9LCTYv2V7z9OMRGV9PYHDBdCcprVa4FrStWDwox1T6A4u1Lx0pYeUd/YXXoAcybH8CY3vkUXLyeaJ2FPSaMkQ/gsWiTposEyws7sPbANcTAGHCFi0Ylo6/FrbOlxwUf9A9guxVTVHbtbH4v7N/d+djxZ9amaK0S7UbpsH+kB99EVB9DhLGGWa2G+hyeffagRfNFAxDlTMTtYHj0IeRCDk9PKva8Hf6FcB1xyiRvhLseF0YbafrQjx/E7aBk5Exm1bUDX1RhczvA3Ln3QVwfKZQoJV9fHRiHZJ3Hry8jktofPLVsSWdHx/tLd2fcBt8bMAXnC5Pa60FhICKb51/35STCjTPBKE54Ba7DoIc+VNO+M2B7Lk2UyVyPDYMRvcs+9+54PuNKFJ6XTv2lGokcH3bNLcBWq9cLJCrtHAuywrfBX2dsHWFjLJRthMUJC0wr7zWpnhkVrVrUzvAg/0IY6tlycVAp2rxbs+xQwca76iFfsSSZKYlcVcf1/auDB+fQtGs/gnOEZYmjntkQ+MY7CRyTlcB3xt3hOyOyEKUkC4f5HUDGtpADbo6SM6r8tXcTHS7kAujL2JMxpdJuiR9ctsFUjVOn79kJ85cDJrdJJMUYvp/YzBX8mu/i/S8JYTyNpfdhaXaxXzo5etTspvtx3e9/zyS4LkoKKnNxcF9xPf+HE/83EJy7VtOoaF7xrxavI/+bA2azC1Yl+GtvLTpM8P0iw/7vVR1liq75r4xtLw5P/hP/q6EujBYbpeJwl/Ff8P824m80D0EU3/jfCw1x4g/ncTLaMCXmSvTk8OpT9VTVrGc+dXkIBkj31XQeR3qpvZ9wk7LtOd+7eNT8e5pZEF7Gqj7YCJIhL6kz2ddaE16910qtADLc5fdWFfnc26ZzNEFnBsFiKdRWvvuaj3Ze/yRjrifqg+Ws53p+dnI5rT4Qh4kOexQTggffUYW9Wtd6Hk0OpKMfxTY=
*/