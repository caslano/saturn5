// Boost.Geometry Index
//
// Get smallest value calculated for indexable's dimensions, used in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct smallest_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (smallest_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct smallest_for_indexable
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        result_type r1 = smallest_for_indexable<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        result_type r2 = smallest_for_indexable_dimension<
            Geometry, Indexable, IndexableTag, AlgoTag, N - 1
        >::apply(g, i, data);

        return r1 < r2 ? r1 : r2;
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct smallest_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename smallest_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    template <typename Data>
    inline static result_type apply(Geometry const& g, Indexable const& i, Data const& data)
    {
        return
            smallest_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i, data);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SMALLEST_FOR_INDEXABLE_HPP

/* smallest_for_indexable.hpp
87fG4/cN1m9+I3otaNag81jBv6egjD/Ov6fjdwzkP+Y1da9/lxLi/Zbdx0QjfWy/Y1NN3miEeZ3tWy3TQjQtbL8Tbb/jbb9Hp5nh7EO97pgeCqeD7XeGLY4P2H5vs/3+K8IZZMQLPPfZflemh37fKe6kO5b+XQxzP8vwB377wvgdC5PIvx+BSebfL4I3i3+vg/wL+XdrQ+8K/26P3+fz7yr8bsu/P4yBH//+FL/b8e8f8LsN//bGol7z77hYGP79EdLnTyxnWTzm3+w+B7+H8e9l+L2Uf9+BfuEeps/xI1+5XzlszIOA3T38PaCZFAgn2RP82jpT+KJJ15fpEoATmO5X8Z5gEvBCYCqwDJgBnA3MZnse8GJgV+AMYC/2/xoYMAyHX8fhJwJLOfyqWDP8amBnYC2wN7AOeDpwPnAocCGwALgYOJLtY4EBYCVwHrCa/b/mdU3/LvouenAuv8DO/N1+iL+B/YF+4ACgyQfDfEkavt5+k68P0Ac8GWjwHUNZKWC+hdEm34X4fYjbmC/jPEF69xaYBfwXsCvwB2B34DSkVx/gMdhPZftpbD8TeAQ4mt3HsX0i8GfgpUAP3Jex/1XAKOB1wGjgGna/GRgPXAdMAN7F7puBicAH2P4IMAn4JLAV8Dl2fwmYCnwZmAbcy+5vADOB+9n+PjAL+BEwG/gZux8CtgEeZvu3wPbA79n+E9ujvGgTgHFAwz0R2AmYzPZ04EnALLa3BXYFdmB7F2B3YA+2nwzsCezH9kHA3sAz2T4SeDJwPNsLgX2BU9g+HdgPeBHbZwAHACvYXgUcCFzK9hXAwcC1bL8NeDrwfuBQ4CPAM4A7gGcCXwAWAP/G9HuAw4GfAkcCvwSOAn7N/t8BzwLGoGyNBSYCxwH9QMM/AzgB2JXtvYDnAIexfTSwEHgekOLH9ouBk4GV7D6P7QuAU4FL2f1Ktq9i+9f87u+63Wp9iwH24nrTN9qsN6cA44D9gX7gqUCLfyfzt9XwdwZdEvAkYDqwCzCL7Rb/4Qb472L+Dcx/N/PDLvx5L3u5jXTyd2f5e7D8vYBpwD7MvwimgPkfZn4fcC7z/85vtp9rgLnAPwCHAm8Cngm8DTgKeAtwItunsH068Gbgdez+O7bfz3Z8nxr3/FfM76Nc4ftmOhzh77/UwpR/N7A123OArwIHAPcCC4CvAycA3wDeAvwAeAfwQ+AW4MfAncBPgC8BPwW+BjwIfA/4OfAz4BfAw8BDwOPAL4FG/f0nsCPwX8DuwK+A/dk+GHgEOAz4HfBs4I/AWcDjwKXAn4FrgZhsBtcDo4CPAaOBVj4W73HPx2d9Zjo8B/QBnwemAncBrfY/yPwJmvb/SW7/nwLGA3cALb7VDfBt4/LzMDAe+AhQ6g3zZWjk/ZuP843lfRmYBtxjk3cn8ydrvpvB/VwmsBWwNdDiq2e+WA3fwSST7x/AGODnQINvDL2ZoPaPccAhlrzxLC8wFvgysAXwVWBL4CtAH9tZDhQ+93TzI18NTAHGA1OB0r83wJfBfJnM1xoo9XyvezvxHuKZBHwfmA6sB2ax3fpuIfPHa77bntM7DxgH7GBL7+IG+FI5vdOAccB02/cCe93zN5G/5+P8TQJKeWS+Vhq+H1qZfD8Ck4DHgRbfVuaL0fANSzT5hgOjgSOAUg4byI9vYky+I8B44LdAKz/2NJAfX4EuCXgYmA78FzCL7VJ+XnNP18/5u18A44CHbN/1M1+O5rvXcTm4HpgCvAGYQXYe7xntLfM/yeO9IUb4QBoftjDlPBnYHtgX2Bl4CnA48DHgSODjwCnAU4HlwMHAxcDTgLcw3W1Mdy/wDOAjwDOBbwEf4fZ1OzDGa9LHAQ0=
*/