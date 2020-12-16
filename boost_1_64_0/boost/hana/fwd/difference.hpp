/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
4u9USY//epTQLzRu1EL7TRy+H6HvI75m/bbw/ge4BGMxBk4zSYa/0wtqYsqnsT6nBs3rApoJAhrf+RRO7kSwiaES6BAKBJO8VWsrYqEPLRp0XBNEay35kSGN+OYppMFqGK7t8C2+H0Ruo13XOiRACl+effxuLrpMuXZh7LaZFN85rQujUd6vldFhULdHyXz+n+xdCXhU1RWeLclABmaQEAYJECVokAiBQRYTawhZABEnDJnBssS2lL6O2FKdYakhQidpMzxSqaWL1lZtbYvVVqstxj1hkIBaWVyKWwWp+sKIYrUBkTD9z7nvvVmSGBTtPvkm895dz7333HPPPffcc3jHGh0AI2zVus3dL5IquhfiuXsvZiMUTtj4UwH80xdVc4Qo7nPtI5FQjbhmmRDpE/g2vzChsHe+mP780ubSGQETssGFds3iz0CPPY4vqfg5abmOnxyfiJ8LQ13wc+NGFT9vvLJb/KT41PRK1bd6nC93aeXN7L48io+kpFeMPZbnj+mHMvpXeflL3R/O8Pka679clWjfKE9Y5Cd+idQKgWR8V34Gi1N5k+pmo0fKvWUMBqVgkdIFUv33gNHL2m8EqREt963T7Yja61cY6bTDQms+FaXs9LI4wkllGJW5LnFYhZMqwgby4Y2rhmIJAV6Or1aG44Wd/E0F5gTshD9uZfmDDvbvPcCtXDNXv6d6DnIrpnIx9e31J2iKGXQv+tDS3rSK+4RqOs7iZ8z75RZYCSrVLvb2988V7bm6fadqVzoWHKmqH/kzYGAH1QlTLdB0LGTtT8cINoL+UpUgFR20SR4V7FetvDSTQ2Qlag79Ccqgyu6JEOWqIzSP+Ef6VRzThWDfTKYOlO1jhW5XoES6jYbpRszFpsss4Ywqj+jdW0tVCALDPcoKbpFFKMbQthhXzDYxEc2PSMRNi9ZMk34t6M2fa1Rfp+cDWi7Po2yTTtJ9tYk8EmX66RFKmiVK+swm5if80C0AnhOumBKtU7kmGvE8QoAiQgCF1E8HEeqlMymUfqX1Ba7OyDDEaRHjn9fQAgrpUb58lRBQlrPu58uIJByFtQcPzjBtVW7l5P0qdYQxGbdOHe9TsSiRIEMSeG6hrkaqmiTPwzn0mcoahIfZJ9saD8rRUgW+ThsTpDh/3YfEzwVGKS0FlJJYRg/wLs2j3OBR6ecKm9I4ljFA+UmBiirj/OXKNzwanngFvVhVouEJ1pVhMxLwBH5tEzDjJYEZj0CmzBmhybmUEGLkBHWv8imfNvT+AV6m0Otv+5Po9V2p8UuT45E/Ts83rOlCz+9KjF+WEq/bf5O6s/82n+2/YbyWEK2cTQ4V8LLMiwdQTDwGSI0WiRf6OCimW4pbQhFg/ElqVhAOkF1OkM+LpLtuwDBMb3+eDKCqf4nauXOr3FqwUjqFQJ1C7ib90zmjRIpc7Tcx2XRerFFmJ1PmWUjBlPlamhY/mCmQRdVmrLQQHWKKPrlK0GBBkVvO5zeHSpFdXPSNZQkUeUOZoMhlU9FApsjwafmXP+gU+cBsjSI3Oqjm5YBLeNV/Q6PIJYIiexTTNTpF/qt66AqK7FE2Fccp8pVoB1Pk+/iWzjWzBZ19iW6NMJ29Rl+S8sGoXDlO8E0JNy+K8S3Dd7b6W4vvQmUUGxDOD2fQhSxlzmhVpFwm6O5ZbpWHbppjgZzylnLSFcgTW0WivT7l+NWcgj1taWb5nF8VNtAksukv4J4mvSlm2ILPC7fROLxie0WYxR7ll5dwd89HqTrZfUb6zzKk1iwx/7skcb4swVAup3myvJrNbTbyVSqSAxWAKW5apClHjZTatZ6SQrof5nRl7OXcWe1kFtkn5SBaWXmpfjQTzJX+pnc=
*/