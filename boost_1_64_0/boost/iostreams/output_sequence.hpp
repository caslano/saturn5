// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED
#define BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <utility>           // pair.
#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>  // is_custom 
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct output_sequence_impl;

} // End namespace detail.

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*,
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*
>
output_sequence(T& t)
{ return detail::output_sequence_impl<T>::output_sequence(t); }

namespace detail {

//------------------Definition of output_sequence_impl------------------------//

template<typename T>
struct output_sequence_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          output_sequence_impl<direct_tag>
      >::type
    { };

template<>
struct output_sequence_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*,
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*
    >
    output_sequence(U& u) { return u.output_sequence(); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

/* output_sequence.hpp
iK2NJXXWAnHzTHFzg/ThhswYJ1Li/aJtA3VvF9J55jfmOCkXK2vTFqmr5SLN8j1gKRd9Au+WRQlF3z893XLxs3ynSr4o9l7R9C5RLkirI+5ta3+HnOi9Q+obuXrpuFNP1Dbie2tjKRd5WfkFORPzZQNdTYsj9nWqveAYk8xHteZplS0a39axNPu3A34pHn8apzwzMOfUhP/1c043t3L1q+6OXz610bs9v3yo/b3Js4dML20uaul7/w6p6uo/+crYT26bVWffD7/Z0P+NRvccMOaEaq7+1vfHNViXcXulCyu/4KR8fesDxz6n9ZkdMke15Z2Vh9YcsfKJv4QqNliRF/ffM6fVvrdw6XsXr5vm6r+5NHPVLTW/vHdf8uR3dy17rEXpc2MPS/wM6X//gImd/rE8+cZW53yY363gf2PObF0jl4zRxjnRNein6+9xOn92hz+XQOY9iFlw/92BVAouB8M4OARWgdmwKhwGk+BJMA2eDNvA6bAnnAF7q3wfeCocCEfB0XA0nKLyuSqfr/IFcCzcoeZ/VPM9an4AjvXG8rVPJE6/NYcbuWQ9uMspMA5mwniYBZPgVNgIToMnwumwHzwL6nmSOjbOWL26HzxPsqfO++0Nu8K+sKfeD9H74bA/HKnr7E+DxIGEexCcBofC2XAYzIPD4QJ4ku7DfDJcBUfAW+BIuBmeAu+EY+Bd8FTdj3k0fFj1H4F94E69PwBNWMdPddw7Lrqm3hwMGblyNd3z4fHwMdgDPq7p+QQcDMOhaDi/434svAROgwb9bDXPgU+jfy58Bi5W/SXq/hVwLtwA58FtcD68V+Xugwu4fwieAx+Di+AzcDF8CS6Fr8Fl8C14EXwPXgz3qTsfqf8OwZXw7/By6IZ9NawKXblq8Aruk+GVsDG8Ch4P18J0uA52g9fDPmqvL7yG+xHwWjhKzU9X8/HwRu6nwptgLtwI58Nb4DnwVrjY0fiBt3O/Ed4J74J3wW1wK3xQ5R6Cm7l/Fm6BL8Dt8BV4L3wX3ufoeZCOngcJD8GH4T/UHROiXuKe36JfCbr6leHvuE+FL8Bm8PewFXwJtoUvw05wN+wJ/wAHwD/CYerOSfA17keq/mmqPxa+zv2Z8A2YC9+Cy+DbcA3cC6+BH8Kb1d6t8D3u71T9h1X/EbiP+yfhR/BPcD98F34K/yJyWg5COuap48BxTtH9NSog58A4WBFWhM1gJdgCjoMtYTzMhFXhOlgN3gQT4OuwOnwfJsJaOFgDNoJJcBxMgStgTbgapsKdsBZ8FtaG38I68B8wDSIjz68F68H2cCzspvrdYSM4CzaBebApvEzNV8Hj4aOwJXwatoLvqPle2AYmhI1pC5PgibAFbA8HwQ5wGOwIT4Od4Hg4Dp4Bu8KVsDtcB3vA62BPuAH2ho+o/KOwH/wbHAC/gwNhrQj1JKwHXbn6cAjsFtFwwmFwDhwBz4cj4RJ4KrwRjoK3wNHwATgGPgrHaT5Y642bwa1azyfAlSZ6nUC+CcE2sCJMh9VhW9gFnqjvu36wF2wHT4cd4JmwE1wIu8PzYQ94DewFb1B7N8I+cBPsC+9QffWfjq1QRi3+S0QuDJNgJZgM5YwU2BDWhMNhKhwJm8NTYC19zx4HL4QN4MWwIdwIG8PNKr8FNtV6uRl8UPX1PazjBvb3cGt9D6cbjTeYDLvBFNgRtoWdIMp0hf3U/AD83OuHh/eo+3XgB+r+GVpOz9RyOglWg5NhTTgFtoaZsC1cANvBqbArnAb7qH5fOEPfa2fBkXAmHA1nwQlwNpyi8pkwG86BOfq+Oxvmwlx4AcyDl8ACeC2cD29S+xvhPLhF9bep/gE40tH+X68fHdXMjWPoXtk=
*/