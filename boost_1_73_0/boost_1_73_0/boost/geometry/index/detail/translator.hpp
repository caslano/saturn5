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
kXuPjW/rBXYPxyL/0UEiexn4xVqH08Z5/f13uPX7v8v2deyaC/fhOlVYTTTIWyX1WM9jXfwlWXMmSFhIq6hZRbSz5YwA4Of4YrUXcNlz1R9dFRfJIY7NHgaLihgrFfDiFccs7bvh8S6Fh9OpB1EAHXVGtMKIuOGZ/Tu5ymfe5+A6xTRtbIq6KBMW9NhHjidJxJEc47VUr9nBixJNZKafEaw89O2Qw+tMltWSQgirK2nJRRTL2X5tbNRbLQoClSC1jakRIGetgndILPly4RgD3ABl/8wil9qrlYT4LaaL4CZ0Ma9O4YrIl3h8x/jl8enRO/ON4arRo0B8BMUWHvvKiHt7+95Zztns4Qep/ALLuGXxwhk+VNQwF8fVS6HMd8Z77CajOAjWLonuto15FktsnBt+6ZTNbIXubtG0xYsB9czBJPMJ1jA+z9HAk7NawwLnnQHHajktyx2qa8K1rH3aJ/uHPxwMbbdeFyG8nB/BVCkJy0z4xoNk+Od3+8dDQggYOmQB3beWNd1phPAbN5CcUmO8cB9DVfEj0gjAv01dgN0KRnKHRzoG5cH4eXf/AHXTyLe1XtxTAt0bLkjfDrwK9XCvnW8KYWZLh0S2APznRI+OkkFbd8UKdAv9ViU+FUDDaYZq35TnrjCJkpCG
*/