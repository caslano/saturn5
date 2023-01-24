
#ifndef BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,1> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
xslb0gcBzFXLI5jAXU0MdAD0xxOZ3PaivS3agnCO+gXRwR55cg3BDBZjqctjDfWBf3uEMdDbI+293b6wNOqxGuJ7r9M34RErfStKw0XJa6XusdBtaVeilIX5S0FnQOrpH/E2X9Drm+UdsU1d0NvHFvSy+Udue6InKCYXU0wtoiRUVQ4QQi9XrRwghPP9ks+J0QUjWmyb7VBThtUzYi/WFIea4uEva/etXCo23Jvvw/8zxOLx1lAlGeiss1twvU3e8RNi5DitW4pO+V4kg8g1hULkmgL4Gwmkda4YXQpdWWpfGLkmj7Yv445l8j428512u+UHTQzCmKdA3XFQ4JOuLcTQS2QfeTHo6nf0GH2ggbtvMO6iW4XOCz+DzYk7nsreRqGNPgfZ+3kmiZfKfkz3xhwj4CUZ2yYggQOaRk5iZNpZl3WcDbgei58cP5ilxw+y8EHjfgik1NYKg6iMzJMFX2yc7I/lLn4ezfpx0PYJ+WoLE3+VMMvvz3dl2ciRl7Axx0bJgxaavBdilIGNS1qk+zR0axyszNNY6YpjDGC++wrnK9V63GP1D5h2YVmeX/IcB4oZ5huBKIfb40NW5PhwGvVmQetCqEJxNKy1aLKflq9YILqoeICOT+BCnpTmi7qtvpJtYUcgmhaIjrXCn92z3Z1nakVvSdHR4mXWsN0fddt9JWPt4V74OgFWj+ArSQunwzc+Cb6X9ra+Qu7J
*/