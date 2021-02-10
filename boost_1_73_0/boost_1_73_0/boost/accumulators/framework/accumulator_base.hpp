///////////////////////////////////////////////////////////////////////////////
// accumulator_base.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/accumulators/framework/accumulator_concept.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    typedef void void_;
}

///////////////////////////////////////////////////////////////////////////////
// dont_care
//
struct dont_care
{
    template<typename Args>
    dont_care(Args const &)
    {
    }
};

///////////////////////////////////////////////////////////////////////////////
// accumulator_base
//
struct accumulator_base
{
    // hidden if defined in derived classes
    detail::void_ operator ()(dont_care)
    {
    }

    typedef mpl::false_ is_droppable;

    detail::void_ add_ref(dont_care)
    {
    }

    detail::void_ drop(dont_care)
    {
    }

    detail::void_ on_drop(dont_care)
    {
    }
};

}} // namespace boost::accumulators

#endif

/* accumulator_base.hpp
eKlcPsV0qf5avM6gxQJ1GNazHWpKRRpRF7O1lbFlkY3xjkDcvwcmznKeeA6KDi8hf0JNlR8N27hpct1KPSV5YAKCR397Wa+nHKwz5O6rDK8y1gdezuFdX5imybwp++o8WYxNxcDVqkvkC/7VnRqtI9xVD7qj7qDf6tUOBoCxDHE2BCHcbdjhIx3cEa+Xb1HDQfuHz7pFxeH4Y/UtCofzFHwn9jPeuX0/w7Lf735mPOTTeMpNDvG88ib3fthqTz03WMxr9QdsdBzhFTc6WXmFjY43WXGj44hYaaMzKHqljc6k873Pznd7qzHe3hNz3l4Z6+39gXhv71HMV7z7Wdly7wHKZ/cYEDQaOJ3h8QMZc28lztx7AGvuPYg39x7AnHuP487h3qh93D3+jNwZ7yXjuT+vyp1iQFW5k7NyGXuq/m3sKQr/aOypPVXT+3cwrVicBzGtc/zDqNt/M1iZZ9UaVeJZrXZlnlVtVuJZhYwVeDbLDA/cUXsHrc/JskDPE7cyx/LhPOF2yju376ZY9mTcir9MJ8Dn4WFLGZ/jU2q5uAgVGROrsq3pZA52EyEUz8dq68Sr6w0qdo4HJ6P6K9XktDfoH2JIi2yyCC5ghjUA8hD1mC9jxU1YVl5hD+ZNVtyCOQZX2oENPnkgM7/u
*/