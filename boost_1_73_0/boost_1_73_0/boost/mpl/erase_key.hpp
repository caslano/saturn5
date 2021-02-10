
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
zvRLULIotlLt6QTvjkCkzOEgddLVEpwPF+v3+NtGDBuOzfot5n2tK5CWvc72Br+wytMa2mmQqaMyLsO2mZBJC1tEDZ7NjPNYdGqxRFFWxhnViKe5g7YEXGZnwBbGOjLzfyWDvpMC7vn9gA1IyY0nsi4xRxLVub2SZwFtGx4bA/tcxK8K+O23+AdQSwMECgAAAAgALWdKUlQSTpL0AAAAmgEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTU3VVQFAAG2SCRgTVExksMgDOx5hWZSpPRdkbmG8SOuuJ6AYjMHkgdkZ/z7CJzkrkJaLbuLsIJVvKs4Ghvpxnr84n7nEupo8pokGl9cnY0d/nA7HFRjCy5pb8CzMNaniCQKVSwbltEQEyrh1VphTqNJ8fp5uXzp4OiNJZc1xDdm3iJNgK7uMDsKCUFmJ+cKkbRCWJBCY3gmQi+RqUKKVSAwVjoLJHQbwhXnSAEcBEdT6pIkZVfHw8l6zln1W0JR6qSTN6Tl8x3mZE7wgyXe9p6jR2hLg7KqsbDmyEvClgPuUWZeBfrKuuTWb6oglsLFc1DnD5X/19rhRWrbeH/HA1BLAwQKAAAACAAtZ0pSYOFFyCoBAAD5AQAAHwAJAGN1cmwtbWFzdGVy
*/