
#ifndef BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

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
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : minus<
              typename Range::finish
            , typename Range::start
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

/* size.hpp
z6Q5GOPH+ucSeastjBS4a/31qGivoSkSxtUCNHwX+qs+ela/bO0reXPc4oXEEvjN8KtrGMCI8D5FBhO2Bi/3Ob4L5yplEgccKPlMlhrl4Wvwb30E9ooLhstia8g3eT+9q2QpCdUz+mvMZ9uE+1yCAo/giabhAaKF9shHH8fNunCZY3NE2FDaXoPZSH5GDU6zBftErcQxOxGGATtXzNc95lYsjNZ1tSwST24JTUb37FxMtdCyY5wdfeivBYjy3ukcOKcdFK7qDLBV5kGefBhQp/VQp3VRp/VPDtoXas1Tzl1aK5OiXkbh1kqGsNARvlbJPmpSOGnczZ9b/GUu0et8CH9mlm4ZqFDFM3KGajBWpR2Nw4nR2iylkWzOde4AuWyPvjX5wFGAsVelm7GoBXlkes8uSZVnwAeuRaF/NLTqp73wct98mgfPOlp9LsZ81h+JGO8rirJq4iB1aS20/spWfE8Jfh9igo6Pvpz389+3IHsvh17pcIOQj75IxsReJ+4xHLFhC8aAKzS7j5wNHfF3lV+U5bV27H5ItIFFBTKz/4DPokd1crVNYbJMBp9TKM1mnep8LJp5r8uEXJIsSxtXqVZJs2Ivsi6XAKJ/66Daoiz4ThupdAKIKMwM98OLpRuWkOFvFrKNr5vE4jsMRxyWNHvFJsVm6dubVr5Zath1MDV1osrGLSn5ZTZid2PGfstzs+6hzw/o5u8mV/Pj
*/