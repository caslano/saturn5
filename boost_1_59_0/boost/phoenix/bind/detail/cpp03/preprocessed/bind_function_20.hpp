/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            2
          , RT
          , RT(*)(T0 , T1)
        >
      , A0 , A1
    >::type const
    bind(
        RT(*f)(T0 , T1)
      , A0 const& a0 , A1 const& a1
    )
    {
        typedef detail::function_ptr<
            2
          , RT
          , RT(*)(T0 , T1)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1
            >::make(
                fp_type(f)
              , a0 , a1
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            3
          , RT
          , RT(*)(T0 , T1 , T2)
        >
      , A0 , A1 , A2
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2)
      , A0 const& a0 , A1 const& a1 , A2 const& a2
    )
    {
        typedef detail::function_ptr<
            3
          , RT
          , RT(*)(T0 , T1 , T2)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2
            >::make(
                fp_type(f)
              , a0 , a1 , a2
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            4
          , RT
          , RT(*)(T0 , T1 , T2 , T3)
        >
      , A0 , A1 , A2 , A3
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
    )
    {
        typedef detail::function_ptr<
            4
          , RT
          , RT(*)(T0 , T1 , T2 , T3)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            5
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4)
        >
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
    )
    {
        typedef detail::function_ptr<
            5
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            6
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5)
        >
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
    )
    {
        typedef detail::function_ptr<
            6
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            7
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
    )
    {
        typedef detail::function_ptr<
            7
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            8
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
    )
    {
        typedef detail::function_ptr<
            8
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            9
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
    )
    {
        typedef detail::function_ptr<
            9
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            10
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
    )
    {
        typedef detail::function_ptr<
            10
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            11
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
    )
    {
        typedef detail::function_ptr<
            11
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            12
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
    )
    {
        typedef detail::function_ptr<
            12
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            13
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
    )
    {
        typedef detail::function_ptr<
            13
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            14
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
    )
    {
        typedef detail::function_ptr<
            14
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            15
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
    )
    {
        typedef detail::function_ptr<
            15
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            16
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
    )
    {
        typedef detail::function_ptr<
            16
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            17
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
    )
    {
        typedef detail::function_ptr<
            17
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            18
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
    )
    {
        typedef detail::function_ptr<
            18
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
    >
    inline
    typename detail::expression::function_eval<
        detail::function_ptr<
            19
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18)
        >
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
    >::type const
    bind(
        RT(*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18)
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
    )
    {
        typedef detail::function_ptr<
            19
          , RT
          , RT(*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18
            >::make(
                fp_type(f)
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18
            );
    }

/* bind_function_20.hpp
FhU+4UtDoVpR+6mKw7woK3lSCRVNE1sl4l5PiWdvLEP91W5ADQovhOQNk1/jNA2ZDYyYA2VMu7cenaLqQqf1w+0eQjy7HlQgwdLAflwqV214Qo0URQeMOKaCP8U5cuH5d4CVTsCxBZugqS0zUPlOq2/7MtxFog9RIsrAwDMeDYxCpL6FWste1A/KmP8Y2SkTA8xuhm2mh1jrboGSm8FtszVxwFGocT0qMmASYYLY7Gkpi/dqaJOLWIbeqml2oHsGfAVAwxikUoNAAHU+Lzg1dH6YxXxvNP8OIKCFef+psyV4phnsDl5tgf9ANdgRuNT8b/iFdUQK/dMJrr1o6ryF9lQDPhGuelyzoipQ4sqGuu+b7eYhAGa3f8cDA11E+un6+Q33LPxuWfLTTPfHO4ymvxvig/Ayspbufyu+sdZU3/Cer8ISBkHkCguddniKceHnRjLjzrhzMwhEwsHKt7sABCz706s9QvvbOTSX41RiRn6OGLu+V+vSWooW679a4GBQQQfbYUDWOZRWmRuOGwAyoULGFaBvO3zNjbJ6SK9siU6i5os+U3W8P3xhFVq0/SH7RyGIiKKi6Bn+t+InFx1j6zL3ZybFCOlb4Es49Uax/mR5tlfgKGBK+UzrKEsaQjS2AHSYXDDcWV8FjbIERjezcVA0yUoceyxOytgKj1b8mVbhUjMKGd9wOfYGMu2G13B9sA8wG7s4x4cFxvFPaqSAaUy8UmaoNMyTjA1MxGKI+QWpiY2gaOyAOXwOTf6/j6eb9MMZggu/gUzpv4hZ3nhIrFJFH6EyiIjImgr3hFPI+bl/jnZ01/DIzDRkuFWRkdFoWpXe29A0jQPpwoHAXh0F2y58pvP/lHVe1vTFlonU3z6diFxdM4MLzr5TTUTemivzL20GwJMaofa5gYKNeIxjYnFoKBi2rQL0iYFL1ccvq/fIHMUIqqvKTEw8BUl1paxYv7Oi8WMfBpRuwCkvqSqCZUk8RA/dTHBX88Ic5yxhul0VBjVxVcAPmHqT00CBf8TSpqqDO6k1mu/N34NfgFL0tR5xa3SPTAdb7I3vuSCr7xojwb/PFNuxdusf3fXedEW6AGm6zh6Ak6DogRu8nOqEZM3gvfhBj4m8igX9vI/WLpZkMxsOLS7oz1200St9bSRSMB7FMCJmnKE3s2jd3DxNv+ukWkothFPioA55c1P6q9QkyiXVri2M6dHmrrPpYc0GMVDo7/7R0KyoCZH+5B60pl7E7FE4bAuSl9xzXZ9Do0Q3n/EMoynkpP/JIql7SmLiJLNomjFy8abmPd3xDqicVOf2LYf3PtcyaDhLvL2ShRb07ty2wJjZPFvdDvH3hoGuh+H29SwBcNxC/ie0HiJR7qNt7nmtvbknlGmh+MCT1vMzOeQpzC8o/+84KPgOw0d0WYeEfDdgQ1ecB55JnIdViZ6H8dxOwUv16ELfEwjJUYs35MQ9/KD4ecaMZN/V8LQILEK9w5zB2NQ0VFREpf3Se2N7W0bdAg6USuXRy43sb2u3zMwjLVFp6+pCqBR5fdcUHg07DU1pPltT2xqZisaudBetzRUDs7U2/u31PcTUbSW4tzVNLhBTS+tqk6ODc9fSTJsK3DyaIywuIx4mBo614srixdYeMxlrrfcJ6W76GYrkaBFDfePi1qedKJ+e5Pfoc84pNyMCe0V9vUOwImu1U6/Aovfp2JKBi7m5EEgwAI8iHck22Q+vlu+0k+/0krIVJugaMyJ6BWiGp1l4Gqf2dWFjS8vCBbolb+nuivUKZRKph+dxmbDeorc7QJyLm6ENDwnnUgyGZfDmzQ3s5PXI/eK6eQRTrJRmZjX9du4XiolGFiq5hsHqq+XOx3pzRUfm5ElfcE/j2nIpjVNlxdpHTFIEZU8liYT6wyabi6jINOaMvstlQA8o6bE7JDnrtYr9Tv1MCfOaHqLDV1ZCLiA/JW2ssMjCjEfV3cBUsKKEBOUYzExn0baE1yz6DQVRR2WZpTv7zhdP0ZjdcHufGrHKWE0KC9b2nILvYm3Q5PN9+xSv9GOAhNorK4Y6tzq2Y2iwsF8CmsLEY+7U4rr9OGOmRsez0GOEovFcAnDo9uGze6pN9EIcbzJLszTqaRwn8GfUZPFz7pH3g+uZsbsSlm4t2qK8QLbQy96Sqti1RkJa5aLmd/83QZbVh0hJIFqBzLQw9sLgE/4c4mMn8OLEiGKEwACJq68xd8TJK0kTxfZARl5b2V4nC16xW4g53bJyYJK6zw51zJkTgiBL+79TgrFRkC3oWEGvaB84LQl+uz1LjI7CrdijNgWj/A2lCpR02fi1evnNa1akgilNt5DBhWrNHYOYpzRtaZ4SORumHeYDbx7LoYer069e/E/NwA7EgCX+AlRmUW5tAE2HQbGqbFXHs5Ma7Vv+A1YaXz2vMdu4A4dyr9cNcRCB0mQ2NYlUTGBfuiouL6Oitmk1V+c0HTO2O/NMlSefs6LOB8fJsbG0hIQE75MQ3kz+hlSEnCVsX/UG0VqiwL0zL+6315F7IcXQrTtVb0i5IaHnyxLSurZRuTZ+q+zB6cVrkl2HoyGdPtGUsNOuHYnxcdjc7PBji1Fy8uXtRSoKldEuT1apt5UXo4f4hae/fXIiHipl0XE4xULEerZQI/RchlNmNa380itnAt6iPwwrK9snKkwHZk42tFE71Az/lGoYg+40fYPXdq/dwE3GSkMytP+EtLlkCylD7xLDuizTYZhX6Qrzc3Ki1j2uL1w1RzM3U5nUTysluLlaXxwxQ+PASiTZ/kk74zVAZGwgt3NMdqyUx3dm6yQ4h6aHGk56D/u5NNzwSYTwIfOX96eMdNJHJZXw72rV0vO3qHbIpz9bwUDopkj9uxmOgoyKRTRv6i8Mv7nPK2fBjmmwCAAaUGB2PLpY5TBmpvUmcKJHpBAgA34v8O1D5P/vdiVQ5BhRkX9nnXWo582n2Y8bm9PcffoOfCF/gFq9mMWvfdI+Gq2aea9vuJwJkAk0DU89AZvbKlO1IAyIXj8t6lQrAR8aNXK600xKPO48xwZLIsCR38FpoiF2tt8tA8jO5lWU2evpsNUlm5KMBv0YLi/BPAcIA0zOORhRNogiTBZx0TRi+6Uc4F/EWyF2gGUTZc4CRmM+YUjyuuXhjudT1daIkBMeTX6XLdm1wD6ygeyYVgs0gXEvlNxx8HVfjBkjZq/ta+1tKZ/iqGS6mbdmx2ABsSVrHxi5sdGBHTQKsVSMsthtzk98HXlOqjaY8ZTDduSbY/OxLSasBw5klACJpo+niA5N63Uzy79OGQ2jFyiF1giSkJaC6yDZARHNQJG1SQaV70R0AkqHmSSKjrMj4Q5hMDQomiTfW8jY+YmRZYj5f4M2qKxSCZHRSzPV86kxSBRKjDHXdscVNTl/KoqsklXD6Uephlyt/qCWONFDqadGwagfQoFVs1cUW6VMIEl/iXK+oCyCpIYAptFitpN/IvvPevqJ3QTJJPkJAd8XJgEAApF3ucpDM+ch85cjn2lDzAtDSPfKJeGLiQIK+rRXdjS8eHagpdtup99s5nQ8TGahyVD6fzDkzX+opW17HD3ml4fDUre1mQfGjKFRK9mDzRPpB/P2/lzQZS7mZn2NTP+TTNqiyEZG5ixcxRiaJncRqWOMyJa/jDIwReb8+KlroKr7aWL8qDlFIVKRd73pJK32F2bwXJG15i7orbyrfN7dcbDCFezoEtaH1yVa0MrIgidtRyUL6vt+16HM/Uc2b/s+8PzczHrnfTg0PvrnbXTis5S7WM1+tx4QIHgxSAZmN9F4gsrXP7+FKvQDFkSIdZSADd6ctxPyQ6zKccGn4EZBxAaNr9fEBJQ+VnxPr6WGpJVwIoL7Ok18XFAo519WouC06S2WpzGocaYoF63Y2Px0YIF4qCtpsKJelq5Gc/ohW4y19xBwZnQtBcRW4FFagy0kghMIKlxc4KjflM4B6zXBeUbC2nxiS1N7FagBcrLDyXri+B+BbJ5WXJpnSyebnBqfP13RTPPlnoXWfZQnSEUr+cjViIw/MBJFK8SOCQOS1A8F6aWE7GTDyie56M7Q6rvtjKNMontOGKmVrXodTJWK8dP4oIiGGJaHD/eR+R9CgrN3uUica3mvAiYXj8529hvmVEsfZBoFe56JZrefzIA+q8GspnqV5bC5NzvYrex9f9c/QYgAQz6DkiB65swF1wl1/PFUo9qU+CTWk3mIq3ojF5DumwMvOJdVx7CGfK8XM5qa9pbUfURzRZGeV5wuL44YsktWkhWK1fwS/LJJ6Le4Rasd3L5m6wjlZD6MWEwXtBL+tG6qvUX+K18Zbc67k2X+WsneJy40VA9tScUapJlBZR4OlqwTD9e1Wbd4pD6vUICLobMFV+crYy0q+ks2Kou6qS8yXtchsRjBHSodduC138hT00vOJsIVnEFUTAbJwoi5GReEp9gxWkFgBbzK24yVTiGC9PK9j1tPqNLBak9MKVBqES9ynYfxJ6tVrNTSHyvo7eEkNlJ1IcyAsNPDpYtxl5yNWemOytZ7yIX3TFsZWVe+mAukHlaXZPaVjc9KKNGr9ftO0ZU3Ms5Y14GkKjc7KwsgSWyk9bsno7BAt92zTkwI+O8/Wk6hyrYiL2OxHaMAeXfzJ32sgbEYMPClqzJgDD21+2La4LydlmPtEuNZqxxEsJW/vKrc037ZNKE3abesFQZCvJwbQZEozKWNp/eIXLHaQZEvA43c61JxZESjfy/P0TR7Uuj5uIafJamvxQqUGpb3gb4T655Mw0Egdjt9dWthRX2PKuqie75SBcBiswk8FNuM1rOJuqjV2fE75+buj4aoYJ0DQKnPpA7FjHYIWLlYsfRVE58lxtrOWXBlDeU5Vu18cm52C33/GI9ujB+Momu63yPsJNCIz7vz2AKtZWKhgTI0ihoZPfBbu4ZA7g6PRJesWCowFkwefOi+xDi+VoKnuBV4VmHoeVBF+JllePgNf6BFXfuKI6paLGiP45/UgpdgCfRvyHK7G6hPNxUHbeiweYWiOmqyGGIAkH4tB3VG3o8XP2Fl1KpnPYznsq7aoobF2iloBmdswM9bppyxCsLr+K+v3WqKAjmyPwEGSNKqaH2etxAye1cUl8f4eCqt78A5v/V2NUy93aN6xvDhxu/8eQkHYe7ok51n+jNZ+lKhHDRbXjLutwSBEYYwj2QwDGNRrMxDJTWCM9amHJkOA2Od7dnGRO3WyNQxI3y0tRCFnHWIc8Vd1g/a8HArdCWGKFLMA/sqVMYjL/WdLpdvptMqBAEtUFyclIfT6/ZnGAdzFsBnz9rLiQrw8ZWlf5vH3nJZxbYxvpmqw4cKp3B8VZO9/gOtVRBvousGoS+yuUJ6gD6DEtuFGhQBKGT6RpKhGc6JgvRIMtF2qqbPqiS3DdUQbMVJ3xO3oFfrRcHiYGlx4Zz5kaPz7h2sxz4GCoDVK/ILf9M/96t+PtLBk0R/RVFoKrQY000/llVL7qQOVCeZ6Asyz4AwCgYyFrELhdjZdVpDt0HaV/VJkU/vE/urvlT6XOPTIXvupPyFbrdj/7rHwiCOmqbCoqRNaqWHG9ibn3+vilbE0okL4jk0oJD0DbhOFTW5W/SZeOiqP9K+DxarxS5N54HoI8hqFf4xsOVFPaQH45M2dYNq9OFkNAiwKTRFKtN1TeBxa0G+BLtGu++aF5/V6QFlxfXPLaeT46v9G4ElGUVKLTkJKr/tTDLRDrr4dJUgluZxZjoQXUyxb+NRqJ+OeKLseLs5kMERCIHPv8L5gJhrQBm8MSheKuUiteB86x7jfd4j2gV2GZ0vk1SiQ8E37pxS42axZKElX1+KWDhf8S/o7258Hkei+pPardn5unGl85E86QnFQQvpzOFs+WNJgd7TAwmEGVOM0yJzZ3vzqyxDVdkCiGVPxEyIcxlear2JiI0pYOU/EmO4odGrTwU4Q1aFqCKAKLc6/AA0E2b15KTVFLLuh0d3MJEWbaVrDma5ZfkPGiE1UzZbwlKsvknjBf2RkscPcunvnRojEI6xhJ3QOy550pcPJq5Pg5doDobWdlEMEZvc/KHK+BO3uxZny7Bl8OaqW0ncLeNGefn4+A9fWzwo+heWEUMV1breCieoT6zvcTn+6wPTgfrzXmtlfvd7H8QGmqzIwG4TOTn2n2qhBCY+k1ppmP4di4XfAs+aESW8nLVW7cDhqhVilZpR2vwZQA0OqVaOI+sKuMbcVYLnrr4Qhk97Qft4p4FUTv7hjuK4jbKibczAk/PWuYifnJMgwuvjBzZmCzweX+QQ2hYrCpoMaLvsjpcf3FeZeY78ZgnWWYoQHosyaQNFwg6tW2OKJbwCFZdfXaby+bbKMEblKA7ghEZsAXR/dBm5O4CZ6DegymezL41hOA0Sc9rAATNOYtzsazfadvz9GuJDjPsFy/h8HMOxKT0u558GIzJCC1/FUt4oaRx55A/N9oGPN9uijpzllvklIyKEZmFOGVBIraceH/hQnueHt94VLHUgXgvtUaLnxNJDSq9wMNivVV6zmTG7tWx1/2KdSdFWPLYzIDVCQR/g6ciQzB1FFPloTQyMbamj50jjr3wcB6SfD4bMsDUQ3bl6NbjVNymjazUL+sp4jTR2lA/wdmeOccFBMkfrNvqY1L/wNBTLMLsMi6+njQs6xW4zib3gu8Xw2vci96/0SPECeJJjFQg5cMX+qde+Fe9KMKRwfGPu9hnQmm6OyXH8MMipk2cKlzHngGMGxTo88CXiBlzAulOHrHAwh+5WKYn8ngM5OoYPVumhwfmjfdYijYI16qyPFwlrN9dyH+Y0oQB63RTDrGpSCHA3lsfDdLApMLIFmmxJ0FKUPcGdfpIESqbBz6vlQoyOr85FFXJHKiTb4j8B1/A7ocL41nh9K+npZqfQIIeyGblN6K2DnZGiJ6Cg60cvDXK6aHAkHngPxLthFjniy1u73qhVlOq6wgeZg6WqwGS4SjLTkSLvmwnAY3BPWRk4YNa37qVA0MSZbcdYHtZE7DtLcClQVNkCQ5aX8UNJONyQVTNhv8+ahJ52faQth/F/sUEtasasvXIoXUy6gKBnUlRImYr5dY6j7phKIxYHfQhXOQBWAjarxiPDPXaI1vxMVjviZ5r2in1d/KHSaFx/EekbQHSxjbmKp0xnF8fXmMDM7S0Y6CxD3pxlIWWdC/CyyXK4AJO+Gmfz/+RqizCW/6i/ToAYqJWo/R2Dc3sPPCshZfnmjm8fGiomxsO9fwelSiZaBKqbORx85233GfrO/mm1aFs2gRlSpqiWsFeOqFDQSt4vR1YtbqX8T/Tuu4gw/Kqr2rUSeAZax9yXA2murhDpwwoRoJ18g4LWJWtrfgv5vnBEBMfgp2dQoI5mejbKysPCUvK9ZbmXKFH/NVbqvT5zfg5Y9IXPE8DrG5nats6xPF7phX9ThzxWfFwZfFYCbP/CJJAZS6JQHQM2xDotvFKzQc/RxSkK5lsVTx2t+b5R3mWyIYozYKy4VbK7GKfbxCOqMpWKZ66H2K+EvWhoSmzNhaWVvRqEe9hiAsarCzI4SzaRpp/RdoRaKxuee2lyxHE2lm2rlAWZe3nNXqXjXFbWUO1M6OFJDznwD5588RT452j4q5oyWIrCjWmTuqOZxyLlkaTi0PgmDoh11YeL
*/