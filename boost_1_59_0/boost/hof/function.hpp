/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    function.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_FUNCTION_H
#define BOOST_HOF_GUARD_FUNCTION_FUNCTION_H

/// BOOST_HOF_STATIC_FUNCTION
/// ===================
/// 
/// Description
/// -----------
/// 

/// The `BOOST_HOF_STATIC_FUNCTION` macro allows initializing a function object from a
/// `constexpr` expression. It uses the best practices as outlined in
/// [N4381](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4381.html).
/// This includes using `const` to avoid global state, compile-time
/// initialization of the function object to avoid the [static initialization
/// order fiasco](https://isocpp.org/wiki/faq/ctors#static-init-order), and an
/// external address of the function object that is the same across translation
/// units to avoid possible One-Definition-Rule(ODR) violations.
/// 
/// In C++17, this achieved using the `inline` keyword. However, on older
/// compilers it is initialized using a reference to a static member variable.
/// The static member variable is default constructed, as such the user variable
/// is always default constructed regardless of the expression.
/// 
/// By default, all functions defined with `BOOST_HOF_STATIC_FUNCTION` use the
/// [`boost::hof::reveal`](/include/boost/hof/reveal) adaptor to improve error messages.
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct sum_f
///     {
///         template<class T, class U>
///         T operator()(T x, U y) const
///         {
///             return x+y;
///         }
///     };
/// 
///     BOOST_HOF_STATIC_FUNCTION(sum) = sum_f();
///     BOOST_HOF_STATIC_FUNCTION(partial_sum) = boost::hof::partial(sum_f());
/// 
///     int main() {
///         assert(sum(1, 2) == partial_sum(1)(2));
///     }
/// 

#include <boost/hof/reveal.hpp>
#if !BOOST_HOF_HAS_INLINE_VARIABLES
#include <boost/hof/detail/static_const_var.hpp>
#include <boost/hof/detail/constexpr_deduce.hpp>
#endif

namespace boost { namespace hof {

namespace detail {

struct reveal_static_const_factory
{
    constexpr reveal_static_const_factory()
    {}
    template<class F>
    constexpr reveal_adaptor<F> operator=(const F& f) const
    {
#if BOOST_HOF_HAS_INLINE_VARIABLES
#else
        static_assert(BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(F), "Static functions must be default constructible");
#endif
        return reveal_adaptor<F>(f);
    }
};
}}} // namespace boost::hof

#if BOOST_HOF_HAS_INLINE_VARIABLES
#define BOOST_HOF_STATIC_FUNCTION(name) inline const constexpr auto name = boost::hof::detail::reveal_static_const_factory()
#else
#define BOOST_HOF_STATIC_FUNCTION(name) BOOST_HOF_STATIC_CONST_VAR(name) = BOOST_HOF_DETAIL_MSVC_CONSTEXPR_DEDUCE boost::hof::detail::reveal_static_const_factory()
#endif

#endif

