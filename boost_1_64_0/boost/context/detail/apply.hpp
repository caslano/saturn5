
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_DETAIL_APPLY_H
#define BOOST_CONTEXT_DETAIL_APPLY_H

#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>
#if defined(BOOST_NO_CXX17_STD_INVOKE)
#include <boost/context/detail/invoke.hpp>
#endif
#include <boost/context/detail/index_sequence.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4100)
#endif

namespace boost {
namespace context {
namespace detail {

template< typename Fn, typename Tpl, std::size_t ... I >
auto
apply_impl( Fn && fn, Tpl && tpl, index_sequence< I ... >) 
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    -> decltype( boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#else
    -> decltype( std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... ) )
#endif
{
#if defined(BOOST_NO_CXX17_STD_INVOKE)
    return boost::context::detail::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#else
    return std::invoke( std::forward< Fn >( fn), std::get< I >( std::forward< Tpl >( tpl) ) ... );
#endif
}

template< typename Fn, typename Tpl >
auto
apply( Fn && fn, Tpl && tpl) 
    -> decltype( apply_impl( std::forward< Fn >( fn),
                 std::forward< Tpl >( tpl),
                 make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{}) )
{
    return apply_impl( std::forward< Fn >( fn),
                       std::forward< Tpl >( tpl),
                       make_index_sequence< std::tuple_size< typename std::decay< Tpl >::type >::value >{});
}

}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_DETAIL_APPLY_H

/* apply.hpp
PjpM6qCw+9lOFoYnYN6acGk/3LzqMsdzHRsqThSSBdBxPv9DbxA5YPD27wOgS0uDNtrWcbtC94NgP/TrMH50veQ3QHfJAciuraLsbclA3g+CvH8H37Z7jX8gMTFi7+X+UfTg53A/8aF6mXODfvXV0s/o137R314ZN+fV+rSqa3A9kNdaue6/1AsN+Db/FerolXN9OH7+Bn7AKjMOesVX+Ie0YWGdeVfE4FM+4//L1GnHzeOQT2Ui+V4D3KGUdUfMn9EQjLu9deExP6vBT9fUhePU7YX0iaFz07gmyOvx6W2pPOud7n/MaYB1uinv9ci6lznLeITPc80InDs6qiHQqXZzF3Iu5S10cmoIxyV7EqUVh+rgPsvXhnFqpcyouYcwau+yNWj/Kb5f/hiQP8Ei/XNcIH9ea8V21kvdBJe6IfaBwW0UXIIjn1wW+WwJ+ATaNLcgON/RM/iLDP45gr9Y2yV823adAPlUJpL/ZKlvvzmDelJDuF0nS5rg2C5OI59PDfhUfObzVOVDaFs+lhJsS5We56At+b717ee7CKhrVycHOtp76EmdrmRvf2cXbyds7Bno6+pY2722q1PiIVRNWaavv3d1P73NQQsCUmbGlGXc+2v969s7qJpHDrxMcmNfX1c/Mbm+s3tt/8Cg0ph5IDTW954XR8O79D9TEenu7afI1RuJ1ult3iY661ItZ13aGqaUsH/0ZQokMg37TwytpY2lh4M9ez7DPknbpYVU8O75GQ3h+7B7JkeSXEpND4DUL9OzWgu5VD6fHAveEDm/hqMGJgmaHRo9jWHzuG6G0Vr2ttIZgC28J6a4bd7Zsge7DHii8wi07+320an2TI52+pkrC6xwrnZslMLNZbYXs9qiAAA++fIGs7/T4JfN65ts3Aba4KNamX+B1TjYaGrCwUr7O8B/QmS6ayhdSIKza6Dl91wOoP1ujnJWQ7DPcWHIb9s25i4ep3JjQyOyVupw5zj4tlymmPVhSeqTyx1sjM4DEJ6Wf7WDUVPzOX+/61lUdp+D5f13hPT82tmoT1VMmJRnguplvhEgfVapzcTxMi6HgFKfrZQ+O7XM/YDevi5655vLa4LLXhHWXyIpGkx5Cp/hw7OZXCHwdQV3IrOrdGbmtbzPy3DHXwk34cPyIxl+FYjhqxoM3H+jylsmezAdILvGacggVl8OQN/4HbOGsJ/XTelqjinh/9DPWy3fpjVSRmJCMr4n51SDN/vGeJxousYbKZKu7sCzQWtZHm6NfrKYDcd2oUGGMV1ogFFaxqXcByCdk7nAOpDb0mmM9z+FxsWm0PmRPdyffZmMxCNMs43q8HlcHYyTizkGBsI7hugs1ESHRCSEtlN7+mnMdU5oGy6p4bnFSCG9k88idmRoXO729ewlNa4N3enJIb08VKLIZV9J+cu9IuP2099neZrfl0tncnyeWNu20hvgs53rJC7iepDTGi852EdH99avX9XecS4t/m1a209vY206nUVWJo915rA6R7uR2qJ/z2okP1Zk2sN1bCm9z9/L6fWpndSDIHOeg50q9rIP+JpVYdzG3tmb5jcL581N4isNiB7nhPd+5oOL0Rjx+R8kWI3Hlx5L/Zng9FCOpsGBzuq+rOosx0MqlvZdu1lv3fgj0oSnY34j6q605cLMcNASAWg7YvdeDrovaY+loUJcw2nww7ERGkq+Kv+tc4/nCFx92OeKz7qlQWIPiz3ZKnhaRmOOXCBw9VOHGvwf+qnDQmPE1LXF+MspwRsTvFXQ5/xmE51CHBkPzvlSebZZuRw11gvOFib4vp9/52iZ6O849GGryCxies0aYL/h90Jtl8YOUP6rwzq7Yxr9NVXdGaHB659m/rA=
*/