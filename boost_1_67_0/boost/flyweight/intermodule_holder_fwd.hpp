/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_INTERMODULE_HOLDER_FWD_HPP
#define BOOST_FLYWEIGHT_INTERMODULE_HOLDER_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace flyweights{

template<typename C>
struct intermodule_holder_class;

struct intermodule_holder;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* intermodule_holder_fwd.hpp
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
*/