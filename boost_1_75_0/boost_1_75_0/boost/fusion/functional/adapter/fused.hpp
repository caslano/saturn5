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
PStviboflbc0o2bIW5rkE/vIiHWCv/XxM08UIl/3Pg5tNTDkMfGqVR9jJTGWqYtk/rRUNuzjt78Ugty3vfEZL/IHepNYJw1h+eze5HeKsPcQ/9FOATSsZisLEucevkUKcTNuYV+tTLpewNc7+Pkovt4krt5ZP/7i806Df1PEP3jcG157s/iuIyeO42ssX1vwNQZTR/Nd2C1B/AFI3g1ftcKQsyxmfwDPz+AsRYFqPT0d4BfFMtaT3UnGAvIBGWtSGMpY12SgjHXtzShjnX4t2gBdscXblXQs5mVPhxEUz+tsbdcs76H77+ilZKwUKWMlxb9HItYddhCxjjoLx9s5YvSdmpGX9D9Qpuq7mKWAHSq9HAYYv+LNYX5zHVti5Wlk5ixcFab8FRI0+zTNDnPebxHSSeEinQwvNZKjBajY5/G9nlfi+jBBFok9D5kdFz5Aw6nzCD0dYO6dfL00nEr0HKq+WzMSgmqR7slVPjfaVK2FerUMmyKoFu+aIACEfAkViqQK5doSPd9QcVCztoZJV7pes2io2RtiRMmYS2pMxdLuGnUiwmzMlaWMubJ0Y64szBQfhzbmeoMUggBEokGVoHj4NAAG4Jl0AFAJrsmz4P08fM8YBlwFG0e0lNbtY8LICjsLIBjjE1dEUJfO+CWa2OSbfWAFyXWmFGxpOD6xoE+HXLv4Gcbw33neWXfYLNCx7NEe43M9ch17tKts
*/