// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP
#define BOOST_PARAMETER_AUX_PACK_INSERT_TAGGED_HPP

#include <boost/parameter/aux_/set.hpp>

namespace boost { namespace parameter { namespace aux {

    // Inserts Tagged::key_type into the UserArgs set.
    // Extra indirection to lazily evaluate Tagged::key_type.
    template <typename UsedArgs, typename Tagged>
    struct insert_tagged
      : ::boost::parameter::aux::insert_<UsedArgs,typename Tagged::key_type>
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* insert_tagged.hpp
WCzsI8bYSeBuF7g/CtyDRR0yhit5VuuQ8XZt6WfRbodPuwtSk7f7RbT7VbTrJuqldFJkJNvwuj1taJdo87s1HltHuzLt+m+/Zfrr5a8sJ46fLv7JIktOko4qU8q24d/7wHUXXMqZ09epTbZd+/F7hQdW29/JS1tKceHKMfnhtnfhStn74XbMtmvyqTy45b2vC69vErz9s/k9r7Nn109LzbZrAM3Osq+XK9d/95LX3PdkrSPDpGTX/+yWbeuc1zM=
*/