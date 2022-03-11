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