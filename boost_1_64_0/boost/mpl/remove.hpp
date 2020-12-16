
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED

/* remove.hpp
y02FbdQoR6w1fV81zFOEscTVLvS4N2TV4515UXq88BPoEfdjLz0Fxfio3ULxG1/8/Vrenl7q+nD+1Hrn8xTr668wVDe1if9ostPQTYOSykehm06WXeZBl+Wgy3K5Bz5pUz2ALvuBjR6w/oDsR+6y3yGFDqQGq5CC0qnLHFRdXPjtIs3moMvwjd/CNl2zVOkNLBx7xMrhTal6v2lVlRqTaBSfcNB7XDMu/V4XMkjcnWQ8R/SgWzxnnOxh+pDfzWJ5ModKBpXgy5BP7edSD0q/LpCRK4g7UeJGyVTtmf0GKr3W54QFBOcbSEH3XzMEXQ5VC9a0vI+BFLD1reEoxqMuwW+BlAvFb3wZcqggQWA8kqhJ/I/x5Yb9D1b+SocZgJMLEPUDoNwAUQqDCLDZxO1+v8cMlHlhs21XQ0sd6ABpwzDBE/cYHfhtofLcYokH6LUuKGqIrsoNG9j0igvvc0Wn67fia88HVVfBgjcMgp51UWDIFR+iq2DzfxqGYqr6BXdD5H6GNbR6GbmfYSjr7eBA83rzloIWofndyte6SefQtkdo+2420lf2sSJaqypbReaPKdPHgZ1v7cQ8D2ytMBOi0cmL1VVvpTqe3hR2FGuviD0Q/oKWqsoW7poR1LAsSbs0e09XMb5HmjoKNfg2+J8QPWwzOO4xXrV3FnO/odIDslL5d8tsvsvuH+jBN7l/rrJnsvDaPx/V2xV5SlDhBlVhdBktmGuC2lmnytxcYmV7P2IFtReMRD58wEJAqEW8Drr0eGzRgGK/2SdaTK4IynZ6njL0spwa+iAqvvu6R1IuH0B8FGmCu4dPMWpnlyVRfeJQu+x4XWW7fSuVgotayCs4UICmySfoONotYumywf/mWNq8n+m3ztj7mfB9i0oST40ZLowNbrbgV9+1RibztLs7lE2TgqbLMVWZ6pM5e5S/PRnm/cN3YWmUk0ZjFT4YkaoPWmTs9OKNadC5cdRCiz7HH6ZbZHmcLM9DuUSh0gWLcQvWr4Q/wyt/fAtICJF643TWzrWlne7AovpF+YTXEJy4i/gdzpKJonUoalJF7muLKPv2OsoOOUMPeRsT4lTx10fwR2bbABLT4jA3wmCuDhw88DAZEzjIuLag052sM/BcYgwADy7DH7mT4vij7x9n9UetzByseV9alKWRH9FdFXE7schTPlAN9Zvf1BW2gP3TX1HFjSoqirvPXAVfBCobLM1r55sl2qkwKrf0c/bQ3EBpCwwYsH7jdX0UXzBZz3eQ3ePjTc+ooqHkUW4hT0hbo4T1t+zUfcMHo5l6rmHtXK6V9ZfWXjYMvMBf1HSBnjLvwPFH2rypP4ASe6jE13h5Erv0AMlccDwCKPGx4mLtd8dx0ulLY/e/i7nFx4vpCvpDYNiXLgvQJ8+K3ET4ZjyMw/dv+lvxgDfIauPRXURf+ZnxA/TobntV5fakctrOtH2W9vdcsBj8Pmq6quZzGMEfg7qZ3Ewavxi/xSNoXcQD2y667VUQEJlniWaBQk8JhOZHbS/Rzs0GfMuSRNS/vVi7CDlisHiPoZTDfl37wwEdY7clB5l17Z529mJNVZVNSeU3lZF8bgw3TbO0PsPkoHAlnsjfBXpQDGB4NFtPE91XpKqdjcHxwANqcBQValSFAQy6XcRfE51EzzcGlwtRb2c27ElXqUKg1g8Vi8UAtIvGbJEhBC/P0cUsTyaxQyeA858IStCD90T8Jq8ApL454EgjNbE/83jkgQwYj6Lx9j5Jq93bn1GwG94HE9Do6Y72PQ5ZtDwxE4MjancAmi0UrfKzyhxlczFQ/waRkAcY+MSOKZKNNZ7CbkN72YHR0ZjWvCiqOJMMwGYRUAaJwYw/Ft6KuRY=
*/