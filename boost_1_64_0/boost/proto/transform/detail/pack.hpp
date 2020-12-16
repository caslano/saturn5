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
XLlifmBA2T3xUjZdLuRdm1hnYnDsC9H2OTszW0wRKezSu+uT4THJJPYWAtcp9slfYq2a6tYRNNbhaf7NuZ3KzBeMbGnGw8Ziw83Pb71qS7N/vSrHx819PPO7qOYar3Wvk7hX7H/bkIG4bYww2x1hfjYvbL9AtjpKMV2RbHVbc6259kbnntoguxvtB/li1KdEjFqhMqq14oHgdWdnP0rU4Z3EfyfVYRfxP1PQAe/7jYvXEt3ZYpwAHXw+0vXibiHR72a63cF0e57wBa/XfOT7psTj/ABa+bsaFxDthQHydQXI92aiv4jovzLOWZWzjF1n0NMr3lnTc5zxKJ+rKC8Nf5AtV0qFXcrSNLgwNg8/14xJI4X0UAqvdzuwN5pxCTFG0Um/CWmMS2V9knUQPseFLVCVQipnz51dDNgRhpezhzsbingL63dHTXJ/xR3DF9JnK53Xtefp6tVbSV+XsvjiVrYf+3bRRu9oxkf49ncSj8uIdvXEZwL36WzX5c011jgncWZD83hPs3++/16kFZ0HgSdl40R2Z5F+D8mdo72P+7xJvGXqW1MQ7zpd496VgyXqiYJbxvt5GZN4r6pzvL2nWltPHEe6bRLz26ua/X7qamrbDzL7+LXNg++2718jfM21xOvD5JM+Qrw+6sYANdbNHtVrL2Jdi9bA+LtY3nmkjzP9zdnHu1NH15BDl1fPy6P2uo631z7fWZqCN/2t3q5nsdSnRH/7dDM+or99hvT4WR7bsXa4gfH7vOB3YzM+gt9NxO8LRHuebx08koed4jinfeen3oP15oa3WDje+N+8uZyt+M7uE0xT8jOleEvO+QEoxc+Zbglvp/O3HXR25Wam55Za50+C9mOx9k42b34lw9cpgpFe+/yT369k+vyK0OdXm/VH3K8kfd4q+sPXRIx+G9F9o1acMck3WMz9ymb/eSPs9VO8pLz3OOvZOvPtZrzb6Vzvgc7pXRg6M2D3je07Cxo+kuXruEd4fcPeNdjDx6pJvZeOmIzp+NtCx99pxkfo+Luku+8JHZ9IcdDRNI+5k+juYv5rPSvrblHWD5vxEWXdQzx+xHh8ia2v/ljw+EkzPoLHT4nHz4S8Hxb+9hdE90tW1jKR537K8ydaa3uA8vxK0F0j7O03RPdbQXelOKP1O6J7SNDtEfweJrpHBN2fBN0fie5RVqdrWBv8Sejv8Wb9EffbiMcToqxRob8/E91fmG88nK2F/ZXgr6Y+8rSxVe9H6TJm5sPfOfFwo4OpTLWUwvUqF1/VPs/Dj+j9p6FsMT2cRVlRGpf+xselsb/zp2cLIzlnH208pNdHzpXvKlLdm2mP8B9U938yPT8mzpI8S3nWUR7V4tBNaal1HqD2HSqdv47yryC9PmX4D6bLvjeKRnN5/fNwqI996woKJZg7lk9rYTp7Dm+G3sHi1xkt3LZQHtL4+GxrFulgdovV2+0U49w7zpu+Tt7BQkHfoPDqI94R8r1768xP/e/86hFwOFvy5c9idpAtpREv+GkHcxVi64cXMpWsh2HwIgDmuSJC8TyV5UsI6nundwyMLoqOgQ+OFsfAqvmcDp1ALcsDrpKp5Og9Y8E7d2Z2aAxue66cs5JzPptPCNKBDjr86W1VjEtke3NavHZxNl/ovRMY+vQDWya3PrJwnPWRg5Bf7unMZfY7c5K/W3Co8GuNZKNXuftMZKPN+JfTLRPrCq1E18Zs+Sq2xjhP9IeDW/AR/eEQ4nEo0a6s9WZ6oZTVB4PcykkoP6P1XiHrYVTOC5msrxR6OJxku9fdV6I8L6I8nXwf4DnOg9w9gRe32D2B1bQncGRL0J6A4MSXriSO1b9BjFVHUV1eyuq/gbXVMaKtjm0=
*/