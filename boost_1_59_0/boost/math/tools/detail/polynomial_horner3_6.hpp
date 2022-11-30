//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_6.hpp
tXSmfnrhO4wZxlVmLTeDjoySnfEzYta93Uzl9rZPE7RSiNYj9jDcvNs9udUKkioXFzdM0yojTl1BdhD7QUv8FXt51LvzLIy63PUI/h8v3rvxA5FQIDj42GWjwmMQ+6IZzsa5+DCZKJZMedhgwuS6pv/JwRYgYWOP4ZJzBlwqFC9EeubM6MitTQHV2Qw/X7vFUbMYSRa84Hcooy/d4jwL48cg8852xiZvT7TZjMM7kG7j3E2NyhTqnkNlZQvqF+Apv1ItgqJwNkUMKUoS9iMixV6dqfZkW5tPDfRRusdyLX2VQCNFM7DQw6NNjwmnTtIrFKvkVSv42TrqbPhpwZghZ2U5n12VfMwT5x0dzgPsmHTYIWHBvYN8OkHxHmW/OnnpxxexKxahrejvixgn7WKJmj0+eBfh86j0l2zQfYw5svDDrITP803ZLVMXhpok9iLL0Hf0S9kk78iGsnlTyy6YEKJ7vC7udamNUUxRyRjsyqrvzLn0EViIuLz6bHH3ypdA9o2Umj+UxitKA3qy8nlp0Ezo+iIfuZOM+t1ZwqCqDvL7ydGNNW90T83EqtBXJjxTnEBMoXKWLU6C8rkmngVUGslrmKbNs1z/vlX1npT7v1BBQoDyhN6HPFy/+Kx9n4h4hJTKL5bEiZNxFaFEpN9F9eb3kD/HivqNWedLE9M02eN2iewz9JlsaERd6seOFtAeJWD5lZiQwS35h4t/1F7snXrExI6rq2WR0d3Ku7t+EaqTpdYXEtEExAAFQKCfLSOJEYvp/vhXVwB18KXC6AQ93SiLoeOHfSay5k/h+yDN8jk2Wqn5RfWcEmtcZ4jBY6cBsKx4XKrelGd71fO6LJfz5bzQPcTgEKkNEQwr6c9Q2CzT+2sf21bhSlKRnDc+BuYft9+5QlDIcRSBpfU+6igCStM2Y/kc8E15qBs1RyOSY2Z2ugZ5ygB9WzK9ysGkZnDve3r3+coRBe2jJ9jqmgUt7ZC7tP9CwT6iH/L/lSKheAM9E3Q3AcwSPZiACf+ZeC/i5f5oAo/Q647dzghNb4gbVcfcip6oES8GeRD3yl2BncTkiTBpO5yeZRY1d82ctAWdwbHSDE9AJIJ8Ud875Gavdix1E9jzr9g0Woy9oWErzZeYc7s3PxGmayPX19rRh+BDcxKQwuJPs8u/XkPruxsL98vnIGZgFhFmVAJoBLeERq3tp1RHKRDWIl8U/dRYKZ2Z1gnMJLoVvS+ByJ2kML1F7mj6jf7Ihl1tZCP66Dh321dinYbLoVcaKMnng+UaDEoU4tOMqQwKEA4TlplOSxKq3a8lu1LrHH5ovRsuDgovV1UrE2zZVqJfz1j2loG+HwOvmpzDmbq9Xfpopm/bXz7hGuOGpHKK7Z2mMBedAmCXSMjaY3Lr4X5srhJjmq47yemyKcu7QQ9vDodrzmpY679cqqDtHGgM+K8+k8Rll5RFg/qhLB/s7OyNWkoHC0b96DXQiZfzZ9aBpZxZ8EVksqQv+NQEQz9Vo2VVK/oRuxM4amcxwbWeehKqF/ECU5PHY6cq3GDRLYsHFDl+rASziG7T+KJOPXtxl5RJrmri1mzzFrhLiHCNA2U51dcWIqDFTXOdIxgbw5GHrFRxPjv4Mp/RhX7NiHMWdaLv8vUiljOLAghcaxNSy1WnYKWyl4LVB0MCz5U+uOuP9a2P2y2BBjkhR6BEHgmmnz0qzDs1PaTFWvhWeZSxysxu6K7ji1Ua/oCReGjkFrMhV20H0bvAVC/jsxA0Y1SwAYSAocmEdM8jPp8/BBJSNgn2B0yHA66ACgOVtpJsuG8e3LvqQPNwVin18p1ALIlo524YETC4VaYR2XvlbjU1I9e4BrANR43SpLKv5m9dJtc8DH9kRRUdvpnXCmSR6cbbcAl9N+pcN3o/1KE1svX1D/1Ogqa2v5XJYQrBxMqsa8kAp+/Qg0hI9ArMiiIbuQBD7pGe8shlfeO1vJvjqagH4OwN76Xm/5zm1nVL7dS1lUJmaqo+g2Vrw1032nB3Vz/8b1EsCd9aJmkxjpE++4d5cC9s5e0w144A79ma/G2D8HDNfRarGQFerXXOndyghd8wjXLqNKWYwkJ14B/pZVXo6eht0jPUm8ZaPjz4WdqwxuUBy8aFEZBnyOlYtXDaE+jki9b6HlueXLsXE9lDHLsbUZLI19srQ43+ZYJdXk5FET3p+TmJ5yTuiiRSE928l3sBcJvHn1U4rVye82NstU6UaOX/dT3CPUHYHDzu65To9koHwW1p/vWQ/EKFTgeCr8d82Qj7/vRvH6dEkOiLTBpMV1rm0YKh9XsCoip0AAt3DkS6ndp8Mg8ocaRAsBrREQnpz2qQrGRUjznpSm90Qi5Rtscqh0JdWWbOqpST1d/G7mYB4gbcbK3e/hmzqVMPU6pNxaVIRkoqCYozp7BAwGyrFa0Cih2+tahpXM6Gp5oFRWsPBIjfnYK6NvEpGQjmZqzQ+f1JSIOHmSLEVhDNYzF14UWgyKiEUVTV5rVh/HEVa/h33tdhwtv7HUXkvIuf6mHpFZKpKpXDF8505BKKVaGsh5zSA2j/13A1WG7KJsPIbwZ7u4nmuxgvP0oUmPS7cf98oQJy54d5S7VCLPztoq1g42XRtWgQdXETWeY6zBkRMg/3f62OBQSOvfGZvfB7hOVrqMQEr7yPyznjpYW3vgelQL0D2bWBq7Gp/7MFVrBtr83WDdZ5pHgaeifOp+Rw4UGtH6nKJsEpKlioEzhxnzIITMnEXjiLUxXa/4QEyaGzPEqX1lBK6lxALESIXqIm4QzU83xS2ia0ylUjM37I5K7fnwuaX8tj4hZgUiWtSipFm4JYaRswvo9HmkjhiTqoekoJsdJHujbsQ9WiU1/6vKuTRTiRrOOnZwM9IyAAOH779iEslpkHy6BRfrKApdyGSYmBauXEkZLVLt2dv2F96aeJagiVMMXE/dVGlqRoo1p8ke55Ag2AUSyJWcBxO93gOG8mwsKMZ6dowxcJVcfh4SJXzl+V6y9qzhy6oBjXT+6o0CjqPst9IGn5NqRMT7jDZDGlB1+n1Tqkp/7+hzWI2iaEpmYKXFUbbfFCxOUzoSIH+jqxqpeqMw4KWMy5sNb2RaQXNAnEFMdx3MuXNsUF3Yfl6SiYW/g/SWwPPji0m17MLetrfT0AU35S2mb1hmaOEclefebnyZGJy9KU5ZbU0st7WkBD9l5qipxCrjE2JgtbawC45QZPvb4pswzAvsvO0J3U+gpb49cAAGE34M1PA5T32Z+7sA/kfO884sne8HnnEzYegA/llMsrq/1foSzlUqbrQL+UL+Vu24iuHmmE4D5GH1cL+p3aECIvLQJs2zaGJfXwmPT8eUNxMV8+Si9N7EFERN1u14AeJXsnRK2R14aeKegxlsfYvUHJFqXpXrimWyH0uHF7/cithcYNoM0BRZHoB66ebrkf7y1jVL+C7ZzS7MIMAbsa08p7u4V2D8a1ES8uBKF3uhmS4+xi2gZ6hg7YneHx+5NYGJ656kN7KA3S2tGTNrPpJLzpC0WKXngV01+XLCjGChyHKjk9B9DbCVyyvlYXZjyd3aTbyJaON4qlffe4JkcSgvrRixK9ZYOH+D6Or8YZowoWdkOzhU8L4bPGEyOidbCa01EFvlnSebaCje3RKVrdB0s95iJoE7/V+OAWo8ch8U46jelUPq1Z7mz9Re/aTxAeyGKHDpFu8ls0fps4mTdkSFE124DU85sKMAUleYM7nBbQM39b3UQ7xUV0LipFHxBVwggi6lmhfhpstOhF3Af3lPgO/03PpiqQA/p3ZyWlRejs6+L6CwiTtOMbw7tyQdppyjK4IPtddlS+5zqYiK03IDJdJ+jCrLvkRvmh6Po5l3BrPRqHMlbNhpj0rE5ODtSAXKes9/P14ybApSpu5mTk2EimzFFdGb0hUoaRNUOk2ZagPCWYZbJuyPDKqrt4e5dijSZdtcdU3o1a72M8odCDWsQ4bY61UK6Tjvgh8+uaM/lWfSs4+wV4Z/loPpZDqTv3BPmAHUeMJQwrIlovunY6uwSPJ48HHfs82JKnixqo7qVwgkZ0jrGuWm41DSphJoIxUAE+p6epDaamRrljbWOYb4wjJN9pesJaYUzhNLjQ5tcc0zYJldgUhBVxAEG8FlvOaboXBrHcBlFAq1ntOTzw9F7wkb8LC3Dt1fOH73XAXfgHjjj59ibdLwIv3fkAmjsgv2WrX//XmqE57Q1KqNTJv/w3jdmrRdttETP9e5TfqHX7qpoTaJlq++qYFd4L7A0ivG/TGrXq/AQSj3KY1YVV1zKTUGBtYqIbFeITAhsIhk6YE51BqfuFJs2ij+hGZBHneNWQ+PWD0AHJ4VamIpsE1xRtyA+kYeXi9wZFAMH18g3iH4ltiv1QswBBz6tXN2W/cvVQ4xAMdsycCzgsYbQhsRBc2J4pUOSiURbum9R3cUljH5koK/J9PHyyfFyAxdj70RDQiPSOFGyslw9GxKGE87RwMc6rJYBEWk5aen0octRGZ1oqJe27CcEqKT/g/KBkOLlUQJrXr4Fxp+gtMkKieC3AuOVqMLFokm9C8fy6KPdY9P2ePpl/VVCN5h0GYPc64kS7d8rWv4nQe2L7pMk4WCF3HhzGbH/ADU7GcvI3TihZQW9XiTAAh3eofBSKWKymel3dPKnheOTymUdYL3ioFjK9bRbPneSFQKX/FtuAS9Wv5lphpIKLo3FSm2nTNsEn/cbn4ZV5lhljaCMfZ2SfY+pws2HxUqm8a8FyqarrKJaB1ZBQX0OR4tgdKD0NlEumcc0HQC+yYCTkBoOt6K38pMoOP/+2vofuxD/DDPE2Vn014oHkO8TdSIn+0H7/465MK1bWS19uRFtjWzMiW2SRmOPAlrWR0LQlswTlQFPTRqJW6DTDRk4DpaCqSV9WRDZHOXcTEhcFs3JUrMt+j0wnEZ7DZtQMlX5tGwNFvqfSD3q4AQyue8QDx/nW/QR5IOgBNWRvcOwRtsjf+HlaV3kb5bwwyA5+LBmRpBGDUUaMnjA/Aqtc5PJBkWpPRTm4ID5rJL4idNceixmizvy+ZWJlIHk4s4P/TZZFidhPURXT5IABWKeeEnpblHConK0mDk2Pidw3Mm4X//h/xXz95KeLNMSgwm45Vglp280ZlHB5yeFsxDxjXi+pW229H4K6ObIsRi0JZni8uenYhSrF24R+wyXMqlLWqXWTp3N7UxY/Yexs5oA0OzM6/I2M4K71CkwlouyyExRXPKhOQ97PozoZP8egiylvkSiTOWnv26Oya64DVn9c3DaTe2CYKV0GX02aHyeDhbBUwDaAnAWTIcvvYfneVl3PEtt/s+OpdFSwkm+diIFyrhekannrIRqMF0GqBX/GDvSCj9PIVj6kjCN9wBBSKJsYI/l5b7GBw5G1YDPYgQBRpEB5IgwXkSqJgiRpTy7Ib5kzt6mMCHm966YioHYw0wSNpFRD4TADR2KL1mhox8vrCujQ/st44zbo45mTFtVoDFHW4BXDgbYX6dTtAVU96a7T3FA7GBpl+kJW5NXaOEVt75xWlMRIINkHWxEwruAWU2CQtHoX6Iiqn2Gd3/C5aQvgDxQJxIBKai0XrAEGZ+krJDe3XVXF/XQ4wJpmcSepHXyXXt9F/vLqKrzcuIP+ckwUOk/coOFynvPpHzCSrDaegwBvd54sqkX7Nht6OjZDlL8Tkcql04/whVV17R33ZNRucO9tWTNbpM2TvdIE3cXv6J27mT0GQrwvOjLCeIr4j1IS7Th9amm+HqXgYi3bWcA9WUjLWb+8hwE7mf68Ny935JwlYTMeN0fIUH+z31HsHcZprwPxTKVcmvqcY1z7tpIC53bdWf8uRKrpQjl49t2i5/f9kvfR9p9EBiJ5nntY+Yl5h423uxZzdgw8/xOjJDNQsgoVwbOjc7ubqtv1/IqeoyifaF6HhAe2MxwwFjCi3LZzjNlWG1fvCa6K3ka6ye9K6iBhzmeG7UJW9KZCTCi7Qqg/c6GvEI3Ck1JAVCY4X9G9Wlmb7inQ467yR7bZZxDBQX3y1aAC8ePYehWwbhzGfZiIGKJxCaaghHZiISKCb4DRWf7kNi1fij6IqI8DsUjuNorHI+ErKsX41L57gxkBzPV1pVIRG6Y1xGsUh6TIs3w2PVpgzB/bJSXOvzstZ+ftd6LzNKwHl7mTO4fJnuFp89YBxZiR+pmmq9MDwZbm34VPeBDS9K/7V5D4rzavqUPxuuMxiG3//9DrEYH9P7jc+23adwUeiF5VwaggDT/sldjSZz1/o+uugysI7576WykzPfH2O7H3Z+4Og4/GAL+7F/9GGx5oUhlqruPa5ZMvrFKpXv3FIZd6GUH/z0jjtZYbdZ6HEME7ueau0DZXmQpR+jEvbWeN8ySROFb6BmbIQ5GQfvaBsTBpoHusy7y7KD+ToHR8YsgaHwpWAknCAttNSCuCoQ7P2pFhCpIY90p0l5nw4UX0dPjsRPuRT/c16xMtuVDWLvExvapLiVAYet3hBL70/cuerQdjw6pHmCMc7KqHUZLeI6RWYfv3+UvwGgVmW7RHcVthftXTU0PDGmCu/BKhagiwmL3n/h9e9nAz/rXm4Sz1XYdY5VqVbDCikrkz16180Rb6Jg5nuP9TawX9OA12bHYhAzh9T50e3NJEkCMhU8UEqI8/CN1mqRc8BKJiRe+zIpSIrFDy+pliSRmbRVwVHv1Cf+/j933lZ9/YFNjfIRproVcna3RKIRYKAYDD0II6v/7o4icaNNT0dNQUTWTVZXGg8fUevvUbFtz5fASdkGVrV+lGyN66xnrZtFtwWiqotPs/dXnw/NpEnuynPEXDU6c2pgXOmoJDO/sKVAdvz76PsZNKkSqQGBL0POojJjfKv4yjAdGPg+ph8cezK8bFG+HPG0MSQ9pnInAVUuL3PwvTvQxJ5xVcSJgbxKzJsG9r1eruF0YoxBM9Ap8hiHt/IWo+iIYeSm34ScNlfPAF4nvRivZoqNLKUg19pgTKEQse8+f0XOLX7Q74dpZ8x2q8o9GVbslHFJm+xeJBqYlfZvo5YkDb22/0EuALh5/yWn4MzZRriAmE3/C5c9JX9owHItwijFkG/lbm92m6CONMcT+XexShPzAlHbEw8aR61Kw7Rria+/51+or7oxikOWEzZqjKu3kCU8M5xhuDDC93pqATOdEB9K0QTUGO4hNa2chHvv9a7O5g2f5+UqQHvIm1ANDAkBZFer8RB5U4Ki4pm3Wt20CyRoBgU40QYU/Twelhge8ZPVag1kyU6Kemoez76gvyjIyTVFDiitGrYKstjAkZO3h0qlSjaoUzaGHXbrA+JUBDVDF39ovRSfRyWYDmSOFBx9DKf1ZQAh07pB8+UoX4iFRUWmMGR4qsBw3+raGtPog/G0QMsysTYMhjLbrJUWMroifQy45qsdNjMdQxnFV4F+5J0MqGuEKYE+7wt/5gjz4uDvnjgR8OTmCqix+qkOzvwxgqbiAg34AF5LnvJKN83jz+xRRfoBPFDqUa24KTuz7YjFXu+Y8m1f+J1kqHxRPavQ4AvC6fo51vUU6b9bJXb2vDTBf5kSdTuDt2OwntZNt4q1U5shD4q/CJ4rUhTXNkdpjUcwPvrg0YCYqPgK3owLvzJ5ksfZBmUuSn
*/