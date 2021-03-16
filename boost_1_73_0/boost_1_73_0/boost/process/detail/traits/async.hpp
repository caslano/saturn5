// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_ASYNC_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/decl.hpp>

namespace boost { namespace asio {

class io_context;
}}

namespace boost { namespace process { namespace detail {

struct async_tag {};

template<>
struct initializer_builder<async_tag>;

template<> struct initializer_tag<::boost::asio::io_context> { typedef async_tag type;};




}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* async.hpp
JA9/pfJc2K8t3nzZW4eU9/semarrURsF3FyirCBPyyulf0nww8lz00tZz78CsTmhfD9e21+WWlon67vUU19FuV8FNJ3ULqECemfK/bwyrIiGX+7XMsDOEWEVxOZ+vTzlvblfG1n2LLlfbw+dinI/yfclAcevszSc+/WCc17TKKrzy0U2dPCuj00J8DXsw8kdszN/1RvC7aMtIdbPxskWthSDp7RnoLCnM+GEAn516XZ1nS8OXycpcQYFeP53pro=
*/