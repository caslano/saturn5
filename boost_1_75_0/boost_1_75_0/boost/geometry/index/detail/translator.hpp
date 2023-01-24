// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP

namespace boost { namespace geometry { namespace index {

namespace detail {

template <typename Strategy>
struct translator_equals
{
    template <typename EqualTo, typename Value>
    static inline bool apply(EqualTo const& equal_to,
                             Value const& v1, Value const& v2,
                             Strategy const& strategy)
    {
        return equal_to(v1, v2, strategy);
    }
};

template <>
struct translator_equals<default_strategy>
{
    template <typename EqualTo, typename Value>
    static inline bool apply(EqualTo const& equal_to,
                             Value const& v1, Value const& v2,
                             default_strategy const&)
    {
        return equal_to(v1, v2);
    }
};

template <typename IndexableGetter, typename EqualTo>
struct translator
    : public IndexableGetter
    , public EqualTo
{
    typedef typename IndexableGetter::result_type result_type;

    translator(IndexableGetter const& i, EqualTo const& e)
        : IndexableGetter(i), EqualTo(e)
    {}

    template <typename Value>
    result_type operator()(Value const& value) const
    {
        return IndexableGetter::operator()(value);
    }

	template <typename Value, typename Strategy>
	bool equals(Value const& v1, Value const& v2, Strategy const& strategy) const
	{
		return translator_equals
                <
                    Strategy
                >::apply(static_cast<EqualTo const&>(*this), v1, v2, strategy);
	}
};

template <typename IndexableGetter>
struct result_type
{
    typedef typename IndexableGetter::result_type type;
};

template <typename IndexableGetter>
struct indexable_type
{
    typedef typename boost::remove_const<
        typename boost::remove_reference<
            typename result_type<IndexableGetter>::type
        >::type
    >::type type;
};

} // namespace detail

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP

/* translator.hpp
qEOciPQwtKJOcBqRLdCqv/Rd9LKc0Jw6eC0Egy0a7E7yt8kK64p6nmdyhUNfnZYYgv0b4a0M8zlU+tuQGBv53uTayLDQ3HT6oznECCSJtT0euaB6d0ysHeCTUm/FuojejxlxWxRFNxDp3X/H3x00xmK2lmN/E4j//B2Tq0TU6qAHqxu8PG61wdMlV67mug/Gkck7TKNcfRU/x7U9vc/KFyd1bTniYaFbHgKNOS+wRPJx9F8oTt7AvQH2mmGew7qb3+/WZsqlfJt7UHyAxJvjPN7E5bYDBmzv1V4e0fRrHZr9AZnXANwufS+l/0bKSOLug1aswgmh2UraoR5281kn66eBR2hTfeRX7DZ4fFqZSVyOrC6y245xGunS/OVJksOOfTRlxK8yQkdxzS4hiQ9z6ZkFNrvKApvSxv3bqA9d3rViZfMPcnxQMOljLk2bUcm6foL4ibDSY8Fzwu+Iv+WElBqKpExcrweiXlN0wHCEByTROlje4kdDsaM0o37vhRG2llnr9OmX2TBlmxZfm4RpPq2VdJskXa0xcyskodK30MpX1glb5AqQxGpJheZMSf1Q2u66zoc16fGkZu8GuQeZ4lHNOqX2P8Bzv7gxpzIuJidwuZ/rT2qFx40AT9fWTmOlooOplUcftQw4/VKUcZTrKTK+JQleDWBrlqtl0vj6hVaYpm3G4zl1GSJ9YfdF1mKbxdFf5xi1mntIELLH
*/