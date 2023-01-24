
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
0G69oL6SDjiY8XOWgtHvHnYAuFvVTy7vN8OBe8zpQ4u7TC/+R/xTbn0CtIPknZYcsMJvmVMcO8l+ZlGQXK7utD8vI0y3ywse/QEzfqBP+qb06Z1my18MLR79tL3PmEnTO8U5HJjjxePHJLi6um5Mjx2xJvaZlJRnXF0Thg5NWPBM7IFIhi9bMDoCnqEpczs/13noc53hdWjnCNUalQPKZ1b2HNXLjvisiRjtaHnWOK7pEZjF0oeMKrLxpBbNYng7l8HtbOI7svThW7Rzhth85oxD+h4eW1qy4rZw/a+l7pmV5eHRKiut9i+z7tCynTLG3n48jEtLYMypMeSln0sPcSz8+OjhFEP6mOUwZt6E8X4/2CV5MMbNg7H9MoxnWrBb6mG8bRgPYxXaM5XR/X4xZMVvB3tiHoxfR+cZyq6D/ZFSNrRDA4zteTBeaRt27VpSFj+0BseonBDXLBgvly8pzjl86vD+y3k922UZovutnlWYfhtspcolhfHFME5dTwm0z4KxqKwyK74BbIxCGJcfxLvaL9m7uu462AbbK9Ojc2C8zVpelj4+3dt+dl1e/AWwk1avNhTn4dgMtsL1eZWGvWBnvL99197rMI6lg33TUJOXshzG1XlaSP/a9vrlKZ0dj4J9c3d2pXb55l17Z8F4Xww2z8tgZ+RV5oyvywp0vArjoCG+nT3w2TsP7Ii9MFbPm5UytKFh+67iXXWV
*/