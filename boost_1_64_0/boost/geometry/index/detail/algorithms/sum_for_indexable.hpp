// Boost.Geometry Index
//
// Sum values calculated for indexable's dimensions, used e.g. in R-tree k nearest neighbors query
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t DimensionIndex>
struct sum_for_indexable_dimension
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE_TAG_TYPE,
        (sum_for_indexable_dimension));
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag,
    size_t N>
struct sum_for_indexable
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, N - 1
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i) +
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, N - 1
            >::apply(g, i);
    }
};

template <
    typename Geometry,
    typename Indexable,
    typename IndexableTag,
    typename AlgoTag>
struct sum_for_indexable<Geometry, Indexable, IndexableTag, AlgoTag, 1>
{
    typedef typename sum_for_indexable_dimension<
        Geometry, Indexable, IndexableTag, AlgoTag, 0
    >::result_type result_type;

    inline static result_type apply(Geometry const& g, Indexable const& i)
    {
        return
            sum_for_indexable_dimension<
                Geometry, Indexable, IndexableTag, AlgoTag, 0
            >::apply(g, i);
    }
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_SUM_FOR_INDEXABLE_HPP

/* sum_for_indexable.hpp
+kzgcGA+cARwAHA0cBDwLOCZwLHA0cBx3N5OAE4Fng0sBp4DnAucCJwHLAT+FngucAN/byN/bztwCvAZ4HnAXcCpwHeB04FHgBcAfwJeCIzD+OEiYDKwGJgLLAF2Bs4GlgDnAiuBlcAFwADweuA84K3AGuDtwDrgY8D5wBeBC4C7gYuBHwCXAH8CBoEtkV/LgJnAa4EVwOuAtcDVwCuBW4HXAbcBVwMfB24GlgOl/XyjgfYzjttPILWfQBmnMN9ATbl7FP1JNnA78CTgY0DD73FbP1Pwpnt74E/m9pLbg1Sg9ItvutezzTw+ugeYDtwCzGL717zuu5r5NzN/PHAk8z+UgPE3cBvwNODDwGnAR4AXAR8FXg7cDlwOfBJoyRV4i+Oja49BZ+D7wHhgPbAV8AMb/+q33OM1vKUZrxHAdOBIYBbbZdzJ/H01/F8mmfnxT2BH4FfALsDDQObHwpG7/PncD/XlfugUYCtgP/5+MUwe81cxfwvgFOb/e7wp/xvAXsD3gX2BHwCHAj8EXgT8CFgE/BRYCvwEWMF2a56/lb9zrWaen+E38y8HeAqwLXAqsD1wGvAkYDmwE7Aa2BlYx+5Svva758ODoEsCPgRMB24DZrFd8rEB/nuZ/z7mv5/5YQ/1P/vd+584zod4zocEoMW3pwG+RObzMV8S0ErPeua7UJOelSgfqcAAsBNwHrAbcDGwD7AWOAG4AHgucBFwKvtb4Re/4x7+Eg5/KYcf5PCv4fCv5PCv4vBXcvjwl/Suf8e9/yvn/q+C+79LgBlsl3J/wD2/3mb+/cB04DvALLZb/PnMP0bD//cos97tA54EfAM4CPgWUMY3B9zzrZrHNwFgPHAeUMbbB9zr6wZub+7m9mYjtzebgNJeNMD/W+a/kfl/x/xrgJLuzN9Jw7+Ux2NBYBZwObAN22Xc+657+9+d2/8e3P73tK9rveueXpM5vaZwep0HlP6mAb5ZzDeb+cpt6Vz4rnv5OB5lxvMnYDrwZ2AW2/m7GDi4j+uSeLzcisfLyUApF/9m706guqj2AI7/WUVBZXFBQEXFfQkV19Rwxx0VzTUhFkEJENBQsTAttdSsrNS0yNRwTY3KihLLynpWVr6ynhmVlZUVr9Qord537vz+V5AZpfde75x3jpzz48OduXf+M3f2e2f+XKZ+XKV+3KR+3FFf935sf718VpbznKyfn9F5/D4i5SZZHL/3yXI+iwH4HHbGIuyCL2FPfBH74n6MxgM4zhyvjweRJ8zPmWdxPPjFxfyc37ErulBuMHqgkccTR6MrZqEbzpbhers8Yb9dushyu8p26YYhktbX05/Yr29Pub6oJtcXXhhopnX5SClfy6J8NzkOd0dP7CHn9Z7l7/sv8/m9JX8fuQ64DgPNtL6vXSXl+1nc175Q3SxfjMY0D2AHfBU74yvYW6XN6S0lSmV652V6tTBXplerlnl8q40D0BeT0A+TMRizMADvwzq4Buvi81gPD2N9fEvyf4gN8FsMwlJzuN5Owz8152e4xXZ6gP2nNr6EoXhQrncOy3nlVWyPhzAc38D++DccJPl0PcrntLWox+0e5ufswAa4CxvhHmyCe7GFpPX9oUwv1GK91pXtqh7Wx/oYrNJ6v+EiySzfyWK/+dBTzlPoj59jPfwCg1TanK/j2ApLsL2M19vtZ/bb3Ysyf/tluy+W7Z60Kr+GyJDyu6S8Ly6X8gukf+QWVOd7VMdG7GTkw254m/SHLMIUXIwzZXwG3oFzcQk+hEtxg4zfiHfiZklvVWlz/nyNe77Pzflb4iJ9XsZxE9V3FrqY6/MFbGAsr4s5P/uxB57FAfgSjsKXcTIexBvxNUzGQ5iGr+MspC0=
*/