//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_9_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_9_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[4] * x2 + a[2];
      t[1] = a[3] * x2 + a[1];
      t[2] = b[4] * x2 + b[2];
      t[3] = b[3] * x2 + b[1];
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[4]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[5] * x2 + a[3];
      t[1] = a[4] * x2 + a[2];
      t[2] = b[5] * x2 + b[3];
      t[3] = b[4] * x2 + b[2];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[6] * x2 + a[4];
      t[1] = a[5] * x2 + a[3];
      t[2] = b[6] * x2 + b[4];
      t[3] = b[5] * x2 + b[3];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[6]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[7] * x2 + a[5];
      t[1] = a[6] * x2 + a[4];
      t[2] = b[7] * x2 + b[5];
      t[3] = b[6] * x2 + b[4];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[8] * x2 + a[6];
      t[1] = a[7] * x2 + a[5];
      t[2] = b[8] * x2 + b[6];
      t[3] = b[7] * x2 + b[5];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[2] += static_cast<V>(b[8]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_9.hpp
oPFEz0NMd8igripirwEDo4+/IIenoKXtxkzDyqU9fEuL+ZdR9QgSQZVu7h6lKFHsdAjZqHKSTcqXruY6+9J6qHND6gDTKz29XS44HqplR7mo5PyhagiSkJHTL9FKaLt9PRSA4bkktzjUmPz796g76V8umwPjlLgVOtkW+4gdrkoq/wycp5qbx28ubnPzltsV3C1Z8G/KZJZmZ5bNZFHatI+R9+ArIC/OUzNv3nXJ6rGw6rtQ9XnfnpdUVlOnLT9Igg59KxCD6/7tciVAd9XY5OBKFbGaoIkiA6uxcLjVAD14/c8gN24zLcRTsW/fL9EWESJ3pOVPciMVm2/4VDcjbm5TgqEB6x4NAq566BDSUUwx8X+kLV4cD3PlH8Ft3L6WPntw882+L4C/cVbA5AMr4LI50evyQhMk3fXUImyosKDnD9FSZYHTB7FLwrlWuEpsSe95ofaiVcRK0WFvYcT7kut0QhdJUCplHcHAo0XpsnDfplAZdB0fvjD81Zdhipx5weaf7mRs/tJ4ADfhFVzkcXi1IlGAgxCvYvmcmCh3ANIH0LjDgDifCmN1Y/OM+1FIVkvkp5w5f173SZblUMBE6FSSIYb4nXZCcbUMO57D7h5vBPYxPysfr+pbA4nSZc9WfUeeaDhkXXz7pscorqAgp2+X1lffZqdm+fennDX5Y0bPTWEA/U5EXpAVlRTeZslr53O7W3Og8w4XoSnIiTVYrinW4BC94lyEUY6ENaSNjFfD/qYEp2ULXex0OCwBFObeFoDYALsTp3l1Htp7TVlTZFT23jFhSjwWREF50EHxDeyx4hMY/IQBpN6BQQtADz/Jqy5Q0VEtrjLnv7SG0Rk8JwaUHfwJ6Ahnr7GtYzvnpfcF/YDXyCGMaOQSnuJm7Aq9SXHLDHtv6Pp+PKyrNQ+W2dFPPYgCiim4CTmgJCP9nEkvkHPRuCuXhpTj52UiKlGz2K6irrGAz7+xSgrh0KdKaJTpU5UbEF7b1B8Ur+/G4AcpaG3utVL39JAgnMOV3oJKBxs9gLEw/hgBAMwaGQC77t0uqpqGJDCexJoXPKjYQ65wTB8IUCD4ARB+IGl2ESAi8fWIx5G27FRIFHqpyiBgNdDgsj7wOAgfUmzg3l5Y9EX8RPEtAceGhbuZGrBdz4/FikXKvHvDVRmKWkN0AmKFlPbwZJhw9F3opvj+EVhPPuwIUwp5DnZNMfD7VeKlJnwe+XJ34vVMRfqXLdNzXI5iQV1K6DR6UmLVcO2LYtvqdf3caIT544zpt/kwIUV036CilrL+JSsbFHJsnZtYrKBoDi4j2M5kWsXKFKHQPG5sKyqGsK7E0Z0gQrsFxPCO2jdhYi3nyeMlj1HIMhZCR6XOiVa8FRHKxh+M6dmUytdLA23ldzyJBC+79nrFDMAlQPyO2mKBV6aJbi/AMqMGuIl6HfHAoaxQ2luUzdFBptx0sF9GvZ2Eu8jhTAHwISH5HxR3izIRj/oH94oEftJkYJFJgfqXZ2vPIm5ujmxC3yOYh5vFWXoeHhqTwh6bFGH4Mjo5WiqmemLFGOE3cFSYp4HZB31aC8W8urEoiAzwh+Zv//cqhAOMPsvdED97mskWDl3KKOV3j4nZPSQ5rvk9so98Kn5IaoIhn2+wm2n85xWDuNiOq7jPMq540y+7Yu3QYDCxw8ey859Zg9KeykBFin05RoVjTFiBquOTKqoqpMu7kTuz4ncuymR1QvXYJgF81XkeRp67vEuK3LE0Pc4mVWhkxqPtJivWFVpui3ZrP8WWJnSeIVtGIbQCh+5r8plyCBqYelwP/uCe/mwcc0sdDuaJFQwnOABBKNzcF0DRnqK/z4pVCl2/d4rS2dk39b5k9Kteogw3+2echhN8Rox1nls4FtzxEm1yNMuiV0wBC6dYewBVhH6NVfO755MNCLKVZz9R07J7LG0zitHQ1FDapgiRj98wi6bylDsfs5FOXYITXvICxwm5v5K+39tRFZkKevAGTUuP3gjJrOqvUfCuCi2bl9oiAzT5ghLyKm5ofRQ7dwi+qK1TWWYCqoyan6R6tPdNcipMBnUkSGR8ZRavdslwaSONDNZjbCZKGAXgtlvz1ra9tbW1bdu2bdu2bdu2bdv9bid5fk1mkskk5z1ZDvei7xtTK2E/HTl9OtWk4d01AlVSWHXYZ5MmiW4fPSj6HPTNin2IvZFvkmes73//VXyrk9wXdfYs4kAT9MPfe7M+Gf/w6o6U/523A4B3ZMulXlvtyRyGKl5p5myNVLEkZy+UbJ2XKypNJXHGv33XTWqchTW+uO0b5fELQTDI7Uswfima7vcjGK3phG8wRA4vpfHFjKUICMBupVxQ8EtyyU+dhUwbmhtyr9srmdnIbzwa89SX4G7KLL+g+cgQWh9o3DqRJwSA4pVaVqxIuE6yOQ/DFrd5BRzHXBpPyDmqLEdwh0KXHMUMhk7lWmiyd4N+FPw59ZXAy5SYlZWmODm0/fvO3MYANqmgTLMHPHlOcyOfUp79gWjO8IQV3YbIfCBb2+ZNTL5prh0lsZZ67N2ccnpm2JVK7nLlLklVOuGVaJUiY09gsr7F+NNh7iapAEau11J4SG4fNnMbdgR6HBFhY4KLWiXPbchEZAVnA+/zdS//9sAueI1EWmS1xbkGc1RustiUtr9zP9KSvjJnlTG8ycMHFaAsG9RZR/dq8sXPOuyjY4mNqWKMGmEa9TocNRRKeoHg3F3gn/11GuDml3B4eyPIAfVEwCI4ZODYozgYCo7mKgHFaMBn++2Gj/Y1RsDKXtbn8dCfWyqiQ8rtLBl6z5AOr/jn9FEFCsWsKCEAXBgrA1oQt5z1n7vpfQYwGrfItIzvkpngtKuPR1Iy5SzMdzni5ZroHzH4LYeRsAF0wM6Fgc9ooWekeDwvqzl9ioyj70K/68WUq4N7ZyY831Ai9kb2kZAIupmFewE1tVLGmhXwNESZKvxzAbCaPFICmKtdMXgK8qsf3lU9OfjXf1McXyZlpfFa6TN9Bco+rcljGAxKtxMvC6weoulp9n/UkioM1AzGhV8PBKvZZZRi8GG3xdWmjNY34mSdX/P1xwGvSWxiepX8MDuxz+f1REdiayr9ZQi/z7TYGzFD2SA5AmYtLOa7MDvHWXNlKdDC2w1dgmHl6UrN+GEIElNyg7byURooVUM7S5Jqpeyvr/hSsNdIR5Gt/47MZokL7dNmkHRV89cP2MW7StGo8JgA8l/yDrPdmk4I7P+kkH7ZbhPtIabU4wW65PqthB4eqZpW8ut7rFqnAbGv2z02GiZhCKyPbS1AX1h7MnoQeSiUultr/Cdv1E5T6ZSvGVD0XTGyHdny1QaBWL26HyrZZI/O1KsWVWcXDoMT7wRPGYHzu1XjCKhQ5GB4cLFByI2pbnj8L/uE1EOxA8co201t2i9dX/2iQRVb/phhW3phaI/pIrqmwzv8l3zKbh8pQln7mvOObcEX9vbBPlK8IFGVoCY5ulsw06Lu1HLg3Vfzuw9enusAAlYD7PjDaaaKJtGGQyQPIUdrfxEOfkVXQFnNZdJIjdqwaJuKLI6Aj87OCNcrV3TWgVNc/GBR6d9OqKjHlGC6akJHRUOmGqS7ff6HJ+m0rLnvXHMbBX58FLYWMzzFe3B/yflB1Yd329H+ZyFSNcTAyDpNA+3e2H5OztK+SKBdbuRx9+ksdDNAt3eT4MRYPO+jra5d3t/8fjVFGeELG7u3mm5lpNLIOc82F3OeqeEAXaXDMxlbmXnNj5S0oTCvifdGEXbEAPPpf0q5b3adDSADuNjFn+WxbrGfdMxAM2twrppvzNysCHTAmfTTLHurzavEb/MlXrs5O8BSKcIOI39xKwYI+7DKsozcCHBRmt2nC31N1EJkROhBHMot4f/ouJvqLPdaqWDDaaRsTCFUvo+6H2rJMD4quGVnAAIs/dPd2VgrF7E8q8fc2dBbLrJ8VwtXFOYBUL0v0mUdX0fBtWVHYzumiMJu4JOsNoWFzg4t7LlwFRAaNESOW4OPUtHOu1WIy6pnBpVJFKnGatbQZSFEN6nmXo/fCpqGdK5pICoFUUDI1s7YtZfWD2aBPcgzeXS8dCmKNDl7BI0YRWtVfWZLlrMNifCEGRrC47kkppCj/rk7RI6TlAojC5qX3Rpw8hTKzyTCp3RL8p99AcgqW3cnvrs4MDkXfJ2+dL4RT8uM4G1dM9tFdsfeCtsZLrkYVOCAQMonPGOXUykIWx4DR4MrVhNUrK7LEJd1b0OkHCKqTvG4JlqVkg64DBpn882iVw8VYh0fN1ftoTu/l12cIR+hbjV9AxO29VETIdo5vG0TwAuH/w3sDBcyJQ8OD+spzuprpsHl2ZTJby91mHuYHjzkFFKJNEotsUOamuxkqffpHvHSI7jZumMFDiODlLoXajD8t1nPQIqi24x9XNFnMkt70QzS1hbqQNpaXEStkDhG7jz+UCau2kOODXtj8q3+3zgC8TNry9EylM7WO7Hr1OR/09A8VJRPkz6fn9r/wV+ZKD85uKOTrPVH3B3A9s+lWbGLSopTTCpMGEle4ZmDRAePX/QdUyAq4W0WqTeR/kWwRJqI/s9haaJ/KR6SLHnkQ3vGCivJhMpYLcK8TDJdcoWZ0P5hAIx/iWW6eLT+XX7nALNV4LVI06qCRI2e+lyclvW2nLh+Nu3CtdrlRIqCeiXNbGjZzGsnnZ/o5t8Inmsql1L3FZs5072JW4wEhX1E0daMA3KNU9dUVruUAD6ev+U2uWbfUiDNMEEQ0Phwd3rQoZOjGBc0RCaYOKM+fr5K63IVYvMMVkxhr7bmsluptY2kDjIqea6qYjUH5u6UJnuK1hEVhejzVNcM82n4W6AWqm6tcmJrQ4V95vwUZQy3FygNbHzWJuEElCtIcVb8oDvTlukJQ+pDKwdmRJxjhOSGN43ZNCado4t9LxKmtld5uZtLcjLSQMkZRbQcjWioknP1ffSDoK8sePf86H/TB80+PnE881YQfkB+gpLAQH4AX7w4zNFjdo/emZ2i445k9KeoApX9jdp26ScaUeUZp1YaTh/t3kNUM4j2jcfuTonciv8EfjA4pZs7k2b9y6dL1hnIsu+mVuvBQ+yep2K3RlvMZeP/OD8xK6mahrOnqMfHBH7CYuYg4GVa/CHnK5fkvlstgi16ctDOa6moa7O+JcEptln7gw+DQOef3GZleOTkJDcyO1x+Y7jJ7RFLStVq7C1OKiNRrYCy9WTlwC2XDP4kt20Klp2+pDMF68BJqWOeAZE0NXjqu739yC3csqyVR/FUNVX1RnlIkrv/PD2bOeW5oi1uRAGNGTTB8mf40sdHdtaKOJbRX8MzQUp49lEgY6Un0RP7XGqoUCArvqdTQXwve5L8YaYV2FYkLoGs/N16a52WeFMBpfa8PIAnfvx0GkRPYfJkx4sP1cKhLB1Jq6CX0gMZ1l13zBoYMxcq3WUUsoA6iG48U80mLacY8BdDWkRc4IXJEifXszTjn9yn1dlFmPKYbuoRIZkqFcOU+5GRWB8zN9HvnLUOG5TsFE5Ynuq6dyCAMsMsNz5h9/lQBqNzijJOD4Dlg6gFtrY8mCcpnvfbZM2UBVlR6z4RsFiGDzazhwSnl98o0NiPVZ1mkh8jr7fCPachfAsLgKkpJRfGID9sHsN3ySbyaUhKwF0WTBIM8rKCpw+uFjOzqpClmuzqm7fBtOLqn+7rVpS+f05Ker8Ud6JGx9Fav3FU5vQ5JibK0dfVeuVxz44gHeZmWPyXGdmaKnnTKoMJm1tkjROasjD8fokoSmV2xKKvV2tDcpwVyU+a/nKdhZLc9eWf6bUKxfKM0YZRolyVvylCr5nQGFl70GLNhAv/Iw4K3SJcs4TiGTyhcBDTijPrn/zUxalczyOddH1dB2+hZfqPndZj0hPWBBxFzOMq4OGaTjc8ihSa+0JR3j01x9hXUkrlLJJbVUeEnuYsR6VQY/NMnjAfWPggXM+XOFlaVssYxG9SrFJXlxUN23jMYsvMzkVdYPIyE9VJe1+44FratnRMIPrzMkP/Ul2NkqM6PbQAEYLOPcIhcnuqauBSh4V6O+dJq9VrBVfErzX7MGqA93IyPkdUi7ejktH0Br4gjuBGXsa7ldkCtXlrg2gwzMlABmpX6dUbU+ySzueAdRUG+qitN8OkqMU70Slyxwybt7pE7r5cVdEkQxLkHR2NdKGpAalKZlP1gc3xyL89lCI0yrVim11F5p2Iryes/TQ97ZVIUbB3nPnIU/lE3NGvSMBmWHpscYH4Enq+V9g8e0/kUPDkvJKxait2SpLH7Q/4I97mDJ24VOEFHzJS1bLQ2NsuDXP9rWEneQaj9MVTcJLRw+rMiPEsJkgaFdyTArd4OVS1rDuFgrXXd9n7z61UvdOB+7n5DRxoneUWOif3ZojuV3V72sK1ECHQXSt+BlS913OX2clru6z+k7zGP8/7kYhwxEGciZnSRTGkvPA0oEvSxgD4/BH2zSr8YUa6S2jziMLNkkaQEtPGAoli4SSCnJFQg4LIYa0RvRFpWJfUqqSjbRJKxU5rk3p2e8plLC0w6BdR+E+iA5lvZDRl18HXxYrTWquDSjWeWeX7FTmqnZWdPQqpIXbF+E7eM3RqxSoo29hjkg/M6u/lHZQiEdKifzL/7ucz9oEBgqP/DnpD8qiHlcaupEflJrnRWkRcp/RbLaEcalAx+0dfkVbi7vSOQMzPMCLgWhjSg/g8Rjm15zoqJJTcSFjzHBkjmDulriyYHDEHPh+eCxvEUotYOXtCLICXV4o2VOOkpV9RKnE44C0FNNW1TuE9OHn7m04Y/LnkJBMjKmb/CiSA5C2eNAX0sgXcwVIGDE+OzFfcM21HkNYsXXDnPjR+S41IOOQIsaePWssm9vay1jcygMqGJ0v8E3lR3ztZuoZ7aYIW13eakTq4f3v1s1t7BbOVTS06T2d19sl5AV6ADbFRUC90Jc9DXWwcF9i6Gp9z5Z4621RITBZ4dGJ7EmqzRnOnebtF4qnYNquBdDNinqDGt4H2gfBeJPZu15utPXLtK8L/55QQ7miZpN2e37fG3HrMZBCZpk5nH9v6m/EIoeqqD3pVCyuvRXkBeVEf6Q6JBjw3vlu4xg1HbSuGG8L/7pYwNBjleYRfibH0+nymX9JmQ6KHpEtD9Jx5IZKKOPkyk0xf4OLz8pkQ8fcHDFMLLHSL0f4ajxehe+42aUpUH8gQX4noVr2Jwh6nMnN2sv1z3CB2mFulz/wrmdSwmpjsofpReH6sjmIV2W7t6c5xNjwxyZUd9n42nay+QS+kWFY+YtEev9IIUzzHRWZUhBcA/hE8j07xw/JgCP1q4WdF2T//tErNWpfM4T1jXoEUOVDCLtb5sgEh8LXA1ZHiek4q7W+2LWh/m6LS9CmcKDWMfvRzwcIMGrbRPM/ZFIKrWqIM6kVucBdl8gfygN6XQeY+YuID3lW7yIBop5QR/uWZsy8QNqRUNzNW44Uf9dXoU/CqmYTZcaVf4rzym0b2+ej2qdDmyhuqzHk4EBoWhihQrZi3PjUDqov8IK1CNlPFrJdBOj/O3hZPp307iEHkDhKjdUE7AtHIdP3kLT5w88H2aPkPcQ5/MYvVjC1GIWaS9d3tKwmAqssIs8chvN08xPEVPoA8fSQdQW4vGxo200az3EzxjuzqO6D9A+DFPZjkvWFgnbwYagqbM71Q+nBhJudIFmD7HxXWrRH4eMnliFZqngZYrdjtO6h7y60Bx0vix72YfYR5Ly8XE+q80KAnv5kn1WaH4JZxNSyB0KiQsnTyITSdrkOKlYUDBua/e7BoMeFWzvpSWkiXsFXCGt3nzpYVUKFm1yIBxnx6WejmbXeCFxUa5/oFc666KNwTo7fAm3jO86onXhMHfT5+0lZVU2P28oJ57Ib9xpoB88b+WsnJD4AMEkJiNrVvd3Ml9prpZbWItQfa1eRblk9Fy09/ueBty7rPXkOU1KMPX4+I5JZUkHBUpfHR6L51/MaYDkTneLhkqOdQFuxDphSy9uWB0OSdVHLORPuEp8NPyuXqdDeN3MZhDlsfDcT5SVT/G93GoOW9mhdsx2Ey5zB4sIOQs5hG2wW862oplE4V8qJj59sN50nXZQIxOzHkaTr7ilI2qDpLBHcR6Ikn63haovdKa+tfSjXdBz/R9cj6uT3JA4hujMvo18AOvFl9i5eqsWUSp7YvWLOfFRoco/lVozE3hoouQb/PfBt+cBPeGkyTZ8WQIWqnq8AdM5y+BosOkNVtGcjScSzzsiisYYNl8/ngknp7hIXQgL/G0G2QNanwqcfqkpwcE52etQYjaYauWYrUiRnmcgqzXO8vVDjhelTphmKEcBr38WyZOJE6jqr5lTvitPX+s0CFDraCEX94pX2xMK+danNkCyVlobzZV6j/Cx+kiK1ZjNidti7WZzJAVhRGklsMyWx74hvnr0Qz/xTH1ZqdmDFom7EZt9ZygRFLP+mCUEdd6NO2n7h51iR2gupztYcqGf6KTbcrck1m6gTPouRxt/LyDocA9DQqTN4d4thNb3qLC3Fc1557pla9XnljtjHZ6BVY6CDAPPNQZJVCGlt53f1wmbD8JFGtLhhjSKi1KdykCrkxrJ2SIsDWsxW6Fmh9bmuXsy+gY3YwO1MdVE5IOzPjStr0hUeKkT+cYzRYnOrC1bqOEtCgamdl08Mh4m187gsHl54cnWNWfLm2Y/53Y3iLToyi6YQZyfm3eck6+FOyNAHeuvOVcxG/IPP8w7zZZuGTpEDnX6SFCNQPWS5NqgdRVXtQ0Wg9IEMD9mWr7VW6I7eTZV/xakC6OV2qwLMU0TW39nzIzITgraGV8Afxslbmq5NYNtC+SlHBcbL95Sn9o9bhnKF81tMVER9I9PIG2bF+z1Q3roFhnhjlNaaAvSV87Kzjr5tWNjs2yOvyK2234XriOe+ZUfiTJW6cfRkblqZewHUoK64iyaye6rSwItLNeQWZMxfUZqfhtLveiN0iOq1khBafqylsDTTAgRnJIYjQO3I1YtUgm+HU0yQNvAev/3Zk7uHwC+qMyTXidfsPbC0nE4TGsLKJzEAFj3VH7V7oYrzl7N0WPJXTdCgq3X/TVYabo1MBUZfpZJ6RI7auWuntHTwjYsNWxL09HHkyJBwVps6dHGoa59t1ha/ZTGxvy06VKIidbvg/XMtYtOg9JY3MeLji8OeXob4=
*/