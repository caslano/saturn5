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
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
*/