/* function.hpp
V/xKwAE3QoIxGQS8Xy14RAxUOjaOHGlGS4KfgDASP5jkiaLE8lhKKRW9GTdmzC4F5wptJIvU2IAmn38F8jDp7Ex9s/71hPM0xwG1ZzxRjrHwqGEGEBYILCVVQVxsRE2rJVH21/n6xR5D1YRmrYF+0K2YWPVkanVtYiw5yo9Wyd43LZ0mv8JQpmcWD+xDg7n3+8ocxwZn3RGaqquNbeqLA7HOxFbB+qWFd4ro4eny1oUvC2EBTz3oD1PAOESQXz2EjojJOp0mFciTGMvVeAtQDUCfsYzS36+WUO1jbQsW6S+aAlaW8bV8+3eYB3C5jFN0/QKBIlYzHpyH47nl7WF4ujx7Ls6KIW4Own2SdqHzrsFpl1gXnQxlW/VYJGtkH6le1kWMfcguz8tk+1wyrArCe+HO7cFcwk+lw0jR06ysMNvt7FTSZes9OchdE46e6ZCv4rAndhpE5nUBe1HIXGfUhb94jBA/6Nm8tIRW7P9/qzDpDauGvbR0S9vRi8C6xs8yZlFXoO1cuZinV0zbHBdn/CAa2gPKDGhVaGOuYbgZXQYSDW1PlijtXl13XslgsfjIvFRmHmGtREghaRDF8nQhSalm/dGEHh5bR5mw4z7D7mriipZSdvXx9OaWg3P8Pdl1kuN5zX7ynZ1o9SBYP6bc3FRsUCRFjR2toqbTmPCnTmWpW5DD/M3WjfGgYdUBic5TKNIk5Bubx9wGWSV38EHoij2LB1Qm19mryi3pq8yRsge4mhl74vsVcl6dd7tKLQPz41qoxkIjAf89g+/bzh/D2urWlXMvOP+jrNchAuq1A4v+/AKjKa4A7aMjksECTKRtZ6TM+NsGvJMeurr+SJtRvzv4JZU3lH+O4LnOaU1zvSWEK+e5mmCG6LlDtahv1tn5GmYG5UzF3IioZCKaZHz8vh837ZkVyoHoVJQQwmPtIkhGvvOIwTY8mC3tGTKFhBXCIZDGpIIUl2icJ/TSUWDbTrY6Ryk+qbHeyxkvXbcQ0+BPw12XAsg3mSrpiiHIpHormQ7IFU9BPPKYSZWYDYK9ZEsfReQBZTwWPz0nH8vI39pNN5LlMUxGUy3Dw5AhB0HHqkYXRBLqZG/AtRYYi5DGR5oQ+H8Zs4sHISW0YmtKlgXlHzJbSnAhm7VKNhCjsBNG5S5AEPbEg1Kri2wQDFzqZglfAZctJIG7Be3cXfUtIG7Xq0nPjuKoHIlKBEOahDMuBkLXKBGzxNUtRd1yNJsH4U0d/P6lD4jbDhOV9Xn8c5Tj1XBtqHaqCmg+TcsLO89k2KtCZUqzTLR++HDdXdhltxFLjEOWey3gPug7zIqbcD3hjzVuW3wzT88dtoePG+0mJa/shn5qeFF+ENEAZsZ7OaPv3tis0g4hl6hm9wl8kMmu7AR9+QR9/GIAcaIOTetymwoWIQri3tWGw7oyqPfrjxU+hgSU5MF3JKVdAt4emfg7JoknkfdeoVw75UophaDT9UN72k1sdBSB7BGCtIxRKf8s/ObDrPYF7x9EenqwAfn4mNIg0CyxU9QwEd+t+HOsAYZ0cTOnIL2fDdxdGrh8y7l48Wd0wb4gzCt1he0MzFWLXxXImkmjFxULn6MWy44ARjqLz8Zuz6XxG817U81OJRkFaHZUKvm5PMu5OPFncMHrSADvrORzpFFHRM04pXSspf2MgRvLlq3ZKrI5wPaHeGb+nrZhrCkDo7ihnLr6jEgxAPTI7r4InUjdRd6Z2rJPznoKlg48cu427DYDEwJ5tHUObTpQhI9j+k5qRiWEdbFVVHBlCJXkWv8hiR9rj9ntw9r8INNFnCkdSItgwr5mTCdKUOOge7Rv7VKLY91/Duy0h7bPsH70ismZKQSKW2sB+8n8io+mk+u+erwsOZHxeI4DeKM5PtdcCP0hxJo7mHqqY3arW4ui8zwLVp6Hql6yi4iZofsrR/LSwGphzl49NNmdeUzPbPB+Lri6th7P2jYQTEKJQztPHVw2oEzj3y/zzAAEa+GPQW+dTVS/dttUP80stgAhuseDxp5mqNHlmWufP0HPeynkyKXS4zBWwYhyUy/jxLSEW9torFLuk1VRtm0c3bVzD7aPGD32vFl1Grk01zaiu8OzdAC9DWgx7DBU53JIbexueUI+qVXEMrPdjC0LolzEKaMYo+WkZN+56Y5PjB94S6NavyJztlr4SWQW+n237X7YuXtkWep8Celd8BpRgaIL+Hm/dxKSC+3jrtwaoXEuVM2pW1Fj8A9mFxPKTKzL1efjeHbbLlaxYth50eIZpHg1AwYAuZMwLOFtAgVBPAbltRbtOjydZYtbMSpZ44HwVfY0P646XaCAfAalrSwQyKB4YscLL7U0sCUxzjLZ29qBuBvvcWamp6U4zdc20+q7i9r8e+sEderykdJfUq20M97qxqZIMQNr7Pl6OPRUnMUp/PQoOhP2sGuI71DzoOg6lbXAUeRYiwYA2u0SLAObpY+4i5dBHI+nmsM8FBSkHL6keTNmCpRtyMS878Krb+FQpGUzjdeLRQjVViiT5x8+PLTPSLehNFoQ7Tksmv4ylwESlZi0dizkOIyRZfia1uSFDJlMMu+n5/vNsGpQmRsRZfXztKi0B2pfvdDZyccljivyPmBf5+dH2SeMusM+GpSUWjXRCv+deSNPeuyPiI2KmB+FwGuYerxFss2g0unj7VyjnI1aU5CJwdf3ZzzoHtFSPsVeIWr+Yy0H52tBAqARpAUA+UE1kP0k1lvRYpZZyJDcjHmGm8vEtld3UL80CRwzmiimJFG0sYOhe5F99yZGFBOLEOa/CCYdGk9oI1v5wYtIt5OhTui6tDDVCHdLRGj7kMJ/poulhQMdAqhMmZop666bbY5bUogooTS3suo7Q+hAVete2b2Ol/x+K7fE8ZMqwcqOZVHZ4Q15GAl9Ohk7DgdA0V0eDGvESB5kqrAGcevKEKiq/bagnzaBuTC8iexTAr4qE0FPaVS6ohZjnQ687hnamuG4Jg+otpUjG16OLE9n2IUGzccy3df6oPTw+AE99kdYr8YpuNMdSD/ZEhA7oVPqnJwdhWROKtjwn0W97J3VlhP4DK/oMcyluU9KSJw7JjaXXY2iB/z2r/ECge6q13tNMqSQX1aABejcQVPQxzPQ2lXV1bekaJgZp6bKSjg7B9aXS57+yxNZ3sa0jC2pM9UrO0CUZjUK6WSgUoQ5SdUGvEXS6HUNJym2/57ayyLSZw3RDVDTn7SoN/KnVaLS1gqWD6BCWf/NFAkwzI53/33gr9C4OxnTsUzkKpy5+Ku/kXhiutkDUDswPedx5GLaseEY2eTdrqBf3XZKbzkYvAilZXOH3W0oVDfQYfwj7F2vXVN733CC+T0LEi15p3GhuUkjFJtHrieZxAAxfiVz+bdUK34FRP1OC+7WbsFjf4/wC7njNLfQSQL307E7PZloXIGW/jOogwPOzeCnTP3oQzTzBZMV/9XFeM9/SbRWkIhPr0RldDXn24A3uwHQ7Mg61I5adLufzD0xeiu8YE1aX2PqQoBszdv17yJSwkrsHddo0cVLHUyVpHrskes1P7Joo2V6eZqmVIVRobBnQIf9/Je41oyO4M4LiHAx3pZfxDiMg7lGNLRv68+8xaavu4Hs/RtR0T/KStH6kO4CI8/BWafi8eN4q/zyca6+A2SBs2DuuPiy+OeNSe0Ke1/azX8hLxXlzxftTF7oJMoYjLahr3vtcLDiSaiFq1ZhEYLlz7L1wWWXGtDtMnhOTpONWDyRr0FF2AyOjkhep/8MnvI526TzJpZTIG9v9v02nMIx2GLelwG4NEzsY13Ntqhdm65v4HiSVo9ZHRoXCDRowmY+ol+rJEMaN9SZJKW2fwr2wianSpTQTuEqgF92eESTVG76gyVcBsr8douBdc0vg/VNaRfXpniMca+V4EJNou6JzDEgJrGVYR+Z7aDeNWBgj7BYhDQuSchDE5VVLer7n60ZmulQJC3wFlkP8lFC68oE8m+ty2BunO4y1lryObqFCFiPx6Pd+WhOP2akEuajt2hZ0UajhR0MGaZ9OmHrV8g80fsb0Uqg6lUTupocDB2L7O0b//plqptPPoP3oRQHu8FoHkabkcW88RZ5e2NhgkrbIPdeeJv9/bwNQGAffVU7482zqoBY/DeyMwyQgYMinWW2RjqbmSAXgZTbJMWLKvH2fbwFL/1Ipln5ASyyUneq0BziNb7+KSFWlsoJypF9kPSPU+vVJa/HNYZcdK72X2dfyIzMI0JEZvqEhrgZiIcd548IbpjImvj9l3WM8zfqdhmVjl1UxbebBOaH+XQZ5va/YQ5WfpinwQHNXWkfNyruljlHTh7fN1Juz9O2zJytx03xGR+P68JP4NsorihP/Tkz2hdeG33VLtC0KEJ85blTUp0eZR8MVqK1BE6QRibN1ULsVEb+yp8a5bdALTpyLJ6+e5u6MVSDJPwkN3+HrkDvC/yUUIJnGBTtgZ18K8q751wjfZQuXs2AG6zhWfEyNDJeLpE43NLScIOqtBc6gtFKXzcf8xRxgn9V9eqxHw+u+DG1/4TqHA+ZipF7lFjkKEyCYegs9SIW70kDlCwdNICWJuGnZB6lO1Xn19RnqTYmiQRewmEZhWc5FFrBrD1pRpKMdixVofYFSFJjPJaBsyWDbVc6gwxrakqgSpJz9cxPo5x6PuMihTYUVNk7Dbg2XJcZmGcjBioHggumsCcwQBCIommbjUxjTPwqRxegx8iBF0Zp3ndiyw/Rsk+VfhAe1Zt5idPYzLtRCbUl1mZwO9GnnN1jgmnhrERZOuHwBkNsYZzwWdDagawGriBZNvHrGvhMqLYD3stmxr/DcH1ME74asRs0stFxkVWyJriVTpp302P4sJII6zpOtRKuGvwZPWWeo3ZLVOBudd/8j2ZbqTzyG3edFRZPTHytkGutipn9gtz42InpGMacVeIsHLLzNLdAcIzqtEypuBCC3Q1x1kfVMa/tJR2yBatd+ev2tAFdpgEpIRyFapEE3sRCvMjAakNovcrLY0TCTHHUwB+V1OUaPNBBaVSN9EsyymbklQuN366nxNUz/k3+DR6Z15PQv3mFkhkaps43TpPB2nHmQt/WGnpIvHUsxDF8Re39B+EzdEulL6p6KzAmZSGZofKsqyr3NKcCzgr9sjKjdH/9AcSafIw5XG7iNmlx44UkHpm5X0ktppShJA6FP3tfDu8DvUdWFwcHIoALXkABqBG+aDBncELif2zyANEoRwu+OCC4MDtoyP0BFhxwMsY7jTdm8UMpNWLW1vq3p6akpGTcb2JrSK1M2gD+GcD8DTrpzR1q92lNO0ELMpEFfOMTK+yfk9r7kUQ8hOrzutpBOl/HaqKaCOw3v20ChCsMdKtRIAfhn8CFmYiq7S8TAXf69Q1cP/nKWFW5c95+g41bvlh4YWgcCwM8GRzlOdtbBVXaNaGppc3KFdkjwlLxymLEU61KIAlcSYqbOEQIL3pgzNZ9xH+jnIRp5Cl2BwdJf7aPTHpaYZHWoTmU5Wh39GZiyi24P76ptIj4wrCNwG4oThiCRpaZ5PP5vAnjnL5Pkom9gRbsLfAmyFmAjbwPXlQNTaLwRGZq130qXfBv8gzKVYu9pvrr+qFEOXnV3EVSE8JP9kbhWgiXyb/ov548eLT7ZruBVNj4e9ZuHZC4Nn1oc4AGog+8pmZp1muKDyCQpdYicAlepY1zpMdCIFFxcdBQc0eB3bzSYLfdwzaYUIY3mDY3Ft2UIx7sOwxKjGf3t90+oglqbg7GOgtSZcoiTkvBMJ2N0gCYNGGPSB7tqUOPeen+YEW9mrVmTAZA1aNDHBJsw3rE88lOh5Kt0FGw4gJEyOowuV4J4ZDzLamJXA01CJm0ZVSlQR+IgUjXAo5a278ySC3Q9qwLk8vmABEXuxaJjRgq3XEt+UxheufyUB08WZ/Pn5kbfHsmPhwUxwlxbBcMSr1YppNm0c2P7yDR5YayRkPzGpXxKr9tkNLwOn9XJx6NfNPwmGf9fJl08vyMDiA/hU5p+ZatWE8vfNLVOoKyFtK5zjL4zoL81sk+4Sl3Cxb5gS0PoNethn5ATE9rewLOxNKuMHzlBX3oACbNtnzJBmRb9KtAJM6d1jdqwa6j1whvCDOm8IH7yLiMhtXPTysFbU+yUMwN35YWUdsQ2OESNOLJHDLy5gTKmJOktiBqW0NyOM20ehrlSwmpSpGM8pFP0KxXTxn2TY83xRpa/vNA1Sm6qrIKku/oNUdgOpHcOhMvcr4GZkSYtnKuTonUM/X/dKXpnjnXNSzUPx7aPU5OL+d+T3a0OX9DJ6euhaZYLj4AkkVlZVUKW9QYyi/8DK17F4XXQ6pVLHK2YZF6PxizSMmnrEX9etc8Bp1GqPuoZjuo3cgBMRf/HKZZgJshUSouje7CmWFvqy/pdswwltw1mLglGp7nZUdkgimIaYEJMrMBtcDGmnZKQCNcAPZR/06DqSI+sFLXGIGdSfxdGbyxRQkFtu8jA4TbjbHJJv5OW8ntpL6nnFAyXBNQmS95Pcu4DGPDHxqcIcPEiPRN+llgsIxIz5lZ6pyPxhrPCl5wVHp+9igogPANMdQ6hdC7WRMbAx49b6N9N9xF1vw8yNPVUjtX6exJVGezLbLGxaatYG/NVxfu7TzhaJmxmDum60RBheEkVnywlfbT/T7BR+9DgvWpiO/eqJPclYyJmlNYnLbTp4p3ctXQVXiffqXglSUHjbynT/UCJeSjDk0/t8o/dPDO24NKj6sKsS0vK3ed5oCsUZ2U3HQdKhOKYe7XR+4lYDG5rJJVMSdtChPIaQKwhVwpvSlx+TIuISml2Pcg7/HBVYVotTXoPMVBPUb8ATRJYq3CkquRkKAhQSI0e+Bp+DSyxJNLSMRSdqgkSPdNQbaAMzBWf73iC0kO9QP0XvdPH7j2uKF15top4m9zUmZjITlhhZ8sIZNHiSJ9s8TcVCRbYZCvmRft8WRPtQJA8satawxmRrw7b3CeY8jeHDjIuRE1RA9K4IG78ZDZO9Llyu2pU03UsNjRbHhlV9hSMhUikbAnotOvsPQkSlb6dfwEItA7HAJwteDHVG7OTixd3jAG/RM0q10IuOOzvY/XXQVIGjb/DTHD+bWT5H6do3M4jharU6bwEKlBVAGs8tXdqyd7Uci1i8GCPt8C1oayqFIUJY9qUmh0J31VcUJPWds655torB6whyxfH8JscUerWGjIyZns7+k+OfUS/YV6lkkrz4mHyJXc4LQJ3FY9LiCIXPFfoRHUsMOszXnBNuB2spREZCz18zC51dLjA8KRW3xTY7hl2BwA5klxwSDdGh1ii3MqzAokMD2PqxeGmB3B5AP4N7yetHrbIWYKB02/JchxAusVtVXBsGOS0kXNAJ5K/Nz7z1EqJ9ZcAcuKOUGwluR2TBqTIkuNHpIiK4e4MyIhWBWJoqiOBppZYZRF7EfUQz4INAXwePUmNyesOmv3DbOZCbG4UxiDCpTlaBdjoxmnHdXWEjDHyivcMIryc2knBjAlQBK1sWqjuGk81pIkLZpUz/3v+YP7N2U123Jk8xyoQ/pRUmn+Jj/n2b+zNPCKSbCKKMXh6yUpHJsx4pogPkLhs63kvpzBxeA4jVf/E8PO28CUsT1VoKHkZ6NZkI0V1WtK1kJj
*/