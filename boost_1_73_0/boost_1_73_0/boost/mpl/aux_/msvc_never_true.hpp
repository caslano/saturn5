
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
6+rqqryDVvB+xJBfe25aAI1HnaKOaXZZLJGEJww6xWrxITGz9HtSBatg9cNIEvxLuGGqnyCTIWxgbBc0ZmDuk+lxIabfkHxFKK21vHsGP+cOFEoG1M8z5A6WGRedZz1gHJN4OdHy+ikREQ1D9UCeOXdo4oig3WSIZjHJgygBXQAyQ0lirJLX4+o62uuDKKFxPC1hHhj3H8wHJ/cblyv89evLfXp9kQ/Oxx+uxtwXrzF3qcbu03moxl4ZzKvXWe3Jdebm+XbAxwJz4rE6eyzfak8k6n53ov+Kqf7cVFtBtLYENApW8Hxs36qvuW+9bq6us3fV8zpjIbDrt3PMv/VD+390zL6lk/HnObfx82Rarzx/nNNkdoTgaN7uviO7caTVmS6YZQM8Nc3yt61QqRSnz4deAFRhR4t99Eav1z22mJim2Od6dv7AU5zH21YcDXTVC1Biis/NTYt4CR2BOcWyXYGL6JaqiOvGGWeSD7M4ykmkmMaKbbQJ0kcUto00wfUhhBvdxU+QORcMe+uxIHySkJCjuJ5X0nGYNe8cm+1r087rIONIK9eR8iEF/EmUtfv7xcnXw/3+0Xmvf7Zzut9hYxFrbcaKXh3qGUuj5mTva/di/+R8Zw9fQ9g1Gguy12VKfBiMh2QwjmLfymd1
*/