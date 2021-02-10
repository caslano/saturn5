
#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/list/aux_/iterator.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_iter<typename List::type> type;
    };
};

template<>
struct end_impl< aux::list_tag >
{
    template< typename > struct apply
    {
        typedef l_iter<l_end> type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
H4KRGI0FQR5fSa6jE9Aa9Ew34JncInuRNPGq0yIrMD2yBDfw66BaemIZisA/scxiuRHQHwb+8NZLk3vvZjy6G47G3/rsIUlwb72lVBs0AtYNKbGpVhaV9V5QbWwu4K6dUZjYQisBSakNnjFxs8fW36flud2V7OdBqcbLUZKrBg09jHmZ1h7l5HII+TGXLrBpWbQ0LrCkGxDEbXXCcmv3zOhka9rMT7O0TNq1W/6zr/Rn892BBOeDebSKnxZi0LVqES3jrtIVQKjkDifnfkJdSHA9BcJAoeDCCVRSVFrtyBPUsirkukSi4I4DwkTvdlKlzse/0i19q8zv/TGpn3H0e9xht/d3rIqsgTYWkJnFCmyOXa8hlwbWiAr6Jte2z8K6wxIFWbM60eWEtf5bBTidrB6ba2MF/Oejx35Tdt7DhrSpgYeq5IP32XL1FL31jkdAwDW/7rEeebwohPwsyy935C9QSwMECgAAAAgALWdKUoYaXnJfAgAAVgUAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3MVVUBQABtkgkYLVUYU/bMBD9bqn/4RaEtFULbhgDGtJoEwiYGGsF0fZtkps4rUVqR7bbUmk/fmeb0g4E0j4QWYnOfnfv+e4pmeXGlszwnGRC
*/