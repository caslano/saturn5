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
LUplhl/2d28JIf7M/3G/RYEB3WFkLAWxRq9NcljPdIExHL6zlynftUd4MAUs02eJQHFQYpkQPbDTUkn55fSJA+yRKIoQx1RhueTC3B94ERuyLGp7kvHdEHuIF4Sem7zBa1CLcqbTr7RIB7q8fRT1aMo4ELc4uo8ZYKm4Grv9bwmvgzvcvxzhWY76kcIweWmn6zT6+b+Pd4dTuxNBR+Ywm6w9muNeFwI2o6zm4SbV/4QAXcVyaME3VSdzonf3AhGazZOHgBCTHQXrXtj6VXViLCCg00/nkcjxqvbaxXy57KFBF0MsToaKQOmwlNARab4TeFdaV7N55ze5gLoGMi9xRDiVk62N4oB+gR7SX3XLxxr6vEH74RVEMJ4KG8x3Io9LQpEHkgPglrkAJhbuOZZqUm/YI1f+Bs0p92Jpp6Q62PFDbNTwSn2rlrkFOCrhKNXwa13ohPx7f1+bk9U6GVDJJSw392uulLgIhURSV9i060nbtcw8L7YiwP/QbzqPNpQzGj5hHReGHMTpmf5m5h4LnlsvT3VvgHesUsROs0Gj+MiQk8aF33TOvAujXg==
*/