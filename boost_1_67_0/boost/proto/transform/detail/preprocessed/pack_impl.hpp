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