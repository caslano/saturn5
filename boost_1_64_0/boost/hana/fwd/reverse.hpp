/*!
@file
Forward declares `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REVERSE_HPP
#define BOOST_HANA_FWD_REVERSE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Reverse a sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `reverse(xs)` is a new sequence containing the same
    //! elements as `xs`, except in reverse order.
    //!
    //!
    //! @param xs
    //! The sequence to reverse.
    //!
    //!
    //! Example
    //! -------
    //! @include example/reverse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto reverse = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct reverse_impl : reverse_impl<S, when<true>> { };

    struct reverse_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr reverse_t reverse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REVERSE_HPP

/* reverse.hpp
8BlcMASqJ4L6O1P/OnBML+KJWC0c3xE7jc8QQW8b+Emopc6DbhFx4qCelilaH7nRfIY+kq71Ee+Z+siQVTh2ZBPR8Q4kykRfwVd55iNExhUgY0f9WfUV6pZn0V8obybvIx3kbTBJ8u7Ldv6b1d0tr70rAqcXouCZOv2CXCVDrFG6ntvN3Ds7SL4MJC9pPR1Ejm4CIsfH/vNJ5F4msnQmcvg0Ih/YjcjTdSLX0+tErvt1Itf9OpHrfiZy+ECi/Xsg8vRORO59F0TeXyPygacl8oHdiby/TuQqyEEndI9SiIH0LRpIieQbZiZiCIy02xb78J7wNmSBEmfwmEmp8eZKvtm1t6j19MNqyPyWqnWnf7zDzH1+B53167SMAnnxQipaqS+hiN6ITHzWaKWNJIV+cNcQCj7d3M43Wv4hYnX9Gu5HcN+G+xrcarhauKVw7lqrywFngXsH/na4f8G1wB2Aa/08nnAvwD0H9ye438P9Cu7HcLdjOvk43Gy4Mjg/nA8uD25M7AMe/YOfvh45Eu8i3+lYj7yurUd2d1+PZGnrkRxmyL/VnSHXuu9kY49MuKtHJtwlZXVJVjxDfKuuXT/QmYrsBSueXInknGIlktNpJTJOMuHZXVciL3WsRLKoovpKhCv89QtT4Z/XnmuFz7D2yNHXHlyRLguw7PfV2mNtPtFj1dOd1hs8/Zej0tNiRIHxByMHbeZ1mFD5hq4CG2m35jxYgVCwJ9m0JCkPNmSZ1Pb4cfPKVyS7MzPyXFvxTSSnibRPcn5hWQo1X1pDGS1FaLlx6uUIN9/JKxF9FbKAuI55sEM3gcva6vxcqwU2YcxSNUP+WU7aN7LwvFVfv0oJHS2PRm1twH/kHvID7hzx689h5VGUoDMXjkM4uElfefzlfuKmgomZzCYV48lsknyza2/0mImAAx1JNupJtDeQXBGtPLzInlYeb5BkUF95vINCTjMPnmZRQmtB8xuSNWtS97Rky5UHfHEwah+Gj/QxKCsPzxzUNB9VLgRTVwKrgstZSTENzGM8bO/gjICDFjKCQMNivc4rwfL0iWAD0vN2HFKf27E/dRsHR8ELUNQNFDWxe9REippEUTfIKI5I3YaoGygqn6ImdY+aRFEFFJXfPSqfom6kqILuUQUUNZmibuwedSNFFVLUZBnFoZNVomtgg6TkREK0swoEFNlHPPsPNGp6yNSZmlySmpiqIBBf0UFPTElLiaaoC9BYskB8dAWPJXm4LwDbKHZo5n/mrSQVjiRszi+QJSciE96n0h/Q5M9SAG3U5c9GJrDW0SxmJjFptwh3MkL6LfTKYcy2e85Cpk08GEFE1QNskAgD5jmR9owaJ5vc7KWIlhwiqnbw+0jqUnerx5iwuhBVOYiq8P+eqJZqRAWMAjsuWsNQry9Hr38DfT9T7+95D5yzpAG0an6DKHXlcWaHcxHiOjU7jHBwxCexwzSca6eH/4pVu/lNa65bY3WNgrsC7lK4AXB2uBP3WV1vwq3G++fhlsHdDbcI7na4j8PNhtv0JavrabhH4X4O960v4Ru4Grhb4Jbdj+/g7oC79X58Bzcbrgxu6v0f8MP/Db8AG6TJqwXVxRZ1g/qhuLAo64Y58VO2xfdblKNMtMoG5+ONylGMOso2dQNOz0QaBT9KY5Jp7MqGYQmoZimVHame3d6ibF55oAI/6IPWxWwNlj7KhmCs2CIuvbc9wUMt9vz2xTsDkBUURrwDDLpG6kPqhu0ChdDnyjZzYw9l9AxJV2jVZxHeYiFAqEroTgcsyrMETWym5dzOyDuzfvfIo931ER7ejI4VwMdMrORtWGJUXyCOoZP+b7fOMO0+Sb27UdP3eYlzIpmhrvNL264=
*/