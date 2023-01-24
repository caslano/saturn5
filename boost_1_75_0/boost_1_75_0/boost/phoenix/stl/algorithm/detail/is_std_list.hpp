// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_list.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_LIST_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <list>

namespace boost
{
    template<class T>
    struct is_std_list
        : boost::mpl::false_
    {};

    template<
        class Ty
      , class Alloc
    >
    struct is_std_list< ::std::list<Ty,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_list.hpp
ocWfReXRtpRMomEzo9C+H/rB9w2eE01Hr2PILaJpEhqHl3TKx+vF3irKVfBICuq5fm/wBvOquXPf7KwUbyXD4BXnPJv5UrYHMqOiAVKkPmkQyBnA6owA6mU4j3s66WUc9IQW2LGggwY//xjWC11k5zg4WsP3t+KtcSl+6CCjX7jf2WyAlvu2aq6x/eG/pm48OUk6MtSQ6RvBW0d+HQSGVnctr2WlHFH3dLGptAyorztrTczJzWZx/LYeXVU99r+nmtzL+9vpAZ6530937vbXP6nPAb6Q/MibFXtpd7ztju/0iFHomKjqH/P0jLJHJEeFj49yRETjEz7Xm8Cbv6JAY1PFDYaqRq1jz/qtEsXequb1Vq5lcPOleXGnNrBNvfbmFsOC+fQHviHHYe9m4uRocUFXZOeLUd9nZDMDNNvbtLeFZgBCBNbtz5cThnmKdB7tEuht7yBxA/lyc+5xUM19+8Gx5tnwk9q+umtfatqvjE3QX1DGUaZF8XTffFbzOJOGmKN5fQ0mlVFBbpQjlH2EOipXBNYoSR3Mse5gry3/uJHD5UiM0BpKecJle/iis14auvETXJd8cVH5hLfr6rGiU2Z3f/y6aNKMjhojEbhQdR5ex4TCadlzPSjU8WyVnp48QdJMxJFNKwBbo85OiF9F/T2N71DBl6pLmT/TAqx1S7LqONzQ2nLWEINzfg11EpK4U5Wu1ArubWS8fDk5
*/