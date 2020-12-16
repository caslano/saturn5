
#ifndef BOOST_MPL_ERASE_KEY_HPP_INCLUDED
#define BOOST_MPL_ERASE_KEY_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct erase_key
    : erase_key_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Key >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,erase_key,(Sequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2,erase_key)

}}

#endif // BOOST_MPL_ERASE_KEY_HPP_INCLUDED

/* erase_key.hpp
KM7/FyFjhs6zRe6ogf2WX9XVQnXRPLnQVtdOW117a3ZjT8yel33x1J2UkzW7Fqg275R00UfOp/uhNu3sSuL3pl1+Dlq2Z9PuDp2f6ly8E8Fc920yAoREza5WWagWdSIqAsI+9v9o9GU9tr1mt7q5lWOG+YAFfS7fl+w73SlW+1RGtLyp8ZH9fHlD0wFMvi/hZ/Kn4U8yfwpsdvGPsR/iqhzJXvkenjTa4sM4AxZBWstZLVdpU4t1Ob4RWistOx7EDcUif5lYbB5JyGEcNo+aiCdKLKpwYV62eV/m9bQ8QpENcpb/7GulH3TgAFTnk6t9cT3KXm7PvEFEHLS6sjBd+9nwqpNNQ0JKdc8Lmqn7OfUoW2rQVeVXxoKNn8jNjHrjsZOoB/S6s7AkmFVfQqnwOfdQoBBidyATei3fQWoMn0Xge2poY8sE7FeINy7HPmrHcCLpkmYUa2btT7NrHsf/qH2+W83nPMsrzQIRFGj2zDO/TKQvBPdjBfdN8/5d1jZs6TYc5S9ijdJcs0weoLSEqulgYJs6GOAYYuE3p9LBwISv08HAF3eBKihdDgb2kty1uHzHIg6zhta3QEmlQkfvlSO5955UpNRknpM0ueb6+F7lkiYL5dVyMR9dQJNRboB/NJEMResdLwU/oDmFgZvExte7MqrOE4PbvSK41yavAtysad5RqopYsYZpkCYmRl74b7oqzcR8fq06hmupwk0kSW7CLHkVV9oHOPQUa+swCYiXHAjl/3v8aP5EJpsawe9c6Dw1TZ7/G6AEcSHATsSPvGb6FKRHJhvf+Y1KjZ/vdYDujP9N5zzmvQMBkgtlNeI9hkR1/PZ8oe6MrDseoUwq/gCriSh8gJtCWSjRSL543ezZv01FEMAK6/fxfrkFUSu71u7mw5fFiw1amxexYRImto/od5Phr905grpj8V1I7GKuB9jzdKjdNYKyL65BosfG91tSwGxkdK3YHH6JzsAHfLhFIWjF6UAS483bmRZU1zVFdWiFP0WNBNeN2xmGQ0eMRnWgRlGgFs4ZLWlikMVNDni+5zzD7UsfBIF9WJkz2Dn0BixnPoqt+a8kdOv+h8fM81bGerCrsognYpcyetM2jcZR9Xr1ks3Uc55OJocS25/n3FhsPIru+GZS34E0Tq1fRd4CtYC5neuXBSmO3p981MJfL8O8rMxn7e+LBAVRQbyh+TyOigvf7tJc2M9ceFad4sJNbqmTZ9Y4bz8frTvzBtaVB6E7Ra9QSv34AF8JewFmOBb6jOIgJUbdonua5JYAdUNpA79YepWLhrz9ukTLWVDCZhwF6Xv9BDe77Qg0qiZDBQUNwoM0iHhDXockUS3Yyv5f2oshaBbxEUNjSYoYF1ltW4BJsHCMd26YTkOIR8+fdaWuQF88d4IdOn3N4O14Nvok2G8U7TOD7VZGlEF95CYZIVav6pl5NDF5IQ7S7hby+FTmEkTUqzmQ2RsTxqE3BN2oD+tDS9RzwDLRkfwR/ZH87YPUXOn1t8Y6kchO7KVgKvYoSfm9K1y0PCsQ3sY098CziqXHx+P94BdKHxK6GRssiTWrjAm/g/0uydu4Krd3pFf4LgIW5qU+/HN1/+2PdSgklkksfYk1XffREYAb8tIQksnqmYR0lFqjmBJQQ3P4GYLMV/mXein+ylgaETiNTBJb42YK0MQtwLcTIn0FjzU2PLY+qA3cb+CQtPNOiBRIph/bMv3YzDQ2NjxytmT4iS3D7ZKBqWqULxTe8vueGqfwDnqOeI2ie5Cjseeh66QO5Cf8StuCeVFlqvPB1b9CTyGPLR3mLT6eP4NpLMNTPNTsndQBkRvDD0jrF63WYzlSbvkjRgYfOT/PWePDOUo=
*/