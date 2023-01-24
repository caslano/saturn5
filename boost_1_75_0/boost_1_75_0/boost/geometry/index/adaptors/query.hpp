// Boost.Geometry Index
//
// Query range adaptor
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_ADAPTORS_QUERY_HPP
#define BOOST_GEOMETRY_INDEX_ADAPTORS_QUERY_HPP

/*!
\defgroup adaptors Adaptors (boost::geometry::index::adaptors::)
*/

namespace boost { namespace geometry { namespace index {

namespace adaptors {

namespace detail {

template <typename Index>
class query_range
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEX,
        (query_range));

    typedef int* iterator;
    typedef const int* const_iterator;

    template <typename Predicates>
    inline query_range(
        Index const&,
        Predicates const&)
    {}

    inline iterator begin() { return 0; }
    inline iterator end() { return 0; }
    inline const_iterator begin() const { return 0; }
    inline const_iterator end() const { return 0; }
};

// TODO: awulkiew - consider removing reference from predicates

template<typename Predicates>
struct query
{
    inline explicit query(Predicates const& pred)
        : predicates(pred)
    {}

    Predicates const& predicates;
};

template<typename Index, typename Predicates>
index::adaptors::detail::query_range<Index>
operator|(
    Index const& si,
    index::adaptors::detail::query<Predicates> const& f)
{
    return index::adaptors::detail::query_range<Index>(si, f.predicates);
}

} // namespace detail

/*!
\brief The query index adaptor generator.

\ingroup adaptors

\param pred   Predicates.
*/
template <typename Predicates>
detail::query<Predicates>
queried(Predicates const& pred)
{
    return detail::query<Predicates>(pred);
}

} // namespace adaptors

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_ADAPTORS_QUERY_HPP

/* query.hpp
IZUEUGstPuZFRXyvlpBSdhEtPC16mGFrM1IKlRfXiuXUG039FB+950x+YdEHLRvvHRSj+Agj05HhUXcQdKUcVE2HbEnIh3thYcZ8ezVmUjoVI5Taz3OkEXqIUlCyT+Yc3M9nibEAPXoz4JrVa/LID5ASS2bitqHfWTT3MKiYUKRhafrpIVpo48g1ujVxegisSFFsP04NLB0LMEhIPCkilFsj+97CpmEC3ydIPzYIg7Gu3C40mOMwAnf+Qpz/Rpq/UTxg46K8WnCgUYImVhgapXbA6fRgzTfPJQW/vs8kMYG4HwBChjWpdg3Q2EgEFapZ4Pn6G34eevG4x5BerYC9mx5i2px04NEPIyRSKgXWn5+g7hU/owBE9gmcQiaGpvRJ74UYbKuoetmTpg03srdfCeWm54v+YrbEkj4OnfCUbC3Uz/GmDE493B5S/ZO05zL7Zlf2yZbAiLZSbytOC1AEZHszK5QgACg+9J4NwOo2B2cHlhSnZyNIqX/Qb927oIXe1+Ve6efOXtKy/MQNzABorQANIWK94lnOEXv7Uhb0x/xJen3DHeY/GHlSxXvZ2PZyIp2KORZ7Dx12hGvMa6PcDeQKTmt9mlurAIVtqivhrCULFdme4YzmteNnEdBEjQWLhkgn18Dq1ip9evRMLSjSaZa1JN4C1SgaSAFnnVok+WZtRpYz9TZYcF3vpAsy1bi89IY+Li73uhHwBmOW
*/