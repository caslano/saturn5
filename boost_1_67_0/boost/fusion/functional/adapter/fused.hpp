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