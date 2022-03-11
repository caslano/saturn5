//
//  bind/mem_fn_vw.hpp - void return helper wrappers
//
//  Do not include this header directly
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

template<class R, class T> struct BOOST_MEM_FN_NAME(mf0): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf0)<R, T, R (BOOST_MEM_FN_CC T::*) ()>
{
    typedef R (BOOST_MEM_FN_CC T::*F) ();
    explicit BOOST_MEM_FN_NAME(mf0)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf0)<R, T, F>(f) {}
};

template<class R, class T> struct BOOST_MEM_FN_NAME(cmf0): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf0)<R, T, R (BOOST_MEM_FN_CC T::*) () const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) () const;
    explicit BOOST_MEM_FN_NAME(cmf0)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf0)<R, T, F>(f) {}
};


template<class R, class T, class A1> struct BOOST_MEM_FN_NAME(mf1): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf1)<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1);
    explicit BOOST_MEM_FN_NAME(mf1)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf1)<R, T, A1, F>(f) {}
};

template<class R, class T, class A1> struct BOOST_MEM_FN_NAME(cmf1): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf1)<R, T, A1, R (BOOST_MEM_FN_CC T::*) (A1) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1) const;
    explicit BOOST_MEM_FN_NAME(cmf1)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf1)<R, T, A1, F>(f) {}
};


template<class R, class T, class A1, class A2> struct BOOST_MEM_FN_NAME(mf2): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf2)<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2);
    explicit BOOST_MEM_FN_NAME(mf2)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf2)<R, T, A1, A2, F>(f) {}
};

template<class R, class T, class A1, class A2> struct BOOST_MEM_FN_NAME(cmf2): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf2)<R, T, A1, A2, R (BOOST_MEM_FN_CC T::*) (A1, A2) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2) const;
    explicit BOOST_MEM_FN_NAME(cmf2)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf2)<R, T, A1, A2, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3> struct BOOST_MEM_FN_NAME(mf3): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf3)<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3);
    explicit BOOST_MEM_FN_NAME(mf3)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf3)<R, T, A1, A2, A3, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3> struct BOOST_MEM_FN_NAME(cmf3): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf3)<R, T, A1, A2, A3, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3) const;
    explicit BOOST_MEM_FN_NAME(cmf3)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf3)<R, T, A1, A2, A3, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3, class A4> struct BOOST_MEM_FN_NAME(mf4): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf4)<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4);
    explicit BOOST_MEM_FN_NAME(mf4)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf4)<R, T, A1, A2, A3, A4, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4> struct BOOST_MEM_FN_NAME(cmf4): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf4)<R, T, A1, A2, A3, A4, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4) const;
    explicit BOOST_MEM_FN_NAME(cmf4)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf4)<R, T, A1, A2, A3, A4, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3, class A4, class A5> struct BOOST_MEM_FN_NAME(mf5): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf5)<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5);
    explicit BOOST_MEM_FN_NAME(mf5)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf5)<R, T, A1, A2, A3, A4, A5, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5> struct BOOST_MEM_FN_NAME(cmf5): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf5)<R, T, A1, A2, A3, A4, A5, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5) const;
    explicit BOOST_MEM_FN_NAME(cmf5)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf5)<R, T, A1, A2, A3, A4, A5, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> struct BOOST_MEM_FN_NAME(mf6): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf6)<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6);
    explicit BOOST_MEM_FN_NAME(mf6)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf6)<R, T, A1, A2, A3, A4, A5, A6, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> struct BOOST_MEM_FN_NAME(cmf6): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf6)<R, T, A1, A2, A3, A4, A5, A6, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6) const;
    explicit BOOST_MEM_FN_NAME(cmf6)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf6)<R, T, A1, A2, A3, A4, A5, A6, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct BOOST_MEM_FN_NAME(mf7): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7);
    explicit BOOST_MEM_FN_NAME(mf7)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> struct BOOST_MEM_FN_NAME(cmf7): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7) const;
    explicit BOOST_MEM_FN_NAME(cmf7)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7, F>(f) {}
};


