/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <typename Function> class fused;

    //----- ---- --- -- - -  -   -

    template <typename Function>
    class fused
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_const_fwd_t,Seq const>::type 
        operator()(Seq const & s) const
        {
            return fusion::invoke<func_const_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_fwd_t,Seq const>::type 
        operator()(Seq const & s) 
        {
            return fusion::invoke<func_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_const_fwd_t,Seq>::type 
        operator()(Seq & s) const
        {
            return fusion::invoke<func_const_fwd_t>(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke<func_fwd_t,Seq>::type 
        operator()(Seq & s) 
        {
            return fusion::invoke<func_fwd_t>(this->fnc_transformed,s);
        }

        template <typename Sig>
        struct result;

        template <class Self, class Seq>
        struct result< Self const (Seq) >
            : result_of::invoke<func_const_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };

        template <class Self, class Seq>
        struct result< Self(Seq) >
            : result_of::invoke<func_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };

    };

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused.hpp
86Zt+RghzfmRxcLFT0pDQllIyOsiEWYD9QLP178pIz46ZlIyOP+RUghHkCej/uiYvzpH590yPMEn9orW9vjBdTuUhCIMviMRciDJ2+F0pw5ZFERr1lENN3QEHdObwMan/0oZaub1U/fy0HnjmpueeZz5/XYVidWY4VKiqmcAXro2iw/ySznYkAOAqo5h8nboBt6euD/04YN0+LTE8neytznJr/m87rUIJ38EGZdEN4szapLFdA4pdl/eW9S/zZcd1S/Sy6D59AbCjOPepwSRfDkI0KfwyhqAvaRTzVJqyOeB2yDIroD5G8ILaOSihBK/yNGIGwEMemhEI1OtrThFvpbBFuvB2S3OFEcb2AKgDOr6RkJfYXlOfdAz+0j1+I8kgBL4fKh6riZwZl6qQfHvPdaqb5pXK6ETfeqpKVBiHTSL6yF50vjnl/JMi/xAEHEYkyS5tzh/wXdsBXLf9mc96MI+gLplqZzNV8EgbV8n6EWgvvig3/sXtR5UeKJN728FyiVj59jLOV/I4FtfaIne/fWT7xTlcB2A665PhJoSfzD50FJst/m36OJLBQ==
*/