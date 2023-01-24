
#ifndef BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
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
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::set_tag >
{
    template< typename Set > struct apply
        : Set::size
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
tojywbfIjrX7pmgEaU/JyJIdzHiWLRjzjDcseGLN5vGEwIbcudf/m6dD0CYzGev85jqnOBnrzutpXswQtO/5NF9nCLob/DOQ2LqeGdMnCDccvNSt7dV0D91XVllP15CTKmjc9OpKxDfQzw2tWVwYEkQ73U6GHZhhVxEuF3INI7r7mOYdzum1Ksu5dt9iZmgb8YiqJTdN0O7jCOoxajXNKYBatEOD9hIRlaQqoiO4ssmqEWQnAc6ay2KzXFBonmzTtety075NzMxgAuwUqvYI+3091TBl+YPHQvhSg+AGFoFScgvDigkxivC1V4EBts2/wMDbfFeDS8xQnwpIkrLUEBpbJJjqWqAzuEWIZzQbNl8UYXENy+to+1HFsiMs8grj8a1YZP4OFobox8JMLA2T+CGHvkwE3dkwBju3WNjz1iTVZrS+0RbMHs0c6fHGTaflHfRTromiEQQ22NtF7svqyerMcq2/1PROZiFAOKbCDu4VKy6youB10c0oyjWQv5XwxL+McBuGEtpuxBkKJfwH5dttRvFE/l8HO83/pnwxB3sLa2fgf6rHPfWl3IRcGmqzNM30FDP6Ypj4Ys+1awsa7IZjTeVelBdkzlKGeFGjdarybb3i5yub22x1uDHLcGYLxzWdiGdnvNvg7H4pIMpI0+PFFbI4rMQJwRdMcX8/xpWNv25QFk2CjY0ZVOQn2pX4UkzF8G22eFy0T5hO
*/