template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct BOOST_MEM_FN_NAME(mf8): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8)>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8);
    explicit BOOST_MEM_FN_NAME(mf8)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8, F>(f) {}
};

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> struct BOOST_MEM_FN_NAME(cmf8): public mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8, R (BOOST_MEM_FN_CC T::*) (A1, A2, A3, A4, A5, A6, A7, A8) const>
{
    typedef R (BOOST_MEM_FN_CC T::*F) (A1, A2, A3, A4, A5, A6, A7, A8) const;
    explicit BOOST_MEM_FN_NAME(cmf8)(F f): mf<R>::BOOST_NESTED_TEMPLATE BOOST_MEM_FN_NAME2(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8, F>(f) {}
};


/* mem_fn_vw.hpp
mOHqeESZb14+eRFLM4jzQZWAgT4mVtcpK4QW/gFZmNYeTyRrxmhYl30tUOFJ3AYramNi1ul8jCq7igxTY+E1VhfnexqaYTJRcVyUHEdLoiRCVNOWENTfbt+FaZ4wZnYfakOFYzsU2FHPPUKoVkAUTWRRHGuUxtlKxH86gHZorMH6w988vIdFnoZasysaa9Jzubx9szLRGS7sus395iqd6mlM2ZrmEENe5hHuMa6QUaX2qLhZzhAgAHkqPMCTIOGJTGAfa/x1NKN3aEyIbKbiFUALgZd9d0nnUrKc/VjnwqpXEunN33FwM8mu47iMBpEwF9hC0U+s3UXW1y8i8v1Z+dTKaI7QiRjvdo9/iAi0/xHFV95LQCjoKV5jutSr1hGaO8sfrwgIEZVKYcg5Gl5KCRTgCcjT1RmJ12tB9RThbW428NmHpKwWhsIMERErHoBhBSee0YkBXrJbYaPvK+8mIBHwm1dVX2v9HOb954Btf0C7waYXtWw6qL5LSM+NUx76jNR+cPa2ebDj38fRk47RkIyShJfrBYMZQMwcftkMIcX/RgXbnXJUVzJLqnQpxJ4OGVGc/Kup/bxrknNUE5WXaZe0X0I6/bpsQSWXGHn+5uFZFzq3z8nX5BuGftOY4JVWoQ44AgNtO8hqS4dpVjKPKNdW3mps7gEH658Dml97Bz3Cfl7EuAd47vTZXIQTjDohtL0k7alxMT5L1DHCG87n/iChMPo9XTJR+CN/MNiHrldHnk+dr1HymBgsVFLmYeu+kNtFY02jthcSBNMNHuX4LwmFZd1K7xuKL95C22H+aG4j1C689GW15OZwqUsHP0pcY5tU/G6klMSjtHot4NsNMsV1wY4WTJEy/Nav6dxjMj3kblsS6gbGM4xLsNhuZ8CTddLWGUYXaOjYloG5pOkmIMYmI1QgVaOV7b9XSpDatxTcuxBma1hJLLh70G0oH3Y7Ar89cgiAxyBj8fC5NAFoHpMONylw7eVlIrWFgMOaIBgZBuss75gPNupcbTV1acovJrhLboqZ1VKyq7SypZ5quwyOrBcn3Q28aR/bb0Rc9m0au+28U0O2dFoU64/MoZdp0qlfTi1umRvUzA2tRzJqdGI9UgaxXXXey2cmStm3QRw4DYs0NCBR4s31g01+j6JD53XbResYABmYy9Tp+9pvWHYdbMQI3Ger27pWuuqq5cLGeOIkOCNwCjEcmkpud7Q6OT2QrpKKxwvf0cipKVg9yjyc9zT/+vtqhnCLVMEtDZzZPJrpzRehX3tv9pgir9shXHoHYU689Om8lMJ99i+7tMBTcUcxJdrAITvmzkAAGxGk3BxgRx0o+89UU/zSKErakPfxjzBV+corRzlFhIaTnMKKjJwS5US3NPUDV+yjDarQEdOLMYwbDUTTvsfhscPsTg64uzNU4S4+LLi5n8+WLGv4SBM3b+p4TMjg3KquJBLf1S8jngSYv3f7BtEsfuW1GkaXLIv40NVW2VUSTQki/4SbCoJFH61iv9MK9XCEgQmjCGfuiC1XJwUPQhTyhY8x+uXA9kwGqsSvZSQeTagu/2KE1C83QHVTI02ld00hOhsnPJkSUD83YO40JA4PCh3grwThbU+TJy2DX64OsPZXsmyGKdtTjLCjOLdCcDoG5+FObYFiOxOyoI4x/TPOxBEkWbhhVaU7r1NJvmXQpg4FPcBtDZGf4A4KK7EVFWWc4ldlBuu/8I3z4I40sz6QxL1t8Zs4tqV/OGKifez9DCXhatvhGcAIV/eGIvmLLcoCrm3Mg8WbfDo724W1Zj3+UK9C6Baz+HeOML/ZYiWR61iboz05TGaM+NAEbVDPkHZXeu4DzoInsQVEon8urRNkDQ1/ksUvS23H6NwpE4AA/mixnktM/QSBEZiISN8oDymrHV3npl/JTwOcJwwBQ6FBxSAEp84kwwu8GDQPDhTJ+INqqsGNtJJVnqDGvNyjChmsAE1nV3z60DgAULpA+DvNYwhRhMhanyRu/oa6BKaSSfcc4nqwb7C+4zlerVJqCIz46oDVB12flzLbQfuO6zxyGrQ2xeAuLJA4rcxsWzUWVkrlwKgdx+GPLECES93wPIeboj13PM0REV2MhDzOeBa0gFVzhPqu/4n8CoSxiW2Y2ZQG03J+2FxccIk+u8gRwp/QZgCTFYZEtQ1+Zm7LMcXWWsXKvooJUbcS3ML+/dPY85q8yYeM/ATE/slmi20KVwtHbhJxY+wMIadF75MiMJuSBC1cHa1SlIR0rxrF8f1G/saxVV7liJhA8EZQnpMKUjvBZ1KTOzM4OR3uosrYpK966LNBgpoVbgnxF7esAVybhIqjmZytHdXdbJ7uEUg+LmdietZza+R0OjmtLt6FCEC7c2nJ/AaB0X+1qxZdJNDSe/jlgE/P9pDjbn/4WNsRLuy25hawtYtOxCqFYiMP2vchKoFCngYq6+hqCDi/ELGlHEF3StCeOCcbydGBANSn9s3BWtHfJl3jdUb26SWmOLOLQtEOBzmR1k91nrHabBoWTLeN1sktgz/C1bV5EqXY+gzkx03wKAulzUjM7VSvcj49CyjTmlYPvXXWqabeRBP95MJAQkcp8eceEiqFHSWj7G+6TUcNSsc1tWnIM2PxsJNCP7j5pT2iN6LYVDCcUxmVfx1OYHUaWLGUohSPw5XGg2MdpZaqy6y/SML4fFaSj92drzRYqZ6qW6copJk+mK+Bvpz4Sk1C6HYN7ObwnEuPeuyKfdBKeFx9tV6P0MZVKmXHnx//SAtMi2gaJaGCDPp7gS7FroOtL96bsrbZ2M85dscoJC6ilKt0WJVWfyYCU6Ct4CZgyRGTU5fzGw0viwKnMUOcZ45ewCcik7uaKLroOqyXfE/0LV7i/wDHv9Zj1n8AgENLrZ3jkjBMz63Htm3btm3btm3btu17bNu2bXv28/74zmAfQae7VlauVKU6axMfFxqU2XwrcUgjhVhP6E4bW4saW3wNYXe++yHMc3o9FcvUKkSXpR+xGT3tvqWg9uZaPUl0W1wt3czSEIHB0YnZpUYT17nNngDUzQer2wga53th1eoVS9RuOnijEI9EH0cbNB3c0M6Jrtjax1vbNfSRksbTpPCgfjTy54t/WdRx6alkG5r4j1JoXiKe/9I4hHq47PMMRpyEtAFUI+GuRrtr2G9uNHqSjG+YgjS60IAdYUoPKIDytluJ3+K8xoeeg/FQExDV2hGpNZ1EK91we/Waz0MDTMTgzWAg80/TJ3SWoRUDqsUvdqnjX/d9J0m6X0omXV/SDrw9Oh8HvJYYelGMnxkPme9Kz4RnnDLCBWYGZ1oDJt7kIbwT0NwBoXn6W3aeGnI1zBpHL82Bmvoqh3jDVvCRETyiQFnFFht7im4xx+zcbm7Gp/rE2K3rLbyDXTOH8k1uTC0OIJKmM+xRCgP2M2gOIitHzWH1eMKQVXpeQognqHLIjXdsUQiBFUELVQ0XOyT5/Jtuyw/uD0l8wHVeRUw61LETYTWbRvrJhCIk+fkrR1ObSibCtTHQV6c2v16924D9nnfBzx+LWBCpm+q63h6b1xxVqT5wHtk8+auaYdAkATOjxgH9tGYCGhhjPFa5w24T4/RwmBfuxjEZO6J/i5gISqZFGyzfOdh4NqKzAhrwSFwaw1oKIS2HgUPUdbsZlJorsC7OVWimGXIr1BVqKWzU9YYTKfXSUrFPJZ/CXY3wWhmvfLjtwDGn7nxLVkh5Y2y16KRXxJL/63f+fVTyAuJhK4JFlwSM55bODzEBIUmhB5Lc7P7oUIMDP+CnTffDH8GUOfNoeV6H2JPrIZ6Z2rrXH8M1McFGzn2Gwow0+JDZQCxGnyY99U9j8Ia1Zo0cAFPV4+hfjMjxnrJFwtHg601wVCM7mnA73xmvRTvdEWsy80Dzp3X4gj/GE0j+nlLjIbIkgnonMCB4Q/GiJDQkPn3AHyQUSYiBqJ5x9N9aOH4VTNKOpbIBt8sUhv5zb4vMKkxWU5sCMaGwWu14t3HxxT0PysvfQ07kE8VSnFBfbnax0aG7dW1uZHI7fEiO1Etj9HnqKNNjZAYNsfXZ4tU2fU5QRyvQywQwRWU4BR7337SzDefcHEVnSJpT8w8TT3Y5XbDHIrukQgF/YCKGYD5rrrXlTfSpUFA5xH1Gz74Y5Yafs18P10sZcvq31VuO3EPJ1xmsl+paThmqKWGR1UDokZCQT7TvVB9HAqWOhPYx9EKtCRkc0P0phcubdIICPAky9tiU1/pWKN2lE2qyN5G4BO3A2DCmgkWwF+Xu9/hgzxR3VyHuqqApoSLBZxsgwhTEwIy9sd0wMCMPIiHB/H26HT3x/LpP1GH+2pFnx0CT5mP7clqXmlPjxTrlpWNcJ2QnATxY2PHcDXpeJzuzyFCa60b38QMAwAG8SOYLFM2BYTNIH6LMlOdZE3ewK/5tETl2M0JKU4XG3ubwR/kHYcRCkI99F8xSCUTELUdgskrquJpNRhpHhQZpDraZ6TnWPeVtn6/dN+d6UEXERP4nI3E7uCLqkx33Isdk2IgqzTYtyqEQ8TVjgjJ/osfk+qCW7ua93TKxcvt83jw7wRQ1EBskNNS9Wte214aregYJ4VKQyVtLwnKqjH2YK8Nqlhdows7Fpyeaerx13LzAWEVQTUCvQNrlPbtvOUkDrAsEnS/sn/7cLeUwQTHVk5cgNt94bueZ14ZlBGcKBvLvTQTuKGoxHH8n2ZCgUntYI40nXxprAaP2/KyNa5bTF23QBbUqZYVGckqSj+xcfd+iq9DovpYnLXkupBji6fn1tfOn/SHPG9/Jv3H7P8u78VHAONvKsIQupwexPz6cKCbMnbYXMppzKaTMkBn/7ODFcMMENBTIYEzvaxtTAQUdUK0JcDNe7bMeI/QpvYhgqWFteK455y1FH2GM7ipaoXltYokh/xEimzpTjzqnvxhrSd9XYu8xyEq2nRU+fIZ+8uBfBPmvwIi83TYFzhwPEWOa8xjg4ovHA46lirP4N7wdXAx2akta1kFJZ/DRrlSEQ87k+mjSoP9ptS8QRRorCVQARKBojgrZwfPdI2HRZca5OldcROiMJa+ee8HkVYmlemO0teAMniyWhYXEqNngJj93PRaFFtCHCu8dQRiePglXKZjUW9tUuJzls7Irdw/MgRw/YPiQGfJdCZ5Y/zNd4forKjC5waeeHwQqCBrUW1i0mi1+wI7dp9i0UImBxsqUGXcZwmNihQhkYPCRe1IeeyIK1EPyHG26CePrRK1SbYVsAIv18EAcQ31oxPBXxr+SJ6NeZeCNXYj9rWwvvmbZ3qO2QhMPoIA9csKs13s5GKnoqIOCJgRjdnE+gR+C9YcCX6kuf1iYw9X4l5w+1t6SfbEP5BUCQORvCDj/HbpUCoA/SjBLzc3lioe5SHVhnggTnHgBqpMYmxEgApkhIYMkccms5KUZyxSnGJ78KDt3OxZhUJxnDmQtcWEqGjuoaF+h+Y0HFlup+awsSqm2YvRZkigrvHEtPITqIw6yDLtMHSfAYqgNOVshQLh2b+anTGmX/MbXUufkhA5zYmlYlVqO/BRGJoMd5v23gIByIjES+KzsVfpIHzI4yDub18sIaAhE3G1KdaymHgiQwiM4GAUByeX2vdXGIp6PFcGOhc3JUmRm2CQFuNFSi2svzWa+TFPWrMcxnTxnz0KivNh9+Sj6HpoFmgppHwCMJ05mOsqytkzdW+tgeb8DHyydESoTwfxQ0L+Vq975Fvh5SD8TwgEoTcKILW97cVj4WuL5WN7YMrQfhG95vqzyAAYs+dPVNRhj1qEzD6aYhImtBmmKjHgj0W98a8PLqHgYkz9XOEKNjEVeUbCB7IwUy/vZl+OOs75FF4GyIpFTIyzgscBK3mhCpZVlJA5vLOVMyux3On38xo1lKiq1Ul7ByhxjDjMeVooVpkofw3FGlx9parQ1xmRx2RQjlOax1PCjgb7xtc+pbBPn9BJnng6VyXHDk2fY65HFEPa7gIQyr4LJO1pPeEfGeMR8+FB4yFel+WgbhSFKgQOCkGVyFOb4PFWlipAxjjeMw2sPfyu809pBuSR9NiiCnRYDhirFBjvAso6+785Ykda4x/CJwXwahBrGLG+BOZZKwak8EissKTMqiWVr0uNTt9Zz2YRMEghZdZA0nfpqczPOUwNu+H3ba1uBj0ZCgPMu2FqSUCq4yIAM1KkIkTMdDGJaHplkVVPSxmI4nfCDCB0dnL+ZhZF9BiKPhSkrmL+MeMyATMBEJeSNHXbS9G/hPhREieGuU/YCIt5qvVUWXLdeBytHFtuWwDRGA5hYiE5a+G5zcfdMjbeXfUgjxAgmHZbRPWIhgVLv6xFZgMxO4VSxGSQljuDE1Ldy7yeBBNRPSCcSmPzsq2G4R67OatAIhAuwzwMZCBqUDCb+60imjliEB/SilA0zTgGkMUfnYYPzMTwBfqB+8YZCXs0Qy6Bl7gRL5p7PlaYsHbapxMKVAYlXxl9CZSrnVA5jjnDvGHJ4biDC0lOc+Hr/121tMeYujBTmqtzVBLgUc9iZKa6Yc1vga6dnq2QN9CdkfVq7pioV7Gf4iOxIVUcHHFt2tTYYcmkShG8Th+fKlHl7ePomI2tyc/wyaY5VxxalO9iKeO8LgRXJThDsZRDpEOMTFkzX2MfVl0ryCB8Yn7myACQw+C0qZ98OFCJ8OtlZQGoxplseM4BzOL8kACcKpIQ+MzFySUbYV3S5FYBqUJRXl9q7ZQcvp3kzMrIjs0EODa3TELga/xgRFYReyVC+pLaHvNgMES22gzCHhf/CKk1IzHnj44nQJUdf4Pwe59A8puRSVf/UwnvZA1MDiGIufsAEKc36dTaVmxBnwxtfEqskkC3j49LOgaXvQRgENh7xQ6m/OuE4Tn4CCQzS/gl8B/rUfjMwHPLxi5DAFzHWs4WbjiCCo18AZuC/DNegW2KAa3ax9iE55BvSYNxivDsfKQpktaDrPoydUFktsKHJrXmDT+nqwlunu4x8GfzAIFHXJAy+skqr1ETBstSdobKFcUVFdtmMnsumP5i2Z1PHnHAYSv6wuTMm1xM90YvfNk07ENO3D06UxY5WbGPZROpl7zCkxus44o1hwa+qLBmWCcwPoTCpgXPx5jA0fQ0E3KCJjiWAOIZQAiOKijINYQWwBEUEtFQzAp3Ci5LxbJG9KoRbC0qlrhZGwifm02V1PJ33gIi49nQIFVdvzmBDQVDWjRHr2K5IyHD+XMxsYr5dqWHICuoXDdTrOHJ/jXlXj6rV65iUDkNmejD72p6d4FShlps/cSCj0sbhdXr77u1ugNu1v/c9S0Y7G1o+AyXFTL7S9EBMLMiDiHTZ50TCno0py7eFBCyMGhmpIgsbAwGZk43ohxy/LRJPqEwWNBkIrai8GaBcL7bUCMfVLvFjZKlJPK+SRI7iQA6wIcBzfZZ6w6lj32zqISUmwKTAKwAt7Rymbpke1ZY8xkWUW3cMrTiw8MaHu4vXIctXijgjzREiMwGAAgMN8cZ/q90FNmN4oRKOgeEYGlCvZshlyjTFKwQ6G+qeMzhDQclnufcEhANy9iDmA/GtMJLNHUZG/IhdiKQTT6iIVVKl2UY7deBpb05fRNlEkDivrx4R56o0M+RQ7ocbGzMNpeFXI8bosne3dgnRhX6IHTxTwsqe4Iw6P3HKqdnz+9t/E5Fom7/PlG5jUhpHtxIuA+ftAIHx/viAZt6AEVsH+/i2EcZqhQ09Dvz3WutMx+eQNAvXb5FESXZkmKIJ29Kile6hQ4bNY3L5HYQUjn4SOwlNGHqhoadH/BiI70bQwFxWRIzAA5Pfjv3I8YOL224iOEPHNYFoQg9pCWQUkKkQKaHfmslZq1WimjBIsQgJ2NhdfPMIWsHLrQ064XGkOUT1+9DukdvkeMoTYqWW2gXuTZRRFEknH1bc+OxIsSFfQhvrRrJZeJ+N94+1P9YZ9rbqCD06aYHZjo7TrojbL7D7J3PCnOH8lHk4OuzE8bkg9Y2vqLNAKGKFRQp+jieJ8SFZlnkkbaLpiKZ5oMX8bvSJAg8NO75ZoTPEXCP84Dm5V1Ect2OJkKAj5h+2LhT4DrF43LPYTUvwRxIQUWA4PD6dFwihghRlJ3mAcuUNB1K3cSJ0FyLUWRtgB5UIUdWEnQi+ueV6/2pCZowhySFnlEpHMG3PbSL5h9ftvv4YLGho/eHjkmWT9iwn+KyZ45uOOOrPLThiIUNY0Emi9FsjH0taePLTT9NboPa7I5eAmChiwvZHLNkECoit2lGTZc50cUztdG7MUwMPjjSy6hAecToEBVwjxIX/cTjqmf8AYogrjHiiAciG7Lok4AFJT2l1NfTNwh6+GYtRaUez+SoE0yKGxWHcUJM0/pAvCx7X/aPyEyCvHBFKzEucJcYxIhRJW1gyVzTXoK55leaDtjwEZyzdx6CQjV7glmT79tSa4z9DQpgivZcudT2/IBJSGuaP/TDHVeosBmXeY298LsGxX1QDKy99dWpiF1gypdCBQ3YsS5AjVlkenuky0zDC0zfVZweMdDjppXceqFChQlwYLpv3s+lj8/HavA278aNzkYY5WvymvZfPtT4+7+KEAAO2xAVGxbvRrw7GC6YgcmgdjnI4WKoMSCUUBCKuTTN2vaBBIJCoVK9jAhpIu5DJ0QQShmoHlDy5VcYogxPzl6OvRvKiu8iEDx4eWnZsK55hL9dOFvQ8XngHQpSBWS73dXPZeldptAlR5op0covzeOFXeUXtyfGhhfDXOnA3UemuVme7dytcTf1q7p2SBY5SXa+cUKzuhDS08roFGrwsGXxxIljyoUwHBrNx+sz4bw5Po1Ts+Dfzmpp5WNCh74yCN5GWHUsPUnGEsL5+fBjWnbSF7YaAef9tHwgIB+aJEyZ79bPzKk3x/oZWY7vYaS8PYyFEcq4j2h62ANY6efKHgpTd/oi51peUDlT4u+lpYQmVxWKMoRazzDw/v7pYcMQTbiIOoGFjgWdn4sQHE7sp4bYESEdDryr17tJQfd2mZnWfO2I9++DLq3y8+ouan4mCwkYeRSoOLHz4N06UOH82/KXqCY/jhXBtHt1V0T1RoMIUNYzAifQw8yxrn5nAADTl6NuIXmxYr6wAGwMTa2vreFMWAZclqCzOWjG4EEWBCALTjp5UKzRqdi63t7g0meDi+f4MAxBBl6ZzpP+bBUhcY9eKKBbTyrE=
*/