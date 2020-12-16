
#ifndef BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename mpl::next<List>::type type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
wiS8HTOwG07B7ngn9sB7sSeuxF64Fntr+6KU/NV3crzoLPnrgkHYVbM+gvJctyMaLfkZg744Fv0xHgMxQfKXKPkbh90xCQdjsuTPiOMwRdJ7uZRcT8h1BvFSRux/qAxpEu8EiTdD1n+mxGfCUDRjV5yEPTAbh2AezsSpOB+n4TKcjmtwBq7DmbgZ5+I7OA9P4D14DufjJVyAv+O9GEgaF2IoLsIuuBj74BKMxaU4CAswE5fhTFyOd+MKXIorcQ2uxudxDb6Ea/F1XIfv4QY8iRvxEt6PV/AB9GL/24yV8UFshQ9hF9yC3fAxTMTHcRZux7n4BBbgk7gKn8KncAc+i0/ji7gTX8VdeBifxeO4Gz/HffgVvoy3sD73ox8ewHr4KtbH1zDPy1Ds+59BdekLkumH+lMvRrhKcFXfmD5AqXMk4GHCRcJRxisNtNdBzhhYtB5yC9NeI9jqI31jnddJHo4tvl4yOY55cC4aupBudNYeLGCQrY4SB7mupwwfzPIxAbfgXHxt8I2pt6w01MsQSgiIJi5cSdhLOEWw1WdeVX4zzFqvacYY1oe2fvPSsKJ1nGHDrfWc/TCV4Ky+s9II13WenZS/jfAqUd3njJFe9vdUSWM+YRvhEOECoXwgfYYSehFSAz31n57BM3gGz+AZPINn8AyewTN4hr/38Gc8/+eBzw15/h8oz/8vLdI+/9c/+49R+wBw/Q5AUI7m2X8JnvsX1/5/f7ZluX/ZM39bu+Uy8sDvSlnSJ/7IfAkTJH0Oz/tDrpUueb5/xqR/3r/LZH/eX99ke/YepvZHGJZpm9ZWfbZ/PkOdpvZvmJ6utgtQ5z03UZ3W2jZty8SibQXGTSzaN6LPxKLtB7zs09rYpj0yQd+mwI9pq0w3r81A/Wu0GTilaTOgjJ+xtQ9oYx0/6/BN60u2v7cmXsZPOmljcEyZpwzzmPVtx9PGZTu2OdBtOzNk21kg2/Y82/sJ1m37hrQvqC/tC7TxjpFn6tOkXe9k5Lk2jTMlXoe2BbXcjNfdtgWyXtT15PCegP65Md91B/33xou27dD3dyH5+07K9Wtbe4VJlvzdkLYKknZdvP3KGZy2VYi1lusNb6dgizdA2gF8Ievzc1mfZ4wSr0MbBV9X8cr+2i6F+ZRoErNyDNfRbsHxnYlLmnLTr0/9+rsg+emuPB/DaKRdAzNKfuxtGtzKz5Ak9/Ljsp2Dfvt0dZyRvHjeB/kr2hjMtbQx8ClTdXaPIyv++Xn7ds99Ma3jkr/f+yBBOa7bEjSRtgRNsTzepmlLsD/bdVuC+dKWYAH64kKsi4swGBdjE1yK0bgcY3AFfo/7S8v1jFzfKMvPVa5LpL3jl/IM8Gv0xe+xLl7CnvgTxuG/cTReRiP+jCa8gnn4C87Gq7gRf8UH8Xd8HA2kZwd44fNYGvdjGTyNZSW95fAXvAV/xfLIPIaK6I3eWBUroT9WxmC8FbuiD8ZgNeyP1XEw+uIYrIFJ6Id3Yi28G/2xAOvgoxiAT2Fd3IWB+DbWww8wGM9gffwCG6DBi/WNt2AjrIRNsBo2xVp4GwZhM2yMzbEVhmBrbIkR2Aq7YmuMxjbYE9tif2yHw7A9xmMHzMJwXIgRuAwjcRV2wsewM76KXfAN7IrHMAq/xGj8FmPwCnZHpT/aHhiAPbEx9sJQ7I3h2Be7YT8cg/3RiAPQhANxKsbiXTgI78EhWIBDcTUOw604HF/FEXgER+IxHIOn8Q48i2Pxa4xH7zJs6+iDyRiIRmyCKdgfU3EkpmE8TsDxOBEnYzrOwwy8BzNxGZpwPZpxI2bhg5iN+zEHX8HJeAin4K84Fcuw303DcjgDq+BMrI6zsDXeie1xDg7AuRg=
*/