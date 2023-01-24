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
2qrTZDj2nH4W3Cw2VhsKk9PPxRQjofAQqceygf6AV0T4A6mDIPwhm/lDNvsHA/MHA/uHW8wfbrF/WCH8wdFQBO9a2w+GnitwUvgMWoyAbn4xLond/Izeq6e7aVLJbeuTBodQRVS58kyeqPLaEBvOnhdo+PUO8MuK3oHlNOS0k8WVvdA/Xzh1hqMj9NMHTqQhtpvYGwl4bziETuqNxL73YHlWNgkyow6R2WVETJddIj+IrC8jsi7W6yYijwt2k+LdqJNGxDrBTlR9Beyo6ruhoaqv6Fy1qu/2NFGQb06zqvqipphRfUWjkOr7aa1q1Vd0Oo/q+zlYvQ8/47M3v95blGBV7wGXDIZQhd6rpflv9R6WDL3jJXi7XbjAQ3Rb4nLhpo/j11Sp/RpEldqoIJlSK5wsV2qJRvdcldpDjUypnY8XZeFsvPkUFUaprZlootR+nCh3TibIFNqE2RAWn4tT7Xb2cwHldopRPKfMK55funEonupouqm3hOMsfRuF4tk4lUfx+LdRv68o+VEpaBbuf0y1qnfwW9zxbf9bvUNO+Rynwvvvwm1DolsSlwmXyz5/cheUylLcwkplCGmCUtn/vVqlMnsyzX+YbFWphIw3o1Tq9EBKJWi1aqWyfwrX+z+tbHv/570KvRI4xapewXYmRafQK79/dP9P9QphuegzZcu8K9ZpEmx/smPvZlTNvGxK1UxaU5ma2ZAoVzPP
*/