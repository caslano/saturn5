//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP
#define BOOST_GIL_IMAGE_PROCESSING_DETAIL_MATH_HPP

#include <array>
#include <boost/gil/extension/numeric/kernel.hpp>

namespace boost { namespace gil { namespace detail {

static constexpr double pi = 3.14159265358979323846;

static constexpr std::array<float, 9> dx_sobel = {{-1, 0, 1, -2, 0, 2, -1, 0, 1}};
static constexpr std::array<float, 9> dx_scharr = {{-1, 0, 1, -1, 0, 1, -1, 0, 1}};
static constexpr std::array<float, 9> dy_sobel = {{1, 2, 1, 0, 0, 0, -1, -2, -1}};
static constexpr std::array<float, 9> dy_scharr = {{1, 1, 1, 0, 0, 0, -1, -1, -1}};

template <typename T, typename Allocator>
inline detail::kernel_2d<T, Allocator> get_identity_kernel()
{
    detail::kernel_2d<T, Allocator> kernel(1, 0, 0);
    kernel[0] = 1;
    return kernel;
}

}}} // namespace boost::gil::detail

#endif

/* math.hpp
oKaK+g2QEpfXM/rwNtubA26h9v7KcGUBeWUGNfVBTPvCy4mcb3MZGzbmv15KoaRABr44TMJbOiaQYcSZ4mUcGIwP+yO21zePhFNGcM9YJ+Eef5svCrWnmPjq6zyQif4As2UMp5Np49Zm1maj4A6XMvViJP8pK4N1nsFECcNEjcVaxowlrNUyswLhobZV1zbqGQcYoPfp4XA4WjjO7ooCL5SEfc7JNyAIcbq/GGzYEOF/B9weXGDksZy1pMvKPDcZ7opnKSVGxlUjXnZtiQYaE1wkre1LqBhMiBVGTf58TBbVBEeYzbknMyeNWHr95NT5I+U9nRkdzIP9ovZE2QJjjuzWOtdIKEQoKiI1Gm1jcjggBifLluzLB2YrUbio40mEEU/6Cp+CKvQgPOZ+QPQppiTlqOVrrbw3AdNtXiPTfeVJPfcVQ3iW7Ak7974uNfVEB9tSGvpQT+q8pSX8E+9KhqFghnbo4WnTcttp2SJqLvQ2u+wUTwwA10triLDSDRKG2kCabDafL612HDVXSaRlevRcYhpzqADKHTy0KelCm2IZWrkqJoHyMg4zcdtQ/kB3GyulxPzjmxgHcqJnJdKpe9e5ti3NSJ1SbQhT2lIiWY0ewtuSVcO3RkLsEILbkLtzQxMO5rTKMPtgm3BHuRTueM01xY+LPbk06THv565v1Wsf75Wfs6t/H69Zqrl0jYFLYUYaAmTyXC739T3O
*/