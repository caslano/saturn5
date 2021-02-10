/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_LOCKING_TAG_HPP
#define BOOST_FLYWEIGHT_LOCKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a locking policy:
 *   1. Make it derived from locking_marker.
 *   2. Specialize is_locking to evaluate to boost::mpl::true_.
 *   3. Pass it as locking<T> when defining a flyweight type.
 */

struct locking_marker{};

template<typename T>
struct is_locking:is_base_and_derived<locking_marker,T>
{};

template<typename T=parameter::void_>
struct locking:parameter::template_keyword<locking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* locking_tag.hpp
lQ5evLJa2TXtqThydCOMe/prtyE7EbzSl2qjJhNC16GyRw47Rc4fdP5kXnCF1VJaIT0KYz8XtjKiX6LxJLoaT8bxTfDMtGozYAO1Q3SyLHPL1Nv+62/7r2wTf2YgB49p3/Rfu1pcDOPVYgq/RJPV0NWzbcBej5vDsw+OtrMcDiGaLGf43HO1eOI8dLCvYUYPF58W43h4eBjytw9YUeCHxwSHy9V8MouunxxTP31WmKNPrlaj0XBBzfZA9V9QSwMECgAAAAgALWdKUvTJScyJBQAANw0AADcACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JFRElSX1BST1RPQ09MUy4zVVQFAAG2SCRgrVZtc5tGEP7Or9hRv8geguw4beok7RTLckyDBSNwXE/VYZA4zLWIUzmwrGn637t7BxKiycQfIo+F9ti32332xZoP4PibfQyL1MFXP5H6j/CDz1bIL8WfbFl9XiCKPoH+Q8E5Pp9hagR7qU/RETxL6hMMlVTU2HpHv6PoGebm5CR9jUh4HtFPPNGSjfxYrLclf8gqGI6P4PT8/Ed4AS9PXp6YcBkXnOUQVKxYsPLBhHeJOvkli5+eLMl+NoFVEOfWgcIw4xKkSKtNXDLA3zlfskKy
*/