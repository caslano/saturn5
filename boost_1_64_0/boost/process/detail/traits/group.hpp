// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>



namespace boost { namespace process {

struct group;

namespace detail {


struct group_tag {};

template<>
struct make_initializer_t<group_tag>;


template<> struct initializer_tag_t<::boost::process::group> { typedef group_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* group.hpp
AULD+DcXnWxqJ8mYHVCN9ZiqOB40y99SzuDxygQFejZNAAxtjYQVqTx3Xz+nK9JlyGrRmCQqX1h7G7j9NFh/yCkvD5KLfBroaKaG/XEsxlYqZSqxnHs3k4ZLMtn9jX63ULRaMn0t9dIdbfKaoqJF1haJ4vb8MmKY+gX2VB6CDoGzkfJRjDgK9mmssIGiDmOM3GoVC+f+zv6fCE4zcc4LhtTBuqhFrSZmZfpwCGaUC2nHQFiD2Wm15yOdZCVH86LwCG2tQfeU0HFhniLZzG/pJxY9BPlE8xMzIvK3b9SNlU8K9SqNCyycBJQJu1/rbxqSjockyYaQxlgpTRGKI8ENckeAs0mjrW1pPEvIzNoO5ca2m3aX0TxdIChcd2u3/jUpbHqRyNoESOJb2ckUJZThUyhbdzK2ZCQScbU/j+sRIPAST4DRcMAmdXJWjlucJ4B5vPutGDWW7TIcR5meQyqzMss79O93O8y7NyyKvmGx9DfSnxzmL1o2M+8xrHtsUYfVVwk3GOAg9Wm/DOL38VOceRwTEA0xReXf4PJ8UFafHr0u+fNwLqeD0hfprw==
*/