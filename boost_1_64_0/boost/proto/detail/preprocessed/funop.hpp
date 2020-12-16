    ///////////////////////////////////////////////////////////////////////////////
    // funop.hpp
    // Contains definition of funop[n]\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    template<typename Expr, typename Domain >
    struct funop0
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list1<
                Expr &
                
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            
        )
        {
            type that = {
                e
                
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename This, typename Domain>
    struct funop<Expr(), This, Domain>
      : funop0<
            typename detail::same_cv<Expr, This>::type
          , Domain
            
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0>
    struct funop1
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list2<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0, typename This, typename Domain>
    struct funop<Expr(A0), This, Domain>
      : funop1<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1>
    struct funop2
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list3<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1, typename This, typename Domain>
    struct funop<Expr(A0 , A1), This, Domain>
      : funop2<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2>
    struct funop3
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list4<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2), This, Domain>
      : funop3<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3>
    struct funop4
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list5<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3), This, Domain>
      : funop4<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct funop5
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list6<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type , typename proto::result_of::as_child<A4, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3) , proto::as_child<Domain>(a4)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3 , A4), This, Domain>
      : funop5<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type , typename remove_reference<A4 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct funop6
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list7<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type , typename proto::result_of::as_child<A4, Domain>::type , typename proto::result_of::as_child<A5, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3) , proto::as_child<Domain>(a4) , proto::as_child<Domain>(a5)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3 , A4 , A5), This, Domain>
      : funop6<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type , typename remove_reference<A4 >::type , typename remove_reference<A5 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct funop7
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list8<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type , typename proto::result_of::as_child<A4, Domain>::type , typename proto::result_of::as_child<A5, Domain>::type , typename proto::result_of::as_child<A6, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3) , proto::as_child<Domain>(a4) , proto::as_child<Domain>(a5) , proto::as_child<Domain>(a6)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3 , A4 , A5 , A6), This, Domain>
      : funop7<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type , typename remove_reference<A4 >::type , typename remove_reference<A5 >::type , typename remove_reference<A6 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct funop8
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list9<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type , typename proto::result_of::as_child<A4, Domain>::type , typename proto::result_of::as_child<A5, Domain>::type , typename proto::result_of::as_child<A6, Domain>::type , typename proto::result_of::as_child<A7, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3) , proto::as_child<Domain>(a4) , proto::as_child<Domain>(a5) , proto::as_child<Domain>(a6) , proto::as_child<Domain>(a7)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), This, Domain>
      : funop8<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type , typename remove_reference<A4 >::type , typename remove_reference<A5 >::type , typename remove_reference<A6 >::type , typename remove_reference<A7 >::type
        >
    {};
    
    
    template<typename Expr, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct funop9
    {
        typedef typename proto::base_expr<
            Domain
          , tag::function
          , list10<
                Expr &
                , typename proto::result_of::as_child<A0, Domain>::type , typename proto::result_of::as_child<A1, Domain>::type , typename proto::result_of::as_child<A2, Domain>::type , typename proto::result_of::as_child<A3, Domain>::type , typename proto::result_of::as_child<A4, Domain>::type , typename proto::result_of::as_child<A5, Domain>::type , typename proto::result_of::as_child<A6, Domain>::type , typename proto::result_of::as_child<A7, Domain>::type , typename proto::result_of::as_child<A8, Domain>::type
            >
        >::type type;
        BOOST_FORCEINLINE
        static type const call(
            Expr &e
            , A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8
        )
        {
            type that = {
                e
                , proto::as_child<Domain>(a0) , proto::as_child<Domain>(a1) , proto::as_child<Domain>(a2) , proto::as_child<Domain>(a3) , proto::as_child<Domain>(a4) , proto::as_child<Domain>(a5) , proto::as_child<Domain>(a6) , proto::as_child<Domain>(a7) , proto::as_child<Domain>(a8)
            };
            return that;
        }
    };
    
    
    template<typename Expr , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename This, typename Domain>
    struct funop<Expr(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), This, Domain>
      : funop9<
            typename detail::same_cv<Expr, This>::type
          , Domain
            , typename remove_reference<A0 >::type , typename remove_reference<A1 >::type , typename remove_reference<A2 >::type , typename remove_reference<A3 >::type , typename remove_reference<A4 >::type , typename remove_reference<A5 >::type , typename remove_reference<A6 >::type , typename remove_reference<A7 >::type , typename remove_reference<A8 >::type
        >
    {};

