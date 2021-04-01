/*!
@file
Defines `boost::hana::is_empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IS_EMPTY_HPP
#define BOOST_HANA_IS_EMPTY_HPP

#include <boost/hana/fwd/is_empty.hpp>

#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto is_empty_t::operator()(Xs const& xs) const {
        using It = typename hana::tag_of<Xs>::type;
        using IsEmpty = BOOST_HANA_DISPATCH_IF(is_empty_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::is_empty(xs) requires 'xs' to be an Iterable");
    #endif

        return IsEmpty::apply(xs);
    }
    //! @endcond

    template <typename It, bool condition>
    struct is_empty_impl<It, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IS_EMPTY_HPP

/* is_empty.hpp
Ipy/S5bgFmbtcWbh8gP7y8BCCTH3Ct+UOf7VKzzKbmpIbpljNhdQ5kJMcTqV/gn579I5nJE0xND9DywDkOcorEmZW1wVb54L81T3hfBAceHN5ydIKMHJxbNCwnKPt6kZ8Z200jFYWBIo3Vh2EQCiq5PM/lPw31I6OjfjAzsV9jxsbTYCSjI/3d9S1DEQr/VwfjSfsALaxGGz6t+t6q40CP4cGLxHqy4cEDXNr6IvRJg7cQVAGNqeVXxuQfwFMMYEjDTlzFl/yHNXtGYoqPzjQB+LbkU3SHwvGSKZiTXJh+cAMsCp3NU2dRHks6uCxQPDdf2Qg5AsSaqlU153MN0x/5/3FOiHhCOBdAZw6TKaaf8u/ddULc4SPc2zDB58ac8FQ8PCp38vCpJcd4rCCntSNryn9VHl5z9/AegbeSgajF8638iYCn9ITNE6Sb/pgEt0nhu6MdDciC6nkF9txP3IAzeIbaZ6YUGbw6pcDlfkYq9XqT6Ute2c4gyZRugm6ICA1ZHwhICFQoXwbYT3xW1DZstzh1cheFvfYXmFBoeuq9coltBlgbgyINTnhQ==
*/