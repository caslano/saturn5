// Boost.Geometry Index
//
// n-dimensional Indexable validity check
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_IS_VALID_HPP

#include <cstddef>
#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

namespace dispatch {

template <typename Box,
          std::size_t Dimension = geometry::dimension<Box>::value>
struct is_valid_box
{
    static inline bool apply(Box const& b)
    {
        return is_valid_box<Box, Dimension - 1>::apply(b) &&
            ( get<min_corner, Dimension - 1>(b) <= get<max_corner, Dimension - 1>(b) );
    }
};

template <typename Box>
struct is_valid_box<Box, 1>
{
    static inline bool apply(Box const& b)
    {
        return get<min_corner, 0>(b) <= get<max_corner, 0>(b);
    }
};

template <typename Indexable,
          typename Tag = typename geometry::tag<Indexable>::type>
struct is_valid
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_INDEXABLE,
        (is_valid));
};

template <typename Indexable>
struct is_valid<Indexable, point_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

template <typename Indexable>
struct is_valid<Indexable, box_tag>
{
    static inline bool apply(Indexable const& b)
    {
        return dispatch::is_valid_box<Indexable>::apply(b);
    }
};

template <typename Indexable>
struct is_valid<Indexable, segment_tag>
{
    static inline bool apply(Indexable const&)
    {
        return true;
    }
};

} // namespace dispatch

template <typename Indexable>
inline bool is_valid(Indexable const& b)
{
    // CONSIDER: detection of NaNs
    // e.g. by comparison of b with copy of b

    return dispatch::is_valid<Indexable>::apply(b);
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_DETAIL_INDEX_ALGORITHMS_IS_VALID_HPP

/* is_valid.hpp
0nA3TFw6TLIPn+X5WITn9XRxjAqL4znWfczHzAA6c9nLhvkScVytxrGquo4OFlZCvbZUQIm1e/5xOJ3J/3RNvOEvZ5naIL2fg4kjvfNJPrRZEd3NbajOnc7xlrdN8D3dW4kHHnOsvdPbJjvVdOD7n9r6x7TJbm/bsX9ck/tZl7ftpP1c/7iznH5ltJ+q7LiLxvpMJONcxgq2sprmyDP4N17nGowHwtS+6T/3L854/MsYMzjiwQefGokH+CQemY54wP8E45Ep8VDL0pAnnO05+n84qPGYXxOortWfHQAt7wdIfy/kUp5Ao7TnR5oxvslUxjfyDaVN9zzpOItG84R8NT7Oe4XOeDFPjNvb4vBv2pk1/fyAwlR18j7p2M+kOBSocVDvATrlZ/p4m/yLy2pDeQL/Rvc7xzUuP8IMH1PuMJk/4jHlW1ymCsPkn6U/58F0uTK3nUP2F+mNPZcxJfO0lTXiSrI/6FkFuWRMyWue1pjyCqIZB9lj5B53Sju+n+MyDt1FPGNpHBrGQ2sYzyHvDj3F65VtreXKlo41T4s2a0do3TH4tLGYmOZYS0xl2nym9UXNIndrr2Uhn1m+CkYZEzfjva3Gxr+lO519zzc5+H67UN6635F05jX4pB+62rneCP8T2/dFmNp3+Ls97bhXSXVstTYefK9SGwfmgS1UNonaKpvwb9q9S309ozBVXVPP8N41y38e7ePAqHEITUHk/QX9viHiwrxjcDbPL/s38vYo040XukLU744NvlFaLrTjcXbQWlNvdD1zXGT7Mvw9x76MIof65taz+v4hr72aZtwz6PIbtA32C/D/7/QLS54zma/idrUW5hrj7q0qu/vdLG7DphL9JIkP+OXM5bdEa7BzHRT/TjI/nUz2GY77HFZ+F5L/LHAkEc0xSoXyWfgj+uFnEc1Q+SZiU0n+vI4wgfxLG53Dus35ECbsHA+MpQMIz/5W7aXt9ecB6553zjG+NcanahrXVQaKSsuldXOfU4BP5hQLyb+03N6+wV/mFEHkb9bz/9k5xUJy428i3j+1188phrygHwf689R418x3PRcC2vA1MCKXegF/ZQx4vBljQHWNi8JX98BeFL2w9C8VZhniWqDEg++f6ePBtGmu9Zv9qX1M0qzPF4bCOMGxFX2X2jy6t6auoatvnu9y5B+1a8WOeMvdRG3cix15SLQS9+KwPPylCXcX9XlI4as67XZpzvMZ83xdXOQOoWsdZL54fgdZXXuF+PBvdBzc6JoFwtWur678K8eFzwF8zfVqnRoX3KfT7w89TXRvYHVU9oeYt4PbWJj928lY+CnDjtH4VcpYmM8NcJv+BNGcz3av58YOVA6c42CmTyP/pah3XgcP6a1DHta/ZO3nZ5ntGLtn/ZX36INP2Dfpk/R79KzvTh3ngv+/N9YVHSh/M5kf4/HuQ3yu9HAHyTsZJ+jOcMR3NOhu95TSCzExnH8Wf2u3uwbKO9h81wBxbN59A909gkUdpe9T4tt/NwfGbchQlqG+o8R3fgD1bZa+3WS6PO3bWgmdaM1f2o2dzTgXEPaekzIW3vUyj+f43Nwx3v8v6BSSvbbMRceRMy7Mly3naKaT/R+eEpqJem3vKyvBSd5PJfrPPEWQ8XnRXcLhgqqjsXaK9C592dJt0MmY/MUmJiR2ddVvwLKVUxhD5X7tX8ger9V3kAIsI/88qktcx+Qe2k8pTa836pvMSvyV8jThFXXPNsrSadBZ8qSh+9ZMF91ou9zQffQDLEMSM/iss+EhGRaWVNQZV25nVdeYOtpdygTzJEUsTxfNHcULX9XfldxqlwfpqEkP0DQ6r2hUr9PhPawnmfujeGAdvr/T9n1MeDHq0L8=
*/