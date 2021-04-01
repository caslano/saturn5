
#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/index_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, index_of)

}}

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED

/* index_of.hpp
r7AXEJVg/JmXVu2A5+cAcWlkNtkEQ0+sGGYFS9jAAJGv5WvcY/uWaHI7GF6gWFsND0aNVE2mfEIgxqzdAXdsblUs/q++kxWzuhoIKQqbtERJ2YBgfkJoRp6BSvog19ftpskCoPRBMiSBxBBHWOd+IRHgD6VLWqgCGBrPObOfFkCp0tSNjrIPRp/axpjd4KnfEXLnquO2GrhrTrsLJigAzmi/Y4zkMG9GBnca0S8KvemQa3agXrCJOwxmCYagJwbt/wtWrJJ9UpFmGXV275+zdkJT4ky79s3EaiS+9vCHVlBqLugNDIwIeycZVBvSmLV/DTLrhik1oeV/ft8pm1PS1jdVYulZ9IPoIm0nV7Od7uZGAmMpUIc5IRyNi8It/mcZaEgnhg8uhgGaHv58hZK7lREW1gpOmCVzrBn287EVcPm1yE1GaH8cPsB+PhpKBh2OLS31y8j4P/vMesBgr7gzVBOx8gQ66f/l7A8w+lScSnngph1C+QulE/ctykMo0Qjy1Mwnsxd6RkLPCNouGFwjYQys54S3yQOSOPja1msy1s4wiMgaGqaPNy1mhA==
*/