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
wiWJHdfACNGjRNdrAp/h/JdLPCPk/Alu50/xfn6dH2NguORLhOhRoptrF5ZIPC1VPJ5rF26XeJ6BoXAHbAF36T0XCCPh56jwnmuRvezjzO89sC18FfaHr8EB8AAcA1+HV8J98Cpx1/nzpKytaJM/u/Bn8EUYBHe7hUs5Q7i1smbwehgEy6Be21rCNbfJj62yFuoTMAxWwCily7dJSKmEHynhQ2C6hDfWCmkAB8K2cAjsCBNgLyMMVHtQwP5wHBwEE+Fwcb8cXgoTRDfrw0k5b6RNfUiRckyFvjBN2km61IsMXR9kjBrG2KT/EUn/oxL+MRgpuuQ7Y8je6/NysWOF1OdSt3CDJFxDm3ALJNxC2ADe5t5+nvJezsUSbhYMgrPd24+Ei7bJr7USbp2Eux82hpvkOlKu14iXMUw1bmpdW32lxLMK+sO7Jb41MBjeA0NEN9NTeob8WyLx3SH592u3ctsg4ZrYlNsMCZcj558p6cmV8MG+MvYm43kV1dYU+tzHWU++hc3hCdhB9Cvh3+Fk+B28Dn4PM+APMAf+CAvhT7AY/gznQQft7hbgA+8wVHgnDID3wED4AAyCFTAEvgKvh0fgDPgpzIdfwLnwBGwMv4YRMMaHNgFbwCjYBjaDHWAs7ALbwEHwPDgCdoBTYBc4C14M18MBcBMcBJ+BQ+CrcCjcD0fBP8Bx8F3RPxK9Co6Haq0x2Aymwzio1iqHKbArXAh7wiI4DBbDMXA2nABvgqnwZngL7AjvgM3hZngLfBL2gS/DvvAY7Ac/hlfD7+BFMITy7gq7wW5yHaz0lbEeGV+q8CEMfx/C3SF7A7SB78O28APYTvROosfDStgH/hkOhsfhJPgpnAI/g2nwc3gT/BKWwBPwLngSPggb+5Au2AQ+BcPgszAcvgSj4FuwKXwbRsMjsDl8D7aAlbAl/BK2kvtEa8jfjjg4GJ4HL4ft4HjYHl4DL4BTYSdYBDvDhbALXAS7wTtgPFwLe8InYW+4HfaHe+EQeACOhl/AcbAKJkJ/8vZKGALHwzA4CTaHk2EbmAQvhDNhH5gLB8Cr4WSYAufCafAOmAbvhOlwNbwebpDwWyV8BcyDz8IC+BEshqfgbBhA+c+BoXAejII3w5ZwATwPLoQXwltgd7gI9oa3wsvgHXAQ/DUcDpfCsXAZHA+Xw6vhCpgMS2E6vBPOkPPcAO+HxXA9vAk+AEvgVrgYPgGXwSfh/fBp+Ah8Br4I18BX4b1Q369lzGWKzf16iaztvgy2githR3g37CJ6PFwOe8EVcKQcHyv6eNEnQcpC+k0y/gJH2vSbLvBzXm87wOawI+wGL4TdYVfYB3aGl8GL4FBxl/sIYyr6Pk6f3PM+Ei3pioHhqr8u9zM9tqGu8cquC4z7GXTIWnAR8A3YXPRY0bvBfZL+N2Ei3A8nwwPwOngQZsC34HT4e5gL34bF8BCcB/8AS+E78Gn4FXwb/gg/gX6yx4a/7LERCEfDIDgONoSTYAhU3wDCYhgF58IW8Gb4nnH9hB/Ce2ClXOf/BB+Fx+CT8C9wB2xDuOfh9+h7xN/r8Av4JvwUfgzj8Hfcn+u8/sZLf9ulErAO2YEcRU4hYce5liAJSDqyGHkI2YMcR0I/5TiSgMS5fZ+2Sr4128LfpVvVd2Xev2vz/A5Nf2O2F3kfqdLfm/13fGv2n/CdWV2/MftnfV/2n/xtWdan9d+X1fb7snP9bdmcT7EB2YYcRD5Hwj6jjJEEJB9Zg+xCjiPBf+UYkoTMQzYgB5EfkHafky6kCClFKpB9SOXnjvpf/e8/5uePZP6z5v8z36a4qLBITf0/B3P/i5pyrzKei3y9jQ+fu/cL/65xY/vx87q/F7A=
*/