/*!
@file
Forward declares `boost::hana::sum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SUM_HPP
#define BOOST_HANA_FWD_SUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Compute the sum of the numbers of a structure.
    //! @ingroup group-Foldable
    //!
    //! More generally, `sum` will take any foldable structure containing
    //! objects forming a Monoid and reduce them using the Monoid's binary
    //! operation. The initial state for folding is the identity of the
    //! Monoid. It is sometimes necessary to specify the Monoid to use;
    //! this is possible by using `sum<M>`. If no Monoid is specified,
    //! the structure will use the Monoid formed by the elements it contains
    //! (if it knows it), or `integral_constant_tag<int>` otherwise. Hence,
    //! @code
    //!     sum<M>(xs) = fold_left(xs, zero<M or inferred Monoid>(), plus)
    //!     sum<> = sum<integral_constant_tag<int>>
    //! @endcode
    //!
    //! For numbers, this will just compute the sum of the numbers in the
    //! `xs` structure.
    //!
    //!
    //! @note
    //! The elements of the structure are not actually required to be in the
    //! same Monoid, but it must be possible to perform `plus` on any two
    //! adjacent elements of the structure, which requires each pair of
    //! adjacent element to at least have a common Monoid embedding. The
    //! meaning of "adjacent" as used here is that two elements of the
    //! structure `x` and `y` are adjacent if and only if they are adjacent
    //! in the linearization of that structure, as documented by the Iterable
    //! concept.
    //!
    //!
    //! Why must we sometimes specify the `Monoid` by using `sum<M>`?
    //! -------------------------------------------------------------
    //! This is because sequence tags like `tuple_tag` are not parameterized
    //! (by design). Hence, we do not know what kind of objects are in the
    //! sequence, so we can't know a `0` value of which type should be
    //! returned when the sequence is empty. Therefore, the type of the
    //! `0` to return in the empty case must be specified explicitly. Other
    //! foldable structures like `hana::range`s will ignore the suggested
    //! Monoid because they know the tag of the objects they contain. This
    //! inconsistent behavior is a limitation of the current design with
    //! non-parameterized tags, but we have no good solution for now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/sum.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto sum = see documentation;
#else
    template <typename T, typename = void>
    struct sum_impl : sum_impl<T, when<true>> { };

    template <typename M>
    struct sum_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    template <typename M = integral_constant_tag<int>>
    constexpr sum_t<M> sum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SUM_HPP

/* sum.hpp
xk40hxiGEJWHZ6KgeAsSV37fx4TswRlx9t2WpMq8/zUqh+eYNBmSx+sF2EnJmzxebC/rjDqLYknI6COtahYNv5SSOF8eMbAG797FNUgmjGjLj26NaZV7NuqPNn1OLglbosgLiB28hWFF2xuQsiqlkwerGOLQjXqM39Y0gwap9mRLr+UKJ96U0oaOx0TS0mVpWWWB35W7WvZ9EPnigqHjUpuKW/b9M3LagjLTuBJTU17LvgOREQvKUseVpEKfeF88Yl1QZh5XYm4aRVngL1v9iVeP51laEyHaBnKpqnkd/NOr/fwOFpB6F/6GWdb6JHNSrRe+ymWnO0Of7mCW/I4ltHy10yG+gjY7OLOVhEvyC2F8DrwvegnHU2FCGK8D8WUD8TcNjn/mADxoGYQfOhDP+av7m9knDL6/yfkbeNvBeM7fuP95/GA852/gnzoIDw7qMX3XmQr5prg0XT8jK+Ohh78gC51YNjH4r048wEKArCDfvrqlr1+dWHWKdgngRheWcCnFm3oMDR//ysqM0WACehL3r8gjIIIYx6FGG9+/mmg53P0rpd+UrRXRBVCSOR/yT2oGT+mcR4r0GOJ1EFrP38BC64JdVB91Yi4OCPmmynYzfegvnGKUnAZiXlDM2MRS6aOfe6nfys28/kPEl7D3TyYutVbvS7rZ/920XJPx9tyd8P1AfxyHdtXwrIeXBeXGRR3lNRleNnjFdpn1AA5AURwvRWEJHF5uTFAV+nWObP1byoxS3AmJa9wdGdIS9zRNInmlGPcWzbOIVbgyBWEKWpke+wT5bek4r2V7B7B5mOoLkRUJ/8d3X+kOV4XqezDbXR6+HrPdI2/q24nekqGIXN4daG/1LqXygecrJW1fm7gYvUrdKRo6lCZZWoEFrhu4SG/83SGoBfG0mV4TeCnGTL5HE9ViPdzVRIDo0l2V4hHdlS/u110NYqnh+rWBXRyTO2gvKsbBRgyQiYa0oHp+LyYpyEQ+2GUwSdOBXESNDZMKsLzNje+1L+5kuXwc6enhCoewMC0npWk0SkmsVV1AZG01DHa4gadb3whBOL0mqEYW0lfsKslg3+W672b2fRG+7eVS7jjLZdhXn9tqIYepaQjOw695G+rTYeLGGwOcAGedJjXF2SIIpE8cBNj1evKLZagdNiPUdQiV+wTW8Fp0gysCWvcZpyCja4ZUtPRsL9Je8K2/5BIjf7uj1Dbd7lhoWw3gEvuuHvuwSnjAN0K+zyX5RlpinvFrm58ev+76kUb8Ba0cMwepFI9f17ybBuPcSm9obnsp/qksvNQE2l56x2iEbfpBezUFDH+Zl79XzbosdE6GvfVbYPR7H0Io0tckc0rVYuLrRvTbgICnuVp8JeGpmVnkmbfyaQzI3D0YKUXtX4vv3aFtifWlYeo7KSjbWpgSceo4IT6zvZzHvDV3D3pQGw7FqJnQRlh9Sw/RPnFKHd0wnFz50zOMyj+Qin5OhYf3a28b+b0B73bLP7nK7+kK1NaK7+w0kGuB1Pj2WkB4nja8H4B32fh37T9iS8vo1rQ2VwRw5PS46oytP0YYmiNrgmLou4bvNfCNE9MVFOufMtL7rvT11IrvP2IErZKeLpZWT8ZkHHvaOFz5MnDi0u1yTwGh9espxu2/k4ACA8Ws3LqEd4rKWNRJcT4q8nQOFTYZLe4Vb5tUi3vt85+Sz6QWlVHDzTuQ4iA9M798krOw9/wP6OJoODUoJrxmlISuMIpntknCXPQnJiaIuM4kTQlXU16EpEv4bz5lFOtbwOs3VK94zqgIP3z5/gP3ycfeNzLLNsnbj8wj1coVh6amrcYpQrrJsP/DxUuRayUWrAkii6ikY1a0bemTRqIvpMg=
*/