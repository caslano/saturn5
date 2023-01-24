/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct fusion_sequence_tag;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct set : sequence_base<set<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> >
    {
        struct category : forward_traversal_tag, associative_tag {};
        typedef set_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef vector<
            T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
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

/* set10.hpp
Oi0IaHmcwx8rFcHwjvDnVY/WMhr+PGZvEIE/EyM7sOPPdZEN7PgzPLKBHX8yIxvY8adbZAM7/vzpjmhgx5+v3TR7lQ5bQ2SpLPxZw60quFWlhT8VFv487w7Dn89etuNPhY4/xe8RDlS4FSTRU89aTwXAdjwbWR3GnOP5KQpkLp7S0OZhG9qA3XV3PGLu0z9MoYwM4gihyzWUOQX+9Yd/8YAt/uBHGpbIqMqRWLI9Kpa85jIs/h8ZifAI1MvZDC0u3bJDW42OCRtkFu5mm6bM2mpIs/6tt3aky4hQ+Chc+i7FCqYrzsutKYxaFRZqvZviiVxdQJ6LYizgaDknhuhbOAe91dkx1q4nyRdTEmfIXa9jvKzlXk0LsmotmHnBSatfIlf/uYVq9ZFHq9VhZsBqWv17nWEwc/tCO8yU6DCz9116qsAZCTOfhsPMiT7aapfjx1hpi9iRkaJJzfJ6DP9yaT+zXOr6Yb+ngNK+brPIY6VZas6lbUA/rb2ynilkRjxbVvon/xnDwaX+5OBSwV242A3SLEAGTgB9wdyT48LNtxgRNfegfNG9zEkhY5trOZsS+QmS34rNB18kwejfnWxg9FAnBqNaC4zu7eSJXPBIkKUYZOhZYTfPGMLPS/MMzeBjebjBhxbrfLnCykKbMSrVWSaHWgjpj5IjicZ3kiOJRtDLlHqrl/9mpxwX/gYelamxYA79pW7WMjmZWVOi
*/