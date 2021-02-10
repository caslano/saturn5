
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_STACK_TRAITS_H
#define BOOST_COROUTINES_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

struct BOOST_COROUTINES_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT;

    static std::size_t page_size() BOOST_NOEXCEPT;

    static std::size_t default_size() BOOST_NOEXCEPT;

    static std::size_t minimum_size() BOOST_NOEXCEPT;

    static std::size_t maximum_size() BOOST_NOEXCEPT;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_STACK_TRAITS_H

/* stack_traits.hpp
7lgpsmHwuqG2kGkHD8jQSXCWXDqXQbgYjoIEb4LjfLd5LlLBKxwczmpQNUt5PwqjyHHA9qIAye8k3ACTF0xtL3FnBzDa2t9GTG3sTu3puZPE7qVjLodBg/wLUEsDBAoAAAAIAC1nSlI4O3sW8wQAAKUKAAA9AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9ETlNfU0hVRkZMRV9BRERSRVNTRVMuM1VUBQABtkgkYK1WbXPaRhD+rl+xQz8UZ4hw6kzqtGmmCpZrTTBiENj1DDOaQ1pZ1xE6encyZpr+9+6eBLaT5uVD8IBgb1+ffXbP/rIHz77by/PZHXz1lbp3Si967o2mWv2Fmf1/gzT9AO0fGS7p+Q2hhvBg9SE9gm+y+gB9Z5V2sd7w9zT9hnBLTpI/hmy8TPkrSVrLzn6kNjstb0sL/dERvHj9+hSew0/HL04HcCZqiRUkFusV6tsBvMmd5PdS3N/7Bt8OAC2Iyn/icF5KA0YVdis0An2vZIa1wRyEgRxNpuWKfsgabIlQyAphFE9voskfA9iWMis7PzvVgClVU+VQijsEjRnKu9bNRmgLqiAP5D+XxpLPxkpV+xQewaJem84NJyEqo0DcCVmJFYUTFkprN+aX4TBr
*/