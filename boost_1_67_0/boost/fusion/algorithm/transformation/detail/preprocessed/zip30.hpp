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