
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
d6xSaum47PW5Gzlk5EDwu3l6rcTkoeHxX4cyfgLZfCt2tZxCCa4OjCDecnVIbiW0ggmBVPoVzNUasbeHjjPPfWcZnlLPjU7D1ngQVxb3JYhuWW2Lys626tL5WIDwKJ7Xkw9VXz9L/1eI1f68y6KrunyeQ6pQhAD5BA5AOA/TTgGYg6/a1j/qtm5zHi/T7SulyMt3hjHPzzeKJ0xte9ZJ2wzDPKManxmoSVTz9vr4DVcBTefngXe0cba+JaZFmP5H2nma6PhzjLee9xmCpvTGgKC++vLqVx/VoPjMyYGelgCuGZeCPipoExE7yeGXNF51D9poJ6y3+n5gvdMvBa1gJYsa2js7PK8R2b0OKfVSTJOU0vQ0tWosLUAaxGCifbCUFMWlUcQCkJY3W/fJT+j3Jk7jdrA1ALkZPAhxdNibKIigFgDN/MZSNlzZ/maTYfm3z1JqKjahDllCqdjRKpYoDzgul8FnFClZh/c47KtCY72nnd69ZxQJKNlrQg02l2+m76jzTqXmCElkmbvnOO106WJ8dKnv/T6VCO/Hkrb/zsPk5U42ZJGoNLHUqRLr+BnopfRTR69CQrlUJ2imOr+cj66c7+Nd9ZnCHTrRLIcRSAIfo0r39gTXB4oucI8cuzM/89Y7AjVkxBLa1ePeMoURbEZEgpE9XpLq9SOciHD1bSESfcuYiE6N3N/CJF0C3qw1VI04idnFHZuoxrIo
*/