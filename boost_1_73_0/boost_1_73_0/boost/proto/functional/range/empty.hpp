///////////////////////////////////////////////////////////////////////////////
/// \file empty.hpp
/// Proto callables for boost::empty()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_EMPTY_HPP_EAN_27_08_2012

#include <boost/range/empty.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::empty()
    struct empty
    {
        BOOST_PROTO_CALLABLE()

        typedef bool result_type;

        template<typename Rng>
        bool operator()(Rng const &rng) const
        {
            return boost::empty(rng);
        }
    };

}}}

#endif

/* empty.hpp
DQtniBWN0DM1B5EXKk8G16ItyaOxBTlElaICoUe2mSpeipxbWb5G9Tke8bWnxpZHm7cHd9z1Iwdj981oJZMNR1qP+EqhwzHobUApKM70jKekPiK8+pd9KBwurY9DsfsQW+ApthfmTAij5T/u5WPXl3+aZTrYqO/pM6WNvqePkonI8+TZT8e3b9kGzim1U+INSem21HJ5tNJxV+TCkuWcZK7Y4SVSV/DDdkIF4dH6nm46rhDbiDnOqlCAjxMietc=
*/