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
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
*/