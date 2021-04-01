
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
3KY7/7sFkrnAHG6q8qAOlb7UmnVl4UNH2NlR7wk479PdAmC4wF8JgKyaFqxz47HNBXEla82Q+3lWpXjI8tSIxK+jugKqIgSc4FoKDKeLPXZh0mw1sZCL7Ecw7L7mSK3cCaCkeHDDj+Bt0jF0sY7Ay9npOucpvvKhdv+rVfVbdW/SvGzI0iK43CvhUq06/AtC0IN+RlUxAsHI5eKcNkg6vo4DPtiOzMt5KlCJAmQKbVEl0yviw61ynrAlQ+FBNSeLdn87TnSFfA/+CLzLoUMWZM8LTYIIwfWWoGY1rd5L3WexwcQEbSyhhNJ7LdjBIaz8MkC2JQowsw/Oycxo31xqMjDOYiow0pvkNCjblu2oy09+MCdpCH78f8bjttiCBUU61w0ghTEoEQhE2CoUTNjTCXQJK94LymgvD9glRc+sUTpUum5NDhRp8trx69awEEgSJJtXOpL3r6cfMqsn7vSvTr/VCtBFoAfAvJtij18ZPrqcOAQXazwJHjALmVUrEA1B4z+xNd5pMiRCiNpKsPJTBoFwyVgCB+OCa1Rdn24O3RAfYS8hLMFp8GAGDQ==
*/