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
Xpdfnnv5TZJymwq7wGmSr9Ol/GZI+c2V8pst5Xe+lN8cWCL20s/LOhHi6NDPPyj9/EOwOayE8aKXfpF1E+79/Fk8pw3sBDvCzjAZdpV86wZHwu4S7x5wJuwFC2BvuAL2gZfBs+FqeC7cAPvBjfA8Kf+h8Fk4DL4Eh8NX4Cj4DhwEf4ZjYH3iOhZGwPGSH5jLegJVhrzHBZzvL+3D4AEYBP8KG0s7iZV2kijtxJQjRRLelXY5ou5BC4U7YRx8EraFv4ed4IuwG3wJDoCvwqHwD3Ak3A9nwj/CufDPUN3fDRfCgzAH7oaL4XuwCL4FS+Bf4FL4NrxE7PX4vUjGfw7tuomMdyLgKJgAU2FrOA8mwQzYDqq5JFgOO8K1or8edoc74Dnwadgf7oYD4F44CP4JDoFvw2HwPTgcfgxj4bdwJAwljimwIRxpjnPMb33wesn/MJgp6fhS8vsr2B5+D0fAH+AF8Ljk4wlYAH+SfPsZXgy9cu5/MLwMhurz+uWbDoyX5+rzzAPuifpIyv8wjIQfwyh4BDaDn8E40X8FP0YVSbjlUi4Jqt6pnzqPvDU8D3aBA6R/Hyj9+yDp34vgApgCy+BQeBEcBm+Bw+EdcBR8Co6WcfIY+D4cD7+BqfAEnAK9xOV82B7Oh33hQjgIZsKRcBEcBxfDWXAJTIN5cAEshIthkR53y3cH2MNBvlAG5QlwhciZS+FZ8DI4Gl4Ox8K74Ry4Cl4M18DL4a+kP74C3gXXwnvh1dIPXwN3wBvgAbgRfgxvhkfhJngcboYhxO13MBzeASPhXTAO3i3yIF3Py6u5BZWezob8hsZvDOXcA46DyXA87AMnw35wKhwEp0k9nQ7HwxlwIpwJp8NZIg/mwCVwrrT7ebACzoe/henwAZgBX4cL4JswCx6G2fAIzIFGunJhU5gP28FC2B1eCM+DpXAYvAzOgeVwAVwFF8Nfwwp4FbwPXg0fhtfDx8T+NXgz/CPcBI/AW+HXcAM8Dm+HP8E7YWgQ+Qwbwy2wPKTmM5EHonxnIP+y5x9Hj8QNaiCqHLXhJM8//m84+3jf0NqffyxnH3Pe9C93/nHA2ccnfe5xC+McY/u5xzWeedwe1dd+5rHtvOPSlf+9Zx5XDCUdcNvQ/46zj48NPb3nH+9B5Z3FucSoXagjqOgOnGOMKkVtQu1DnUB1YiIvFbUCtRm1D3UUFc1LTQoqD1WB2oH6GBXZGT+oVNRy1CbUHtQh1InOZ84VPvM78zvzO/M78zvzO/M78zvzO/M786vdLwS16Bc8/z9/YcEi4wIAgj+lOwBiPOFNxyfyXjbHWAJohGycGVTiaYV5O8KutJqnLSwsK+B7iro74INo5irNs9i89v2xT2JfNDHwLDa8FyzKzXY/3w/3VffD8lz/PlHsrfthP4qu/X5Y93MveUaVfehJQbIfVtLTFnWDcU6XTo/ahKOKojCzLA/vOk6HaxEntQ7cPNc6yH6O6POEcUg/S+eb014KcZfonGfaPqpOedbEuofYPb9krfWaYPk2jWos6mISFDnJt5Z9SdrwyZNGpc0cOmHGyDSOezP3gi7HDWlZglbSY/qJ0fFt2FTH133fp8SX8IifCs8Sv9kh9vitwG2yU/zY91OW5Ro/8RMTsDc5N9Osw81gcpX4Nz7J+Euey75bniFpOkfSlC5n0Z8dRCjCEvynSpqom5mFuuo41h1x203vB1ih9BO8z3h66TXW/SfLmnOHNjteh9FZhTED/UVKHx70uSfEsU6maj8d9NrvpUofEXTE00D5GRWv1n4bD9L7Gy5XbuoFfUgeWPYGStz3qXg+Y4u305kNMXCVCi846E8ib77Vewf9ZyKsVmGM9TSStOQ=
*/