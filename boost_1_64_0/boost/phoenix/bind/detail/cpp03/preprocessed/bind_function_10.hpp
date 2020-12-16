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

/* bind_function_10.hpp
BoWxF7wNDg5v+CpLXtpuc90RGBw5QlCgaF4mG/NqjmuDMjBtoFfSpjDYs410brOixdeTnGOeFozBdYRIz9PoSruWIuZDgPEh45PDM2Mtf20yocfxfYI+SgCwolemOK/0BT0vIz1F8aF1wozmddurOeYYrpChNVrDvJXKY/yZw/b+Yq1ay8NzYuH7i+ND8LqGfhG/Oclvqzqkg9dsLUm1oUIb2Gele3ZIfKNWyuQqNdx87abTJE6RGNN53HXY8pnMZ8qpFI66sKaX8ERK45e+VuYBgVJ1uMYmIb1aiO0L4VcQnnyl4YhTh5+SLxO2yzkLjV9t4eHxUsGd5QA/ND7M+FWIhfAf7H+sRczUJb7OKZFxfx7fZ5RNbn+HcDNqSR28o4FxSimG3jt9EP3/JnZp4Vbh78WuxTdVIHrfAo0NPcf3dauC77QdThS2dS/gd40ZexVy1D7zWkR0X90gH2lvgt4moP1WwlB6uTZYAhrs+kCzd6aqO3LWu3NnwnTSeWFbLwWG3jajLAz/m68gGslFywZD/9kyh67qR/B+55Wg63qnYDzG/+0JaBN6w8jvSOoldoqfJe3721+jdKCJCuBAVp1pfs/9povuG/ntlnyn/UMunc+Chk28pj86GIoppHlcvEjjR83TO7AkKfP4Ib/p0Gm1TdCnEU2vGjolDV67H9H270sM3axHDmra3y5qGoTHQNuZHoNekn3N6aawJ22+X+I0KAzb2f/V3+kQDotoM44eZ15oK5IQZdA8P2DoQXAkXT8fM99p77czfdCPfDA5YfJd+ieDwS7tpNoyMLQzIl+ar4xMU+4ZXLBfNKjpN7j0QEkHtWz3/JNLRw9pqoAobZP/KsKky829bSyAh0aapmwn3Fhd/qEIJmAx/7zuj7zG6R9o9NHTi0ZHj7p0X0Zeu1z3J5euxoMx7AnPTMm5cJ3AVRuNyg4PG3YYd4ZHub42hDFqSjX03jBd6RO/736nKwv2LJQwmKPprMNgH+/K7c/16MuDM2MdGAydkTa/U85Yerg62LOh7b9BjcvH4GjsGdR5V2Nw6CHYrPaHIZP3n/8Yg4W4MOE6GwjX96d4HHrX9BRcAGX5d82Hx3OB7Q7H9HxmDJaqbKozwtjhebAbsc0u+T4rDgsVIiy/RT+fDApKg5bG3xCD5615Na4z/l9x9aw2uAye6+/GeP5UJ9zP736nHUuDto1qZvz8E+9F7EhjzwPFNeOayGc/bVUCaPrVB3w6DPqn1jPNp6RKA34/h2KKOeBkJAZKKeICfCwSgxwxyiI86jCqdlDX1afisBR8ZjjAm377eYGnN+qeNbmXx5Azgh6wmZmGK1aASjDuGz4OmTW9RrWUwSPmsAtMeRl3WzSOysz698NYnFJW38A3+vGz+bGI7oJ4bWpcIfyv58OrcDJwu8T/rTYKwfCDJIu0XBfi09KePc/dfw6w/QBXS/0D2swZ0PS/G3qQ8eTM9FALdJ3Xv5iOmtexTDBa8pOew6RHyMzOi8AtGVPx7gFmErqscUYPlvs0KrWZbHiuudql02Sj23W1S6cBntZdbd1WD4rGmdGd8FUT0zkcH5rMQZ6Lu58XwtCLaYw5FeYDUwIgDL26vo9HYiAcllPDwXtWLRMPJgJLS2Moj5Wq38St+b1Z42Er3BilQ6asfyA6bZjTCSkm0gPGpji+lTAU3BaNZGineywa7edTHTk0ygD/bPN693EWhvSVbd7ZC27sn9FhCmFq6jDxmkWOzWPjVdWZeJAhflMdwXNY42aHGIea7bTku8qiD+x5gi0/7R7QuRTF4vx7xDob3ixisT2lsckIbPBkL4NNzPC/GqzKVkXNU/1zQtu4U38x9Emcw4xrmY8=
*/