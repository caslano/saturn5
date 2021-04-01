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
yOB6gtGU+hiwu0aa1AtSqjnBA6P5WIg0AZ3acUe5A7UAhIZagVVyMgD1BVe2vZWJTgL7oHKRpiba6i5Gjav+1XWPvajNDqXPACstaBAQwd69F/pT4/04LpyQWUVUKOVb1TWNzOINL7HiZSBaaxY0BnmseykqbJoeo8yZ9xg8+z5Fuw5wULtthryif+T3sishYqfMC1yhoNqmI0iK/93vQtpjbEhphkOhPKCfcASUI757w/v5URox+tEv8Y+SSU9IUAS4lHhQHCCp1DyY5sDJpBEDJVgSKhHtjAEa3b5cNAzGkWHxUSRt4Lr7Zq7R/S2n+aLyeUa1NWhxT3BMEs0yGCf7neMSkzoVwdkqsTkXFoeoMMKO+iMbndic+3YJFJPqmuTr5cMWuD2ujuq8C9HIt50B76FG4UkXpjK40ki+iwlXUwj70b0SB+FwNe4J7IMkS+fU9AR1BtYwPOYAGAq3qzWswTeSlKv+vPYICRQLNQWhESbywaJvb2tbzN6+ir9OAeeZU2rRE3uw3KaflNBM8uHVb4Kyvh+qswUM0ws05nOxYTwOgO35HaYi8Q==
*/