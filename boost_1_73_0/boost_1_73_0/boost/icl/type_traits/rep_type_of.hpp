/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329
#define BOOST_ICL_TYPE_TRAITS_REP_TYPE_OF_HPP_JOFA_110329

#include <boost/config.hpp> // For macro BOOST_STATIC_CONSTANT
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(rep)
    }

    //--------------------------------------------------------------------------
    template <class Type>
    struct has_rep_type
      : mpl::bool_<detail::has_rep<Type>::value>
    {};

    template <class Rep, class Type>
    struct represents // Rep represents Type;  Type is_wrapper_of Rep
      : mpl::bool_<detail::has_rep<Type>::value>
    {
        typedef represents type;
        BOOST_STATIC_CONSTANT(bool,
            value = (mpl::and_< has_rep_type<Type>
                              , boost::is_same<typename Type::rep, Rep> >::value)
            );
    };

    //--------------------------------------------------------------------------
    template <class Type, bool has_rep>
    struct get_rep_type;

    template <class Type>
    struct get_rep_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_rep_type<Type, true>
    {
        typedef typename Type::rep type;
    };

    //--------------------------------------------------------------------------
    template<class Type>
    struct rep_type_of
    {
        typedef typename
            get_rep_type<Type, has_rep_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif

/* rep_type_of.hpp
2xAY8vlDig14y0aFLw6YoRVTWDPasyIqNQbxIrBaRgNcoE6Q7j7sw8Ti8p/tI17QDN17KFG9caLkLpSoSXrDu497RkS1RoMpjmneMtH4fTBJa9guhvdwvJBboHC5bGJmXICggJtJsqje0CBmJ3WepDcwr7bzCEmz/hTVhwBClWKDGwugDF4fNxw6j4YqbbCwvoWQF5BsA7VWhBBSeLC9C4ebwY6FkS1l5TLsHVKdNFKY2FLOqtGteI+QMtw0+wlnvXvj46dVEVUbVqdYQsJpWTi9kZCYdjs2r11gMhbRNyQXBWLfksyYkkcHrESImSt0UaRkhrEKbq7Qi+N7kgQE1LNd4EVLsUqr0s7ebyqmX3A+ci8riqjQcDYwzqGh/u51Mg/TPGE+Eet4UkxeOPUFe6b9gVZEZcYUDT2ULWapJyCLu2ivwBrdnjP7/fb7FCYcgoLPVSieSfLirduM2DZC4rOICoxLNmd1WxF9n6F1e/FK9N3ux9TWqdvBWFk+1zKiCsP9KWExY8ZTcgdXfJbQp6QpwrQeUGMEbydFVFzYpyOn2oQyI0FcfLoitnEe/wL26epfUEsDBAoAAAAIAC1nSlLSU4jW5gUAACwQAAAmAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvdm1zL2N1
*/