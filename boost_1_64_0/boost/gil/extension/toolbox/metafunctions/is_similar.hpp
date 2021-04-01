//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_similar metafunctions
/// \brief Determines if two pixel types are similar.

template<typename A, typename B>
struct is_similar : std::false_type {};

template<typename A>
struct is_similar<A, A> : std::true_type {};

template<typename B,int I, int S, bool M, int I2>
struct is_similar
    <
        packed_channel_reference<B,  I, S, M>,
        packed_channel_reference<B, I2, S, M>
    > : std::true_type {};

}} // namespace boost::gil

#endif

/* is_similar.hpp
jtTD9vq/bRi+mwxR564le/DjpDMrSLwuNFtrKLl8/aSBxQEBiAShtjf8Fl4OhA6IZzJbl+aa5J+MqOXiXAvFDQW12LBWQMKcJmC104CBs9HvkeW5/9Sf/UxRWcs/pPaiE9z3MvlJ/8X62gaNZr+u18T3C+0x+nAb9GPd7OsidV9W6PUQ2VOw8DEN2cf318MY8de/vxTviBFzWeAGlTGyOkFl4zR6KP0Ih8wDx3CG0wYVAv0rIfZp+RG5tu2auzekA2d9dYQL4xjdphRKQl0mcqIu+RUrO7jqsysumWETXkXQXudMIzZZuGJCYUZRsqYNlgq2BnRZV8XeGDGw5vOPOgwt2gd2XZc4IgEDujSgYiez56jnsz4ZB6pWidEoDwlzZQwdPDrj/0TCYoq3H9KrtemQ249sgovXL7u+GajMw5+xJdJ6lFZpWZpVjRs2fhJmQeWxBuzTDudcCkrR3A8S3h8MexWoNp74Uyvx0zzXDHlg92EDmVHbqHhJkZ2pbzRBTAk3UjG7pusF+Lpsb3PramZjsBjIHAgUp3f2p77I+YFzO0IeUuC4RbO79A==
*/