///////////////////////////////////////////////////////////////////////////////
/// \file template_arity.hpp
/// Replace all nodes stored by reference by nodes stored by value.
//
//  Copyright 2011 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is based on a similar one in MPL from Aleksey Gurtovoy.

#ifndef BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07
#define BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07

// Somewhat indirect definition of BOOST_PROTO_TEMPLATE_ARITY_PARAM is
// to overcome a shortcoming of the Wave tool used to generate the
// pre-preprocessed headers.
#define BOOST_PROTO_TEMPLATE_ARITY_PARAM BOOST_PROTO_TEMPLATE_ARITY_PARAM2
#define BOOST_PROTO_TEMPLATE_ARITY_PARAM2(param)

#if defined(BOOST_PROTO_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) ||                                   \
  (defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES))

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/int.hpp>
#include <boost/proto/proto_fwd.hpp>

#undef BOOST_PROTO_TEMPLATE_ARITY_PARAM2
#define BOOST_PROTO_TEMPLATE_ARITY_PARAM2(param) , param

namespace boost { namespace proto { namespace detail
{
    sized_type<1>::type template_arity_helper(...);

    // Other overloads generated by the preprocessor
    #include <boost/proto/detail/template_arity_helper.hpp>

    template<typename F, int N, int Size>
    struct template_arity_impl2
      : mpl::int_<Size - 1>
    {};

    template<typename F, int N = BOOST_PROTO_MAX_ARITY>
    struct template_arity
      : template_arity_impl2<
            F
          , N
          , sizeof(detail::template_arity_helper((F **)0, (mpl::int_<N> *)0))
        >
    {};

    template<typename F, int N>
    struct template_arity_impl2<F, N, 1>
      : template_arity<F, N-1>
    {};

    template<typename F>
    struct template_arity_impl2<F, 0, 1>
      : mpl::int_<-1>
    {};

}}}

#endif // BOOST_PROTO_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
#endif // BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07

/* template_arity.hpp
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
*/