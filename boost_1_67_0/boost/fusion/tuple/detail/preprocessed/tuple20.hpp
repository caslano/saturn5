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