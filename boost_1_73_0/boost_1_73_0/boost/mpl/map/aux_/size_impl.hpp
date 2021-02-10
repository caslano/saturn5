
#ifndef BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::map_tag >
{
    template< typename Map > struct apply
        : Map::size
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
vIUlxWTTJgx5BYBShgU5XREhaAjbJmXhsyhsMloygHxCADuuIeXThKVzJLClVUSAZQ/0WEJK6wY47kfISmAXilTQUCgYd2DhgN9OtovSrCQMEZMDYY+ykbTV0v48NXxz7vkzdIxx1FY5j3Y6pak6HqetT2Fs/fNiadhz1CENoz07bAslbSAEwQw2bZbH0hU1vll80uU82/Dz5bdsUfMdj8+TfVtTzu+ZFyisw0VYsp6+4SUdyfINz8tajG54fRbzpS//dH8v/+ygZVsz3fh1PHgDd62gx3KsRnxxCOua1fgSSzlUJEpJtJ9IUbp/PhsuRBX5CmBu5+aKtq9JlW074IqAcNvwoj4XMw1r2BBSwqs6pc0rSXkSWHEcbWhEc/aV6vcHoOECVZauH/QkIesXmuYtZzr9D1+qF+j//U0WnIfgGbah+cCaJwwP8Gj4mgkDUOd68PsfwvgO7Pl0vvJ7oiPPNVTkS2Hl6z/mK1BLAwQKAAAACAAtZ0pSI5Jp9P0CAACVBQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgyM1VUBQABtkgkYO1U3Y6bOhC+t5R38GlV9aKKCGQjdVM2KhtIljR2ksUbAkfngh+nQDBEQP54+jOwUdKqr9ALY3tmPPPN
*/