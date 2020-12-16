//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_2.hpp
2mBzcTHcT7Ljfc5i0o11uL/ztlseLKkPdZKPkL/t76F+0jbdKM+2YR8US7HPinJ9zstJN+4Hsvj7/PtpRr3OeSet4etq329Rm2QBT/3X2mB1cTGsG94n8vx6rTW/Pszpptll82KaX9smj/asT6gYe89rV5/zjw4pj/uDPFZ87/jDSArOGfLwvvVeNI562iSPfK3UhnEUS7H6yucf2uc8gfrKepDF7v6uh8rWbnG6aO36NTVutE0W023oKViI6ywJZLGK+skDQBZTf/zk7yR1K5wTkF9BB+lFR7tkATv5bdjgoWJs2+tBfc4rSB4PBHlMHvgGzSQPd86soDlW7Q23Ux7tEYfVT7J39+ox9EHWGNrvbKbdjZseQLrR2S5ZFAqtP33WpfC+8A97ncfQmLEBZFF92B2fka0dcLw7aE+jl/SiLbKoTBzJ1eE6WIuFwcXY48b3e52vk248GOTx/P7xI5I66Jyi86QTS+S+8A/asi8MFcXnONohDyzGbYve1uvsJP3YCPI497FXHZTUbc5QFwEXU19Z3C79mMm3+qyRSrHXbBDE9qGkGw8BWdz5/WPUQ4ac9cr2UmNo22TR+s1QoxTeJ/9OrxMlWWzC+TU4fj/Z2u3OPYtpz0udrS1plywK+Xqr51cuxu4nt/Y6S6mfPBTkEbqt57mSusM5TePGcbUf2jZ5TEBky3YMHLocPlP6aq+2v66z7K9HOHdcTfrRJf3bhl/XGv82o57753P4V0uVwyyD1ydfYFvjYZatMeycX2Pvk69d2nK9oDq2QQyu/nHucyyHzZYcHuncsZzsjE6pD/tOtkMfqsWntlgMVALb4B/tdfaTDLaADP70y1d9FGl4c//u+8vfznTTGNEWXajMjbfYBOdCbH34/DtZH7Za+vBo58x2ssb7qF90tUMWs/mZlg6VXIQlh3ewHB5uyWGn8+Gl5AfrgX1P7BeVb7d67xMqCTv3xZaelqgybD/Y1/c69yc59KNt9ZbMd2RLH+N0Dsnf9oE+IGb+Zy3fA4Y6TlRb6gTLJfCc+bpep0wyGAAZjE6+5uGylddrH50TnbR/05Y+AfG0q601L7kQlx/G8V5nI8liEM8EXvPNsKTucvZlyZdN7esta4ssplutD1iCZTu8uNf5CclgG54DLJqivU2vMw9jgnr/Gd2Boy26I2DWEP8HgftaPEpyIZZ9/cJe58MkiyG8J7P+F3RfwOfcROuNqU4pi/e3w56E/9UqB1vqo8SFuOaMY73aJ2c7yOLjv80PS6rfOdNBsiC9ONsOWwr+V6211jOcC3H5oTyr19lDstgBsuj8xLdfKKkBZ5p6y4aVUhZ3vKY9smi9JcGFWHu8T+91ukgWjwBZvOcJFdq7Cjon7kXAZVIWU22SxUQ79AILcfeRGe4jwyCLnVvTj5fUkHNmF/URmj9OtmP+gP/lDlVa6mrAhbjODNf2OvehM7JHgizCTz/4KUkNO7f8iE7aQ9K2Otn683Wq5mSL1x2qEFsWvVf3Oo8jvXgUyOJfr9y7T1IjzjuvIb1YTnbF8nbpxbY2iGKbfQYCjzyc90g5PBrkcL/33nCLbGnU8XbRXaulcqw49+r2jBW5+nzrxwosxK0TS3ms2AmyuOGPn/6npMacYVqXH1M+ru3SiXq1pSfqXIhLFp08hzwGZLHykyePSWrcCfbRvh3pxXy79KIdcwgW4vZ9/ncPtlPI4nqQRfCaO38iqQmni3a7Ty2Xe1ZOu2TR8m0rLsSyLe7pcc6RLHaBLK65pUDe30kR31DETSeb89ir2iWLwfk2yAILse8u/63HeRrNp16QxcdWzFHEhpSzbxnpxWIpi952yQKq2HpZYCEu/5s7uI/4QBY=
*/