// Boost.Geometry Index
//
// Copyright (c) 2011-2019 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/range.hpp>
#include <boost/mpl/aux_/has_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_META_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
struct is_range
    : ::boost::mpl::aux::has_type< ::boost::range_iterator<T> >
{};

//template <typename T, typename V, bool IsRange>
//struct is_range_of_convertible_values_impl
//    : ::boost::is_convertible<typename ::boost::range_value<T>::type, V>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values_impl<T, V, false>
//    : ::boost::mpl::bool_<false>
//{};
//
//template <typename T, typename V>
//struct is_range_of_convertible_values
//    : is_range_of_convertible_values_impl<T, V, is_range<T>::value>
//{};

// Implemented this way in order to prevent instantiation of all type traits at
// once because some of them are causing problems with gcc 4.6 namely
// is_convertible<bg::model::segment<>, std::pair<bg::model::segment<>, T> >
// because segment<> is derived from pair<> and pair<> has copy ctor taking
// other pair<> of any types the compiler tries to instantiate ctor of
// pair<segment, T> taking pair<point, point> which results in instantiation of
// segment's ctor taking a point which results in compilation error.
// This is probably compiler's bug.
template <typename T, typename Value, typename Indexable, typename ResultType, int Ver>
struct convertible_type_impl
{
    typedef ResultType type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 0>
{
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Indexable>::value,
            Indexable,
            void
        >::type result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 1
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type_impl<T, Value, Indexable, void, 1>
{
    typedef typename boost::mpl::if_c
        <
            boost::is_convertible<T, Value>::value,
            Value,
            void
        >::type type;
};

template <typename T, typename Value, typename Indexable>
struct convertible_type
{
    typedef typename boost::mpl::if_c
        <
            boost::is_same<T, Value>::value,
            Value,
            typename boost::mpl::if_c
                <
                    boost::is_same<T, Indexable>::value,
                    Indexable,
                    void
                >::type
        >::type result_type;

    typedef typename convertible_type_impl
        <
            T, Value, Indexable, result_type, 0
        >::type type;
};

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_META_HPP

/* meta.hpp
GUf/Hc6H78M0+A+YDT+EKaHq/uRq731OquF+5bwDv+wdy51G4g41ELUBVX6SdyyvP/C/dc9yZKz3F79redsB633L7WO9J33ncsgU3DjcuTww1lvjvct9Ue0d7l1Oj/WeuXv5P3j3cin5vwfeBHeg3kR9g4pjYJeCykStR1Wi3kaFxLNiDZWKWo7ajNqH+gbVIoFVaKgi1CbUq6gTqE6JuEeVojagnkZ9gIpswQ1OqHmodahK1JuoEAaT/VDzUGtQ21D7UcdQcVziPxCVg6pAbUcdRHlas0MQlYJKR61DbUcdQjVIIs6odNR6VCXqbVRIG+KGGoPKQ61HVaLeRB1DxbXFX9szd1Cf+Z35nfn9d/1CUAt+wfv/iksyjOv/Tvnuvy+jPXqP0HoRpaNR5t1/vzLWuc5kDOw/F7isJCsttTh3KdvTx2dd5LHtC5TzmsQfoXT1hCs3UyJ998rhSc5qEjc8sT3xlvWrat3x19HVnrE0zuWsbX1WFc/CTD3Lcq7DCjkkcRWqGWoZ6tekMXJWNWlMGzptUi/S6V/zfVFRlkf2EJh+O9rzQdb/dlD2czwp+qxx8SNrgDsF7NVNFTvZT0/41nMkc7V9R8d9jtGwXNmH67AZLWI3TO3B6arssnV5eKQ8zDXu5yn7WZ5ect5aBWYfUyhfqX2S88KD/HdUUUayv0H2fH0bLeek12K/kHVfo8pPKTv7fshU2En2G0dZ7schX2xuiqx3SciFAJ2IcDvYCF4ez5iv2vJeRPtw3e8qfrvp/VpHlP6och+qytL0T1lr9509MXI+wydK/4JnITWw3HO23IHiZSwqe1Gs9Uyfo/CR8rfXc43cY5ajw+4gZS9hkFK5/41frpFFej35z8r9+451pwD7fyr7YwH7iBbrfQwTVNhTlYTBPWY6zo71aQzhzVf2sZRJlF4PX6rMuojeH+cu1KOGhLCWws2JJCTUdyT8e9RXqBDZj7akVueVhDbdPVv2IxRkVisrKDPMVJkps1RrvbTUpzFymOkxkR+fo36D/Eg531afpk4bGigmXesTfuXeAalP5yv9u6oNlqEeRak9sGqvAJLf498bNlO5fcXTkziWoB42ZYwON8ZVTrSZo846s5WdeZfCTcr/9ZRLY08OSspHlUF/KYsfCOhH1HEpn6+j69b+ncqDdGKm0mk5N+YDOajqMsn7EtRG3JbPccp7m/h2lc83KP8ztXymTAjTWT6PFzs3+Zyj7d3l85E5jvJZpf0WZbdQl7dHytuUz1uV/TSjbuj7lX4SuXtMlcPJ5b3cUWGRs6mBctbmpshSNv3CnOVs0twaykY1O9e2gX+rrJ2AvhpZi3urrB2r9C+wRqQRff1gLWvD51Uva0fNtclaCVvLWsKoXtamza1e1k6e6y5r71F2s7CLEFmr42yvGyJrH1J+zqJckrSsfXOuRdYShrus/dlIeHOzHtVN1radd/pkrb7/Vi5ne0Da+22o9nHM68yz1SnjspjcRbkLqVSudUn8xWv5tlPpr/X05P+L5YzcyXInqnkG7ePKzdXsIaiHqZathGWTrXwO8O/H9s437CdQWxqb7ZT8JLwoH4Oa15yv7u0UvcN9sW/Lgc0rZZ57KeoOQz7Ory6/lHR0lY23KL/TKRMtGyW8REm7Vf5RTmLfzj621X5bqf21lL2rjPyncheuy4TZVS0DH5hvl4E7pb56ydcZp9j/lLqOLTMt55s/LXcIJqIai6x8kngkX1Btfi/M4a7tGuSehJHoLOe0fZQei4c0r/kMVtt5I2LWz9ouLXXqhJyG1pWHtIERItfTq0+jCsglbeI3Wd/9V6H0R5zTqt13V/pZ6K9W+h9tsjtG9pqvVfa7PYs=
*/