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
+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
*/