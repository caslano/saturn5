
#ifndef BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'at_impl' or the primary 'at' template

template< typename Tag >
struct at_impl
{
    template< typename Sequence, typename N > struct apply
    {
        typedef typename advance<
              typename begin<Sequence>::type
            , N
            >::type iter_;

        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, at_impl)

}}

#endif // BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
zhBxa9nW3zx56aL9Ts6EfjnMnvm73yKeteSkZ8ij5FH9fqknXdWd1I55+qTOMjj5tUn9lEnTC0Cf06rAm3owtKUttf0eHIFXLhZumaW+LL+rJou8afRuoF20U9T6WV7bYeVpK6Jjaj0moxq7s1MzlymnRQroY5NifhQ4RJjCAv566fF9XxwEuL4ottlAgIED80M0vGMcAZ4DUgfH1Ht4HmFVD9Adpk8/6LniTbeODw4CNljLOg+GrSkrdJ0XGBjMV5V37s3qi2kQTajb93PvMMs8lw7xA3wblbpa1umX5B+Kf7Z64QS1bocazVRFZ5TXtJcD90nbRSkau0W99FKgSBkR76MRbNuGbFtbi3QdRREMOb2yvsO4d10T4T6sAEbko4anftCqBGWNrW9gxwmDQV7tVyWHGkBywIyqs2oC+cP48E8m+NCLTb0kXV1mHJRIPf4favQQqCsNCusbYI5SHwTgiud2+Q/Kjy+o2WI3AKQTnLKK7EESyHNF02tBySSv5mE4Tr32ZduyjCMWiGlPNPZWcWlfzrT6Y097Hl+e6j9H/oXNBVHhd13qug==
*/