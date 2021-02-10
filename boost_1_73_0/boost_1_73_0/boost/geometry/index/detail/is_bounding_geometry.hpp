// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_bounding_geometry
{
    static const bool value = false;
};

template <typename Box>
struct is_bounding_geometry<Box, box_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_BOUNDING_GEOMETRY_HPP

/* is_bounding_geometry.hpp
ip4hqDQhNhNjzJafzacUjkhr6Uc1wHx3qtU8yxoaaeKNNMBjcTbNxy7JDIhZJtpmvXtIJ6jyLLG2MHh15S9a0GAOz+m8lSH8NgGolv0LqQVmMQ9vIC8M+v7tReOW7rR9aq5F97cB5jUfm3va/bG7qPgT3NS5g2X80ospXTdORv+6W6edhDvsT85Py+1tQBs0P8Wv//rPAdWqpNBjgUpK+4J5j+2wFxdRhK2pyIfT8RVlsUk1gSjEB1NJicNR8HkiVIjuEVwGENfzKf6CGQtydCB1iT56UotiuH94etzfirvZR7XRHLg/MqpUzrSOpoLh7g+7+4docB9+OHp/sPcK8yzEHaipnW35mi+M+SiipBpKhJziVqyTov1Cwo3/dtVQgv22OSr6/Z2gD0R01M33Lxgnqbcdet992D88ac7af5I8QzCizUHGgCDm+PjwqB+vk+zuebHIIi8u/Ym4Bvz5stH+O2URI+zDYbEUG80g7ZwgnHkFeXfAC6ZWl/4I0uWw13CUL3aOjgERwBden1dIWSJIWhCpF3rlN6iHpEQtNIq8feDUjphVp3BSBifuQk2RrICSkyFL5ON11SFdrgLp8qppls1YNn7m89Xsktfr2aK63USosR4dEjHBsZEUuIry1FytjGRiNFloDE2J
*/