
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
jC3FAhpIktWqswxGlMlJV31NFBd4aIPMep4gNj7TFYIxdPmHvatf3rMhwNEscFtNPQIWzt4+H+nTWzyPayedeEMPVR7oN9sXmYPIfO+Zby1wjI5OCrWxVK8motBIc3QNd78t68gzXhKYHPaQuVl1BIt9mNUux4HN7Y/dFmy1S6nmcGeSsYnCH7cOCMjE9P7lMboWxd9vPrKSTMFMRFQNGi1tjT0l29TdsLb1lYN3C8LZZIKFhX1ZXZALdIMJ6wHZdx4nnCHdid0nbZaONpGiEBg0R6V9P46UtvNVqxKdlDpdt4P+gfmNPhRB1sxk8kixnnvTYyKVJTR6lCeM6jEXf+aDMo7d2/BFugjlJ8M/HVXEP+hA4YXv0IScw6ycAp53VYvn6oQHmkcNXZa0kv9J/mT7aDd9z8+CKl3+Pz0qhsq0oyEVCqfq8ZqFrsid6WwvbOtLP35wXC6G0TTm+gVhu+hPC08SjRi/CJ6e+xDYMpLIFJ0lXorWMF3E2tl1BXjV3CqOTnG0KAu9OxbNhnDtzqu2ED4eV6GBCbo6L1GBumNNdPxgBoeAIus3pw==
*/