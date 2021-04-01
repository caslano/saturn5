/*
 [auto_generated]
 boost/numeric/odeint/algebra/norm_result_type.hpp

 [begin_description]
 Calculates the type of the norm_inf operation for container types
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename S , typename Enabler = void >
struct norm_result_type {
    typedef typename detail::extract_value_type< S >::type type;
};

} } }

#endif

/* norm_result_type.hpp
16m5ghYqST7L7bT+wJZTDJ3FdflpqhhEoMEzpNgufQRNaDNzUnzUvlPOU/o2jLe6VTPfzXLRRWP6tGQD2lITbqxUbqZghT2Lx+9qTb0fjC7JN4YxrAUvMf6joeBEal8kWhanTO6qw82xpCeSd4Lk0Qgs7TYgjb/E9DCch6T4E5Pp1sKxMwl1DK3InnMNLgUQ12G+5e02vHgXIHGW4Z6d3qDaG6CVSJk2bse4JOl8BelVe4m9Uv9SoxpLmRSPSx+FQE9XPTDgRf1W4An938huoWmT1a7U8lX4e3oJ3hjeKEfKRver/FoSmD5n4I0sP2RXbyZTef+N6nFtPNEw+2+W38bpqlux6V+rCWIiCkBhbQNAjzZoI3O1vtpyzfsiczP+lSLefXbilQqctVz1czTvXLHKy7T7bfyvcTmC9Ldw8zJlkqcemJbnnBUBllDp9t5r6WF8kMpVlmJbDnc+Dbs69TpOXXU5CfwR7lxirCuqlg0aTYrhdQ5KGXMFueB5L5aNBNVQYnv5ulB/1eue06Nl4sN0efTnYXhvfIa8cFq/lK0T3FaCNNm5fjGCUQ==
*/