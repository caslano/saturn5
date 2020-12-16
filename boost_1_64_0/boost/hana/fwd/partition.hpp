/*!
@file
Forward declares `boost::hana::partition`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PARTITION_HPP
#define BOOST_HANA_FWD_PARTITION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>



BOOST_HANA_NAMESPACE_BEGIN
    //! Partition a sequence based on a `predicate`.
    //! @ingroup group-Sequence
    //!
    //! Specifically, returns an unspecified `Product` whose first element is
    //! a sequence of the elements satisfying the predicate, and whose second
    //! element is a sequence of the elements that do not satisfy the predicate.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Sequence `S(T)`, an `IntegralConstant` `Bool` holding a value
    //! of type `bool`, and a predicate \f$ T \to Bool \f$, `partition` has
    //! the following signature:
    //! \f[
    //!     \mathtt{partition} : S(T) \times (T \to Bool) \to S(T) \times S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence to be partitioned.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for each element `x` in the
    //! sequence, and returning whether `x` should be added to the sequence
    //! in the first component or in the second component of the resulting
    //! pair. In the current version of the library, `predicate` must return
    //! an `IntegralConstant` holding a value convertible to `bool`.
    //!
    //!
    //! Syntactic sugar (`partition.by`)
    //! --------------------------------
    //! `partition` can be called in an alternate way, which provides a nice
    //! syntax in some cases where the predicate is short:
    //! @code
    //!     partition.by(predicate, xs) == partition(xs, predicate)
    //!     partition.by(predicate) == partition(-, predicate)
    //! @endcode
    //!
    //! where `partition(-, predicate)` denotes the partial application of
    //! `partition` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/partition.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto partition = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct partition_impl : partition_impl<S, when<true>> { };

    struct partition_t : detail::nested_by<partition_t> {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr partition_t partition{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PARTITION_HPP

/* partition.hpp
m3q/Ra4kHtIUu632rzba7/TsIQz4fGh/mWr/FVTx306hvyVTJXXSwYc9tB+Z1aRTN5oHieNXUKLNcbTFPgQMaj7x0xuU30JKBXupaP1NUs4NBNHArWFuoE/cuMIYHA+nVdz//FfF9Dke/LvzPIDPyz0DlWMdoLvUASrkXvMGsbDMSJGGFO2BN8fDn15uyrrTDzafSg6rrqIGQvrFSUHlDQeFbwF8c7w9NdgXBcHbcu4pGG8XPdvFKWGZg6saWeWwisp8kDicLpGVqVzWojKOhrMAbB6+Pnzp+dxnD20cVfUdF+jcfOzLa+OrIA1tX/KozmhxdtRx/azJe6i3QIzRgY9n/UaZ/HpyXA4xKp1Z472YIyo6XC8TzoWKX1ha837sVdPa5AL444zyEZN3fyA2MRwFJGD8uG05TwdvelCtgOf4xP2XGbU5d7IK7SO6+pDX8OP7vZwix3lM7SxlMC8jQjszOSbvHpcYfJxXAtM9dZ0Xci3bm1Gl2nuClqdKYI8T7QlZyAXXGGSiwWfE5WZTMR6MiFVJpT5epYZxndqFZpXcED86dd7gKaZVt1xfP/kXB1tfP6c6fv019/6W6+tv3JJoj7n3l4nvn1clvg+5KfH9+hb5J7fI/1iL/AduTHwf2yJ/1q8S36e3yN+3Rfp9Lco7Nz69Wp+xYn2nt7YPRGGSwNNFrn9Vm+s7Xjak05788DCSwtiIc5VT3+SLzLTUWPKr6yr3Z28uD5/fwfZndV7c9dfH22fdtLJAd+eScjyUOGCA38u3dkfFpllx+xmDA5bueeZqSKi0sZuh954JAYS9eXjqHyjg2geqtPtk1V9hDdY04bphxRzPU8z0hsX7CUSwe+A82eKnaOxpLBVZF5KaTDte/4hGiNU/UxY+fXexTwyaZO64CZTKwlJUYWWysKaXkc8nRkTMvSF0EISXfd7EA0HzZBbaUsOePQweOT6sULBtgYrmu4W7VB12cnxgsiwrX5X1xRJZVhmAwARfNJnBcrWmyqRTVNKNRtKBXK2/XsN6E09UM2DN82GlUCSjVlgEWsMm1fl3y37qIlfHHUSn826m8EsRzhaJcAXvE9+AKLmAgkUiscXHzRVNXlR6OG+fISuORkgWv52LrBfYKa9F5JfwCy2RDLdL0X01r4HMuo+d0cYvViJuChLQMndjEh+/EEQRAfzz7CotZQ3pGW61m1e2gqSiFtDXL/bDEMML1h4/jc3F800reRkZ1hQnjFkhOYEdslrg9wauBNa7feJP4D0poNPEyltYqAZrGN2l4pNSeeKh3KQqzeR7r2ewnRVV/5Yfqc99rjMe7Wrfo3loheZAsBtT0MGzaUNspsXAH69hws2TUThmkSE22CfAr8+3E0MtTGZ7iHaJVEy4Gy8NIJBGtxnklSRmyj5CC53sZpmjwPPY1TSKEg8Qp1xCaX82kf5ewTMQ3sTFOXLNHKsoR2/kEK9dSmzNCme+xaR30/fy4P8M07snyy/GMjg38fAv2eUVZtzr5GFHfLbqH4KGFnpVhna+CWuKanjpQtnhJhqgMVv3I5/c3IWaP3grg+fspWb2FJW9l5H9eEQNRva06uW8s9vlJ4yI2ybRrNDzto4XUpXqrNb6vV/ob0ZsR6Q99lbum2lL6MbRxfBSiOI37dr3iCSTVDEX0o0i4iI1TVBnW/vlTtIMOgbJJ65jl1wXt5+KHu4Iz7DrFzDRccrKQgRoAQURDeoaA4cdaVfGsKuaNLxKujqORk6/2sOYiZImW7gknpTNNom2Jo6L7EbWo7jwSmd4hOkr6RfnT2cFzsXdEytbIQUCy43ca/k0AZF7obmGyJvOs82Snoor6farDX49XCeWf+OPtC/3XSY=
*/