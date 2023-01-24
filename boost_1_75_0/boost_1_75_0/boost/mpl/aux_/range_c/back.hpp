
#ifndef BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct back_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename prior< typename Range::finish >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

/* back.hpp
xkQBZRNnNPYEZU+qafN25Lt+aJWPD3lDhVozL7rCyAR5RxApjyWad58EdnNG22FqmnzRhD13xcrnhp8ZZs1YcWnfMybEOr8esbiOn+9w348y7Nin4XIvhyjM+y67bEkUgF3AbmIiFidHJ0ZeSVMU1M+ulLn4J1jkBVuF6MZ5AuJkeVtFsXNXJlwvos+UkHJAgYKR5PO3N6q3j26Z08aST3SQCFi+Ri2FTxg0TL/oSp5QxgW6kyEKvaHNu0WHTj0hHX2JjRsTZYqLeAPk7s0rnLY+rxXexjXx5ixX3YXXTtF4Af2cdY++fMgK0114GkvkNXgqndLIxse+YR6xAUh7ShnpK2pa8DUtKmRV7O9teemdFnt4iB9RHs6O6Ou+Th4NAj3ly+rGWvs0LSo5OQkyou53Ue1wzLi9KcAI+6zoM5yN9+G8JlwXLBKlwgySkWbELLxRktGcBTg0C2/DXcNVfybxKweu9igUFb+scrfQTaNXg7/IvqLjueteevB6RBMZtEwcwZgfDYipobCdnZnxrOmJM5BC658vDf7Qi0995+AqksGbzpc5s/6o8QV/r2nkzPHP9EXVhIRzC1M8Y+xLPboBCL3CuDoX8ScCYIyFUHeRm5yriYp6jNc0h1nix5Y47aMIWPv2A2/P8tMqMexqmP5ge/psjgsJmgmrGbvTgMIcjxn7aAJL+JjdBTGtfwZRVvTmPKiz/vldh0tu
*/