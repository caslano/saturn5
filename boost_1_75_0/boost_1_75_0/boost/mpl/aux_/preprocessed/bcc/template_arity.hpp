
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
pO0YZlLeMiZtkXy+YzKxYqULQL5Ccfj9rJkBzYFmIYfK8D3w0UkTJkpfznGeb1aVyaLRTttuhtjuZ569vBtrKKtdaoIZaYSryZj2gMlgS5AHJ4uBPKCB+JThllNoQH/JTgKGn65JSGmqNZmaMswMIsGA/cCkfRRmCTbBPiV1S6WyYsqIbtfj0uCixvCod1aYCJLJ+FPy3M7O25KcpmgHNT4/OfKbryEO81RRc7ILWd9mB+ouFbyD5PUtZubzrCRI8tjyLE4z3rJaTEgoLuPaER9i3jrFDH7PPPfE/mXSQ9oLndF+XOeDWZ9V9D4Q+ptccTFeKN9FnuMnAT+ZMHmFXxOMdabTJHTFHzF5MTUm/DVQVtoYWcroCp9N74qezeiK9woe80mv5RhDGyhtHHQN7OZMI9K7IPeyjBeiUdAMjcfgc5qG3UsXyVRzahNcY9u3O8Vf94B4wvHQCW6voA+tOjYLX9ioe810hLqeVJ5ETBIBzxXMXbNWzlP37v3iEycdMabbgitoRb2YFMZcHqfLpucpL7FRVjxD+4Rud3sQPTrQBNS/f72Accx57BHZnhuAMgT3+tccmIhBmAJQXawPyGs+tN/iWKv/p/PvBtaPvSz75Ynh9519LuToeEXv9Im6Qt+dEvtftI0v7h4nVCZ7NQ0UQNEZlkXZya6xB7QtUkug7AzbUPzr5XajSRXs1YHvy6KTc4ypwqowcdtR
*/