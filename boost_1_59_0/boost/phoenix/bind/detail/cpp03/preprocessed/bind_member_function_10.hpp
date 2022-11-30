/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0
      , typename ClassA
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0)
        >
      , ClassA
      , A0
    >::type const
    bind(
        RT(ClassT::*f)(T0)
      , ClassA const & obj
      , A0 const& a0
    )
    {
        typedef detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0
            >::make(
                fp_type(f)
              , obj
              , a0
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0
      , typename ClassA
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0) const
        >
      , ClassA
      , A0
    >::type const
    bind(
        RT(ClassT::*f)(T0) const
      , ClassA const & obj
      , A0 const& a0
    )
    {
        typedef detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0
            >::make(
                fp_type(f)
              , obj
              , a0
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0)
        >
      , ClassT
      , A0
    >::type const
    bind(
        RT(ClassT::*f)(T0)
      , ClassT & obj
      , A0 const& a0
    )
    {
        typedef detail::member_function_ptr<
            1
          , RT
          , RT(ClassT::*)(T0)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0
            >::make(
                fp_type(f)
              , obj
              , a0
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1
      , typename ClassA
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1)
        >
      , ClassA
      , A0 , A1
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1
    )
    {
        typedef detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1
            >::make(
                fp_type(f)
              , obj
              , a0 , a1
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1
      , typename ClassA
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1) const
        >
      , ClassA
      , A0 , A1
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1
    )
    {
        typedef detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1
            >::make(
                fp_type(f)
              , obj
              , a0 , a1
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1)
        >
      , ClassT
      , A0 , A1
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1
    )
    {
        typedef detail::member_function_ptr<
            2
          , RT
          , RT(ClassT::*)(T0 , T1)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1
            >::make(
                fp_type(f)
              , obj
              , a0 , a1
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2
      , typename ClassA
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2)
        >
      , ClassA
      , A0 , A1 , A2
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2
    )
    {
        typedef detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2
      , typename ClassA
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2) const
        >
      , ClassA
      , A0 , A1 , A2
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2
    )
    {
        typedef detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2)
        >
      , ClassT
      , A0 , A1 , A2
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2
    )
    {
        typedef detail::member_function_ptr<
            3
          , RT
          , RT(ClassT::*)(T0 , T1 , T2)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3)
        >
      , ClassA
      , A0 , A1 , A2 , A3
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
    )
    {
        typedef detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3) const
        >
      , ClassA
      , A0 , A1 , A2 , A3
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
    )
    {
        typedef detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3)
        >
      , ClassT
      , A0 , A1 , A2 , A3
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3
    )
    {
        typedef detail::member_function_ptr<
            4
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4)
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
    )
    {
        typedef detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4) const
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
    )
    {
        typedef detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4)
        >
      , ClassT
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
    )
    {
        typedef detail::member_function_ptr<
            5
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3 , A4
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5)
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
    )
    {
        typedef detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5) const
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
    )
    {
        typedef detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5)
        >
      , ClassT
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
    )
    {
        typedef detail::member_function_ptr<
            6
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3 , A4 , A5
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
    )
    {
        typedef detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
    )
    {
        typedef detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        >
      , ClassT
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
    )
    {
        typedef detail::member_function_ptr<
            7
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3 , A4 , A5 , A6
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
    )
    {
        typedef detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
    )
    {
        typedef detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        >
      , ClassT
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
    )
    {
        typedef detail::member_function_ptr<
            8
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    
    
    
    
    
    
    
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
    )
    {
        typedef detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
      , typename ClassA
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const
        >
      , ClassA
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const
      , ClassA const & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
    )
    {
        typedef detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8) const
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassA
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }
    template <
        typename RT
      , typename ClassT
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        >
      , ClassT
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(
        RT(ClassT::*f)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
      , ClassT & obj
      , A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
    )
    {
        typedef detail::member_function_ptr<
            9
          , RT
          , RT(ClassT::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8)
        > fp_type;
        return
            detail::expression::function_eval<
                fp_type
              , ClassT
              , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            >::make(
                fp_type(f)
              , obj
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }

/* bind_member_function_10.hpp
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
*/