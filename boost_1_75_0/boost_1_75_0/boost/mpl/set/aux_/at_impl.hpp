
#ifndef BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/void.hpp>

namespace boost { namespace mpl {

template<>
struct at_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef typename if_< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , T
            , void_
            >::type type;            
    };
};

}}

#endif // BOOST_MPL_SET_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
C2T/0WRwDuaXpp6mDiarN075W2jOh1T99V3IYqp3lsHlCoSl+Y2PRMGTMpYWI7VWopRYcbdxSd30EdSDGcrYLa/JryJks/tQdY0pgV4C8W5QPJ0YURksU+RDHVWaLSE9pmpT8o1/pZxSXCuBYj7KTBaWmzET89fO3KNIVzrEnyYvy/9zIzZdXXir1pRevKco0NtGFGDU1/NneHRJRVrppaa1n9JyQpDR0yoj4fitzjFjWwPbeDI6ajlaQPObrs7oRVWtevDtATkU6fwR+nat8Kj+h9dBwPdSnYSRtPwAw9O4i63cwkZEVn7bgcOD0bmUGtT2jQ+0fqR59NFRR83MKaATpZP0ZvS9UsgfmfncHdU036WyygjBVaYkA4hLTabVseS+0wD/UsQscBMCg1xnTAZ6uBbfxzstRAd0Inao73qql8tOT+4kzzgKTqHrxIfYZ3QFp8gAwkPJ8/33a68dGT2ISeg9qEkYPHDSGTyIR8DxG9wbtB443qHJMJwPa0yBMoeqF+Yat1HsxREe99YOV2UIWNqOCqDaQ8SuLHxmm1TamF/Xf3jQw59rycnK1XJG4bObtOdKpL75T+ifjClJD3GQ6HiEzWIzo/LOyD14jPkNeflS39apjBpGxZ+xx6+Gqoom9WQL0NpYsddwcrtLHAFEHbH1qCSA0Xf9dn+rzEf/UZmfCd1cPQ0F9mwsTd6SP3bfktexGeSIkkk0
*/