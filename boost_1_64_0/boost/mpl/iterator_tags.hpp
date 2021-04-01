
#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

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

#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

struct forward_iterator_tag       : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag : int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag : int_<2> { typedef random_access_iterator_tag type; };

}}

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

/* iterator_tags.hpp
BW/QMKYQFWFdUjDd4gYu45mDalrMBxVC3pGzmdU26PzNaQfysbYmt0Qwg1+WDVHFn9P2ggzXNsAByzsPE2Sc1koUjUAxCe2EGrBryI1jw2QI5rXsS3wQHzR9JOCef2L8p4D1B9VQeiETFVyDI7Ax1ppBUtYhs5sirfUAH9LeJzYTk8ABqe6COQJrWNUlI44KcAvlnW/sVtGrdHOmPnbbISXY01khjvHPPDUOe/JARwfQyQ1hpaQ8/kshxf6IceRdiT6XJRMMOW0TyP9NvrUAYdSn9vkf4dp2GuGyFK8W/pD48jB366VcDIyAwP4WKWFN8MqFkkuaNvIZKYhcbxSX8GnJb3gEEGMEFPpeCxSIYPsMexS7rSRl0a6j8QAm4bmDRt6cmkc9LUWMf5CP4GprDiGs80jPHTy/3/1mafxejMg3y0imigwSER7A1aHQW0Qs+qg520WQuL3xzsjBqQ19XTmMWFztJ1lW32NL0Um4M539ujk4TnozyueEm2S8dx5sTAkCeH/CtLsN4neUFubQFe7OXlwhUDhUmmmEY1FUyMKhxnU+UmiDEacl+g==
*/