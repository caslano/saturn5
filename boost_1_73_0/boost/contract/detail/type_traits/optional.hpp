
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
3gyHwMfgULgR7gXfh8PgZ3A4dPq/fWE+HAH7wFFwCBwND4djYTk8AC6E4+A58EB4ExwP74AT4LNwInwFHgZfh5PgO/Bw+C48AqbQXifD9vBIWAJL4Rh4FDwElsFaWAEXwKnwbDgNngePgTfAavgArIEPw9lQ9EubsTx9ir5XZHjehXrq9xb6w0K4F+wKh8PJ8GBYAcfDSjgSblb7FrXvbWOHlJ3Yx6i9Cu4BZ6n9JDgIroAH
*/