// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_TRAITS_HPP_
#define BOOST_PROCESS_TRAITS_HPP_

#include <boost/process/detail/traits/decl.hpp>
#include <boost/process/detail/traits/async.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/env.hpp>
#include <boost/process/detail/traits/error.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#endif /* BOOST_PROCESS_TRAITS_HPP_ */

/* traits.hpp
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
*/