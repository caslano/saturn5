
#ifndef BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/overload_names.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)
    {
        BOOST_STATIC_CONSTANT(bool, value = 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            );

        typedef bool_<value> type;

#else // ISO98 C++
        : bool_< 
              ( sizeof( BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(
                    Set
                  , BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<T>*, 0)
                  ) ) == sizeof(aux::no_tag) )
            >
    {
#endif
    };
};

}}

#endif // BOOST_MPL_SET_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
ckqC/xMQ+GvxDawAkS2akrZmVHFZhkBPz9tKyTPTKGnExpX6PqkgB4+xqMn3fcjEj07T5qf4rBvAZOA9iTJo0uO+9e5rpMGbQr618NymNnKgaIyebgU6YsbOW1uJAPp7H45iCSdyxp4g66+T9Nngg2S6nTIzJD/uEH/6ffT8EH09ek0n9ZAIn+FjK/Rx4ZrFPkTyuwtc7uV0/VTCHZgm9WSUMb1YqJgHQkHVWgMOAEUfAAEl6GYgYUiOjcaeVoqDWBIMyx2m7r6CLH8aS8pHZK7a6J0D9khR8KDFwOc36Um2Kd1pfN9SN47axjLlGhdF+Sw0tdOoSs+Sl4L1EFFZuGjEzRRGRgefEFG5zvvSBBSIDhaL+xBkodPMnZ59xRnjocdY/5z4FELmhqkDIPZ0md18WvSYkMUefQSRcPaP6Ifb7Sqxh/ZBpufXS7z+yzTkaG8FNtKqu0bFouHXDpatpYOGEXczXfqtQc7ZIfaOvMMBFngOFfmZ+NUQwo7IiOqNDSl5HR9JpEXVRYKc/3GEhlXICnUeYvoZg1d2orpxJW03ZJtSPeUmZUdEXw==
*/