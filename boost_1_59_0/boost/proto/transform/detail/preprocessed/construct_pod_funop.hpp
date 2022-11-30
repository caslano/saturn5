    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_pod_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename A0>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0) const
    {
        Type that = {a0};
        return that;
    }
    template<typename A0 , typename A1>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1) const
    {
        Type that = {a0 , a1};
        return that;
    }
    template<typename A0 , typename A1 , typename A2>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2) const
    {
        Type that = {a0 , a1 , a2};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3) const
    {
        Type that = {a0 , a1 , a2 , a3};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4 , a5};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4 , a5 , a6};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
        return that;
    }
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    BOOST_FORCEINLINE
    Type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9) const
    {
        Type that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
        return that;
    }

/* construct_pod_funop.hpp
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
*/