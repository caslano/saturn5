/*!
@file
Forward declares the @ref group-core module.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CORE_HPP
#define BOOST_HANA_FWD_CORE_HPP

#include <boost/hana/fwd/core/common.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/default.hpp>
#include <boost/hana/fwd/core/is_a.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/core/when.hpp>

#endif // !BOOST_HANA_FWD_CORE_HPP

/* core.hpp
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
*/