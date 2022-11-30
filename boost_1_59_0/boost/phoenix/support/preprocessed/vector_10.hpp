/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
namespace boost { namespace phoenix
{
    template <typename Dummy = void>
    struct vector0
    {
        typedef mpl::int_<0> size_type;
        static const int size_value = 0;
    };
    template <int> struct vector_chooser;
    template <>
    struct vector_chooser<0>
    {
        template <typename Dummy = void>
        struct apply
        {
            typedef vector0<> type;
        };
    };
}}
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0>
    struct vector1
    {
        typedef A0 member_type0; A0 a0;
        
        typedef mpl::int_<1> size_type;
        static const int size_value = 1;
        typedef
            vector0<>
            args_type;
        args_type args() const
        {
            args_type r = {};
            return r;
        }
    };
    template <>
    struct vector_chooser<1>
    {
        template <typename A0>
        struct apply
        {
            typedef vector1<A0> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0)
  , ( boost::phoenix::vector1 ) (A0)
  , (A0, a0)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1>
    struct vector2
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1;
        
        typedef mpl::int_<2> size_type;
        static const int size_value = 2;
        typedef
            vector1<A1>
            args_type;
        args_type args() const
        {
            args_type r = {a1};
            return r;
        }
    };
    template <>
    struct vector_chooser<2>
    {
        template <typename A0 , typename A1>
        struct apply
        {
            typedef vector2<A0 , A1> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1)
  , ( boost::phoenix::vector2 ) (A0) (A1)
  , (A0, a0) (A1, a1)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2>
    struct vector3
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2;
        
        typedef mpl::int_<3> size_type;
        static const int size_value = 3;
        typedef
            vector2<A1 , A2>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2};
            return r;
        }
    };
    template <>
    struct vector_chooser<3>
    {
        template <typename A0 , typename A1 , typename A2>
        struct apply
        {
            typedef vector3<A0 , A1 , A2> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2)
  , ( boost::phoenix::vector3 ) (A0) (A1) (A2)
  , (A0, a0) (A1, a1) (A2, a2)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3>
    struct vector4
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3;
        
        typedef mpl::int_<4> size_type;
        static const int size_value = 4;
        typedef
            vector3<A1 , A2 , A3>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3};
            return r;
        }
    };
    template <>
    struct vector_chooser<4>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3>
        struct apply
        {
            typedef vector4<A0 , A1 , A2 , A3> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3)
  , ( boost::phoenix::vector4 ) (A0) (A1) (A2) (A3)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct vector5
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4;
        
        typedef mpl::int_<5> size_type;
        static const int size_value = 5;
        typedef
            vector4<A1 , A2 , A3 , A4>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4};
            return r;
        }
    };
    template <>
    struct vector_chooser<5>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct apply
        {
            typedef vector5<A0 , A1 , A2 , A3 , A4> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4)
  , ( boost::phoenix::vector5 ) (A0) (A1) (A2) (A3) (A4)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct vector6
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5;
        
        typedef mpl::int_<6> size_type;
        static const int size_value = 6;
        typedef
            vector5<A1 , A2 , A3 , A4 , A5>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5};
            return r;
        }
    };
    template <>
    struct vector_chooser<6>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct apply
        {
            typedef vector6<A0 , A1 , A2 , A3 , A4 , A5> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5)
  , ( boost::phoenix::vector6 ) (A0) (A1) (A2) (A3) (A4) (A5)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct vector7
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6;
        
        typedef mpl::int_<7> size_type;
        static const int size_value = 7;
        typedef
            vector6<A1 , A2 , A3 , A4 , A5 , A6>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6};
            return r;
        }
    };
    template <>
    struct vector_chooser<7>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct apply
        {
            typedef vector7<A0 , A1 , A2 , A3 , A4 , A5 , A6> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6)
  , ( boost::phoenix::vector7 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct vector8
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7;
        
        typedef mpl::int_<8> size_type;
        static const int size_value = 8;
        typedef
            vector7<A1 , A2 , A3 , A4 , A5 , A6 , A7>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7};
            return r;
        }
    };
    template <>
    struct vector_chooser<8>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct apply
        {
            typedef vector8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7)
  , ( boost::phoenix::vector8 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct vector9
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8;
        
        typedef mpl::int_<9> size_type;
        static const int size_value = 9;
        typedef
            vector8<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            return r;
        }
    };
    template <>
    struct vector_chooser<9>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct apply
        {
            typedef vector9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8)
  , ( boost::phoenix::vector9 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct vector10
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9;
        
        typedef mpl::int_<10> size_type;
        static const int size_value = 10;
        typedef
            vector9<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            return r;
        }
    };
    template <>
    struct vector_chooser<10>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct apply
        {
            typedef vector10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9)
  , ( boost::phoenix::vector10 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    struct vector11
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10;
        
        typedef mpl::int_<11> size_type;
        static const int size_value = 11;
        typedef
            vector10<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10};
            return r;
        }
    };
    template <>
    struct vector_chooser<11>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct apply
        {
            typedef vector11<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10)
  , ( boost::phoenix::vector11 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10)
)

/* vector_10.hpp
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
*/