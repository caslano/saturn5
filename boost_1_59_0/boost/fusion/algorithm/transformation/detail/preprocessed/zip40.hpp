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
        template<typename T0 = fusion::void_ , typename T1 = fusion::void_ , typename T2 = fusion::void_ , typename T3 = fusion::void_ , typename T4 = fusion::void_ , typename T5 = fusion::void_ , typename T6 = fusion::void_ , typename T7 = fusion::void_ , typename T8 = fusion::void_ , typename T9 = fusion::void_ , typename T10 = fusion::void_ , typename T11 = fusion::void_ , typename T12 = fusion::void_ , typename T13 = fusion::void_ , typename T14 = fusion::void_ , typename T15 = fusion::void_ , typename T16 = fusion::void_ , typename T17 = fusion::void_ , typename T18 = fusion::void_ , typename T19 = fusion::void_ , typename T20 = fusion::void_ , typename T21 = fusion::void_ , typename T22 = fusion::void_ , typename T23 = fusion::void_ , typename T24 = fusion::void_ , typename T25 = fusion::void_ , typename T26 = fusion::void_ , typename T27 = fusion::void_ , typename T28 = fusion::void_ , typename T29 = fusion::void_ , typename T30 = fusion::void_ , typename T31 = fusion::void_ , typename T32 = fusion::void_ , typename T33 = fusion::void_ , typename T34 = fusion::void_ , typename T35 = fusion::void_ , typename T36 = fusion::void_ , typename T37 = fusion::void_ , typename T38 = fusion::void_ , typename T39 = fusion::void_ , typename T40 = fusion::void_>
        struct zip;
    }
    namespace result_of
    {
        template< typename T0 , typename T1 >
        struct zip< T0 , T1
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
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
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33
                    , void_ , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34
                    , void_ , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35
                    , void_ , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34& , const T35&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36
                    , void_ , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34& , const T35& , const T36&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37
                    , void_ , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34& , const T35& , const T36& , const T37&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38
                    , void_ , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37 , const T38>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37 , T38 const& t38)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34& , const T35& , const T36& , const T37& , const T38&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37 , const T38>::type(
            seqs);
    }
    namespace result_of
    {
        template< typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39 >
        struct zip< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39
                    , void_
        >
        {
            typedef mpl::vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 > sequences;
            typedef typename mpl::transform<sequences, add_reference<mpl::_> >::type ref_params;
            typedef zip_view<typename result_of::as_vector<ref_params>::type> type;
        };
    }
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37 , const T38 , const T39>::type
    zip(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37 , T38 const& t38 , T39 const& t39)
    {
        fusion::vector<const T0& , const T1& , const T2& , const T3& , const T4& , const T5& , const T6& , const T7& , const T8& , const T9& , const T10& , const T11& , const T12& , const T13& , const T14& , const T15& , const T16& , const T17& , const T18& , const T19& , const T20& , const T21& , const T22& , const T23& , const T24& , const T25& , const T26& , const T27& , const T28& , const T29& , const T30& , const T31& , const T32& , const T33& , const T34& , const T35& , const T36& , const T37& , const T38& , const T39&> seqs(
            t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39);
        return typename result_of::zip<const T0 , const T1 , const T2 , const T3 , const T4 , const T5 , const T6 , const T7 , const T8 , const T9 , const T10 , const T11 , const T12 , const T13 , const T14 , const T15 , const T16 , const T17 , const T18 , const T19 , const T20 , const T21 , const T22 , const T23 , const T24 , const T25 , const T26 , const T27 , const T28 , const T29 , const T30 , const T31 , const T32 , const T33 , const T34 , const T35 , const T36 , const T37 , const T38 , const T39>::type(
            seqs);
    }
}}

/* zip40.hpp
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
*/