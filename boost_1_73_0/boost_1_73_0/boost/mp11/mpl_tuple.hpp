#ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED
#define BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>
#include <tuple>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<std::tuple<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

/* mpl_tuple.hpp
C6NdN4QH1M/uFME09Ng8z7F2k0bqZ7QRHFpquRN7VxD8o1t++WP/AVBLAwQKAAAACAAtZ0pSxIh+OO0AAABlAQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE0MTBVVAUAAbZIJGBNkEFrAjEQhe/zKwbF45JaPElYKGLpgriLbnuPyWw31CQlmW7rv29cW/U0eeSb9x4jmRJrlagEaX0X8vig03eIJpWgnTlaT/D8VG1ed2uQ4vYnxQUHmMIUV0dLnotkDYHUo8hIojhQLMGHbCLFv0TplcuBjUoJrUdP74rtQOi/3IEicsCicOqnYOso0+KCo9TBOeVNCT3z51KI2Uu9b6tmOdvWm2rfrrdNvWvFfDF/uDPAYpGzr6v5+VdvLP5G0XYnNIoVqo7P6T3h+SjYq4QHIo+T1AeegBxGNltQjCHqYHKpx2x4J6W4QuJ22V9QSwMECgAAAAgALWdKUoimnRAOAgAAYQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDExVVQFAAG2SCRgZVNhT9swEP1uKf/hFlRNQsuclI6tllcJsW6wAa0g8N0klyYitaPYKYRfv3NCYRNSJMvnd+/evbtIh9ZlyuKCyUoXho4H7B9Nm9sF
*/