
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
1oGIL81wPQhDYgf3ZL3IwffoK9bChSTPyuBcdjw2j9Fpd2Z9PL97nBMPa72LeTbr8gZk7KnEgo8TMUCEazR/u5Te9oihmE3h2sz0qva9QX9VtHS5al1fz0OJN/dnbcMgHEU/0fsMU1EL1F5iWRJwqiD+Tp6t1+Bgkf/JgaxbkZUkLtp74c/Gykej7ccJUhO2QOnZxhnNFh2KCZR0EW6PmmHZeoC6f34pkBuJ2U31r2epJlwHu+VoilKNRv2f/4ZIAnXEGViun28xzOqtAv/ajuFGWj6JamchebVuLlRxlts12iV1Yq94GqprdeZ4g66w7AJCRDn/hkvgPcExn7uVVAf+XSA2e0EPdnItgnCdzw9bAUC93eFtueyh7pAyzPASMTRtmINSevP7eWNLUXbC7Iu7SOtyKYRZho0s78D0AbY4wC4ikZKgtQY3n6B98YOlkN/gjFDCfAAPNXRgbNpZ/ThcvC1gBV1KEedzvVmEppbIbBwQ1Sha+tiw7E9yHJX/ccyhtrfArQFlCChtACt4pDi0wa3rvyEFRDwe483ZnfzB7WfAp/VdHLmBeg==
*/