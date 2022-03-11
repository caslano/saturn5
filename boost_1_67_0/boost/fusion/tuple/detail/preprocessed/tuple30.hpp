/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
    struct tuple : vector<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29>
    {
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29>
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
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24 , typename detail::call_param<T25 >::type arg25)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24 , typename detail::call_param<T25 >::type arg25 , typename detail::call_param<T26 >::type arg26)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24 , typename detail::call_param<T25 >::type arg25 , typename detail::call_param<T26 >::type arg26 , typename detail::call_param<T27 >::type arg27)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24 , typename detail::call_param<T25 >::type arg25 , typename detail::call_param<T26 >::type arg26 , typename detail::call_param<T27 >::type arg27 , typename detail::call_param<T28 >::type arg28)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28> const& rhs)
    {
        base_type::operator=(rhs);
        return *this;
    }
    BOOST_FUSION_GPU_ENABLED
    tuple(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19 , typename detail::call_param<T20 >::type arg20 , typename detail::call_param<T21 >::type arg21 , typename detail::call_param<T22 >::type arg22 , typename detail::call_param<T23 >::type arg23 , typename detail::call_param<T24 >::type arg24 , typename detail::call_param<T25 >::type arg25 , typename detail::call_param<T26 >::type arg26 , typename detail::call_param<T27 >::type arg27 , typename detail::call_param<T28 >::type arg28 , typename detail::call_param<T29 >::type arg29)
        : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28 , arg29) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
    BOOST_FUSION_GPU_ENABLED
    tuple(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
        : base_type(rhs) {}
    template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29>
    BOOST_FUSION_GPU_ENABLED
    tuple& operator=(tuple<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29> const& rhs)
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

/* tuple30.hpp
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
*/