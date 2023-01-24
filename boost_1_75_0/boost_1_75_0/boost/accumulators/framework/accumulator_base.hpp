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
4YDKWCDj3PoY9GGnORug+ltLDLTtGzhLAR0fQM2Qtzni3X3JsOZRusUHEpYiy5KIqsWzITjsMHpn5wP3UTQM98nzzHa/2bBTWRWQ/DngIWGJxFbZlSoo7l9KxXTeuF3RxKYq19S7FMkmoL0sTJ14jQBzIbc65fFkRLdD2/iOqmvnBuSjAWySjn5Bb2wbYKSqeBUT7GtLxFLm3MGlcpwr0Mr7XwPGdQzubxCLAuAY5ceV0J4h4zGCIBv0Kc7pzhjk9MSxd1ifUt5iDUXwMKFnvrvaqBfY7yGSNOq8X0ISVHBF1vkjCN+Jya3tqEg63kusUPL6pcQE+em6jK4NyNRuKUhxlPZrawaLVzIJRW9wxyMZcjdMKRX7r/4RnT2reiseVW/lm6/6zuutLLtAb8WyOk5wc2kc5974ESe498KlNFgIMI70wcVdyaoBFvsNaFPwDVTZRLqZ9+9cYOCmNGRfmcr7X4WgZwT7G1RDekPiA4A2b/WY2Il/96FKzQn43GyxVe9khymikDz9Pga5ypwOdt34fns63gXIExnR4KoeSVCAcJOMUqmxjC3GjLHPIpjwOmSDSm/FSluyb/aNjOypQrEqAKafTsEq/jc85URG/YDym04HQxc6QJIDRR6p6UGxOxVy9FzMAzJMTG0yAvCnw9bfQmOAHDkP44O5Qxx0cmGIg12ZhejN2g6tXhPC956xzbvSofv/50tUjfSk
*/