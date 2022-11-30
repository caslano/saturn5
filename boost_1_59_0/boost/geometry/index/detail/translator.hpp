// Boost.Geometry Index
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019-2021.
// Modifications copyright (c) 2019-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP

#include <type_traits>

#include <boost/geometry/strategies/default_strategy.hpp>

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
    typedef typename std::remove_const<
        typename std::remove_reference<
            typename result_type<IndexableGetter>::type
        >::type
    >::type type;
};

} // namespace detail

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_TRANSLATOR_HPP

/* translator.hpp
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
*/