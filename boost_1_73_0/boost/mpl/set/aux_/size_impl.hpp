
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
q83KQEycMC/kzFkOhgFPQVrEa8TZS6KYlDcf8WxsicnT414dn3gwMuHcO+qXykO7SzyLUXpxbObOmfFxTXgUXQbLfx0z76ztjd29b8nQz+5/wGJajuMnrNzq3Gi6D8yEDTo/GseJTByt9XoGMnFk9Z0+e/PwHhLGy+lEM8gLQZ4Oc5MiL1IOY+bHqlPKL1HuzNBgABd5Ocj9E0+Rt4kcU5iJpz3Ijx6B91CVd1AuNnYo76Rc
*/