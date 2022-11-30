    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0) const
    {
        return Type(a0);
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1) const
    {
        return Type(a0 , a1);
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2) const
    {
        return Type(a0 , a1 , a2);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3) const
    {
        return Type(a0 , a1 , a2 , a3);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4) const
    {
        return Type(a0 , a1 , a2 , a3 , a4);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9) const
    {
        return Type(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* construct_funop.hpp
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
*/