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
c3Rlci90ZXN0cy9kYXRhL3Rlc3Q0NlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKQPAbdXgEAADkCAAAdAAkAAAAAAAEAAAAAAFqLPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0N1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK8eyk6hAEAAOQCAAAdAAkAAAAAAAEAAAAAAPyMPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0OFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLj5wvKtgEAAFgEAAAdAAkAAAAAAAEAAAAAAMSOPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0OVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJpug0H/QEAAMUDAAAeAAkAAAAAAAEAAAAAAL6QPABjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q0OTBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSaTsphR4CAAB7AwAAHgAJAAAAAAABAAAAAAAAkzwAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NDkxVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhT3bFhQAgAA1AUAAB4ACQAAAAAAAQAA
*/