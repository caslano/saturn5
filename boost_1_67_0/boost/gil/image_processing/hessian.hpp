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
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
*/