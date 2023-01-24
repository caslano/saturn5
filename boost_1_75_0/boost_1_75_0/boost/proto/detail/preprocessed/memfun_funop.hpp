    ///////////////////////////////////////////////////////////////////////////////
    // memfun_funop.hpp
    // Contains overloads of memfun::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0);
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1);
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    result_type operator()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* memfun_funop.hpp
0S5m6ymt0U5DyM5MnfYjfU0M6yGQIot6Lnuz4rgQ30SmfcyviAWJvsrNZJm26ac1wbJ0toGBRlYZgR5NpGsDGnaNBI2o3a6Y6kr+yH4QTWmoJ5beLEOVuL5ZCM55tBX5/W4tcbHYOhXxUS6EF4oET01XmOxjuui0g3z43V+225pgJMK/YWksjTNDzXCk5BD/Lnkhjg4gz/RkzftGW5uZzYv4E5q38VUV9gPZhUkUPvbxNRXVVTrsz7tv511RXuMU3OiiOI9umnR29TgkLLdP+qduutCETqndrMMWwX1g9MMWOSex+vwZ1x/VplVRhaXh7hHUR/rvGJWdcY8ZFI/lxGl7YtZOI6KFoXoDHQfB9U9ijxdimsrn+3RRewTqaZpgetvA4ogAChMkokioEecTXRBBQyVgzG+Sj99eLCKJ6hjBRWwE+gSJujRjdcKvhIsXHS4xqyoqr3KSc5jhT8xAnRjKkn7WuE88VO3pmM/M35hzQznnLr9cgg+BtLdB0ZZ/idu3Rxxf8JB0+g7luxtCdbAfrR0mhIZGMhC1mRphyeMwJZiyckBFqt/FgLz+mqyTQdCeoz9USnWWo7fId3OEzm6JJSxQVECU7F0qnJKJoFkTmC39icun4bshdVy+LSm9n4K9DD2uo9vglSPw6TgK/Q3dTLlpPiFtppyG4KIe+bYHI2JKNDAcQjULSp6t8Ptfq3zt8MfQd6HCjre+
*/