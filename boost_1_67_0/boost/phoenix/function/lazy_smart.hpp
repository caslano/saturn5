////////////////////////////////////////////////////////////////////////////
// lazy smart.hpp
//
// Build lazy functoid traits for Phoenix equivalents for FC++
//
// These are equivalents of the Boost FC++ functoid traits in smart.hpp
//
// I have copied the versions for zero, one, two and three arguments.
//
/*=============================================================================
    Copyright (c) 2000-2003 Brian McNamara and Yannis Smaragdakis
    Copyright (c) 2001-2007 Joel de Guzman
    Copyright (c) 2015 John Fletcher

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_FUNCTION_LAZY_SMART
#define BOOST_PHOENIX_FUNCTION_LAZY_SMART

namespace boost {
    namespace phoenix {
      namespace fcpp {

//////////////////////////////////////////////////////////////////////
// Feature: Smartness
//////////////////////////////////////////////////////////////////////
// If F is smart, then we can refer to these entities:
//
//    functoid_traits<F>::template accepts<N>::args
//       A bool which says whether F can accept N arguments
//
//    functoid_traits<F>::max_args
//       An int which says what the most arguments F can accept is
//
//    functoid_traits<F>::template ensure_accepts<N>::args()
//       A no-op call that compiles only if F can accept N args
//
// We use traits so that if you happen to ask a non-smart functoid these
// questions, you will hopefully get a literate error message.

struct SmartFunctoid {};

// We add crazy identifiers to ensure that users don't accidentally talk
// to functoids directly; they should always be going through the traits
// class to ask for info.
struct smart_functoid0 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,0> {
      static const bool args = true;
   };
   static const int crazy_max_args = 0;
};

struct smart_functoid1 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   static const int crazy_max_args = 1;
};

struct smart_functoid2 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   static const int crazy_max_args = 2;
};

struct smart_functoid3 : public SmartFunctoid {
   template <class Dummy, int i> struct crazy_accepts {
      static const bool args = false;
   };
   template <class Dummy> struct crazy_accepts<Dummy,1> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,2> {
      static const bool args = true;
   };
   template <class Dummy> struct crazy_accepts<Dummy,3> {
      static const bool args = true;
   };
   static const int crazy_max_args = 3;
};


namespace impl {
   template <class F, bool b> struct NeededASmartFunctoidButInsteadGot {};
   template <class F> struct NeededASmartFunctoidButInsteadGot<F,true> {
      typedef F type;
   };
   template <bool b> struct Ensure;
   template <> struct Ensure<true> {};
} // end namespace impl

template <class MaybeASmartFunctoid>
struct functoid_traits {
  typedef typename boost::remove_reference<MaybeASmartFunctoid>::type MaybeASmartFunctoidT;
   typedef
      typename impl::NeededASmartFunctoidButInsteadGot<MaybeASmartFunctoidT,
         boost::is_base_and_derived<SmartFunctoid,
         MaybeASmartFunctoidT>::value>::type F;
      template <int i> struct accepts {
      static const bool args = F::template crazy_accepts<int,i>::args;
   };
   template <int i> struct ensure_accepts {
      static const bool ok = F::template crazy_accepts<int,i>::args;
      inline static void args() { (void) impl::Ensure<ok>(); }
   };
   static const int max_args = F::crazy_max_args;
};

// These can be used to make functoids smart without having to alter
// code elsewhere. These are used instead of boost::phoenix::function
// to declare the object.
template <typename F>
struct smart_function0 : public smart_functoid0,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function1 : public smart_functoid1,
                         public boost::phoenix::function<F>
{
  typedef F type;
};

template <typename F>
struct smart_function2 : public smart_functoid2,
                         public boost::phoenix::function<F>
{ };

template <typename F>
struct smart_function3 : public smart_functoid3,
                         public boost::phoenix::function<F>
{ };
      }
    }
}


#endif

/* lazy_smart.hpp
We6zA9JCZQ3zujy+sugPtfJj3d5jhHvwozOD5HUx42a0/HcH4LlSWC6hzTv/YqM4RpvuTlwmeqxMlb2d8+3eptQ7CepN3MrKs6ATHEnW7EFqCP3IRY6TA4M6dGqR6CVmmXBSEqDvyJ5XfC4TpsuEn/xbJoyTCfcRj0ozIeVpct4Xx2uW+HRlgSAIySEE8H4+T0df9PwfDOmnR2X93jLTLNBxu71H3HT506sq76vKMVU5zopyWLVbccXHUb4XBx+xzOTPPKDr4Zd8iHX+dxh9GBPR/nLh94VUXj6I33/j+wJ0bjEGMq0ZVC6BwzD89s3wnXHhB/i95LVg65tM/tA415r3eX933CotA/l1ZwcJ2sLeYRZZ8D1K/9lf6vIFT0Mfeujuy6qyW1U67W1/oQGgrMS8x+LeU+70LjLaw2GAQFX4HEl+itXehsDFLC44JCtQGZJINsiIhfxFOuSiN2PPNpVhy3h4tuO+jowO8a0ZRhduIcPSl7GFInchnPRb84k3dHZvNkZi9HvdF0YhxFFJdlqS0rhgkShCGIh93l77lrko5uHwBuxt7/z/DewhY2AUAC2+IzkwY0j/eo+GtIGGlPWtIT0zyujd3ebkkErdWgsOozA3mok4BwtPw4KeUwg8w9ZysxjmOUNUTxqV4OtvDZHk8S2raYi9hd4B+5bZOtoPO5O9IWVWwRnjy482n/Plr05W/28hi3vKUz5+HLUoINjCBJ07OfEut5yf8n6aoricHDFLFjlFftV7ine+S7MUwFkCmbsoC4ZdGRk9Mle83SI6EfvxyHd/GidJWZDS1U39MlfJBWehfjMr7zcm4UZUxc7F/XGWCKD+eBJ2gATpoCCTL3v2RR2iQXjKUKlRWh/WhmvRh+wYW5xuFRnES0jSbOm849Sg9E+L73HDyqo/gtu12yegMPgrL6CW/vlu7/N0JNVCbnl2OEznENuRC5SqDwy693vE/Glea1amhE/eJMIaFYnu9/aptBNEnDaauh8dSSHQP0oT4JMRE3p9eT6keb8Myd924r3+/pgAi0xhvfrmphnM75J/Un5Cci5yIzU8/rXRJ4doFw1VQtySJPtnCDBI2DlNx3DLu0qSyrTLSdspjQ9+s5cuq4Em/xNXpxWkBl8vKuRKhEJuLKL3PkK2zMSpIc/akIstSq7Vymzt8qKUR5cOy/Z/PmIwBXzqISopFSOFVPie8wvLaRv6y5CsYu5IFUTg67sNQcqWlEja+4wBW81G/9aCFPUAKc/WiQZQ2VicWecpyWwYVVqnwiOwPHUL7CYlo66wOD86FYZ4B83NDnPUZd9VmX96C/4yR8mZvbgMipY1XFGauHRHWvRSkCDkTKZFJybfWutmlcyFustIVT8iQCDHst6YiLX2LbfSGWD7Nld/I3yhTL9WsYZ3/x0Ex03VpmiGvk0oLjeR4nKbUFxuIsUl3ddh70quxbsqPx//dzRmuxAjU0omjWgBBhsTiHEvEb6m99WmY2rTcbWJ8ykriRUgW+p+4Ob9+kYHX/QMSpysJmvFioByJSP4c82728/bcM/QZdBEgiLdTTFhkPNPfEdwg7S2Njqkbo+fNRnxit6QYECbydgd1Xx44+rQN9r4J29K1XLHb4kndaGDY7kVUT3USr9avByFA3tbqwguBDLCrC61HCUJlOCcwMWcqMRDJB9NM/jvjhotLhMQQQGMskqSBG9LvpsrdQDlJ/ite4aIgD8jTDQccKz18rQPjJzEanqzEK5DiBj1DIdR2ojda90PHWlYacTkcDBHXfy/i3S1yqlcx0psnoXLlavzTrd2NlzKlq1i3uMsk1mermv5ULfXFZZmKmN88decno22+uPwT3QhNQN9yop3Wjw4QEf9U+FdCEzBj/xeHJVWPCr7DRYsUR8epJP0BXqduIkmFT7g9IPyiqyS4h7hTV8AXSKT6YUo0oQQhGf/YZl0BSbhzR4kPnNaJk6gRDMlPkiJ8aZ+U/QiRCwiMhGIpAdRLMofQp0coTjupuNV/zewgF7u5yVPm86JqhQ/4SStlDNVpsHAy0I/dYJfc9BQRZ5lNVZ7B8KJxG+zpkez4rfZHA0VpEtE2+9XHwFZhEjnhlw4xaYLknYtVn1A31AAqfzdpNbnWQSS+e8fiJJPPkL4e79BpqZNGD1hC/Z7X4NvNVkqyAuBVUqPmtH0qVQ52fLNGbqEDU+UdRQ/YhjZo708sxI36ur7PtaZjjgVqncgUSB2BWJGoVSLQiQ/OkXyAgNwCp9Cbrhf32DlPz1kdHV0mnHdtfjNlBvCRd3ihnD0+UjJ2Jvt/0sjol1WQe4IjkrWo3qt+jKnqPUZiZgVQLt5rThfdegKxXQyJxVv22iPnkKs6hShcIqYUNLikVblYZDHEiGU964mjnYQZ/roW0b3SwUzk/wGVUBdEjkRUxi9B7CvW94VLPG0ZEZZMfuPUYeFgqDNJh7bqRbPTrFJEBk+NkmOyWpcey49ahTuFjoC0q0VpCnXw67gJ18XMepFe4KC+D42Stxrkj3hf/6XkdZiGpmMUWict4HEh3UYL0/42Ph59hvSwSYapJfh1Jejky8LDcH9zDDhDKxQq05Es4n1srLSdWyJWxRl1+NtvMi8TA/Z2ICunODZ/2cynXstC3xzenQMLiDe96QED0xGL1kjrDxPt2xaizAIeNorJ+qvZTWO8Gd0WLQ/LBiOtWgwR0wXxQWdIxmwvo8s4myssep5+i7q+C/fJOW+Zx/FI+pCE2uyY+FvwItIWPWe4A/0iPtCO3QZ7wtNL+GhnkhXlX4MTZ2ip//kIenj0dcIFRUuygXSFJ1auKhIGVu4KB8Is+pbmJgTPggyVB+G4ITE6EXwOpoZ/hNCvDYSlq1vodmUGIvJGfgjzSQvSlHhL7X90NVMi6Htz0tq+yH5y3TU9t9o1Xz5daoVdskdixztvoI7FjnbfdezRTlS2z+f3TgbQaE13/co23G2qCB5J3DjfPEql15xFsdVKN+uYouiQEAPKm7+hwOoGrTad42x77Jp18PKAJaj65hjbI9aMTsxXvXNjpi7uMPPSyFj/KV28vIvhoVh32WSXJtyXThLou2+9Vv6dnnC9dk4dJB5pF8EsydFTdTdbmjkn7w8ZMSRGkojvsu+yywqHqWMr2MWLzrvQZ/nJi6tY4tsda04gLnKxGQ2M83w3KJLNd9COC/qmAm5QwFVat91KG9/YccvkEeMLqzzdClTwwcM4Rc7fN/fxF5vJnhBR5jfhAY9o36b1I8NGtY8fbX4rSuqoRq0sfJhZefYWE0kGysKkfcbuYJw4DWO8w2tEs9QDZY6taKoji1dq/kyI2b4SuK2Nqh6j3F2itCWYF2ca2wFs/QOYuXuuv0LSJ51O0p9C2KXwsHvDO+5SbReSq33PWmWmsgCk/Jjgmmny4hSS8QUGYPhUP4RSUbwigtQTtQ77qKIZ3ndur5imV98Zj9fgD/Zja5lfsQOX5Slb3BX+ivZnVijP8ifyhRXSFBToVneyAzQ1fp//T3ZxqWiDagPqY3B8E879/b86pH8Z6UmVXxOBnsw5QKe7tVRuw3njTgCrns7eb8HhV9J3q1jFS0FPF3JoDLXBeWd+CNfihk+GDEH+a3vJZvdKlxLZa70LxHtksMkJu/ngU3Cnyk39MLq9hhsIdXKAo2th6ML47c8ZIqMR4UUxl575MsnGCKe493hIbTResjf7UWgPpNa1cvbUWBS+qH1c6/iT/A3Hh1xHiN3KotZGUdOBPEuK7/8X4M6uczAyohmsiUWPy+YoaNrKXl6i4sDMzAMnlLV/KPOgpDWkUuuuB1QUGvOAX6rU8QhHQ2P//lkUI/vKwAS8wQlro5OYwcSkzB+6xF4pVXk8Lfob0Ft3x54EPGJ1+8f0rvbXEYw1z10c1CdHkWYBJAq1ijj+dy3hnVEwFlLkXT+gKK+KQn54ybi1VmKDgV+/t4fKOCHVfW5450i6qfFyFrhzusEEjMOOAMRDhTB06BB4XbIKiwU8z0tyDPCdMM+B727oMBo+64lmcVQ/34WdGkddxB05/Jsm3mC8FMYwxpcehte3NUChQqS16moLsjZAqpqxoWqYiNVqZm1KcbIFXKDBXnsViouWsinFtCLLbXHlG/5rVJ/PC+vs3Bxtu3Fb/DkuqdzVk8lq3BpW1u2mkUcwlu66LDCjpuVTOZzxR/Kp3lH38lzexDkB+ZT63aogqkx0VUrdhXdzVzx3esJQqcnOl67C9XCLV0Ir5ywaXf56Ve12SSDkXt+btlUg1b7MYtnzsaA578tsYpNFs919aWsHeO/tu5n25Gnil22ydJ6uGGiZzd6rsSu3mT1PI3+LPXu1v2bsmLwboN8t2l8TL4jb7p0csNIxmghm5MmFzsJQp9yXWGTW7mGKQXhYVLG/+gBshhBmbV7xQr71hvwvFnvZuNDQSQtueKQ8XQHWE1utC5Pr2ON+SG+9jVdL6xyI6KpWjWwaV5sVKHXtTF35EUsexMm1U/z1AxsymJNs2OjPE2nNo5n5TmeNzZlY/7sDdPC19yCp1sB/+R+g0XAgwayQ754U76JVWXDV1Hmq9txEtX25eSM41J342yq968SP+XcR+fHdzcStOOj3ZujUkmZqFO3r6Gya42yYSq77tyye+EZYYvayWOo3KG2zxcZ0GO1vYgSs9T2xUaiS20vpUS3Sh+NFg+1vpJOmP2v5Rsgb6JX5pByLXz9rPAZoohf/gLKwKq3x/fiPciWAsIkAcJYKcOi29BPwoEaiDhPjy6I87RoBnp5JCqx2B3UTYzqY2V3Y0/RCB8W5ovUKQd7gPpUakn/ZtK7iUvPLwE/t2DG9K4HQJh5Dw3recGQ0GsTdhSMsD1KS1GxdW9uNObyZ/BCTK2JEKagPZy9vMPAP9/zGutSt683i/QWfACOqAsOmHac/1G0G8Zq7fghR+Hnw178ida7Hpu0KZP9qZSeG0azQrbCkhjFCli1BTKpf8Ker65Vfzmf9CA0NYuzLaeLMvphgpXZ0CmtHbd0GPd55ah1o/CS6uif5TjIhmAvfNnNZnFQjgSW6jDJYFCrr0OtSK6wdMaELdclg5GKw5IXfzRI0DaI4lUnsW3kq3+ewRBPFErCWghHW62SvkS1Jm2zSPp10OmslfdX4nEyhow0ur39KDoTmhdIwoOo8NMbHPyNVcLoInY9XTcX8NfQzhgTriI2DwR0PuqszDOlsMamTKB0qpY/2T9IKI/9snp+yweD50QzMgJpJ0d/0xyMT17YnNMwCVfC+0DIPV5r9JIST3NO/eevIGuH2X4yR3ip46SEcBrG7NX1vNOJjy8woeMRAxOBrBouCrEBMrFuRfyrHj4FJmup8vlqzOWag6G79lyoT3/JNfo0jRSjIe4V5V/78xC6TkWzqHcf48XPAP9r7kjX8k77EokRv6GROvOO8o3JWqeTajHE/zNEtV70qfQczKBqP8JKm7HSFPXat/p4VbK2LNnHh0VtQMR1qocTc6FVFPF9/xjUjTKrzw9pnqzxne+cX+NSUePdyRpRkQtL4oavdarv3e+cE9bcSfe/Z9hSSQxDvGSNEWcuwEpcQfZ0vrSpGYVbBiMmIg9ZlOkrQojkbu8JcVfWryqneA6c5lAo/sjTm4m4bXLpd+bLCOV89W/IIcG2Wk4P82Z5vLmbiliVEw77qtkb53q8ObE5m+A5u/5qOOV1JV9XcnVldmq0Nf8yI7S4lZfD0kjYk0Th0N1IFGrgIBVDw06DpMsXvT+I2mttaQFebCybAHujxMKKsu07i8bAykDzri2IUaRZWnNNBKozEBQ50MrRYiZkVrbawm50+iXiDS4q1o/HRYUFhFvWReg0hSUOeytZmHSxt7s+y4p/lI54OPMRDcemLb8vW63qVyayRdRyodeq3Lr5B+mvJm7q6psa/9AeP2NBZ8FRSiWFWFLICehNPxnfP1tr2EX6WVW/NNnB9wIfiVpwLIMRBpXRfOeUYfTbf8ExLMu4CFnR3lqACmaM/DJgiTdZzfY4Kppqif7sF1AlxBB2Z+Rca5qZwhbueRChP90mjcwu+b2Kjmwov2YX/PXl+zka8NPCZQe6MwjGyHoUGVRW7DZc83bHLjLN3HOBjT/5GvI4ID0NHBGP79dl/Lzca5JBlYXffSiSTr7+J/mVwD+rzW7RT63WpXrU5hyCm8lVm/MjhKuoNRewg92+bDcZ0l80rMf/QKKzHMNXt8FKReKGMABOdaNF3egwItUhX90/nOJ7tmrXiO+Zti77kZYTT5LOrlpEeIMjWCt/OmLiy/FCryYGayKgeav9/OI0Q1f0OMlS1SCAQk7V+zzfhOZS3moBze4Uduis/PkA7cI0zfu0n7+ySl5v1wR0JQzldGUtOQNRYilG59kumI916gS2nYh6pYW1k6ty1Xo1U5BkVhWFx81EaMsbAxhiuVrqBbLYQGIS/aTrcpLJMVlXqvnBX4oRQrv8YzxTkCDEX1+1/zWXvDoQsFTICtpU78vMi3QLROe8o+01J1Do+vyJJ56oe+JxMrwFpqjbu1cQrx615i215hDzwzZYNqYSoyA5/Go5V2uOqDW9pI5E+8FWEmQ5TCba3wRQsnhypWFcWIU3fjXHWdNb8j6nwhLi05zEkbS2ywS15n215jh/2IrqVI6RhAjw/n0/XlWgWbvmPeHXlWNAa2YOGzWj1FtY06k0IdxZhYXPnIRR+4CBO2Kwer0prN5uVUw3Pr+vivnG5+NqO054Yl7qCJDaBvk7QaOp7SJkw0gvBr+SNPrnWAxmTQD3iyQQcOtY8Vx4g34uWChirmTlL/NgtyT2QeYFGbiI+L/LSksVH8ZcaLCobX5iyvvVtuUUMLeIeLMc8fYB8Vq9D98lPoIU6YxAqyFIrjN75bfjN74zOIIyMn/nSBiSDrElkDrRbujRGyzci8EYfJZRaCQq4SjgJU7qvOk6mRDFSFRSLg7yh79jbJV/CZyAYN8RUgTgd39+RRKYXYIIlL+FsKQ9fv7DZLmnJIepCnq13lTMvMej176IVCuAvKPLPOvBCRhUTJs/wYwsru5dz+6m3F2WhYVV6+vfXcm2xwRDOuuuzQLFwHwXpYidVuFS76IHsdvuonWwvdF4RQ8GS6veRQ/E/eLPligRwh68ol11RgBr9/D2b8TWir8eJbO74mpE4x8XH7BErfGBUVEQzdCfWoIlgdjKP/07UrOkwh3pYNExOG1r4FPEf76ceM6onS3xI9ixjX/aA8Rgkv6zspYupHGEgMy9+wmbCvdxE4E9K7YWgp7CQ1zBcNaPCjdldJt8hfD7kEEI8W+ukcxB09QAv+NiJDDozBhtQDciGyrZbIlprA1xXlgRfGob0UVPcVl0WreXkEXjTSDzY7AhvLx+4l04yL22xDxGbkoMJqrUU2qNXikN0eKI4WNr7Wy2FvrKYukYJc7IWGSlQHIYvbZGAlY3r0o793W3D8OgmpSxekMM9SdfHIHl22Yl/V1FWdcx29guwo+oNfhcEQBCiGEWVp1LgCO+HGCy12jbcBr0hlXAHfDXs6QR1U2Qz1OdG/XLMZc6WNBmgEJ+v0wphgoKvTa27ZS8+lQy8YMdGgMfZaz8elPGysq+R2a2ZEExBnoiLEoEPL1yWaveNIUpziB3ZtGsRxEGIE/HK2Kgotl/HB6xVRBOgTAdGdFa/jiJadEqdGpw4F3+ozgJ2FwxywigQSjqNmcbllYNuDynvy+zTCdSBhMQMeEUtMkp8POJy3ABrxwJtSGcS9EjG5F5F0EbrZ2xADq6i7GHNK/NH+DvWIfJ4RSXXfR6Mr3DOnnv4UE9hPNDbAR2c50ADLUTiNZLFAH5LegWBTMnlKqzZvs9nexAkZ+XQmvhx0hK/ks73XO+SxSqgPh5fecpuj+E3Xa+/MQ/40N6YY0zOjocMo3enIhRJAje+tdBeUIfFlAzMAqy7mxYo9Y4YfxdP3YilAHu34yPxVQ1TUJ0qsYpwyKg6APJExZ3gVXuAocyOWJu+RixBwNY+JuPyedjUng8XXxl8cTt0tFrFfP2QoJ915u0SvGjqO/Jj1IkvoMfa5gAzeP3wZA9H7yNB0MW2ojgR1Vry3R/LpUYj+cFfQZ+ZtywgR/Y2+3tMfADe7gHSqtKb4oYWPv24EiUA4l3bBM44cCOwTGlxrKtyiWFzbnKFATu8PM4rDVPtwpsk73jjySxl8Fxk5X+dpX2FHZZhd9VJvYXtblaX2aDfI7C5jKh/A5oa7OBdJZ5gCeza3Ry3oc76kUEcJzVo9nusO9ckn66y2xvxau/011p9q1nSQ+9Kr17cTYqgk321nFCy5YNy5atyF3GgmuADQwti6T7q/jdfjq6oFF7h0NgtMDOtW99VyBMZAMthSOuil901Ug+ju/uoyMlDY6UQl+pcCEUo/CVwihYT+t+tSzbGb0hHst2m2EIitvT1TTn3O5boPtF6TvM0XF5+xPjPF2xY2pFWcKGs7MjLWpp3a9UsRLUY1/NSqwtayzwhXQ4clv3Ry+GhLyjnj3RzICfJ6Bv6mqrutqirsbgB25WUZbew7qgvxVldu3lYWJqHStrgKAQVi/zxeQhyCqKoLapGJ8PAbGtXcdced0oOzjYwbwetcK6sgY1v0ZBOg4R2o8Ow99YDUvh5EFGsQ9WZsij6zoM2CS28riDgzpt2unE1g/45Vn/q28k55pBng/PJt0cSclpQ+unk3wTbGWtpEDQHD8w8BkFwOKrbbR253+CIPhOiViPdC5i5pvP6gb8YkTn9eIXcvBOKJLk4H/5RJKDJ9U8Vp8Ku1p9ANb6gdq+ZXAOBYICSi+W7YxgRJeNNgRat2q/Qcqv7+wwUyT478ylkyyHZI1tFlIQB7iSS6kT2VKXug19yhE1exu6f682RAsabXdGI4FCWeiIL7Hq63O0Civf9hzKpsCc42+qlI+ZhYhW2DRfch1JrmrbZoJ9JO13Cdq5qW3tyWe0eWvDPuobLdo2hHjlv/otBqXD7PE/YJ/gj5P+dDpkjGmqUTzL2UWFWbzT8i0UsXOjLzlaT0dt8sJkO9kQShQxDLnRZeUvwXhkZYzMQFGRr5rzOoHgwj9W024zMJnJv1nyr0v+tcm/TvnXYSioYUlSl1H/+AAFacUYxnz/dBAZxViKnKOSkVP+b/6wTiwt/vjTfAKxp8gpV84VUU1eh3KJ5SwjBOxuPsiJ4qKkgww6xTSPFtc=
*/