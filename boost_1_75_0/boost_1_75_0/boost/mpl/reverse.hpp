
#ifndef BOOST_MPL_REVERSE_HPP_INCLUDED
#define BOOST_MPL_REVERSE_HPP_INCLUDED

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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct reverse
    : reverse_copy<
          Sequence
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, reverse)

}}

#endif // BOOST_MPL_REVERSE_HPP_INCLUDED

/* reverse.hpp
MQ9IE0s1gLI3AhrQ3Lmv/UQGRizb7Rq/E3+V26VbcTD5XbKjmWsgZ53woSjX1orc4TrRXaIkxeZYI1Trdyw9emVnY26dQ0N6SOWp3GrmuF7zFaLbXCNpCE2ASi66prVlUe3mVvFYO6Mq+y48HaxKvaHqCgx39CEDCnvNDf3feZjDqF40bHPLQ5uiZgsxOz37AWf2/g/rREuVfdBQhJpNuYuAc3VNJF9U/9TmNxfG87YPHPXwzpGGIrYHOaKmuY83RPe6sb+a6h2iV5BR1xv/hQlwd6mu4h9r8X63YlzxVyYgXztBwm7Zz+Hrn5gACgOLs+nqfhfvS0fnPzIBAMGlvzIBPxTv/sQEWOg9A/7MBLB05ep6NJf+mQlYyrdAv80s/isTkOAPGqmxrYCQlYVLLDBC5jxt/R8nmXVrwt2yDz2VipYLJoVkOOTmkz2K5OeKT+p9o8x8AP7239oFDRKqJYGSX/jENrkBLqj8BSfpseK/XvDyeY8TSzw/G+A3eLdTnGzf3o8LQmzgIbpJc9vC3GSjfaqaxRXztnNc0THdvrPsFZPZ3IUCdi3pzFeN5ZcSb9h3R5/IdBZoc0QBhb+JKjUeVps46U//Q9f4p/F+xix8o9OaliIUYeb/CdCofjR0RkgVpM+ZfSsdaNhr5KXyiIZYrYdueebDHCOcvXXtPjpG1xQyg1h7SkRwYSz+NP4OFRQ3xPcAvYOZZazd
*/