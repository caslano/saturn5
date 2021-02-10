// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ERROR_HPP_

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process { namespace detail {

struct error_tag;

template<>
struct initializer_tag<std::error_code>;

}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* error.hpp
bC1tYXN0ZXIvdGVzdHMvY2VydHMvRWRlbEN1cmxSb290LWNhLmNuZlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLZMdtJRAkAAPIRAAArAAkAAAAAAAEAAAAAAHT1MQBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9FZGVsQ3VybFJvb3QtY2EuY3J0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUn9aevUMAwAA7QMAACsACQAAAAAAAQAAAAAACv8xAGN1cmwtbWFzdGVyL3Rlc3RzL2NlcnRzL0VkZWxDdXJsUm9vdC1jYS5jc3JVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSuDOakiIDAACWAwAAKwAJAAAAAAAAAAAAAABoAjIAY3VybC1tYXN0ZXIvdGVzdHMvY2VydHMvRWRlbEN1cmxSb290LWNhLmRlclVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlK30WdTDAUAAI8GAAArAAkAAAAAAAEAAAAAANwFMgBjdXJsLW1hc3Rlci90ZXN0cy9jZXJ0cy9FZGVsQ3VybFJvb3QtY2Eua2V5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqUMqTM4AQAAWwIAACsACQAAAAAAAQAAAAAAOgsyAGN1cmwt
*/