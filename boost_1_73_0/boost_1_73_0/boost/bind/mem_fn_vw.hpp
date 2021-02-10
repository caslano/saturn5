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
Y2vkqSUjNtTHGT7H0/7HobNBquUCrZy/65MEk4tZRQYvTBqDgWceCwJzfDAZz/qj8XDq1Aq13E3Rtsm+Hgv/n+jrlDYlH423CE6E5jJDTKTE1ss7Wtyh9vpJqt+13gaRUvmze+CyngCFDTbaIjLF/9YwbWCTOVq2FHj7oH60gnMb95TUFhozviARvKLzMUq+7PXcusFz4Q7yUd4UoK0eAe01AN4O4CdYA6gUFFXBqYRqPckBd7x2H6LXcJz+ueRhLV4P2P1G3YRv2Vp15FjFRJggvqAwCSpe6Qub4d+0ONzmN4gQ21U+8QaISUf9wQenwu1WVcAbpsX5qQKmsjfbaDQ3FXUtahckqDnqtYr7wYqZTtdp+mytozT/jzSEmrWRDNY/3HKvmenucmWkoob0qH78F1BLAwQKAAAACAAtZ0pSTY1qVvcIAAAyFQAAKAAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvc210cC1hdXRoemlkLmNVVAUAAbZIJGCtWGtz2kgW/e5fcZep3YAjwHbiPPxIhfJjhooNXsCVym6mqEZqoBNJrVG3jJnN/Pc9tyUh4TgVfxjnAZJu3+e59x65u/v3/ezQLv30Z+r+TfGDT3fiJtVfpG8fl55Ov1H+B6c+4/NnRrpU
*/