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
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    struct vector12
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11;
        
        typedef mpl::int_<12> size_type;
        static const int size_value = 12;
        typedef
            vector11<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11};
            return r;
        }
    };
    template <>
    struct vector_chooser<12>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct apply
        {
            typedef vector12<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11)
  , ( boost::phoenix::vector12 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    struct vector13
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12;
        
        typedef mpl::int_<13> size_type;
        static const int size_value = 13;
        typedef
            vector12<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12};
            return r;
        }
    };
    template <>
    struct vector_chooser<13>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct apply
        {
            typedef vector13<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12)
  , ( boost::phoenix::vector13 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    struct vector14
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13;
        
        typedef mpl::int_<14> size_type;
        static const int size_value = 14;
        typedef
            vector13<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13};
            return r;
        }
    };
    template <>
    struct vector_chooser<14>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct apply
        {
            typedef vector14<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13)
  , ( boost::phoenix::vector14 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    struct vector15
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14;
        
        typedef mpl::int_<15> size_type;
        static const int size_value = 15;
        typedef
            vector14<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14};
            return r;
        }
    };
    template <>
    struct vector_chooser<15>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct apply
        {
            typedef vector15<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14)
  , ( boost::phoenix::vector15 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    struct vector16
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15;
        
        typedef mpl::int_<16> size_type;
        static const int size_value = 16;
        typedef
            vector15<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15};
            return r;
        }
    };
    template <>
    struct vector_chooser<16>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct apply
        {
            typedef vector16<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15)
  , ( boost::phoenix::vector16 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    struct vector17
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15; typedef A16 member_type16; A16 a16;
        
        typedef mpl::int_<17> size_type;
        static const int size_value = 17;
        typedef
            vector16<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16};
            return r;
        }
    };
    template <>
    struct vector_chooser<17>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct apply
        {
            typedef vector17<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16)
  , ( boost::phoenix::vector17 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15) (A16, a16)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    struct vector18
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15; typedef A16 member_type16; A16 a16; typedef A17 member_type17; A17 a17;
        
        typedef mpl::int_<18> size_type;
        static const int size_value = 18;
        typedef
            vector17<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17};
            return r;
        }
    };
    template <>
    struct vector_chooser<18>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct apply
        {
            typedef vector18<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17)
  , ( boost::phoenix::vector18 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15) (A16, a16) (A17, a17)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    struct vector19
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15; typedef A16 member_type16; A16 a16; typedef A17 member_type17; A17 a17; typedef A18 member_type18; A18 a18;
        
        typedef mpl::int_<19> size_type;
        static const int size_value = 19;
        typedef
            vector18<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18};
            return r;
        }
    };
    template <>
    struct vector_chooser<19>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct apply
        {
            typedef vector19<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18)
  , ( boost::phoenix::vector19 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15) (A16, a16) (A17, a17) (A18, a18)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    struct vector20
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15; typedef A16 member_type16; A16 a16; typedef A17 member_type17; A17 a17; typedef A18 member_type18; A18 a18; typedef A19 member_type19; A19 a19;
        
        typedef mpl::int_<20> size_type;
        static const int size_value = 20;
        typedef
            vector19<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19};
            return r;
        }
    };
    template <>
    struct vector_chooser<20>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct apply
        {
            typedef vector20<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18) (A19)
  , ( boost::phoenix::vector20 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18) (A19)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15) (A16, a16) (A17, a17) (A18, a18) (A19, a19)
)
    
    
    
    
    
    
    
namespace boost { namespace phoenix
{
    template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
    struct vector21
    {
        typedef A0 member_type0; A0 a0; typedef A1 member_type1; A1 a1; typedef A2 member_type2; A2 a2; typedef A3 member_type3; A3 a3; typedef A4 member_type4; A4 a4; typedef A5 member_type5; A5 a5; typedef A6 member_type6; A6 a6; typedef A7 member_type7; A7 a7; typedef A8 member_type8; A8 a8; typedef A9 member_type9; A9 a9; typedef A10 member_type10; A10 a10; typedef A11 member_type11; A11 a11; typedef A12 member_type12; A12 a12; typedef A13 member_type13; A13 a13; typedef A14 member_type14; A14 a14; typedef A15 member_type15; A15 a15; typedef A16 member_type16; A16 a16; typedef A17 member_type17; A17 a17; typedef A18 member_type18; A18 a18; typedef A19 member_type19; A19 a19; typedef A20 member_type20; A20 a20;
        
        typedef mpl::int_<21> size_type;
        static const int size_value = 21;
        typedef
            vector20<A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
            args_type;
        args_type args() const
        {
            args_type r = {a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20};
            return r;
        }
    };
    template <>
    struct vector_chooser<21>
    {
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct apply
        {
            typedef vector21<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20> type;
        };
    };
}}
BOOST_FUSION_ADAPT_TPL_STRUCT_NO_PARTIAL(
    (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18) (A19) (A20)
  , ( boost::phoenix::vector21 ) (A0) (A1) (A2) (A3) (A4) (A5) (A6) (A7) (A8) (A9) (A10) (A11) (A12) (A13) (A14) (A15) (A16) (A17) (A18) (A19) (A20)
  , (A0, a0) (A1, a1) (A2, a2) (A3, a3) (A4, a4) (A5, a5) (A6, a6) (A7, a7) (A8, a8) (A9, a9) (A10, a10) (A11, a11) (A12, a12) (A13, a13) (A14, a14) (A15, a15) (A16, a16) (A17, a17) (A18, a18) (A19, a19) (A20, a20)
)

/* vector_20.hpp
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
*/