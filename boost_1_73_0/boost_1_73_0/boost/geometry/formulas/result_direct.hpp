// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP
#define BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP


namespace boost { namespace geometry { namespace formula
{

template <typename T>
struct result_direct
{
    result_direct()
        : lon2(0)
        , lat2(0)
        , reverse_azimuth(0)
        , reduced_length(0)
        , geodesic_scale(1)
    {}

    T lon2;
    T lat2;
    T reverse_azimuth;
    T reduced_length;
    T geodesic_scale;
};

}}} // namespace boost::geometry::formula


#endif // BOOST_GEOMETRY_FORMULAS_RESULT_DIRECT_HPP

/* result_direct.hpp
Dac7CruCNXQ8+W+LDbUZUOr6vhJTSxT08dG602fzptFKZIijQU1xAZgulndNwO16fQ+xkFh5RRK2oaoWj3NCAG2KpEc9UnWH3IFoaYYzJBltFdeV0cgiiqdGpMa5yA7ZqMFb0RvoVmECdQarHEi7/Vyil0VOr5vLypuIdlhKHxp6WQQ4EjHhaZ2mixov1W/JWuWwPr33RqVBmAdUVwp71GLheYVN3T6pK6x5U86xzb1BY15XzpFplbWlwQ76r8KoSi4hOTUlmoBElsZZqhp4O7lI5IZtRxW4yXapKuE40rpsR4Mtj0hIzvlZMSxyq2KmPEHPZ1FGk/Jmj8a/Jk55Farifm4bLv45yrOzga/mVFKr0yd8ljw2yrZ6H5X2j7MkIT9Vyn1h61fBXXR1mlR5L4ErAly6LEZCSEAsOHo8OY0lfMceO3oVnK+pbjLkkZrN8u0rP1D6qhn5WCBpCsacak5SxyESxz7oXv8efjg/Yf5AUxMp1PMWeRxVqpQewz+PzPzimC4yW+6hT+/1DdKJxpZSOFx1LLXMx7n12PtPMwp5aEa4ugiVlt1AeRR89PU0Is+DAruBIdDcbmAoUA88/3zCah6gtEkls9F3TgOxFnW1uGuJ4yICCoec9YXS/O390eaLuj/yUUopzZIz
*/