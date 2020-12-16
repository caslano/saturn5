/*!
@file
Forward declares `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_HPP
#define BOOST_HANA_FWD_LESS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_impl : less_impl<T, U, when<true>> { };

    struct less_t : detail::nested_than<less_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_t less{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_HPP

/* less.hpp
NmPvupRuxqqpS+X4saW9+qTq7yBP1bpSs3WdL6vWpXzsU3AcITSz32uuSLXXfC21tuacVFZN0QEJ739Z0RLdzDMii5gEuHxNRgYfY379o3+03WYX+XCP38D3zJCf+xobk64LiwfhYjPUHBpbLzTcFDSDQ4oQAjjPrLlHuq9HlDiT+39r+3/vf9+AJiZq/onO+iFsHzGwVVtsw68EoLp3koc6H0drcEZssidLt9Mo6RM0XBLXOoHlUHI2OHhLF9X3Phuqg3lfjTrKJCc3mdr+fL6jxZzwy9TIPgtTNfN+EJMZ4VMQZ8sT/INsYb1BM22ZVtiP8pIZxg/JA/WH65EL24PnPk4mZDAKJ/0v9l4h2bRC+cVZgaeQGAPaS58IvlcZmp2M5vIBuO5tJ6RjrVDV2DmM9kH9Dgp7lc0d73zMxEbH1tjD8n6pom3ubEEwjONMq9ZaL4Q61ke2b0vnHbxBDJnHl2XXGrMDR/i2MP87CSK8F0xo9B0SEnGTaBbB/HE2611dfapE/id2YxTt0ZG4Pah2EBzivZwt8m57AkORGir6i9w+3/0etxvWoJRxdEhrGQ86+/Po381yu7BctcJS1nWwRy444K+wKuqehM9xmRqSwW5L74G1oqO0hLNOHl+vsWCvHzHjpEPzEN3VGqk67vs2pDQCcflevnmtP+7BbE8NQ72deA5iGM6FIh4gsXr+2qJy4x3tyOdxCHjztS9nhd2lzSGy9S97jWeUVZlan2hhWdv74Ab1BS7Z+ai1jc1P0772l2qM+A66zSgJkZlHdqmIK6j/sZspo0v+RPJfcQv0J//R+iXDpeqNtDMYlwK5kmsgIj7QgONw+Ka6xUxX45L3mBaGtSdWt1rwCdU3qvX+2kvGeu+T82Hwj0ufwGiolVYbXTWdPFy4ff9wrt9MvoMNrntr+wvbeE/UictTBoLm9lceyFGBA/yP3yeVfC63FclpxoNlKK1+2WY2wSsnvGVKf5Qb51dsVvNqrkDbBpptq8K8xxVEHuYseixn2XmwG/ZAXnStH3N42qTG3Ytwy2CtZ+6s1gouULRywlD8srRYGXvVAR6yBIV5/RXOhvOxMX5oKJ/WMaVPN1OS4bg15ngx3ZnYnjXj83LN42iD3DlMcTdU12yBDPQKJ/aicW8jlWJcI+Fb5X7EEZ9lxxZ2GrTAK6eSFk5kk49+Vxaurv2GA3V7UUynCz6GiWwwYrEFvbZ4SW9tv8mNqxbtwmWbsUVYatlGfnPmzjLqz8TsGrZJxaoGvOof7KK8hjCfi/5kYrDNdtC0VbfDLdRgsp7U8d75E8Tqu58Lc9pK6PKJPMSasm8ly44d2LlkJfY5/G/V95+LtLS9m43ReKthCGluA3HtJLpG5JqxTLYdW7FL/iwL/KbFZ6XFvsb0Qkes1ZFIZwmPWLd4u8O04OqdILx/TGx3bHpjyRD0cXvVrLli5VFv5kz6KgaBgfCIciczEHIj0xunYcvfWq6pm38Om96FgzbMmihTMChwaMUkPug3/gKt4XWRBf3P/vZrdveDXZ/X7fJL6sTM4bmUzP1jU7mOI6w6nqHquLvck1WLi6rKvDRWUEzNxeKCUFmFgiLMAipKmmsrLCes42WHwj4Sf8EwGmmMtimWVlS6/NNcUQ/cU6ya676ZjmETmUwGfVsaV0VgPOK+BbaHjauAKNw3N8M9LIXGvSF6sG3h+ob+VbNE89xk3WnxGTA5WJAnxon+RT1xuCvV3GKMv2X+sCsHxTo12q+/WTWLOrQK6B/dSqwtnpg3c8l+FXjKfUvTxxjkg+wt3aBApIinSZjLfAyqLYKab3U4/s104s0RU0euhR4gD/vxoDamkk315rkvWxmZ574=
*/