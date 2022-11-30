/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    namespace result_of
    {
        template<typename T0 = fusion::void_ , typename T1 = fusion::void_ , typename T2 = fusion::void_ , typename T3 = fusion::void_ , typename T4 = fusion::void_ , typename T5 = fusion::void_ , typename T6 = fusion::void_ , typename T7 = fusion::void_ , typename T8 = fusion::void_ , typename T9 = fusion::void_ , typename T10 = fusion::void_ , typename T11 = fusion::void_ , typename T12 = fusion::void_ , typename T13 = fusion::void_ , typename T14 = fusion::void_ , typename T15 = fusion::void_ , typename T16 = fusion::void_ , typename T17 = fusion::void_ , typename T18 = fusion::void_ , typename T19 = fusion::void_ , typename T20 = fusion::void_ , typename T21 = fusion::void_ , typename T22 = fusion::void_ , typename T23 = fusion::void_ , typename T24 = fusion::void_ , typename T25 = fusion::void_ , typename T26 = fusion::void_ , typename T27 = fusion::void_ , typename T28 = fusion::void_ , typename T29 = fusion::void_ , typename T30 = fusion::void_>
        struct zip;
    }
    namespace result_of
    {
        template< typename T0 , typename T1 >
        struct zip< T0 , T1
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1>::type
    zip(T0 const& t0 , T1 const& t1)
    {
        fusion::vector<const T0& , const T1&> seqs(
            t0 , t1);
        return typename result_of::zip<const T0 , const T1>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 >
        struct zip< T0 , T1 , T2
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2)
    {
        fusion::vector<const T0& , const T1& , const T2&> seqs(
            t0 , t1 , t2);
        return typename result_of::zip<const T0 , const T1 , const T2>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 >
        struct zip< T0 , T1 , T2 , T3
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3&> seqs(
            t0 , t1 , t2 , t3);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 >
        struct zip< T0 , T1 , T2 , T3 , T4
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4&> seqs(
            t0 , t1 , t2 , t3 , t4);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24
                    , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25
                    , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26
                    , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27
                    , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28
                    , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29
                    , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29>::type(
            seqs);
    }
}}

/* zip30.hpp
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
*/