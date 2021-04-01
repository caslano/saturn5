
#ifndef BOOST_MPL_BACK_INSERTER_HPP_INCLUDED
#define BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/push_back.hpp>
#include <boost/mpl/inserter.hpp>

namespace boost {
namespace mpl {

template<
      typename Sequence
    >
struct back_inserter
    : inserter< Sequence,push_back<> >
{
};

}}

#endif // BOOST_MPL_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
73IymWAKky62Dq905qRn0D6e3kBNrw99AK2nb/64aXg4N+Anb4976J1i4IAYxgOBRqzs5y0irrWU2pIwL/RsQgsEjYMFYzuymh7k99IOjxnC/o8L3wSASpnTg85XicuvP6HOzhfELKqCGViW71g3L7zOFp2mawGe9iLiAcgU0LwsmeCTfGL9QV8/aBuOfUoIkh89q+LrshHBWfOuxHT6q4bVoOJX5HAyWT1slGFm0UxiJfvzDrQWMBMCg2fRA1iqgB3aLyjh0ggzuId2Pod7+YlvP8elgP7JgudNmPGrMys0ogi65cjzH/ySgV+wCmXL1YWyVjANrasWIwCuz9pR3biuMDIahRdYmkfkeN5jyQ/IHY/wMzakuRSzrPxhtROorMOKkdVsiY1bxL1FbyN33aLZgpl8wSkd2W8zj4QWAy29fNE0X9JuQYddrthRd/2uyESnqZkW8Q4b1K+Z08TEHimF9i7WuJn7Hatt8ddDdj7c23rP16chYhvaB2KpTFk3WJEp1QiwrXKO62BLntxFBYL4DERbMKVC8ZeYts8UeiqTLb5zThpevXvGkQ==
*/