/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    struct set : sequence_base<set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> >
    {
        struct category : forward_traversal_tag, associative_tag {};
        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>
        storage_type;
        typedef typename storage_type::size size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set()
            : data() {}
        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set(Sequence const& rhs
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : data(rhs) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    explicit
    set(typename detail::call_param<T0 >::type arg0)
        : data(arg0) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : data(arg0 , arg1) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : data(arg0 , arg1 , arg2) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : data(arg0 , arg1 , arg2 , arg3) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : data(arg0 , arg1 , arg2 , arg3 , arg4) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18) {}
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    set(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19)
        : data(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19) {}
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        set&
        operator=(T const& rhs)
        {
            data = rhs;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type& get_data() { return data; }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        storage_type const& get_data() const { return data; }
    private:
        storage_type data;
    };
}}

/* set20.hpp
ERiIYRiMI3EUjsJoHI3zcAyegeFYjmOdvwtyDQ5tTX4X6uX3djcej3twMv6A0/EnPB334hL8GS/E3/AW/B3vxj/wVfwT30AvbYwuHoK/YhvUCuGN9u2Xa298xmT7M2U/58j30TwMx/k4HvNxHhZgPhZiJRbhE1ismxMj7qymzbFRJp870sPnusuYxZQpTRuzuMH6z3p+xjU+senjElvrOZp/6pjEMvblauJG4lbiHmKHqT6WAGIUMZ24mLiCWEXcQtxF7HCKjyWQGHXK3zsmUQUVVFBBBRVU+HvDAen/pwOptfr/E7X+5FFcW9ub14sLbb33xfa+Tf49gYvaujH6f2cq5aKCfD5gez5gpO79ALSbEJDYUfoML+XiN8XeVjdh+nRbX1myrImyFDWpv2UPtvfy3EZs3jbqqQ2x9dqUm9u2a9527LnNt3eetnxij9GVaacPO3/srT+UR86L5KbC3hYj9Sr1XU/Ut8XEy73xTByACRiGszAak3AyzsFluCKRd9IS9c/rbyXGGO4j4uVeIVDuDbYS9df96XJdv2eo/hperst11+M95ZrbeK39VqK6FlZBBRVUUEEFFVRQQQUV/h3hgNz/p+dmpuXv//v/tPv3EWrsf5Pv3/+rz2Y19xksNfa/6X2Wauy/CiqooIIKKqigggoq/HeDNzHz77//127+9/vef7i691f3/ureX937q6CCCiqooIIKKqigggotCn9z/3+qFpMXFGa2xvP/WhvAMN38flZ5fj9KxrKOJb52LP9zzO83Ljm9IJk583IyGSq/77mSHPPMePva5rjJKipm/gOZo4o/yrJkpuBxzQ/2wrHa8qKcLEkfg69305ax4TL30Rh57n2Wv2t8QMIhnu6hPbdVHOatLb9n1pkJuw69/PZz1nSr23LH8k0Hrw3DvK3Cc9uGeRuD5zYb8zYPz20S5m0hntoemt9G0lptFeZtJJ7btKbkacsXP3FXVun6mz5b8V2nPbvfGvdH43POBFvkPIAoaTPTz0XQReZG6YpjsRumH9K0tpJNvCS/lriX6GnMd/ZJtAlgNW4m7iRqbSntw13tKaXh5m0qlSzfSHS0rfiONW9f2TzW1cayN9HHtJ0lJYI0WIbxuAk9tbn0HOdqd1kxzr3txXu2j1v7S8h42kgwCXdhGW4kmrXH9Jzt06I2mfZRlIW4VPs7VhDXE7cS9W01e7XPTbC32eSisd2mfoJ5201wtH2ceQymR5u15eDJDdtzwli2+uSmt+uUxrjadgJnq/EyKqigggoqqKCCCgczHJD7f26PbY//t8L9/+DeFuf8tvFy/z+K2Js4nPgi9+Nx2fr7fy3zlt37d3W/93e77zfe4y/Jlnk1DXMEd5fuzGiZi2sccQtlrHSVUSugNlFwibUZbRS6/J1tFB/21palFZcm51BSV1m/76Mtn5+Tv8AqbRSOZYVWi5T/Iyl/gmqjUG0ULWijODfPtl+ebLNg0K8Dy6sHjfjzmymftt13G4Wcq5zD5m0UvbErDsduKOnk/OG8MknXQ+bHPBLHYU/MVm0bqm3jb27biKIuUlT7hgoqqKCCCiqo8A8PB+T+31qY31r9/4G6+/9suf8vkvfL5BPjtPkBM5z31lZm7StmcZPf93Wt7f5/rtwXc6+Mn9j6+EvlHTiO9oCCzEx0fzcb7zuSZYFY3UVbZp1vfC9PH2kTqJRyX0+cTrmDM93LnZxpbfJ7eRbb8sp0ljvBUO4Uk3IH68st6cJcdeDWjrFJylwgc4XPI8b7878sR5l5115qXpG95K1X302tW8ecjrnyPr+VUs7lxNMoZ4VpOanhZrz7qJE6bnJ92tpV/kXjV8zbc9S4ltYe1/JgnrY=
*/