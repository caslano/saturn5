
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_TRAITS_H
#define BOOST_CONTEXT_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct BOOST_CONTEXT_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t page_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t default_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t minimum_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t maximum_size() BOOST_NOEXCEPT_OR_NOTHROW;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_TRAITS_H

/* stack_traits.hpp
F1MJpd3gww71IEeBrux/eRxNigUK2UdojAEBcEM1cFho8GSNJNfQRVnO7J+BB5qLWQB++Oq2GYLZDY5OzaL4uryIWOcRQ51+5hOKB5uezQkb7W2CLKF0KQohun4BTRYAkPdMlRaEM6ST9qmrkbQFCic9aqZa4FgSk6ekJ0/h5irdJRDll7GW3k3G74DTV8Fe/oLB5UeFecw7RcF79c9soeKFHvry1A2TUqig/vZdHIo8nVDTirEUOk9S+sfht96guG150GjcxH8paZooYu830eaobTChzMTdC62svluChW4fuwOTseR1I9xuojm+v0i8S8RRzsksOtsmJkg6zO0vRe3/2PJRWRKmCH1SQCdqy4ftiVxhptNGdpV9uwxdfXmw7AJQekgG4nUke7H6RYpPg0LHHQRO2buAVPmoHLLhkBQ38QXSqeW1zyN+Lrb/xDKpJMX9mgJwERrdEm3pn6qapp6/1kyT+wim+izuWUuCQHz19S7/a7xAgjYjIK1FKpMMWHlRpbUeZkqi+KsHUzdqPtntdH9TxwsBBWY8kt3XZ+oYHAfWxkgQlVWizQ==
*/