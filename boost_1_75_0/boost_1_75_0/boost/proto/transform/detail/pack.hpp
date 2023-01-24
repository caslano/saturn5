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
4AurP8kZ7Yj4SmfLCx+krV4z/yz0ylw4XUoqyG9NJkgmNy7eTJ6jWZL3RTJACDyPGRyMex5dn7MCtR5Hm389ur/BnX8JslFpZ35a0INtP50IWEnLFN+anuEfk2wWhl8uBNWpnpI4DtwKnBuq+4W+YdWcZf+G6h3F3eNdW4NNfeH9CzijO8NwcmZuVb3M7B31J+QbYJ1TaUggzuOSl1/8853mEX8nrSlAJuDQ4bLhLc0OV0Vo2jKGw+0lgUi/UdVfT2W+hQ3bVeFImvY/xL79wjAZOUx09eC3ZktrxiAQl4EAC2attOlADlRhLjAvuA8cKzDpBf3lQn0W+EhK3yjr1Bb5gkmzbQ0JlzwigQsHRhq3fdgsRhbpHXUfdh/5k7gdCw1U08jVnPDeecNZ4ChVF8pVn3E7f/5lOebpC+zpkmXB0e89z7zGvGlZ56cJe7Jb49d/5YIdNEQR12Ne/TBqMQU4cxB74DRGrw25hTOLmj5yMBhuxCvtpRUeFkom+t8dQHCo2nnFN4dgkmNUzSozVc4fhmrAavHNSzQ81pySSxz7ANvTgVXjK8kas2s/TTmWX4AcJimzie87xQUitcEFrIAzzOBp3RoRs4mPNnI6Z9m/et4CurwlMx1HR+8+CEOV/aUz/S8D7gISbrBGdLN9Xekl8mFC5cqXWcDk1XZLLGp3Ytyo7bR38jQQVJhFnLDxn+hOSX69X3CcjCet
*/