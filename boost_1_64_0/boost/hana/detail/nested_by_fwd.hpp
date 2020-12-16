/*!
@file
Forward declares `boost::hana::detail::nested_by`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP
#define BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Algorithm>
    struct nested_by_t {
        template <typename Predicate, typename Object>
        constexpr decltype(auto)
        operator()(Predicate&& predicate, Object&& object) const;

        template <typename Predicate>
        constexpr decltype(auto) operator()(Predicate&& predicate) const;
    };

    //! @ingroup group-details
    //! Provides a `.by` static constexpr function object.
    //!
    //! When creating a binary function object of type `Algorithm` whose
    //! signature is `Object x Predicate -> Return`, `nested_by<Algorithm>`
    //! can be used as a base class to `Algorithm`. Doing so will provide a
    //! static constexpr member called `by`, which has the two following
    //! signatures:
    //! @code
    //!     Predicate x Object -> Return
    //!     Predicate -> (Object -> Return)
    //! @endcode
    //!
    //! In other words, `nested_by` is a `curry`ed and `flip`ped version of
    //! `Algorithm`. Note that the function object `Algorithm` must be
    //! default-constructible, since the algorithm will be called as
    //! `Algorithm{}(arguments...)`.
    //!
    //! @note
    //! This function object is especially useful because it takes care of
    //! avoiding ODR violations caused by the nested static constexpr member.
    template <typename Algorithm>
    struct nested_by { static constexpr nested_by_t<Algorithm> by{}; };

    template <typename Algorithm>
    constexpr nested_by_t<Algorithm> nested_by<Algorithm>::by;
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_BY_FWD_HPP

/* nested_by_fwd.hpp
OuzTIM1Je5H/bypro1kj1ENgzGwdUqAlFm3tbE/NT7R1tru5h0FpHthe68L6T2r12iPVPRvy6zSwSNd76dEqvauXHqPSu+m1bhnQO7C6lA23b53FYjxPobLXoGyTHq3SKNv4hXbcSN4mXvV0N18yNTSQ6jZjbYYHW+OL+QyYu4oCzMSr3gm0ZSOw1WEqb2fLG+s6yD4Ksn/RJ3tmIGWXavSd2uRmNh53EeNxViU+YjzOpn5dX1lqTSB+WsFLWjuwmx3Po/DdG19zKv1jew8qf3f8V1Rzqfw9mT0oE3n2FvbgS5Tny5ouuC9vhO9N8dqXyb8vkz8qZGkgWeaR/I0kS5Ogu1KsiZqJbj7RzeRzvTvmo3l9fMPXIjnjkLbzdJzP0yP0uQfayxHO8UrmhUw3C5luFok6t5JuWkg3bVTndpb/WLZuS4j8Scp/HK3bOih/p6BrEf1hCdEtZX1opphTDhB5vkp5DmSyvcVkO4jN+ykxjg6uxEeMoy7i1125QV+XdHVZENd5r6hzWsi/jMpbzuTvZPJnmPyHCPlXVuIj5O8jfv2VGzwPdUO8wx06aPcyAszrkRX1yIl6rKJyB5neSp579ppCBYzGcaGU/NbXuzrdl81JVhbM5V9N/BIblAsPZYowlngu79oR1Ls3s5z5aQWM+Bw6onq7kSekeBbM630Y8TvHCTijs3bL2xsPuWNe1VSn17hpW2FHwdZZGpQFdaQsWuf5uovXNTNz6jc0HyOiE3QOVoE59vAR7oeWmbVKudmr2N8iQX7jA+Dr7nwB23THW3P3pnF4tQKi2DOhGravOgJy1Drwj6EdUMToI5m9nl7i92E28LsHwlALOFvbHsXs89HMBhwjbMC3KvERNuDbNBaPFWO2IM+QiO47mm5DPl3EaMcybGU+N9uVPQBuzpOIX3Pp80S+adMcgzDmfInp42Smj/VCH6dU4iP08T2q56lEu9r6nZs7UgNwG4Av0sAgvTyNuburz/sNQcD6e+m3HvGdXEQqXYa064Ki/GM1rfJeufhyj96FzYAPexz5sE+HLOqHQZjnWiWtv9rUp0DnQ7w+36f6nFlyrUfPKE1XoyTfq/+A6fSHYg9wBtLcz7CZWsewPc1ZwIecZUMDPTp9NtI1zop0Xw4+F9oD/IiNmVqXVolgBGJpSNRc1H9MzuFeKDFjLV4Qwtq8c0W/P0/MVeeT/i6oDPLXqE38+2zt1t+1FmnjR/qx8K+U8gkF3p8psuZXfuCfVGo/MHT3ntmXAqby9OexuMBDyYzZkxhcmcbZ0wuDu9GVHTg6reB7mwkKbk8sNPxitz0BN6cWoK+nc4ufsjpHnEwuBSrv2IKlUY85xff07kbaqMpA+Nx3idjDX4r0qoA9/GXUfj8n+kP4Hl7s18vYfv1y0FfQfl1TeT7ikOnb1teCcG40p4wBvlalaQ+K5Ohf8PlgRPVTfVH8Nh5kv4LqcqVZPxQfB+rikRgCFmZ1WCvWy1eLvn8NlffrUjZf18cLkGmKFODS/sNoY2MsmUw1xZKNiXi7+gEkwyYAY+X/LVsH/5bZp+vFmL6B6nUd7VFupHrdZPZlRf0i7W1tLa4YJmHtxu/FXIJ2F3fkRju3UDm3ltSf/t3eqFs1bLI7Yks73CID4FTv20vNmf4QkfFW9TutjXrODMQQzztFfe5CWtbnbqrPH6x+x4brHK13+32U932b0WhvGm/3urpvyQ4sbyZbrsfLfS68XZ3t5HHfwq4B79dwfWBCd9jGQIgHNtKfs43v7LbZju8H9brU+tYfGqG/5mYfv8W+M6mbXZvRjifbum7TXDvZqJ+dz/fOhm8DvMYHb+wa6En3NXb19XVjWQMdMFuSgKU=
*/