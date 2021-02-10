
#ifndef BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_SIZE_HPP_INCLUDED

/* size.hpp
ULUsyQkiiwUlPoLlHtJkabd/gFGUGBAG9mpbgCozKBL91GHsneZWeP8wavHWzdXdYtTyWn9HvvWvyJMDloM9tlf/+dsf4BdQSwMECgAAAAgALWdKUkEn7q9DAgAAZAQAAB0ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q3NFVUBQABtkgkYLVUXU/bMBR9t9T/cJWKF4RxUjK6WqESYgzYgFaQ8TLtwU1uPkRqR7FTFqH+99lJC5P2sodNipLYvvfcc8+5cmRQm0RonJOolJmyn2fsXlST6jm5juNl/4Kry5jklVqtSpmT1y1UpTYkYu+hERuyx2QMj9hssKG6TJFEDdZVZ89TYQRIlRSYPJ95HWpvwGfBcQAT34fFV/JJGOQQt3gE/gzu1cYeBD4EIQ9n3IZc3cVkAOfgeFPdL1gmnpHcCrtxp9IyKzHdoQQn8KWVDt6iTHjg71EuY5Fz8CaBP/lA02RKT2bh6SScffTIeZJgbeiDkDlqDqvOViIXShqUht6izE3B4fRtJ+5qdGx+GlaYdUU+t1J2tEBhOdgu7UMIzZSiViKnwU6K4K17f9/93yDqF51USqMLlpiYUkkOww5JGlGDw95VCpwrO/l7Xy6q0uEPviT9woYMGs5JYUxtE/ZLiKRY
*/