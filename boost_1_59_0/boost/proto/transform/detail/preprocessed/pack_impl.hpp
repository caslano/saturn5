    ///////////////////////////////////////////////////////////////////////////////
    /// \file pack_impl.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        template<typename Fun, typename Cont>
        struct expand_pattern<1, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret >
        struct expand_pattern_rest_0
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void , typename C6 = void , typename C7 = void , typename C8 = void , typename C9 = void , typename C10 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret( C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4 , C5)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4 , C5 , C6)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7 , typename C8>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7 , typename C8 , typename C9>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8 , C9>
            {
                typedef msvc_fun_workaround<Ret( C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8 , C9)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<2, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0>
        struct expand_pattern_rest_1
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void , typename C6 = void , typename C7 = void , typename C8 = void , typename C9 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3 , C4)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3 , C4 , C5)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3 , C4 , C5 , C6)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7 , typename C8>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8>
            {
                typedef msvc_fun_workaround<Ret(A0 , C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7 , C8)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<3, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1>
        struct expand_pattern_rest_2
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void , typename C6 = void , typename C7 = void , typename C8 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2 , C3 , C4)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2 , C3 , C4 , C5)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2 , C3 , C4 , C5 , C6)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6 , typename C7>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , C0 , C1 , C2 , C3 , C4 , C5 , C6 , C7)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<4, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2>
        struct expand_pattern_rest_3
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void , typename C6 = void , typename C7 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1 , C2 , C3 , C4)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1 , C2 , C3 , C4 , C5)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5 , typename C6>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5 , C6>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , C0 , C1 , C2 , C3 , C4 , C5 , C6)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<5, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3>
        struct expand_pattern_rest_4
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void , typename C6 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0 , C1 , C2 , C3 , C4)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4 , typename C5>
            struct cat<C0 , C1 , C2 , C3 , C4 , C5>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , C0 , C1 , C2 , C3 , C4 , C5)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<6, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct expand_pattern_rest_5
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void , typename C5 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , C0 , C1 , C2 , C3)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3 , typename C4>
            struct cat<C0 , C1 , C2 , C3 , C4>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , C0 , C1 , C2 , C3 , C4)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<7, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct expand_pattern_rest_6
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void , typename C4 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , C0 , C1 , C2)> type;
            };
            template<typename C0 , typename C1 , typename C2 , typename C3>
            struct cat<C0 , C1 , C2 , C3>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , C0 , C1 , C2 , C3)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<8, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct expand_pattern_rest_7
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void , typename C3 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , C0 , C1)> type;
            };
            template<typename C0 , typename C1 , typename C2>
            struct cat<C0 , C1 , C2>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , C0 , C1 , C2)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<9, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 8>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct expand_pattern_rest_8
        {
            template<typename C0 = void , typename C1 = void , typename C2 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , C0)> type;
            };
            template<typename C0 , typename C1>
            struct cat<C0 , C1>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , C0 , C1)> type;
            };
        };
        template<typename Fun, typename Cont>
        struct expand_pattern<10, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_child_c< 0>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 1>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 2>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 3>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 4>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 5>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 6>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 7>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 8>, Fun>::type , typename expand_pattern_helper<proto::_child_c< 9>, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };
        template<typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct expand_pattern_rest_9
        {
            template<typename C0 = void , typename C1 = void>
            struct cat;
            template<typename C0>
            struct cat<C0>
            {
                typedef msvc_fun_workaround<Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , C0)> type;
            };
        };

/* pack_impl.hpp
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
*/