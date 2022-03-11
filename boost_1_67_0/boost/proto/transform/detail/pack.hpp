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