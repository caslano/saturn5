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
WvfDMCOSef3drLnsd/101qRt9T5964k7O35367pVd/IdLt06vvX2u4ZfXS/y26H5Z947790z81hHJcdHTshP/kv24fSGpa33X9nvyO8Y9+V4xJ3F7dKu+HJA8pHkZi0emfmG07pXp/WbTutYT3xdauh1uE7rdp3XyV7sto4fHHpu64Wdb1jz28RBNzTc/+3H3Ft1t46/fNkrz3/3xY8PL1ndpuVDa6YzBqyS48lPLl1ztH32E9csHvPLlY89+AJ9gayTffGyTS2/+Ef0B01+3mxG+7/Onui0HtZpfa7zOtYrIq3jd0x9tl6Tld880G7bq+06bxwzmD5M8nPRY5dtjn014Z4xyz68sORI9u1O62RP3Xpkp/W/x0T+6L6nom+54qqqc17/Mq94eof9Tut8ndfnju1pHT+wJnVD953zjl51aPOjyza3+QXpS3uV1sxd+cXBTs+/8pNhrdP/0v93zuuLY6Mk/ayfjfjw3pK+Vek1uz87dn0n7n0l/dNfzW9cctHYq99uuLI0rUvWzz3rgvUalOfsbPLXlr8/sv19wPa3Z82HfteGmbiigDUfN+oag5/AWLgWJsB1MBneAlPU3x7eBDvDm2FPDe+j/v5wPRyoxw/BaPNtl2/Yev4UeFTPX4acxXIYCStgI7gQxsNL9PyL9LyL9XxL4FnwUvgjeBkcCpfCEfByOAZeAcfDNXASvB6eB6+E2bCS/y+EV8HZcBksgVfDRXA5XApXwGvgSrgWXgNvhqvgJngtvFPPs0XPsxWuhvepX9tDv2MyloRojw8IToKfwk7woJbr77AIfqH5+xJeB7/S/ByBt8F/wI3wa83HUfgE/FbPX+rSb1ewQM9vn8OfpPqQDFvAVlrfp8N+ME3rvQ0cAlO1ntvCc2E7eAFsD3NE3rtWVr8twWZ6Xvta2QdVD6phFPyl5uMheBr8FYwVv67pc+M0vW80vfYwDXrXcjaFA1WPB6l+TtP8T4eZMBMOh2fDyXAoPB8Og3lwOCyAI2AxHKn1fw5cAEfBCjgaLoFjVF/GwmVwnOrNeHgjnKB6c6620wXwbs3P/TAL/hJOhI/ASba1o0+p3C54HnwJToavwilwP5wK34fnw4Ma7wuNp2vu9LsEZcMVBay54xlW6r0bjIPpUJ51YG/YC54JM+AQ9Zu1TJrufE3XvpbpIk03V9PN03TzYT84R9ulEA6Fs+AoOBuO0/As9U+BRapnxfAiDZ+p/tnwYojjuLnu9J08fUmI6+425JrDjTAZboLt4R2wG/y55ncz/BG8C06A98BJcIvqzf2aj3vhxeo/JNe6vpfW9+NFuJb8vVPPP1fX9FdA6/hC2A9eAs+EG+CP4KVwMlwKF8Jl8Aq4HC6HK+BNcCXcCK+D1fB6uANWwd/DG+Fu9b+k/rfhWljf2tsTJkErXid4C8yEG+BI+BN4SNbP6fs/eLqWK4G/H9dytdU1sB3gMNgRjoKd4QTYTcvTHebBHrBI/XPUXwF7avky4CrYF66H/eCD8Az4GOwPn4MD4PNwIPwjHATfhWfDv8Hh8B9wJIxwy5pCXWuk77b0nVtRwFqjSF2jGAVTYQPYG0ZrOzXScsZouU6DM2BTLU8sLIVxcCmMh5WwBbwGJsIfwyR4C2yl+drhfT8CF2g9t+DvbZov+ghZC/ckzIRP6XW0U8e7Z+A0+CzMhbvgZfAP8OdwN/wtrIF74UvwLfgK/Bq+Cr+Dr8HGnPsN2Bq+CVPgPtgHvgUHwXfgCPhneC5819dP6DM5DNFPjKW8iXAcbAMnwE4wC/aCk+AZ8Dx4PpwNZ8MZqicXwstgrtZrntbrTLgG5sO1sFD1Zxas1nTM2qBnzdob7qX81960ta8=
*/