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
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
*/