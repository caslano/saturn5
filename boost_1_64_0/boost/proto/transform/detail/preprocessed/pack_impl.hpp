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
D9r5abxvSOxQERbZH5wYMPfpcG/x8Wq+tyiNY687h3O/C2u/7FpPU/qZpV+DfFyaPR8Iw2Z3KLhwKDA7JxYkRse24i5hUvL6V8proeRVdhJWqOw6EPSiZciDnautDfDkcL/AAZN8yP29sRfZJ8YTj7j7nE/retEpZeLp8Bh3d0kW3Wqq+oVuNaNmivtfOeTD8JgFHt4z1BzrzfCZDT72HlmR+/3nwvj4P1fojE6XJ/9/URK/W5Vf48b7JYJ7TohPwgZE8Oz7rb7EzdNzBMfz9H41DpdUuELCzVS44gBX+CTNYaUoG587lAlM7eeInhjXmxfV7NUneXyJYis4Cw5tngrba+98V2l2AoraqxJ8pKzy25W12sJd/dRImOW11rWR4Jwutg1nWHWEr5LfV5XGz3fqCV8hv7+szocOoLYpQ9rCx6Z9EMIVCH+S7KUlfbQH04gPK7Rnisr4LE97Ls2hPQ+nvC1V9XKEhImfrPv2zm858jZaSnc6bd5wZ1B+Y82IeAgr+ypDp+1HVyF/v6F1J/P8LcL3Ep717MkyyXdZ3G71xBpH84Usuvhq175C4/AH4uzqJMG7MyqXL6lPDssYgrBaN6xUe5AZSk94uDumWFespTxLmtbetmJRvK6aieYcOkvksq+vUT7I8xK2vZ5UewbwgUplFE2T8lhUBjyNa6cQfkJg+jykq4bOYoumtsHoEdplQjvP+Ty2cSQvyJv6EL9N4hlp3EhybGCNau07AXt9luNThY7aSOLF8/9cCZu6aoNsM+3zAlrB4f4k9bE2NTa/QPW5g1y9iKxCZvGVcVypl35qYy4Xy8FAjV5zYx89dg8hmdjmyuvagM41B6kMR6s8n+niCs7FvQ3j5w7QX4z+Ma8kHv8OursqcaL4l0LWzpL4fGfhpH/C+lSvj3BK5dZHzlcj1kfd6YYWtiXszEicrkxsbZTu6FzO69PltDY1W5S8HuoSn1EJ3uvsbpJsGX13AfTdiZrc9N2VUncFVo6dn21pN9z3dt9kVnutgsTOmrid1XCZk63TF4V2LOrOqBo/DsX5tvCw4TwJM/4QdVdvk4T5ffdZKpyU8Gq7Ft7nG26fb7h9vuGeiW84c8e0DuPJy2v8d0wx9sLWLz7PvVL18VPUfbH1MibE4qt7+q914wr85cNvP+mE9crfyevVnGp81F+s9Ic3Cg3jtR3bm5DuoiJnq870Ao/Rv4XnVsRn+pJEHP92N/cK3v8OwzsVD60DvVvhdd2/V/C8L5tQ9kN1Evavs80if4Je0qOwNLjhcXENzrfnJnbfO625VLy+tcoWVleC5tOm5rWZLkJh35Fxsl/WLgPeutYuzLFu71LHm0M4HW8u7C40PA9pdZlZW/aq2A/YB6XsUgoZ7Ewe17U3N2aCHqGApm+siN2/Hh988UDMB9bYtn4btnNungnLHefDcF/4wzV8X1hw42F74Lck4H8TdMRcfx4cHpTLzwMTE4PDLqbGgA/JZiJxYCqR8J8pDm3vG98uEXrX9LQ1docvhu0Bxbr8YzXxs4rLJAwdIybnl0MXvpjW3xfT2vQK7s/gcyX62yegI38SPM4sidNeJfA/F8bXFp+mfiN85FPnmZGu6nD10DU/z2GMC6CVfKk3IYjPVQp3NenVD5PPCu3v6lri8WhRnMdXHA/Rr7LzuA51c72qxxskrG1NbwTtlxXt1zy0NwuM78y+mvQ7yJFty0upLb/JfHHG+C1V/9+mMR98bFjqN7JFPcwrn/4+YtL9vkr3BxIe1e9CCIznoueq8fZHqJvbaF9vF/3+nErjxxK+Qz7k3fL4CaXxuPBfiLXMVcD/jPAmzieUnP+c8FehTVi2fyEw9WaBfEiHZOI=
*/