/* funop.hpp
FYscfsZ6x/4qNmHAb3aZ2MDIW0Y4VlX4S957zVd/10qdIWJeY62+SV/qnLh/kGeJsZfHfNzm2DliQ3osXqxqxCca5xO7tGevF7v2eofYCT1xS8TWj/2q2rG3xIp77GyxJzdWb3Vs9dbe37tAbPaKlrWOZWztXcMlrjVki03usZViU8Zmnu9YidiAX82XcqHY8PuuHejYo1t769MntmHcfz9ybI/5vfPFhqb86UbH9pr3TBAbM7Cz07EGY+e57IDYzB5bJPZJ29y/OzbgL/1bxF96Z9bl7hlpbJXLosEW9WsDPXHGfmn0Xjsr8Vxjaz2Dg2ycr784sYvAksGuAEsDWwOWCXYzrD0H1r4RnpkPdi9YUb+2yPOwsWs8l19t40rhmU+CVYA92695PNXGrvOsXdNr63wvG7ve41tr11AHa3gL3qWxX5O/kYkN6umj30tdX5ocfvAXGyj2y7/7yb9iIyNrtI96zA/MH8wLFgAWCBYMFgIWChYGFg4WARYJFgUWDRYDFgsWBxYPlgDmA0sESwJLBksBSwVLA0sHywDLBMsCywbLAcsFywPLBysAK+zXPJ4ix0Ija65woCeu2MStcj2zBKwUrAysvF/zeCrMe6a63rPSxJ3qemYVWHW/5vHUmN/7pU+t1Zq4m1xWB1YP1tCvZa5tNO9ys8eTY+OaTNyNLms2cVl9nnnmyhYTd4MnYZm11n7Nk9Nmnrm+zzPX+dpNXM/5p9YB1gnW1a+dfUG3eZdMz6A+++kZ0BtnzmmxZUv9BvTGrfMsj+u1sxL9TVzPvUfNCxbQrx35OtD8XobnD5lq8o9gE9dzvquFgIWChYGFg0WARYJFgUWDxYDFgsWBxYMlgPnAEsGSwJLBUsBSwdLA0vs1jyfD1OCaPrbIk2nieu6mallg2WA5YLlgeWD5YAVghWBFYMVgJWClYGVg5WAVYJVgVWDVYDVgtWB1YPVgDWCNYE1gzf2ax9Ni+iHdc8bl1lpN3B88AwOstYG1g3WAdYJ1gXWDeQb2ZyuX+A3sXftqz5lJvRY1wN/EXS3/3T7Ta+LSPAPMM+X7z8Rd6bpLBZq4qxzoiQs2cT1/v1YLAQsFCwMLB4sAiwSLAosGiwGLBYsDiwdLAPOBJYIlgSWDpYClgqWBpYNlgGWCZYFlg+WA5YLlgeWDFYAVghWBFYOVgJWClYGVg1WAVYJVgVWD1YDVgtWB1YM1gDWCNYE1g7WAtYK1gbWDdYB1gnWBdYN5BvVvfmD+YF6wALBAsGCwELBQsDCwcLAIsEiwKLBosBiwWLA4sHiwBDAfWCJYElgyWApYKlgaWDpYBlgmWBZYNlgOWC5YHlg+WAFYIVgRWDFYCVgpWBlYOVgFWCVYFVg1WA1YLVgdWD1YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDeYQL/mB+YP5gULAAsECwYLAQsFCwMLB4sAiwSLAosGiwGLBYsDiwdLAPOBJYIlgSWDpYClgqWBpYNlgGWCZYFlg+WA5YLlgeWDFYAVghWBFYOVgJWClYGVg1WAVYJVgVWD1YDVgtWB1YM1gDWCNYE1g7WAtYK1gbWDdYB1gnWBdYN5BvdvfmD+YF6wALBAsGCwELBQsDCwcLAIsEiwKLBosBiwWLA4sHiwBDAfWCJYElgyWApYKlgaWDpYBlgmWBZYNlgOWC5YHlg+WAFYIVgRWDFYCVgpWBlYOVgFWCVYFVg1WA1YLVgdWD1YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDeYZ0j/5gfmD+YFCwALBAsGCwELBQsDCweLAIsEiwKLBosBiwWLA4sHSwDzgSWCJYElg6WApYKlgaWDZYBlgmWBZYPlgOWC5YE=
*/