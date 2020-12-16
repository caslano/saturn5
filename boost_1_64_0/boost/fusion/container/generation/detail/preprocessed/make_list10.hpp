/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    namespace result_of
    {
        template <
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_
          , typename Extra = void_
        >
        struct make_list;
        template <>
        struct make_list<>
        {
            typedef list<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<>
    make_list()
    {
        return list<>();
    }
    namespace result_of
    {
        template <typename T0>
        struct make_list< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type>
    make_list(T0 const& arg0)
    {
        return list<typename detail::as_fusion_element<T0>::type>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct make_list< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>
    make_list(T0 const& arg0 , T1 const& arg1)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct make_list< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct make_list< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct make_list< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct make_list< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ >
        {
            typedef list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>
    make_list(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9)
    {
        return list<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
}}

/* make_list10.hpp
fDyp5k8sL9uPUuKAKdzOaLbY1lHvKw+W+PHkSvQppuPzYfxwwdGnrDgx22zJkl71rk8T/u3oL+vvo/6t9LH0X461/9i6l/2Xnmk27j99v7jtv1hcZs0jbYIal99ijdWNNacpbafrM9o6lzY+TRut4vcFv5X0TbxR38jyTWjjGizY6/eSvokorW8kLpcnfTNGYoIJpBfom/iAklioNVIZZzKnmscmsP94MV6BvJX9VY2PmuRr5e9yTfFn0gbyO6nLL8Xky/wzt7e1tgt1zHDEp/Ol7yX2rh4zpqR0jgclZhoTqr2fxVnJJLFj51h2F8cySSzhHLOPkph9swrUCRvhJuoUXFFXJ4slm36WeiV7qFeGwflniv4cou5HSfSfa/ll3IFuX5N66dsuoqSuCVTWqf/aSOx8A6m5XAPfQl3zKpXUdQxDAuJs2XjcV+z76YGm1vFLspYcMwb1jzI4fmNdjlUZG2JY31C8yVq3TF0/1qpaMvasJelz0kvULaOyYd3iLONL7cfebJS/g90os5ZfBelTffmnOMpEkZSYf3AVud87OcGSrB9jIeMpHMeZYwzT9w1kX5b11DpOkTh8Dc4ZYfg9FXuZHwoDS+o4ISErKVn2VUpkreNWD3XMV+pYZCuT1NHW7vtdjh/tvWKXfU87l9WtSr0p4wAK8zVlAsc+ubmOtqxprCXL9e/kBBOj9GSfkXMv5zzm7HGcH95vYFtOxiU48sqqZosVdbmsJK8uBuf5KP05Qj2f6M6rsZdLLFGOkyWkV2jniKol7cxfpXI9Vlz/1kUZ/B2KNdj/4r08fqzzY0j9ii/XjyW5gvrVqmYfz2H9sx49YEj/wX2H9+VHBpL4MI6kmozlcM139BX6cSQ1tHZ1l69tEEmZ8tWNIXEZR7n/Cn0bbGf9HHtZbBNymLIzvK/34WaSv0teHavr83qHZQud82JwlPd1ZT8wzCvfIK+j5HXSOS86tOz1sv89CZX5+FuTGsh5dwnL1rrcKa+M9Iyy181+XlxhPX9om9GeL+5c5wKDciyjHFEu5ci2JJepDLIvyTGVwdgsl7+rNfX79XHyz3PK37Yz+zIe63Azz/vzefypgruxNL6PcTIew+N+7JPx2B73Y5aMxw75PrbHeIyTuzFgvo9xMh6D5H6sjvHYHndjz3wfM5ZiHVP0o6lhpdubFMUcGJxwf+/XAw7Ks9Yrynds+e59kh/68XP3irJXSaz+GmyF12I4hmB3bIGJeB2mYCjOx1a4ENvgSmyLqzEM9+MN+Ca2x8+xA36P4XgZZbgR62MnbIqdsRd2wf7YDVfiTfgUdsd92AMPYQR+hL3wDPbGX7APNqFufbED9sNR2B+nYiQ+iQNwNQ7Cp3EwFuCt+DIOxfcwCk/iMKzMd7fhWA1vwyAcgS1xJN6IsdgdR+FAvB3TcDTOw7swD+MxHxOwABNxPSbj6zgeD2IqHsJMfB8teAKz8WechLXo18nYEadgJ7wHb8bpGIn34iicgRbM4b/pOBNn4xych/fhfHwAF2MuLsW5MkYjr4J8v5fv/exP9DXro/YaWIH9CYfg9TgUw3EY3oTDMQ6j0YQj0IIjcSnG4kq8HdfjHbgTR+NneBeexnj8ARMwpALth60xCYeiGWNwLI7HZJyGKbgAx+PjmIoB9O8EvAzTsDWmYzvMxF6YhVGYjRk4GVfg3bgK78G9OBXfwHvxfZyB/8Ac/BFn4u84C6vTfrOxHd6Ht+IDOBQfxJE4D0fhAkzAPByPj2A6PorW45wk3+35zm/rlyrYnSTjznPqYHfsiD2kP27GOOyJCRgh28snnZTt/S7bq42LZHunZYzeGWyBX2Mb/Aaj8Czejt9hGn6P9+A=
*/