#ifndef BOOST_GIL_IMAGE_PROCESSING_HESSIAN_HPP
#define BOOST_GIL_IMAGE_PROCESSING_HESSIAN_HPP

#include <boost/gil/image_view.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <stdexcept>

namespace boost { namespace gil {

/// \brief Computes Hessian response
///
/// Computes Hessian response based on computed entries of Hessian matrix, e.g. second order
/// derivates in x and y, and derivatives in both x, y.
/// d stands for derivative, and x or y stand for derivative direction. For example,
/// ddxx means taking two derivatives (gradients) in horizontal direction.
/// Weights change perception of surroinding pixels.
/// Additional filtering is strongly advised.
template <typename GradientView, typename T, typename Allocator, typename OutputView>
inline void compute_hessian_responses(
    GradientView ddxx,
    GradientView dxdy,
    GradientView ddyy,
    const detail::kernel_2d<T, Allocator>& weights,
    OutputView dst)
{
    if (ddxx.dimensions() != ddyy.dimensions()
        || ddyy.dimensions() != dxdy.dimensions()
        || dxdy.dimensions() != dst.dimensions()
        || weights.center_x() != weights.center_y())
    {
        throw std::invalid_argument("dimensions of views are not the same"
            " or weights don't have equal width and height"
            " or weights' dimensions are not odd");
    }
    // Use pixel type of output, as values will be written to output
    using pixel_t = typename std::remove_reference<decltype(std::declval<OutputView>()(0, 0))>::type;

    using channel_t = typename std::remove_reference
        <
            decltype(std::declval<pixel_t>().at(std::integral_constant<int, 0>{}))
        >::type;


    auto center = weights.center_y();
    for (auto y = center; y < dst.height() - center; ++y)
    {
        for (auto x = center; x < dst.width() - center; ++x)
        {
            auto ddxx_i = channel_t();
            auto ddyy_i = channel_t();
            auto dxdy_i = channel_t();
            for (typename OutputView::coord_t w_y = 0; w_y < weights.size(); ++w_y)
            {
                for (typename OutputView::coord_t w_x = 0; w_x < weights.size(); ++w_x)
                {
                    ddxx_i += ddxx(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                    ddyy_i += ddyy(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                    dxdy_i += dxdy(x + w_x - center, y + w_y - center)
                        .at(std::integral_constant<int, 0>{}) * weights.at(w_x, w_y);
                }
            }
            auto determinant = ddxx_i * ddyy_i - dxdy_i * dxdy_i;
            dst(x, y).at(std::integral_constant<int, 0>{}) = determinant;
        }
    }
}

}} // namespace boost::gil

#endif

/* hessian.hpp
G8MWETuFhof98JbMScD1LdxqTlF8w7F6naMdIeMH3I7L3CZ1OmDQzwkDks/HDeh7JmHAK7/FDUg21vkluaSF5w007oXseH9K1WPKjQnjKJD6sPHtP1Pf6oEVbfJ91A5tDwvuc8hTNOwYRqjeQRmt2ZDrQz5O4KT3mT3Z1n1XcisIFCg+ZOxRfMODLL1PgwxA36PuHdikUOPNCgHJOBAeZGjgXbCtgUu8EvfpQRKX/c3GDkt2kmB+H0M6PDRLSNVlJ9U168CNcbzyuDZJuZaFiFdoLBPkloQJgoEeE2mCst68n8vhwchFPKjywd+j7SrFOFOk8Qzi+fdLUgYPsQxWT9R3pDlica5DXmSahpu1dBI5SDvWWl9LKVdBQJOKEM7fIbn5ET21aCoiLMzBy2Z7Si6ORrPmeJYOog4zDj378+hkj0x61Mnf+X2qRXuCL/TypNXp8sE7AgYfV/CRQAUQKb/F5WJ+k1MoEjsEfuwbr4AkagcWG/vEgDsp2NhSFB65EfrGed9gBBlutcDGKBMEGYsgkNWXKsJ8M95LV01pPiLw873a4RvCABvGW/d6QlObPBzE7PWk+S1FlDSFkuxebYULZebCOJJ5wokB4yHE3wvWb1P8oveYjylE5K5JwWYWPLyIMIZbBPn3UaQcRFw5tON19JgNjVjUjsETRylIzkX6k7LbY6swNgtuGtyM9EJM5c/5c2wZuG2eGGQ7sqampNIOe7/rx2jYqcS9rjWQ8Jq7BtiLfZzGxCbjzAy3TuLVGCgSIrTT9I+eMsmnqf1CAj7yXjrP26/f7XRtU4rNL6YGDyKMvGeDZ5fQdQWSCGj2efMjNkRs9QpdIaM/VLOP2LuA0vbEtKekzj0ISx0TM/T3HXlOxuJVmg0GbRwxzf6Xzpuh3lxOkagOwc8Wc05aR48cTQ4pfREe/ca6aMcZOc7EWyF3lrFRSgtA7TE0xW9Zaubfo6YyBJgXJD9zOIJz/KfJGMZkvIwAzjNBYn5tjk3TUj8BorvUC83jqaVLHdW+R5P/JHTwMTSlFKSL2QCKFHGJYDM12PTckgUc9IFVwD9IAZeJnvJks+S9JRUOYlCid0/T31Z8dpfvaSnf5k7J2CZoNzPHS0yX4Hf+k+s819I1czfHF29SvSZq5jzjtxLt4dx4Lbxi7etcyVo/AglKZqTr7/sa7eu5Wh8B40vXx+ukaLUy5ahVqV3nRV/yZQMIb+2GxQqUy6kpQrGbSP+rDM+vkxEUk8PvILP54bhSlcM46kgc+zj+hUz7vb6PgYOV0JXL9cRXj6LxqtxvASHhz7D4LUtoOz5OLRufDuT9xOx/VR56mxMPSwPZN4Az3sr2/ePklk5Ptr8lMQtETdUMiO31fdAmiO6VGJ4fpCsVbO6Sid5bpqhkcC/yvVlsO07e+qCMTQgVHfRlmcGRfvdjjyEoY6UQNnQEvKW3EN4hYSOUyN7eUk1heYT3XHBy3iJeTy5tk1QASol4c0Hg8aeMaGp1lIn0W7aUkbTQZHT0RTrmCiUUlNLvL7cazIip2hBHJxdviIelf44N5rmkvdpvHbCX7rf6J/9NB9gaRLTNgFC2VHsoPn5D8uU9iBc9gdV+xcdvsl0vkspPhGjZFonZXcraa0A0SkV7quiVXyDa3U50BV7SQPykElEdsbvfB+/Jv6L5lkreTrApljJFf+fgOd2FAcoD5e8ti+te3JGcYtki24uXxU59idbu0nLY9WrpcnjWrt+n7DFyUdgSzzdp8Gz5QCKNA7FzyRiGQcRFL1U4clQJF6H4jcDl5AE6JLEbP7uMM7rIRS7lVM4UvCrECA+RbeA0iLqSgOGOpgsRcsmK0ciNSZPkBIFX6mtafJY=
*/