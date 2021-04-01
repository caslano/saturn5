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
d0DPGIfIx9wxxCOR3azYT2IjR4AsME8rKG0I8ZNR7jlutahqk0MZ9iFEciDKDzh149S7LBd6NSx1XisMhlnJ+76BldDar8jeX32TwsUhcG2V7rpLYnnztM2K91QklQViQgJOBwi1bSsrUUv8keLKjcrPmmLFHUvPRD6ROh4bfKk7ZtJDmriZN4xdTEja3YDmLWkofKka6v9M8Oklo5QpSAflCaA5w6LtyuwTg7JAjHDL17Syzzj9EiqSGfce/x9FJaSqbRpDT/AX/sngKgEO0ARCMWtMB3lf1B+VZEYs5APH722Jj0Ho7C13d9SHA++eLN2m+Y4gJIXiYVgUo4dvuQmNcOhaouTPg2PP/vrj8kJ05REYHXDITFybNO/TwTM53PS+6FqmlmxZIlitzOZ3ki8iId5JMAfk1PotouH6y8GGOC0MEef2pWhscXx8wdt4aPZJt2MXbCQZ1y9oX2de/V7GwLi7+WlGgabKxa7cigq10crL+rKAdMuSTSYVUlOswejVydZLEz3PKwgUIc5xdPipMaF5bZC/XlWuGXJlwoBRb2nyXrkX8GVQvQ==
*/