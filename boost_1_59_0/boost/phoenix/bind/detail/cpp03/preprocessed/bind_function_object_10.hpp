/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0
    >::type const
    bind(F f, A0 const& a0)
    {
        return
            detail::expression::function_eval<F, A0>::make(
                f
              , a0
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1)
    {
        return
            detail::expression::function_eval<F, A0 , A1>::make(
                f
              , a0 , a1
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2>::make(
                f
              , a0 , a1 , a2
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3>::make(
                f
              , a0 , a1 , a2 , a3
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4>::make(
                f
              , a0 , a1 , a2 , a3 , a4
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7
            );
    }
    
    
    
    
    
    
    
    template <
        typename F
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
    >
    inline
    typename detail::expression::function_eval<
        F
      , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
    >::type const
    bind(F f, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return
            detail::expression::function_eval<F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::make(
                f
              , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8
            );
    }

/* bind_function_object_10.hpp
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
*/