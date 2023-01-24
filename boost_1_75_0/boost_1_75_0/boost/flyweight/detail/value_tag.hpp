/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP
#define BOOST_FLYWEIGHT_DETAIL_VALUE_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

namespace detail{

/* Three ways to indicate that a given class T is a value policy:
 *   1. Make it derived from value_marker.
 *   2. Specialize is_value to evaluate to boost::mpl::true_.
 *   3. Pass it as value<T> when defining a flyweight type.
 *
 * For the time being the interface of value policies is not public.
 */

struct value_marker{};

template<typename T>
struct is_value:is_base_and_derived<value_marker,T>
{};

template<typename T=parameter::void_>
struct value:parameter::template_keyword<value<>,T>
{};

} /* namespace flyweights::detail */

} /* namespace flyweights */

} /* namespace boost */

#endif

/* value_tag.hpp
XlPF8hbYAUQLpTYXEOfuzQ1zGM5nrfS05fbTQe/j5oVF27zYYlceqDRTKGRh0mJyxIsaZql6sszt5aoBo2um13CGqCxIOZzLlUP/IFQO67hyyCNVdFzGWneLv92yNNMXgT5j8w6Sjhy/KVZt0HpsUPLJ4UB8VTgbIw5grTgEJqNKUiXvhUNgTtj0OeJqXW4vuM5SczBGPbEhVIVqGsc+GjVMztZiWyeIE40OHpBNyCoTiu3RrI3pPTRzCYpOSIEtXQZxyz1tNaPZ/ne1naISsVNEjb1TLzrA/7eW9ouWcsnLTZGW6o4x+oklxIpweoxBwQH6HzdpyxnMCSeeG2JIx/0pi/eFPkSeMFgR82FjaTu9H83et9wGzTiOyQ2PqhY86UE3KG6E+Hi+phacMOvVAsRLXXszqAWFXc20YOwNesHbN2cII37b+Zl8WxDwWEmOz0XhLKJ/v242hdWUIGxf7YNoiot/414eqZMfkKUFHslXDELJ6l47rS0PwNlxXjpnZ/xuXyeVmyl72A1npjycIhDb/O3/G4mPwsrO5P/9xMQk7oSa7997W7opUMp3ud8o5QU+fZv7STLnBkj5v2qMUl63TtxZw+2w1If315BkqarZXcWI/BLx/8SzlmShEsFdkINqPR+yvQbS/jIouWzoNvChKyAcxz2HrqG3PEcSUeGS8Shc/e5LTyrs5udX6OGBl2gD7rLngnBk1VAS
*/