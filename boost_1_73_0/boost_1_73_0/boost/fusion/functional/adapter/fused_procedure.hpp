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
1XCGGfTqcfcRpovZccYBY9qgrY9WXZBXysT6HklBwBiByJvXbmWFoY7mN/Zl37h/4zgCLfOLvPSc2YvpdICJVTHMIv3yttPbxfJPWk5DreIPsAJXTh1ZoUvQmj90N7NpSjUyhQ8cwWIFu5kV00VKFz5hg/uC8LRmGEl7kBoC7+kEQaQf/D0+OZcYP2VOLpi3z8oHioD4XOJeJi4fo/qCEM8K2LfytAYFc27l/QFlKsacjxgz5UWWxYGA7pB89Kwu3g0vFpNAS8BTIuTTqITxwJiODvFxWaCJdMwhi+RY0W2awr1AioCq/zw7Q1MB7McY38PvdUCzpMSMmGTYQefMCTncSIuPDWiJ+FsSyiCaXThHGG3uvybvE0zbPK9F1q8yjDBEMRqaSdmihfFiSCEwO668NkOZDGgJvLRTMwxFuE5uNsxRrhFJazbkmI4rkknB4bVEOFqbtw7vqxcyvqEzyKGYJYEOzn8Ie8OiWiTTPvuZOLxme6slUQqlveNtTNbZS6hhIyM7rucOivs9FlIs9WgkJEiY2zbWZKm3zFGl1ANVYm9v7au1gBxZg8b1BwnxRgTHGSeyuUvQpzRXucAb3MY4gIKY9qCYDIi0vNmRDpbEib4p11wsq6dCrnP5LXsCz4UML28rv2Nb9F7p
*/