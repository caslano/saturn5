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
HgAJAAAAAAABAAAAAACO0j8AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTM5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnOsfgXJAQAANQMAAB0ACQAAAAAAAQAAAAAAVdQ/AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuM1fdVgAQAAXgIAAB4ACQAAAAAAAQAAAAAAYtY/AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0MFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLUtt5orQEAADMDAAAeAAkAAAAAAAEAAAAAAAfYPwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NDFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSeXNKIKoBAAD1AgAAHgAJAAAAAAABAAAAAAD52T8AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTQyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpXQ1nasAQAA9wIAAB4ACQAAAAAAAQAAAAAA6Ns/AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDk0M1VUBQABtkgkYFBLAQIAAAoAAAAI
*/