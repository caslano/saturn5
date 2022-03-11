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