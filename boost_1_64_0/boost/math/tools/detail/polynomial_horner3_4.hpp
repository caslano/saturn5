//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_4.hpp
wmOPg4TxAiNMUapNrZ2jbcoLvdLxRCSrcJAUtu0hr8ud+toLdCCaWkefIyPhBCyDQ0hpadwjUhWMPmZDNb4S2YIlWR4nlVMwXZiTHeEvsD4gAwkSKZJ+T+i+/M/PWWcCnCoHp2ZGOOJqrkgBLY2T95T+RtfuAvotDBX0gUXA2xPCbnNXhRNLJ94nFj+fRTsnELWVU7+v2bLm4CCJfJ6m6ItDqoyWf7sbLfrWV+HHRVoysQt0dFxSO+os+81/4roDBj018kNzVJwha21icu6pOH9HDqzZZWZwfWPFI3VJjV/T8lTZLNUc2aLrH7fyQ9Fm1u2TW65/dBmtHTX6y9HUySvfSWrz5XxbjQWKO3SWvM0WBomXuokYiRdEK5HtIlRzJNVNvNzLo8yJRchhLq9ChaW+FeWXvT+O6SFA9ZF9Z8m9vDIveFXIYEhQ8CPFoe29EuzwTwZZKMn6zJVaWCD+VIo/a27h6Lhsu3+BtVvdtvvfE98v8RM1XjcniaLOPSFsgp+TenXNGELstQYmQ9fr8t/XWO/hhZ5TwRXyHtzBEcBBK+wNMCb2L4WJUEWzW3z2kPEmzCYLk+1K+Vp7y2aFg6KFcq/dor7DJKOygvjxUYLL7GCafot4V2piOs6vbVUY9H2UmbiD/I6rGcR2K2xlUe5BoE1nD2CQ/p5VQTxqPT0/35peNs5dD+0Fjig5catraXYakiROR87oNP1e48/qmn4Iv3sX+D4/a9hDZPBuUhl18Ne7Aq8r9JJW+5mriysdA7u5T2MK0vH+626AKRUK+/uVJ1v2jirNPadYv58J2d/vr/YFzPCOVrBh4fGABeUT6BmDb5o8FybSLMv9ImfTsEUNox444RRTab1Jf/kydGW/rH8my8fnuerIYGe/LOolj42Ss97guj5sD5eGX58NgNvDIeIjIxKnQ7K2LbxoE8Wp2clYQ2+hPDsda1sBt4dtxPNtBFfx6HY3ux1wqI1e1NL/osbfc0cLn50mNj2+A3DS/qQpEjkTOzWHtlFYx6nxY9cATovUEL5xcCebr82bmjN6537O3AI0E8zfn/o55D7Hz3f348sdUQmd3ttVDzJs4javNhoJfUkOIzrML+0Fbvdif5m1llaWIf3Klo48mkcMi9/V5hATrs7nDYtn21Xn99m4Nt+i/fpuyKG2V4zH3w+c+iukVbYXTG9+dwvvroh1jWoOOL5wa3wJfQ+ccK37zSFwFsDkHtu36v20gquX9uDbF+Q3eSeK+Lv5/DAghk8g7e+GYBc6DbbAgxtsTj2H6/BvUByamg7/0xs1BslfFifWWufg4AOEr/3maE6tR7clQ98b3KJwvTensbFRgkG68E2EJ5F1WOFleRDwhIlJrvWc+blzYsdt1d6X/YkpU7IwqniYFZ6WMRfp+j0PU6ZiRepGQewFKLPckeYGlPkrTVvMS+4XRYYyz4JzjvSsziiZJ3wWBV4UBVnIQKBWzIVjOv0kPT0/ftCS9QM3zPKwlLJzC7eQPW7HKwqFJ1EtKg8E681i83zGD46JuW1vb01ScGvNIs9n/JbgzWuWL+CaBYh6zaLtX08i5wiCPPIjt/ZfkawuiFIxnUnCXgH0nWt1vJAD2d7FOQr4P/Pe+s/Fzxd7bQsgnaaxYfgOzbn+rl4blOcv5Brno7C2qD0p+2L6UhrkTr1H00Z87kKnK4rO4KFfpR8N4LUXYbdxet68I3zwFZp7qjPTEYfwtXOx8yrea6/VnEvdC8JLQC9U0AeOwJCpwhp7jeJJL8QqyKGhIzq+l2oO3EeqO+DyXN0H9Zh39kl0zOPc95LAX/+Yd6kr37UXb4vC+FacblUrs51l4QDeWREN4dxqT+8T+E8kngU=
*/