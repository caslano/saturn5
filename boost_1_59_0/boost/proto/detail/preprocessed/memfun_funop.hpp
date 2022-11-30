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
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
*/