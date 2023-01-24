
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
LsTbegxqbCqqnfDvhYMff8nD9GK1RIUxDcI2IqC8O2U7JCnjvKBn5KD7osQTYf+/goOetQTQ/7Cz9T9jq/HfONmJzr1zvNcT/sRWh7/UT1aqw2hoN+ACoU2UXdHQ89LOt7h/sNX73NWarrlNW8nG4DKjH8A/WwqFnbWovhHrCUKzb+8DQR3hDhCrt9m2qTTG29nOzeMjMPNt21GXlHDVdRuHAKAe7aVrTHaTAkrxD662CPcnf/d/o7SY/2srtS//mH81A1rba5mbSDrYmZk7/5usrR3/kDUI8C70R4jIB0qGsMEPCSKq8CJncZTdJD5f5bCpjVnf61Kmzr8TeCepO0bJUYf4VfK+m8BPHVVCjYZRUVavLL+PGt+WKZaqTV9IXTERpy1Ofd8VbzCaatUVh869fDbJRDe9qs2SEN0RDlsapK1xoeVQWHTo1pVn1AWabQPfLDIZPWUeOsBYxxlRigM2xhdn4uK4D3Lo7xDRnl7thbLZOA/BGhta+4QiSDeNI+mDjGtPGVoItv9QtrdUt9i3nLfQtljI/aytmWfvy65HDaLV0LZ+ymKzOzVZmbjTpzSVF5bupB2CrrXf2KehGk+tbQmNDwLJemAT8A+N64cycz38fnqFvHcKECFEhuCPsTS6pOzKPIfbXYkJRF8OLcyi4QXwdS7DQY/fKKsBzUzeN/zJSeb5nyu/GNHxjMLgtvgZIcLND3fKlo9P
*/