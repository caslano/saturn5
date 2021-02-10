
#ifndef BOOST_CONTRACT_DETAIL_OPTIONAL_HPP_
#define BOOST_CONTRACT_DETAIL_OPTIONAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/optional.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace contract { namespace detail {

template<typename T>
struct is_optional : boost::false_type {};
template<typename T>
struct is_optional<boost::optional<T> > : boost::true_type {};

template<typename T>
struct optional_value_type { typedef T type; };
template<typename T>
struct optional_value_type<boost::optional<T> > { typedef T type; };

template<typename T>
struct remove_value_reference_if_optional { typedef T type; };
template<typename T>
struct remove_value_reference_if_optional<boost::optional<T> >
        { typedef typename boost::remove_reference<T>::type type; };

template<typename T>
T& optional_get(T& x) { return x; }
template<typename T>
T& optional_get(boost::optional<T>& x) { return x.get(); }
template<typename T>
T& optional_get(boost::optional<T&>& x) { return x.get(); }

} } } // namespace

#endif // #include guard


/* optional.hpp
K4U9bK10TDLeyCcLles3NB+/m0Rf0HszDAmsRSmZgFqKDNyaD0zuvjall15fzxfL9XQd/UPptGgySS/YXEi+/OfIa04N1j/3osc7dJEjLQpkx2MPkIS5qOmCvWAn+j95i68m68vVdLmZLubRUgB8QZVR2nFaoBJIN0Ux5ORQWjDHzLa+bSsLarCV0NR19edlIRkdK9YHjLxCkdZhJTdFxjpC9JQJJzpEQlGeb6TIqJ2M0APaJGHFUEBz6WwqKolO+c78qYpCPJDbm7pE9SKVfm+sg/LbpkD4bzabZZTDEkqGemvphpdByLpDIfuUNWUVKkS02R9NXegKQA0twXoHWktS3yoNtEvxgQPqUgXIWF/KqGN9YtnoyDY7K/9opGaP8LTO0h3iCu0pkAeTv6B7+VqSZeUOHIQ2eijvUWtsx6OIxd0BpqzlJXYqHG4J6sVxP/AAxSFDB75RMqAhlMeReF9M4zwXnmZ9QPtVTokiasMA255MdIyiOIb8kG6YjIcx9Tz0gthDbCGFGjQPdav7g6gTvANzMGEd14MvCi4GRAH7QGJzch/4FQe62b/kU/Zmv6SjRxvDFMijN3e1cvKIO8hk1waRlRLy04e18et41XvWhzpYm9zLOlXgLhV+RpAKoXKva1qcT/4wwWVT
*/