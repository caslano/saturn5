// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_USE_DEFAULT_TAG_HPP
#define BOOST_PARAMETER_USE_DEFAULT_TAG_HPP

#include <boost/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct use_default_tag
    {
        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(use_default_tag(), {})

        inline BOOST_CONSTEXPR BOOST_DEFAULTED_FUNCTION(
            use_default_tag(use_default_tag const&), {}
        )

        inline BOOST_CONSTEXPR use_default_tag operator()() const
        {
            return *this;
        }
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* use_default_tag.hpp
gux2IVPd/swjqWf9VWSPKMCxDJ77qGOtkb6WEWhRob9+s6ubyDf8ZvKiuj8k4hu3l++Ybluii2zLUJ1HtO3vGiCH8iWfA2szSEaMMJ8btGYMfldtcKfZ6uRiCZ87/Pter3c8gDUsJoKFBgbxlFWJYaQAAClASyGLbdrgS7N/YGuhBsnNzPRUqXwMSx93lGeZ9mopSxNSfMVmUEFZob4u0RaaXdKcdP6oxWmEUkCstktdvd1mSIi+49AB9czYxc+oxyJ6T6xnKFDeau8N8EgU4E0fm4/ZYtCAAcEecJIkfCiD2I/jMp3YgAIwITPht1hnCaqRG9OtvioRzqsyQI1uOBfKmCc7VuteyZeB5zbuFTW0mlHFYsmvh+9OeJZt0dbWOUX0f4d5A/YxagF0ajklerxTROadSIcMr5S/JzzZ1dvZFJfj6yyDdohNc28kLJt38RaSK6njTpX/62HjBFc9KiGAz8HfPn9lokSy3aHdGSiqBPbebpiwkuiXsfb/i5nWzQjMPgHhuJSQHgcizyn1uCxoQy66UKUa7F0ef30nymz3McKLPuWPw2OMzw==
*/