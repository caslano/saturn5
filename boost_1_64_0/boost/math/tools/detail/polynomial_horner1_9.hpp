//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_9_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_9_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_9.hpp
8OsI896fLnSkyNifO0Uef8Zb8vRbEMmv5onXmc8T5nI53uJ1x3x+IbD9rEnma3K9MU/ax793POP6abLNdX1V7ht6AtB9sIx09/ZkXtewQNhYx2tRo/nJH7L1Wg8f7l4BeY7qRuOa8grNM6uIzSWALEHcNdw5alDosv2FqRRtJOKisA/yqvv7fOn2RyTlIVWzhf908AN8nF/bvBPQD7p3bab5HqP//bMF9tjHdvPvtZ7Rg07T3s+563Vtdcu3p7zC3NQM5/OeDuOMSs2c4/9vO/19ru9hbcWlo6rt2sf6Tt/yYmzD+18rj/kvWo/dksDrEzpjjbzHrp/rZbVuCGmqwLsd71LfuWsng83Q5Hy98P5wzrkgJOWpfr3o2PBtbXaxNqt7vz+e0bqJY6q3WzcKtA7GA8a2FunoBKDHdnb3AfcmkJ7aWML4/U0BT18RE53eLKfHthX9XVdf1Pm7rh/6zDrMYmq9OPfhqCeHei/sFglv/M6EXX4CeuhpP870Ok5+44ZBx6zYByvDwsRP+LsNgN6/916D/9SJmf+UrzazE63DreAAEYaT4Ch4ePue79Vfv7bnC+NLzLqD+/U0994bZD5YYQu8A5zFQZp2gLsD7/4H5/LOYjT1vMPdk7u+oLNl8qx94Jy82e+1+Ay6XqYrrBYubF+c2Tcd7EOQZ3cPsC1sD3zvv3vg64hrl7r8nbkeDnxDPrgndPmwPn3O7kZfgGuR9rhE84XfUaN+3Nnt7xhs7066fiCmySOkdOzrEd/B5oEv6o4t8b3oPiO+zed4l8btjZm+IY9+v5TxxWyEuu76l+sGnm45E550Bmyebyi7ky+c6To46AD7Stb3ZX3ZDXnx4ecOvLG+7A94v4+0foqfKl3Ywdo2w31v0OdR5IwjNWuuem8qFABaSP7Y7nLop6eHISDGZr83fvewJ999n6XBU0MD7WjX+L59Ncr4kS40uINpp+86x/zY29G6VhP217r7QTcPY2T3/Rp/dO0xeuynxW9drenw79XTNjtaaoIdV/fjgd+48X1Qr3er45uT9aEp9Lp2rsSTYBce3vPuQ9zQOOYJppT4X2d72UMo+18F79zbcLmTK7qIcF+21/v8Qi/knK/zRZ0M7EpynS8udEJOqPNBvcxLR3nTixV23bpPwys6/lnf4n+M5f7q7PtQBEHmZif92miW7v394IqcleHrC+xeOsFmvG8ap7Nkj/XyzR1v1z3F9L0lfeuTl+rl2wrdHVfSG/P/nR1f38X07XEhy//3FHogJ7Tr9r3O92c6+x4wls0HCn2Aa076PpjpGnrJPH0fKvRBTpC+qPPDmc7gNhc6gFznRwudkHO+zR/PdfqIDNtZffx0qS9x5cpiWX++4w+9eaqLX47fxn3Q1wv9gStXHM6gNrN9/MY0q2srq9b1dxi3RjS2utqYeiX3zfFrkF9ErjjNST7D18/ocdjIfN6O5/SQzL7Hyc88bpjxpHFlL7+79OIbeZ4r9zE+z/s7SpBvfl8U9YZ7SZAf9jNJ7z//I1/UG+aN0Rf7F2U7zOamf55H77XcOc5fIU83OmU6nnjTMb1Xke7G9TywX0r2P+DkPHo0J2J9EPCBuhzv03h/oyvxjPL9AyUvbOkx30/d/D/xRbVJb8kPe7ik9xb/iW+O3pIf9iJJ7y3/E98cvQU/7D0X0t3CWxV84/4z8n6g4L04iUuE7smrhUzv628NeefNVE4PdeU2/5V3MDDWmx8DGTAmxzSI216JZ6zv/YkXjp0pT8OdXMgDx9dYVu8JfP91LuXnT8NdmttfDX9WxoNvG5SDy7XMtjffAfDlPWHMq507XpGndxdPbf9pdwq8cHzI8T6U6HD86MeO5/g=
*/