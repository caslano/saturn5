/*!
@file
Defines the @ref group-core module.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_HPP
#define BOOST_HANA_CORE_HPP

#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/is_a.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/core/when.hpp>

#endif // !BOOST_HANA_CORE_HPP

/* core.hpp
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
*/