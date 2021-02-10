
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {  namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

/* iterator_category.hpp
fTDzg9tb+PqUeKIHDOCjNWtma1sETzwa5vLksnydY/ZfjDtXEpYkH7Hc0DYAv9sqMaXclQGk1jV4qUqOFdMiPJDaUmE94bHEXoJWJ0md1jubt/W91rRbcEnTEV6ILVHFDcNSl6Zgr2MsMxiFUXIffothMoJ9Tlt46y+QA3PyXqu+U6/R0K5Gdnw4uOzo1BWFKbPFP1HB9eQa5E8YRkrZdUNLL1BqvArj5D4Kxm06UficKJArGCUMULqAfZzdjIba/X4/xYMpKotTV28UMziP5c+TAUKz3nzd5s6TyKXOLsRZMAx/gSdWrqEA3oB64js7JpcbxuJkdrVV4x+fn2Pu9sQyTbHi7YmaeCJqZcjXOT4gVnJp8xcO87WAPsELGa3ODNXlFvwFUEsDBAoAAAAIAC1nSlJRG4fSdgIAAIkEAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTYyVVQFAAG2SCRgfVRrb9owFP1uif9wx1RVqpoGqmmTohQpdGxFfYBI2mkfXedCLILNbANlv37XMY+qW5cPiR8355x7TpzUoXWCW+yxVKqppscctxttSttjN0Uxbm7wfVCEwdLol+2rITwUd/fAV65i37Lh3eNkwNL4iJDGAZR9hBzNGk1kZYksNbis
*/