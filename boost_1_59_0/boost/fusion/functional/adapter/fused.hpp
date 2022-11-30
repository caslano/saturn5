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
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
*/