/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    struct tuple : vector<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>
    {
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>
        base_type;
        BOOST_FUSION_GPU_ENABLED tuple()
            : base_type() {}
        BOOST_FUSION_GPU_ENABLED tuple(tuple const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& rhs)
            : base_type(rhs) {}
    BOOST_FUSION_GPU_ENABLED
    explicit
    tuple(typename detail::call_param<T0 >::type arg0)
        : base_type(arg0) {}
    template <typename U0>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0> const& rhs)
        : base_type(rhs) {}
    template <typename U0>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
        : base_type(arg0 , arg1) {}
    template <typename U0 , typename U1>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
        : base_type(arg0 , arg1 , arg2) {}
    template <typename U0 , typename U1 , typename U2>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
        : base_type(arg0 , arg1 , arg2 , arg3) {}
    template <typename U0 , typename U1 , typename U2 , typename U3>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
        template <typename T>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(static_cast<base_type const&>(rhs));
            return *this;
        }
        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(std::pair<U1, U2> const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
    };
    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};
    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};
    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Tuple>
          , result_of::at_c<Tuple, N>
        >::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }
    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

/* tuple20.hpp
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
*/