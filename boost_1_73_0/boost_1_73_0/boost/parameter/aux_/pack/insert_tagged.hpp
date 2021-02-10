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
0wmyQtsG4z647Cn0Qt2RU7BfrYg27eBNT8ykmB67IYmoTwADga3EiyHGwmFENmNA0XQAclRODo6F2CnthgIhwVWoWaIrosTdGZT3gX7P2mQk3dWd6V9sc+TAHeIVQmHwGTF6PBxxDDjsukqVz1SuRW87aYGaAwVDEz6MHH3KzPTAR4APwpvSrbgD3pJbYJtQh03IoVElb8Rc9ez84rQKymuugaIJnZL1i3QSXv2aRh+mLYaD639enF+e326uR1JW6ukRiUUqvf1Ma7LSiTOIv4aDSnDRtJzMfB0cdzykWCsTykB4HsWsKo7t8iWLf+PUjY392BtE/79BKgHq3Z/weV1rq11zXQN1c12rZ8MCHYOWw/OnIJYkZAHuDz6z7Ek8jIS0ie3WfroN7eqNfQO3Fs4XRSFoUytNbGhp+2mjilCG33/HbpsLKCUjeDRom4msXdfKra1whdpQaeKUEHcnnMN8H3cCDGEpSDuSI3aO/EpIpEjMRAC80Ej3zGW+bWD0hcYALM+PUwlXH7INyRRzlRRicIHIZinEiMSj5laq2Rq7BgWKNHHGcEkfikvbQ1dVu6prO13ta2Oi3jVqr/SaheJrBTet6Kbp53hFZJscJYmOpuTn0Wcf1cZt3/Uw7XHvMV6YKzanq/cXF1pm
*/