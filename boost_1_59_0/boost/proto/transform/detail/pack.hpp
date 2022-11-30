///////////////////////////////////////////////////////////////////////////////
/// \file pack.hpp
/// Contains helpers for pseudo-pack expansion.
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_DETAIL_PACK_HPP_EAN_2012_07_11
#define BOOST_PROTO_TRANSFORM_DETAIL_PACK_HPP_EAN_2012_07_11

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable: 4348) // redefinition of default parameter
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Fun>
        struct msvc_fun_workaround;

        template<typename Tfx, typename T>
        struct expand_pattern_helper
        {
            typedef T type;
            typedef mpl::false_ applied;
        };

        template<typename Tfx, typename Fun>
        struct expand_pattern_helper<Tfx, Fun *>
          : expand_pattern_helper<Tfx, Fun>
        {};

        template<typename Tfx, typename T>
        struct expand_pattern_helper<Tfx, pack(T)>
        {
            // BUGBUG fix me. See comment in transform/detail/call.hpp
            BOOST_MPL_ASSERT_MSG(
                (is_same<T, _>::value)
              , PACK_EXPANSIONS_OF_EXPRESSIONS_OTHER_THAN_THE_CURRENT_NOT_YET_SUPPORTED
              , (T)
            );
            typedef Tfx type(T);
            typedef mpl::true_ applied;
        };

        template<typename Tfx>
        struct expand_pattern_helper<Tfx, pack(_)>
        {
            typedef Tfx type;
            typedef mpl::true_ applied;
        };

        #include <boost/proto/transform/detail/expand_pack.hpp>

        template<long Arity, typename Fun, typename Cont>
        struct expand_pattern;

        template<typename Fun, typename Cont>
        struct expand_pattern<0, Fun, Cont>
          : Cont::template cat<typename expand_pattern_helper<proto::_value, Fun>::type>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_value, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_PACK_EXPANSION
              , (Fun)
            );
        };

        #include <boost/proto/transform/detail/pack_impl.hpp>
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* pack.hpp
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
*/