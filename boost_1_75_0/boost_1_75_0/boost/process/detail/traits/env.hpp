// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_TRAITS_ENV_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ENV_HPP_


#include <boost/process/detail/traits/decl.hpp>


namespace boost { namespace process {

template<typename Char>
class basic_environment;

template<typename Char>
class basic_native_environment;

namespace detail {

template<typename Char>
struct env_tag {};




template<typename Char> struct env_set;
template<typename Char> struct env_append;

template<typename Char> struct env_reset;
template<typename Char> struct env_init;


template<typename Char> struct initializer_tag<env_set<Char>>    { typedef env_tag<Char> type; };
template<typename Char> struct initializer_tag<env_append<Char>> { typedef env_tag<Char> type; };

template<typename Char> struct initializer_tag<env_reset<Char>> { typedef env_tag<Char> type;};
template<typename Char> struct initializer_tag<env_init <Char>> { typedef env_tag<Char> type;};

template<typename Char>  struct initializer_tag<::boost::process::basic_environment<Char>>           { typedef env_tag<Char> type; };
template<typename Char>  struct initializer_tag<::boost::process::basic_native_environment<Char>> { typedef env_tag<Char> type; };

template<> struct initializer_builder<env_tag<char>>;
template<> struct initializer_builder<env_tag<wchar_t>>;

}


}}

#endif /* INCLUDE_BOOST_PROCESS_DETAIL_ENV_HPP_ */

/* env.hpp
Axxib93YmSe5RWci70pELSMsQmKnnHEanPPaOnXlRzm1wR4tcd7tcnG4zSBqF/yPcHIQ3ke+zE/c08v7tte55xFDGxdldtt6o4pVoaeKi3Az2bz7n306zpWi5D9wnTcBbghbk5qvubyf/vKRrjb43TzPmdCXpQ9B/sW8lhbD+xVUsSCuDifscK7BXLRg0reFiVWbcxyxuLi+BqlqkMZKCu1lSm4pDs5g3W3AT7ppqwH2kt8DxJSxqu5GRwv4/pqSGKjaw+OzZoXETVomXruWn+xXW4di+rMMijY8nx8V6UP2irREP9qu1pCCF3PJeM52WltbVZHGqeU9DUsL09shiqKyr2RRDMh4Bxf4UOe2EnxS87Isv9NQIP/Ch5bf6IEt+y1syoCAF60qWZYWR7pMBfHNS4Q/nR9+ummtTBZT3lQJruhaWpp58zHLuI+am4r6zZeskL1BaWn94sxqGnVTxsBO7wbRj+TRUtoEr+XxhJxw0neSZbNmy3Oi1mDhVX5nR9Ljmo2UH/siNBPColRLWXzOexrx46lMiHP8y/YT3LzWDnHZyEEKP9jUSzq/6UdYwm0OvNhszt4ONn9gUuqeZj6U67Nk6DN+IPrLn6/Fqjpat1Y9Jqc8zDzENSW1hWVY6bsSkzQ7S8Q6L6Y+zN0F0l4Yvj3U//EjfFuWrN/no3r/dxjHhe9JffmQNGXsPX0exmEy+ShpYoA9MGVz
*/