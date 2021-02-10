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
Vm1v4zYM/jz/CqItsOaWJr37tLtdh7ixr2c0b4id3Yp1MBRbqbUqkiHJfQH6449UkrZB27UD7ttcNFIo8iH5kKKz++7HPcEuvPrk/j/HB1cymBj9Dy/c88p5fgerPzQ6x/UVF114sLjLW/CqxR3se4t87eMz7fP8FTfnFBh9dMnwPKctSoJdtOvr+taIi8rBfr8F7z9+/BUO4MPhh8M2REwJLiF1XM25uWjD59JLehW7uelY/nsbuAMmOx4oq4QFqxfumhkOuJei4MryEpiFktvCiDl+EQpcxWEhJIf+eHKWjE7acF2JokKMW92ArXQjS6jYFQfDCy6uVhA1Mw70Aq0RuxTWIV7jhFYddM3BcbO0CEHOmbQa2BUTks3RDXNQOVfbT91u0RiJkXdLXdhusUm9U7nlOoszjGDJbkHXDpyGxvI2kF4blroUC1qRChTWzVwKW7UfQkFHquxqA5ZLiVBoJrhdhcwhXTPTJi2oMVrhaLFaWfJ0XenlliJSiCCLxih0gxSgTqmR4DY0quTG6/qkNx7WbHpqXyjJQ6wlaIWRwE6YQpLuwJxZYdvwLcm+jmcZfAun03CUncH4C4SjM8Q6TUYR1lugJwP8pjbcomcDYllLwUvv8Mc9QTjLxsPwNM7HkywZj1I4goU2
*/