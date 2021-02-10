
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
BThb5+Fz5aJ46oYhmIOTITbqWTx1zxeXOye7r8Z/UEsDBAoAAAAIAC1nSlIqLGZBGwQAAM8IAAAuAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9BTFRTVkMuM1VUBQABtkgkYK1UbW+jRhD+zq8Y0S92RPDlrm/ppacShzQoHFiAk1qyhNawhG3wLtpd8qKm/72zgJM6d9Llw2HZ4GFnnplnnhl3bcPBd7ss14SDb155/83xwvvOaSHF37TQX3fI8ycYPui4xvsboGbw4vWUT+FNXk8w6b3yEevEPOf5G+DWJknzMzPO69w8omXwHP3non2U7KbWMJlP4ej4+Fc4hPfv3r9z4IxwRhtINeUbKm8cOCl7yx81eXhwFf3kANVAGncvYFYzBUpU+p5ICvjcsIJyRUsgCkqqCsk2+Idx0DWFijUU5vFiFUR/OnBfs6Ie4zyKDlQtuqaEmtxRkLSg7G4I0xKpQVQYAeOXTGmM2WkmuIvwFDSVWzWGMUmQRgkgd4Q1ZINwREOtdat+m82KTjZYyawUhZoVOyrcWm9fVbXCbLbkEUSrQQvoFHXAnHdgK0pWmTtShMa22zRM1c5LWgjIy5mQoGjTjOHQlVE1lEAhHdlyzEloMXumzU0J
*/