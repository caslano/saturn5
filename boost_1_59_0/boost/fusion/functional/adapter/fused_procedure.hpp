/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_FUSED_PROCEDURE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/config.hpp>

#include <boost/fusion/functional/adapter/detail/access.hpp>
#include <boost/fusion/functional/invocation/invoke_procedure.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    template <typename Function> class fused_procedure;

    //----- ---- --- -- - -  -   -

    template <typename Function>
    class fused_procedure
    {
        Function fnc_transformed;

        typedef typename detail::qf_c<Function>::type & func_const_fwd_t;
        typedef typename detail::qf<Function>::type & func_fwd_t;

    public:

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline explicit fused_procedure(func_const_fwd_t f = Function())
            : fnc_transformed(f)
        { }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq const & s) 
        {
            fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) const
        {
            fusion::invoke_procedure<
                func_const_fwd_t >(this->fnc_transformed,s);
        }

        template <class Seq> 
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline void operator()(Seq & s) 
        {
            return fusion::invoke_procedure<
                func_fwd_t >(this->fnc_transformed,s);
        }

        typedef void result_type;
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* fused_procedure.hpp
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
*/