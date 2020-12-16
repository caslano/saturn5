/*!
@file
Forward declares `boost::hana::detail::nested_to`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_to_t {
        template <typename X>
        constexpr decltype(auto) operator()(X&& x) const;
    };

    //! @ingroup group-details
    //! Provides a `.to` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algo` whose signature
    //! is `Object x Object -> Return`, `nested_to<Algo>` can be used as a base
    //! class of `Algo`. Doing so will provide a static constexpr member called
    //! `to`, which has the following signature:
    //! @code
    //!     Object -> Object -> Return
    //! @endcode
    //!
    //! Note that the function object `Algo` must be default-constructible,
    //! since the algorithm will be called as `Algo{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_to { static constexpr nested_to_t<Algorithm> to{}; };

    template <typename Algorithm>
    constexpr nested_to_t<Algorithm> nested_to<Algorithm>::to;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_TO_FWD_HPP

/* nested_to_fwd.hpp
1EZC0GvyL0fceBOFxsG0e3OzA0YN9ba4CcC1dOUL0Z6edD7vYi0uQrglOEpMA8XW/Sh/QBWXxG7APWYx8FoP3pJd41j67SBfIo0Fzup07yzGZzqDzyb4Pih7Z6dH8bG/o7IvYLuN7on2uYdAhbRFoi7KVmyC9pjHxlf76NSSeOuu9dBna5O7NVui9Suh6uw0eO3nna3nvTP1c3wxIdfsr6Kheu9B1yzKDngxngCD7tc0da1rW7YknV7J4eUu3LHpCmfNguyQx2sT8MoMoB0dmwdttSaZxr3uXgbbXNH19WXyLiLv1NOardFva5L7J3HpyvYyli56T0Nd9J5dn0pGm2MNURvjUEDtvbZYxJu/miPsrEPMRQsi6iPOOsj27xcp+eY03yd+84NBrBwtTI5FTI5WIUdbBB8hRzvJ8ZVIqXgd3Znl8JYaGWwK5Ze+V2+XRO1svVQMaW1cR6TE/uRT+4SwL2Rz8xKrG+hC/N7H/ozugEjQb1Wp6i/LpPt686Z/d4KugsVvWxrRd5d70/quzleRrnF/X8eLj1ZLb0xMejsd68bip6t0vU6fCdlmqXRqECYGflXq8wdG+B3/Aq6Z9XabdrIp1L+uSByEOnccZnp5/IWDfOMoP1jIpXKD2YK+w6++Lst4XoziaLc9i6xpFsb2T8UWI5yAelXRlqBTZgkt+rY7tagNl0ECOBg451Hkjaqyik1tS1INnc3NMTi04gfEOKviaLdexeSKtXYGiWXBI+DR3NbYmQxgouGCy6HUrge7bbYwvc492ddt2+XCFmWH8mkNpb7a7cKXoHNm1zQMLVuWHsTURSQK36Pz4YDEg/W6sOZsz1BeA8m3PxZmPR0Z2X3/ab55xGXTgXWCy38ZeJRpmPXvL49wPxoWJu2dfo1wCPjPNOfxbo7OgYw6J2xcYWN351x4NN+TySiofdOZiaCwEcj/PZ8N6Iaym7JrBhw+7yXSOaw5GrNDqAaf9xZnBgsY+8jSCJnYXFZhccmergEX6eIOce3ykCun9Tti3aBi0gxmFaOkG0dxH7oLsJKP2Y0YX8HrAPgNTCZ8Nf212pzlRvTaS/UaYzdGQYYBJkPZZxxf5qxmSDFz693fD3dRvBc44wvJ8fI2cuxV+9symS64fdsxvAc5740ck/XF5/LCWms3bdKVJ9BGfUbbq+avIbFvXR3x71vX0Py/ls15Mfa9WeT/OuU/NKLzH0b5v2HXMf71eUsWaz5aSRt4GeBqAW0Rf/HeGR7B9F5RfJ9QZJ3SU+jLLjfaMQmri296dcF3FtdT1PEYquNRVMdvUR2/relKtW+2P2eKt2nrCz9OlHO8aIvvUDnfjWw45rFvp8hAvL4nRkr48j+F7/Bk0cYnRcybOS8+X4Wb1o4FBVsPmhCti2bQvYNTWBvX6Prwilh9tQh9nSr0dRrp63RBd6ig+z7RnWn9GLyPooeq+N7Qmdc/Ve90gfZu6g94vxxBbLT9NqIM9yzU5T/kePcBvzLU1avx9ZinyjCNnB1xx0RnSzQxP8ajDnUIWFEb1Nvt+r2NuilZMl5Q8TWlPksVOj3HrYeNTWjXx+cp2VE+H+vn++asni5WjEnYvtzAxm4DG7s/Fm1/EbX9hTR2f0JtfzGzaV9m3xeJ/JdQ/lMp/6WU/7KIP3bTafruR1c+vwZvH3ls1twgBn3BvNs1ftfLfXXNrUn1dHveNy/p1vc539yXh8LTq/3767zin/XvrQHr99YWlW4/BWygLzOw0rGwTRRsSK/3DWyCgi3XMFNuSMEGUTA7C40oGDsLrXLHL2Bd7sUSC6t1ZfHDpitYj4ZNg042hU5+yXQyC/gu+464UPx3skrv6/V5MesrQ6yvXMU=
*/