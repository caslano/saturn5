/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_FUNCTION_OBJECT_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_function_object.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <class Function> class fused_function_object;

    //----- ---- --- -- - -  -   -

    template <class Function>
    class fused_function_object
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_function_object(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq const>::type operator()(Seq const & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,
            Seq const>::type 
        operator()(Seq const & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_const_fwd_t,
            Seq>::type
        operator()(Seq & s) const
        {
          return fusion::invoke_function_object<
              func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::invoke_function_object<func_fwd_t,Seq>::type
        operator()(Seq & s) 
        {
          return fusion::invoke_function_object<
              func_fwd_t >(this->fnc_transformed,s);
        }

        template <typename Sig>
        struct result;

        template <class Self, class Seq>
        struct result< Self const (Seq) >
            : result_of::invoke_function_object<func_const_fwd_t, 
                typename boost::remove_reference<Seq>::type >
        { };

        template <class Self, class Seq>
        struct result< Self(Seq) >
            : result_of::invoke_function_object<func_fwd_t,
                typename boost::remove_reference<Seq>::type >
        { };
    };

}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_function_object.hpp
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
*/