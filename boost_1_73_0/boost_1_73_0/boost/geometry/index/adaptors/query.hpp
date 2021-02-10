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
eJ2ZIpNh5ukiOW/mmNhFoLXpgYjXtmvWbfv2lc6IVvEY5rPpTE/zJxKCkuc+YVoI9b4n+sv7H1lVxwv6CEgP8yJhjxvKr5FlmabzWLNAUE4sYN3chNhXgpIeaxgUpdS9zshFgjEByoMkCi68R99Ib1KhNwmFkULEKu9oIoGB3rvKM5deeRa5pDwkn4eHLIi5ebGYP8FBSIdR1unUZ/5wujHKHWOjrfxcjH+C8jHdOWWCBEHtOYheBoe8d3SvTEXi92M4A1ZSGSM1S8JOJU30oyJpFJXwIHbq4pFmkxpddhSlStYihhwSmkyMgrIJYHTEEgxAURpMs3xDpVwY2YWKLMxHjb6pakVW4aUB3Kqfb+4xbojuCAIlCciooAitWLimHgsSrH9UgPBL7Ovm6b649H7TjJyMANam55tn6VXGyXXERcOLHuG03czY8ctOh3w4WIuUViAL5Kl4Bdc3mXiSWDwmLiaewBpV0oZ/eljWmZ6+0y1VYj3zxh1xJTnLxqnE5cydtwrd25IusaocoM35YipXnE4tR+e2W9ImO3aUuSSzSOYw1fyFzFxssmBWU20rp5fqZkNHeIb+qAu5uCJeWIztPYw4TRtJcm6PsCNyBCSvG1GZa76Z2TTFnDkYm04W3bEyHJRjES2A6irG
*/