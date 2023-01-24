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
nN52pzKnV9+pndPyFO2cXrC0eE5PRMtzeiT6n8zp8kEtmdM1b/3dOU3a/Fdz2m/QJc2p4+1/a07339/snE66Q57TLVOUOX1yijKnw6cocxoxRTunn0zWzqnlqhbPaZcB8pyGDPgnc7prYEvm9Iu1f3dOF2z8qzm9beAlzWnmm//WnDbc2+ycjrhdntN3Jypz+shEZU4HTFTmNGiidk7fSNbO6YTeLZ5TW395TmP6/5M5/T26JXPqeePvzum7n/7VnOZEX9Kcrlrzb81p39Rm5zTmVnlOX0hS5nRGkjKnXZOUOa2boJ3TZyZo5zS7V4vndHY/eU6n9vsnc3r5gJbMab/VLZtT1eiN8v/HTcxrGZvXMpT/r2l2Xls1ntdklP9X47y6ksPlqY2A6WQQjs2fymZ3qsD+Eh3u3i8lQpDpVQ53/6fHwK8HQSe47AoZyj1ijrBC/4NC7v4PQtREI5jPlmEe4TFf7IMwH8H0nz5+YD4AvsQ+wYOLmJ5deHkoTICU+aImnGjAKoM8GfE+k7Gkf0sm45XX1cngG9409vE9e5rURWzFf7XOuvZvdj5uaDwfK2E+hqzyWme4xtgfW1QjUmCNsT82IyOS82l9sT+2kJRFxi7L6JKPS4sORDYMHSuvqbCxqjyTqKypEYnKmvpxDP4EL8DT9NPC5nlgZLOrKUme2ViPuZcFZ7afx9zO4mdmO2hXU2Ikn70Un9k7
*/