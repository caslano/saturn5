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
NVQxdRbY2DdRhmb7NHhoaPvJO7AbG7JbzFw6MM7g6tnJetNAWyUSSemfdlxrAkCNRXF8I5m3MTGQcXPb1WvRN/uNahrlNUqQb+4xM8HqrKPtoUZ4pnmHm1Nb54g27pBRa5cDuv4FZ/mcAYMsaxXOXtMvYaadL1d9cTUy1UhXDdICJ7GwsFNwxWaxM4+zfLNLkMld1MCejCPnfi+5KCV05R7cyHebM+lHN3mmzhp3aa6dppEe+m1XLpAAd3S2Cwd7hWke9Sxtws/uII2nw93CLEpZQvdFuzetIrCiYiVQPGixZ5LOIPwhv9YL5gr0oKZHxGXJj8dcdpcLMh2U99aca3SfNxsjyf4ALI5kshuAshebnqDqHRJYx1JHY+vI7R2RVRvCA2u/BzAtRJrMi1pzt7x9VmFCITxRWWsyaXec/SxNGdk2dbF+7NLO87wb+yaFG+SP/86yUCcax3j5b7KmokxIPZG7YLzv9eAd7sG8rVmGcdn50Ewi4rOcCiJloQXwQtUZ6fyRrfwxPElTqyh0zf3EPBKw+J7S4PEXKLMTDGOJnLaEIx2FgRJD6g==
*/