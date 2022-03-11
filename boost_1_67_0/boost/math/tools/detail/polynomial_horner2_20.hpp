//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_20_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_20_HPP

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
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 20>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((((a[19] * x2 + a[17]) * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_20.hpp
euRrYv2hETrdhA7d/f4XL0Ce4lxd/6og9lelxUe1oVok732582/t+esQh/DKBvqSO5KQKtMOXuGQla9q37XB7dPTFusi8lsKsTjaVb58RvXC8Q1jdhb6+Ce/5fUP35uiF6PVN7W87kOvOTihtWjbxVolScQJ6T8vrnIt0hr3TMlncTgnf/6b52LhbKnkJXqnrUdSJKiWTuXGyTTLDlAI4HLJymxTz8dQ9A5djEp0pi3X8O1vLJYRblgZ0/m7cwOwNeErssv7U+SOhwKUNJB+/OKodXbfHY0DdUYWuioUHT2Qg29nU2uAuKNJ2guvnIaicKb3GfxeVSyRnpVRF6ZhdVUUBdiLmcsxjcqwr8+By8LJm/wL6TuVzbU5eTdsS0NKCDrPMLIvXx5yeJBrToexpWRpowVVcV7ueJrPyZKRQsSIcbJz0HayPOJxk/Flxj1muSVjb+6C9Wwf58Uy9v6nqiMPzODlXqhwVwxN1ZSivElZbHMT52mTaxyrP7nkFYR/HoHdHfK7y6JdPLHXXBg64pOkvKTsx/U++k3qCGNHQqIgTzWkCvu6PuNeTOO+UEe7oyjxLLgV2zXOOyXXCeKVmUYlI/xeOglq5kALLGAMzMKhiv5Of/uM5d6z7aabwO9wGWJY+6iqUq737nM6MaiALLtYkF27qQ4V8u+3a7ael3xORXeyjPv80OmQjmCx1CGaJbO1e0mtrzUmMQuZ5dY3lbMgRp7VhF2i6K/E782jU/P9Q4Y6kPdH7j20xBcumHiOm2R0HhfkBXPCqefBP5pRg5k2is4lrvgApzySe4afnXna8Z0uAh8Q1Qzd4U+VOx6EDsahm8EMOXJX720mmpOO4nUIu7+ohY9vQtdnB9qsBt8TO1+m/jFAyFKxTcSO8BxtQN64jnsbJ8PxeES1d4HhPCcfeMAnukF0zJKNrAalSx0XQ2+E0i5oIEgMKcrapwFt3Q96jQZoACQztfqJ+fQNqep75aXjhQ0UCx3ekZdJBmSUETxQVU/9c2adm+5LdOp6Pj45gzvEA9ojyx477/pBlu0jWjK9/q6lwuXFEsWqafYGhQDDZ+6grySgcPeeU4Ey27LxMJ6WqfH5pIzbkV/42hKDV/qZGfmebCBmwWm14ilgkHeAQIW1/FUdDiouh/guhl1HOkJcjmvtS+XzOPz+Bo2nz9+1I+ZrvB+U90euS3HT2D27fQ/kXYvH/jwlqk4eHA0qF8he8TPn6lLLGJrwSdeZ+7BxZOxyy8A1h0CuLJ6lnp8QIYIiczvbgNvPT1sCeWi/CiL5KvPHC9nLldDx9iwQcW5WyK/fXJsrXEeIe5IByVV48SE9SxarY+FTxeF2kDEjfYnLn/JmOzuTxUxhQsa6kt1wtTBug/9oMukJy3R6qk8vFJk5NF4l6eR5VvSzKrONBPxALXHmBPl860/sdSrr9NwL6koglbRStjD6HRE7p4dOFRp5gi5U5d7MdCy44SYXRM0nLW/+n5fZGy5Hfw0HEhza2wHnImZAEXinYjUdf/9cxfCzdTzt3B+Oujem6s9TQIn4mGAGUFoVPMuWrMYKHtliBS57mYwN+oB4PdF3qbfalgIwfABl9cTyqR2uHWjFnVAb8CqVuT84pZRSaxc858y7ztAiCtgiVRHYnwvsAnsciJLYm+JcQ4DqeRGddPmCJZN6/K7d5KxX0HnNw/WDmQd9OdcrUxBZpPJT3XREjiTJ9PFU005jESl3lqtk8kBgwD81fnwwCKxgSBjFEoPjOUkzwZW8wC8l92Gjyf392LJFbtuBR4X0U07zGFSyVGT9GXhAzVPP1+i1gn2xGPCC8Cqc3fuKixgoxpAsFUgU8nCDidG7KzNzfvErDKyLTqXFnrriWZeYnxL7zv7+LeuIp/E+BJeOXwk56rGof2KHLQfBDzqWCLY+OgaIwlYn1qsyMeEHQ4grUacbkGeJOp44HRAenJm2epOmlWnccl4lKyABPxfVzx3fyrbSjzqe4/rKsDQ4znPIh6TIzVavuFcVJj7+PEJ4rrjSYKiemMES28Op8mXLLrf41tj/ATcyo6c7U0KgsF7Lj3LIvE6mqzp1R7hdDXiW+cCbJy1kOedr4jK2jwjfM7i0fk1W3sV570xDzyGyUX87iLDmgzJ+8oX5WMr+ntJlJgqf1pEQUsvdw5hexz4Y9knvLTcj2ooyOrPvJyEsHwiw5nE8beNYy0mrXOFP61jtbk11xJdPZTIga9rR4YUL0WGo6NOZBW5m7dia+DQ2b/bv6yuaTRYTAvwnzrcT8EIrdpnJBVVxoKFOtB/o29BMKhHexelKbz/rZ3fqGajnJHLdnXKXu8XK4lpUDbuapGmLz1Wh3sr8tcdG9dMY4njUrpEddgJqErTsZ2ism4Bv3kzgc0zuznDJUYzIGBu8TnIi9NhFMbUw0HGnW09aYS/F3eem86NnupU8I3cH811zzBs9PgzB0ecIty8A8Bzz/o5po3DEmR6iPfFAH8ewRUnqLvAQbeNkucIqfqhGUwZN3hlXUC4fS/7GZfHojtkRWK1TWlDkAilNtJiGEmvWPbT9Eu8e2DO2DozBWwPlTaedrKrr4qo84iJ2Aj4qJk7MiZTwIts96XMTCQKAKnRBkJJ4wxjvT7BKGzmO+eBEVhG3FokMp63voIL3CS65aPe058AK9uL8E9s3LVSbGeOsJfWj0J2u+FBGJNtJMB40qxo+2Pxz9i24bMbJyuuMNAPWQWNqr4W3UatYsEf9V+AmN8E8bYSUfraL3ENUyjgB92YbdgRV5QiRXf3g3uIa1GXuaP15BNdH+/hniBfmn3X8N0Fid03s7ZxmHSNBU97F8UZNpZEaGjzZ7QlJNzciQSc1Ak6dbURT54Xu5MUAsJfAxxIzR7nw9ktNju+P6DO5Ph7e87P+/+/qRjLAd93RUPkV7xj9bioLF95An3RqNxeXFMR6gn4l8zQBTBFBLbQf1+qVGATMP8BVES0gc4yZhGpzix7oFyumQi90pkNERH0y8smKIc8bg+2JumULerdj7q2lY+cluxGP60yHl9LPlB7uiRCX6CJXRcxb7UdRdAA3NlSCXoT5BRigbaLQ7gHv+dGjltpracZHzR6PBy5D6qYTlWafGtvEU7XPzugF0SGt+e215clv7L2al7KTbzNjLbeiJgvb8FMKm43TF/QQoo7HWqG7MHgbKT3u4cwdRSgTUAjGj1Qsav4Qws7cHg5AzZ/yvi9lTqcSDWey5Y3yT3QGY9Mt8+RvRkt1gaHc2u36S3qwQc4XwlAl9QcOr7ieQ+WS7NHk+XL0ZDmAkowdzZc1oVtbA00fkqb0Kf+9ueaD8OQeA9aaVlI/jtsrdaUj/NELx+KpHQuV8arjOpX3Ki/ZElUtn2wfeGvD0B2iB88DMVckw4RHl4Uj4tDtigLxvZTeToo1c6LLa9Rae2cwGMJCeVTWs+liISZk/9HPMcQfY6+jeHAlnow32nuQIy0a2hT01vs/unsj8E9DDF9PJbhdZFPVMfMrOWoGLHJrH2Pb/vvXKDfuE0LFDhMkzvDvvklPaUnwkYoZo/bEUwCfJ+ghJ1n+tdSCOWnHF0xH31HAteK0mRDhgYCJxyZ0VrF3B0YRsIwqbwU4Fx4dGQPV12RQ0O24fKmryPrkZvBFS/XCscrt/ggqoUsNU9bwvDxnstXxC0djx1w0T2XHnn7kfL2oZe1W5HjnUodeojksdslcOLWRcPtE9C7q4bJBog64Uq3jZbD2nbBw/duJtM4MDY4vn2rguJl+abtJ0RhAd1BdKV0p+bL3Ls+vRPQ+7E7NpqF8aII70lW9SIeDbvbLCLAdQjaCAwdzceNGZEvv2yMxUzeyfjuRZuRMGEEsi/onwTUzFtKumej17t5wyMqn6KyE1o9PKCLpRJOduI9/nYGe/qIz2zcAEtWpbfvt+cw4Q5ykrWMrprht1T155Qf3P+MR5FMQlhgUeOfMusuVNWVsb6RFgiCmg8KTIAkujPzFC0aK6JubUQsKoGfiYTiKqZZrp8jMX2Szt5N3ldsopRZfpaKPplEBgHEBDUVWWV5C62PYJSp56PE+c3Cuxfj7Iz7Mg6MmBF3Nar1Kk/SQQYlVoGjwN4MwVr7N8Xj9z6sQUa9OCUAOOJA7w9Y0Jd2twOsgiz83zfoEbSwIJsrczJ8pBaPlDIbSLHHbF26v2Y/yP1bZ3nCwixoV9qs1b7vZuxHbtuWul5XpiL72ksyyTPUuaKJZKuM40JLnF5kBLip/7VhxrZKrYewf/aOjUW1wZCRizvs7/uZ1QLX0Rk2a1JcoTgzXwTJ9UwS2wkPFB0vGcJSS9eO6M0V0q9k75m8VH6K5QUzH4Ndx25o5UtluQ1x7V6Hjbg3sEyaSEj9ntmGHyyw3QlcFcG8Tp5EOVmJNZmvKm/jgvophOAFYK/ch3DQejFj38wIWMQV3ujPkOVpwBcjlV4N944EDGF7u9XK3hrYmWn89iKNENBHbN+DX7A2fEJARidfLa3HIlkfvvicnlh77AvQcY4h2b9hYrirgIH+LW9WExWyxL8fOfwdPg4kZ7Cix860Ji4yIka+QkUd3LqHwtYaqnH2nfn8eHbwnQ3/fc5ZYWzh5XyOniyRwkupTrHEAwpTu29Agf3uATQl8MbhniOi3UnRNwQwwaxmuu9YX3a9EE+l5BZtLe0x5JF+0jeFjGI+cQ+ocWDILSjRwNjhybtvdpHNKzlj5nCykvE+bfBTkNKcMDDs+eHLvOPgs7STfTGy3uKWuHr3/RUq65mih2+h8Orru8f3akOahP9DR21KAijOHuYnKjK+0W7ehO3nX3bvpFrg5DcCPm2hk8CtVH8wMyXyz6EJ3ypl83NJjTnJvNQw2wYomeeSlmadHO+zgf8iE5fgzdPYC0a6q7HL0/uHHYqyDZ8MH+70AYM1Wx3vD4PJWXisik79Sr2hoYauv+e91xBzb1+dkZs4pMbhry6XSR474X+9NSKxQadB3clQPzwuPBNG1lFsdyRywDARqVW0R4pwe1KXnTN3FUh7Ph4g0Bfi3xhSW0TI5zRJ1s7HN5GCbiPk8KuvNY9bVhkv+/Hj17XnDQEUw6y7gY0AY7V/qhf3unHlUveqOLBsFZl+1s+TlsK+kkk2Oj+XFjeRjrVE2uWy7F2wlPPOZs+Lh0eUbJiJxtNl+WcGiLF+4OfGfJ0hvkb0FDlzlleuky8LrZsQTA3MOPkFRk5eqBobmrM1SVMbXh0fDgC+vLtsFF7oAfhmq2E+Ov9RbY84djDXhOjnxFq+4hjYNBLnRwmOtknZ9Mh9IcsQwSKb5akoddgRgq8i7VId3eypBQrQC4Un1IweOFLSVYxBmPkcq/oBeKnCVMjOh/TFWThfW7kJVaBHf53J/X4Y+09WLKUS/d05tvuvgtmscPaauzofGUdtjJ5lKJM+/4elKMho0RfjeGceaGjoE+MfOi7XN5VqmIaqdn4e6DvlVrf6pDGbpoATMVWOYIwUxItWiXQ/Vo8iQjvnWU885xRfa22zxlMoV6hFFCpOsw97kzLUVpXDqf0J+wyemWMG2UwxRIX/+G7DGf25zKutgVP3cecrLzabEslSGYqSSmzdolW3hfszqJmUfE3SyqK3kpZS8CEWuKsF9W2KbS8et2bGKoiWzFd8b0j10K+l3QsWTg69Sex3ZfvP3lSkYqdqGO7gRSRD59lCTST1ksWWJCGcu46ICAAC5PWSGIouuSIWCzFDvY22d42SBErVfSJfhYh5rt5iNaFPiGCJMsEdq2OodigBlb4PlWrZopRyS7AyXyVLyOil8S2ONgLDaaayKmiPuWMn9gmwiqcnM1z3mFGx2dpicHJl5nza7UOPA1qcHok13zKx+hflMqZjk4ECLqllanosgULEg26Bo7oVMr4QYEPrBJ7FwigGt/jtBnSYd928zaAtdTrPlekdFwYRRYZhtqC51+vR7u3oXWtrudi96qd8ZjOW6w7UNxOezg+cl4a45VbsylWArL4x/rSRgNfpWkz5CzJwTfHQo6+it2/cBsJbPxyYIEUz9djCq2/Qj1AVAXzVgXYKr2K++0DGBanLUcXECvYIVJ7PnIXDiDy5JwKdBSGRqLWsPYyn7laCTNVHT6QON5wGHrxCPbDVO7BC0fWvikEqi+xPpWuJHaQlaLLHFSWPEdw5o7upPA8AK79os9h3Uz62tT+ZBY+7kj4hu2YHKkbR2O2LCQKDdBmdPxzliFj+slYbcNyvimNFrTEHoHHLrEk3IaVgHoLf38x5wpWxUe4aS7A71giR9+JoqdUwBhLiLj1XOOREXmszXLQ27bNT77fylRFchXf6tpb50G45JNHH9lQA8Z18677jlU7rPNgOTcRs0alEqsWxnJQFJuQlTOYmm52VWUps8M9/nX83VWCbNlHKDBaD5c63eRU0Tme7MSMz77YuGPOJWaVT+QcSdCdFZwQRr7Ru9zlxxDdhqvI80UmibVxo2YAgxTtog0sPFuSuatQpq9StxulQ2gJGmnz21YifrF+Lh+FJPUWVtUWwbyHjaWuaiXCv/uWMask3B18RvT32WPeo3qaPT3GxNL+zCJMetFExxOgdsLrImkelQjDily2J7EQ53hlX4nzqXCfiT7vLCiRuA93L6BHSEFhXT2a9ufkZRgFaAJyrcygn4ThbfzGxa9AzQXg1895bt4fZcu9DBC3RJ281HVxGv77/8tu44KVs624RnAjmV+UZLj3SR/IfLCJB+fNHbUdy1Su3L4yWqIT1MEWcfg/TjO3Bt26F9O+7SajVvyQmEM7IAgVPMllvp5LtFsbjsBE0krmowtPm4VYxP+eR8H8LQMbxARz8yPIITark6+I9LW1Oddp1s0kP2xREAWYFdoYanaB6tsLjIY6jfRHXGFGigEJsLRSzk2xFcOFSgu91girpwqwIsRCx1guSMFDOcg6qZJ1lh/V/j0Pg7PwmTN3Q8Jp4CxeJBX8SO0Sp/4E3Au9K7+SkABYxOIbmMPc2DyUQ7Zia+QiQznAjN+mq83+gI0ST+2GWCvIgVWYhYQwyP4mf+5MWaRvPgtp0Sz/Iv/SsphF99NEcoAMoHcEHgZ+fxzp1zVvAvcXol6ZSOZcSMS3zh9cQLOOgMdkHvgeQw8isLfsgmvgeYhgX82p52qE++p7yTauTrza29hysfVMNSos5mSRMkFKrLxieXI0UO50Mwyn0nzvweRkvvmrQwfCo4qDaxZ17YQwMvlAWDhmMJrJxwuWPB2ENUqaYiBilX5qIbeqSQObGF4cFkWYRrDdXsXJQyGFwO2XOj3xuFjigBkWUHs0pgzbKYmrokD3MatKL386bfKCkbUKMAXTWsZLGYpQ8uGKstM5A1ZAAle8pcgUVFq2X+Mg+hVf3idZqgNUFENjyR+7ACjvDdVsMM9r0Hm4K7vvJveNqYZFgWvD7EGW80mAv/4r7dIAe5g4QcF9AU/7lAJ+7p4D903v6WqwEGq4P33fd0QxSsXOx9uk5b02DfUnmYmjyT8ji5FN8fZNLz9jus2Yz6GusZ2Af1z6ng2xOv0LiuegTqpXD7apcBxAzCWn8NAQ9pks0IW1rnicKvIpuR4G7AI8VfkON6Utb5UGTj1u+S4ZKpqSnu9tdEb/+3Qj9iY7tuJNgeWTmPrYtF5xV9JQvPBxT2XFFEDdylduxHyNNrt/xPPM87tLlalA1D1ItLl4B7+as6B1ncW2s7PHhXIa1ygZmPjCqiuZu9LdkN5ToOv7NkQDAhIIuX/IzHX8izSOYG5s+EfM2bE9awwAddub8cYYjCOHJsGT0VvMRF5Vwefk6R05xXc0JYn/j6j2PTvRF8Ls+nCfKqHl2lk+HnXMncZZ9eS1wbQu9uafF4My+FB7bOo6AtiGMQWsKMZnx7E5ENVzALIl7YXjZxY1EQ9502tM/ty102Ou7YrVJZnz8oQhApVMy8O6I68mXg6pWpI9nJo+uVSI2+JP6HMd2nOw0ClQuoO4UNQjhONVjWmQ+BU6zxYhSBXcgDUQpdi4hjRd+MiN2gAVSMRKYASaDDIva9slIwbi639xb6UaP6TDtAo9OG9RrR0zY4d/bA9hLkX3USjzlQ4f41m7P6Mm20k/H0r6757aNsy64Z81YpQJVu7gxD+U+wEu84sYvhS+yRtb8X88cS27wnVNUyeMAhwOmIEtEjgipR2UAREWKgrI9l1wtSz9OSyjFfFndgDbziu/NQKGOzAwemSqyiyw+Xte6zZHVDRrsrsFgeGnlJ/ZUgCkGTAU0CviSsJmPusA2nFOXw9MA6iKS+Xa7Rqkdj3JWYIvJzCI2wtGSsuKYn6ib9KQ+CZTY/QwGmJRw5KkmlNFi1pupMF7DfsTV2Jzno9vdepfFwGVwz7Z+0hzMEwfJ92Q1LxZp8wPIdtD4XUS7KAjmTIeD7szvyC8bRC2/ZnkiVXXOo1n8ESprvZAad0ubQZ5Dd/khOsIycr3dxQQoeygJcKmynLlsVZN5eeTlfey8Io6Du5UYICdCxQSmgbNOwo+8EiEHhcPM/qTXyDO7qcLuvDP5eppJ3OrnF5XYEyqKwKzQrg2BmJkPvioOEZN55rqFzMQHY4vzlbLA4dlw5XHcutCT/0PA9A+3NX9I+k7OaWoUPCyoTyOqAS8J7xDn5XfvXB/wOkbuhdJtMZCtzxcHLpvc9VX1fnrhCSKKsSF7yGINdtqlwqreK97zmyiK79c9rKVWqKSi3oinDLjjJ4nriEjN6GIUXVyEmmiE274kJ9cLl8IFk7p2OfqMyV9F5Rko4j6TlvzfFIUafgusTtiHdqAprhyDdj7otbDrKewxb0XejSGHreh3tbf+tv2Fcv6yPZTLwN9iAW7FX7zi092DHJQnEbhBrdQigWe4O7F3eQr7wDyKj21Ba2OK76VgNGddHBS/CAPl6Tnc0+sjQFXl+ITIfxERnvTzDZomK0V2hh8c+eEIyxKl2+DQ30aAef8gRd8eGxP03UFbt6B6cx0OZd3PNsnmCpv2ZFgZwQBhsRkDfz9Vjs8KwHOEqD1PmE0no9MACRWAufJy/EqHuXuzSTjNUc3f8y4oV5rAeQ8QGBCEXgRJImRxOO/an3aIVTA0/sJFL2+GPX/+HdOjJOyPPLq+19jHgN7wb6L0Nam/LtdcFqpBCUY5z0+4LKVkG4VuYmANNtmiVoks+CD+uvNUU9d9AoXCGdByAp2so51yA0zq/82e+cX0=
*/