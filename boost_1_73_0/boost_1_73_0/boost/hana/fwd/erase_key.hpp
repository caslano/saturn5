/*!
@file
Forward declares `boost::hana::erase_key`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ERASE_KEY_HPP
#define BOOST_HANA_FWD_ERASE_KEY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename T, typename = void>
    struct erase_key_impl : erase_key_impl<T, when<true>> { };
    //! @endcond

    struct erase_key_t {
        template <typename Set, typename ...Args>
        constexpr decltype(auto) operator()(Set&& set, Args&& ...args) const;
    };

    constexpr erase_key_t erase_key{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ERASE_KEY_HPP

/* erase_key.hpp
CATzyUm7dwb+Rb3M7S2vFeLxaWwW7RJX8xud395UHwu6Ult/qlVD3Lh+kp75T4+AcOqM67/1ifCAp7SN3r0nVS48hckeZyxqU+NsL/wZziHarDdVXw3ieBXpje5sTCTjy5c7exBn6dW4cfGEm3RhOog1aDKJ5+oAZcQ7rUTS+KscH7jzS2Be2RTthAuIliFqVCoasQ7UZGWPGpRxuwfXDC1wcxgbJdEdkgWxAQT0jPAqFDxuxcMTUDC4inZpFsc1pokmbYWnnfn+Eg3H6IJJHLp95BInpOqScBrklCqkZ+qMGOFDm19+IlOs+mHCl2mIwVIGaKVLyJnu0KzYk6Wj3ToXhpVdKW5UeRXzKaubMEIlgfsmvqrPUltweP0SHfJGEpD3o/HZLZEUFQeIL1/StPLT4roXoogsLS7s5nySKN/e8D0rjyuWJaeU5NixIkqCxUB8202ALAAEikQAcoFSJSNXX+bT1OiCGF4FIVa638zwNiGb+bEmLcHT8n6AAnaFFxwZe/N6pieRlJUBqXbv0pinPLpLF8LcL3yQW47ChOyLW3MvxT2eMoyU24xmaO/beOCr2z5GhmBg2Vpt7MIRl8Db0jwDunOZz2vmkQ0U3g974+634YCstxkOfMuIFmJBXiMIIQpyCAIX+RPJ
*/