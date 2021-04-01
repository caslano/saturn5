    ///////////////////////////////////////////////////////////////////////////////
    // class_member_traits.hpp
    // Contains specializations of the class_member_traits\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename T, typename U >
    struct class_member_traits<T (U::*)()>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U >
    struct class_member_traits<T (U::*)() const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0>
    struct class_member_traits<T (U::*)(A0)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0>
    struct class_member_traits<T (U::*)(A0) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1>
    struct class_member_traits<T (U::*)(A0 , A1)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1>
    struct class_member_traits<T (U::*)(A0 , A1) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2>
    struct class_member_traits<T (U::*)(A0 , A1 , A2)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2>
    struct class_member_traits<T (U::*)(A0 , A1 , A2) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8) const>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
    {
        typedef U class_type;
        typedef T result_type;
    };
    template<typename T, typename U , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct class_member_traits<T (U::*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9) const>
    {
        typedef U class_type;
        typedef T result_type;
    };

/* class_member_traits.hpp
xx5FgZOJEplRDJr1ZUOWj+OKR4iSlr/0elTGA75FN9mAAwO9KAjZ8llbAUtR9rp6pzL310bYorLpmkHaZuZVqOfCZvGOgztLmgv4IqAMCziB4y2OO8NmQSSET4msZ/BAVTfOL5MBdRiy0u1nNkCWy6Qe0lcj3ZfeItVWl+lhnWD2WldOgiYq5/vaA9CvLN6Bcg3aKV1Fr5jDFByC4aiwL9mtqH/ncrHi3CDvLazjn0lomna0D+25spgljwT91VlQ/QrW+P2gvzBo9ruNr31iEPMAtWhMTXH1SyalUBiB++Ct0YKgVQgqIYGYvJOnWKkwJkaJJAYuYPHXT+5/hqC42fjN+epTVKx1NZ/pQhEzqRDpFrRt9zt8mA8tADumn535h4DwTG3dxKUP14mFrMOEeo4ixTKgu3li/SxbQ5fQnTcdj/ol8kSx12Tggp3JhxSlgZ59XjNwv88Blyl9e+UhBy48E+eCh++1V9CnixQeEKP7oA9uZ3KHUklWiLaK4CetzDvWyFY+BHs4tqS5PaghPjYrRucM37h1MYAoXMb5EI7IWkBIn4eh66lXvA==
*/