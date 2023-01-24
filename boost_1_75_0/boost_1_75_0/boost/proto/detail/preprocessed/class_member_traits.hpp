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
c51Swqxw1AfsZypAWqcsQgoR+x37gUiKvv3g8bIp0ISwrkMCUqrbvYP+HPiSalIEKgKVUu5L47v8sXH4ua/2FcAFJS/ij9sdft/jw9JIM/urJ/5nwqfZMRqRqlJF/OIDhUmrpBVfkYzXb2bXGYjoSsrEY7scfATEXORskvAabtrj8qpTEnBlTcaS7Puj1hj9pmV9VFWWcxzlbsredGhiZedtM1PhkZRyU/eRvIytUX3C3cs+IrxheE+OkpxRP5SnORdl9il5Bq40aa2x6cORPCKjRvLRgW83pClpvVwJ3V3GoyAnsZbAL5eFHIf2JKlQ9Ix23nHybbLs5G8brshzdqBgMn+mK76GKX5maHt5lG8FncwUR7wSae2YNMXqZ6FA59jpQCMhyLg/bf1VthQroKlvFO7BubHjPnY5jW808S2YK81Ejl4hQfNaZQ/sQKQ4iFsA/PH6z1rylQaM9FWBJ7Spxq3DtcS2BYp9JmjqKkMC7iTUiGyghoZYkij9Liat4mDBbMMU3o8dwTTBsR8+ikc+Cy/sQtO9IkwL7Az0xdrX80pz5sYtAMUPeZHvPvz4NdE7U1sXiccRj2mNDRCXxf+d1aoVLmfGcTetkR3ItznqyiIsL7IefDFrbV/MuxI8O6j4kh0vLAe4TJY9pMeaeYfVaxneD0Yp9IimyEc9MictxZmO2JKenHKZKoIS50SIPb8Z9nma/XSuMkvz
*/