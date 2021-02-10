/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
32DPHe50aPosYsKKOhof8YM6pphyDwQ/IOA1AscSyWAya3haZ5fVvKBxQxbSuyXFtC8R8Dg6z556zzAhEkouwWRKlR8AViP3IKvUsAmpw79TY4oevOPNe67ues2+k6pFKaGNuWjDU1PSPb6hk4ilvFsPzeKqH5VBHjyYEYNlkm3j5AS06kfjynowlDwZowAGrE5jSqtrbmmaSh+FpqlEzDJvbqjO8LOajRvUGkzfrNKYh1THxwAM/WRlHNvMBl3HVrEq+f4Qnbf5Zq1Sjvh5oLisEhhdZGqFhhQZ8r295rHFd/ntmx4LFeHLm2r4ggyVT1OwEtZPrIl6PbCr6AgjPzjhvbq3SZUpfgvrI+B2o8u/AQowNfDkU40fW7CK9bPnSy5rRkE1EdC92qrLnz5ZnT/tBVFC37GupZFtHiAK9k2cGZ2BBmiVcj4iFAzu7Cz08dhI68ROMI54doedlMkzpW/y2H/M2rkFhHVOIeKNZkwpgGWgMYQv1KVJ4sT3KM7LaJkFKI+YcscheLZs43FGgkf5pD9TWmTww9yvYqjPD+A1EISDIKbjzjFSAwOH4EQ1SwkkhOr7eajusVqPVB5b87GsCCPKpgFFKKUBXcQyjMjJ0OLTspKWWZSFXoc4BE8qAlqZhS6W6T1CK2bg
*/