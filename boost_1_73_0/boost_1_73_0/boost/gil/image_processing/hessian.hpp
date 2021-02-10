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
ucks7aEt0zSrG/yPfzK6uL9Rfz+FKauy8nRM5B7uSA/i8JVG6g9HiHlIScpXEj3w+IFlehGV/MMRiUOJCwpx4UFrY377JlUOKDQK4mpTBamb2tHzioYxxzLktnqcriLJEmX8hHTWRNInimyHiefw42BkjmWl0cSiKJvKdnRn+FSb7YqMpk5CS/OZwkqzqdeHivhUO/CKfIpDf6UYZflMYaX5VA9+qTqW54KrjlLKXk+0HXtXqc9NlD/xpE32WUJOG27ZYdHLWixB04g8Q74SL9PzG7MrlOxrqaNPmsBWRi8LXv4iFP2k1/3deN/qnLdPn9HCXPBmlu9qYl5b+vRZ8VsPMn3POuK8VmdLPSMXv+0u/nM49NeB5rYhr9bqS8NQb62kuLNGb0+Yw+2Cl3Tp25L2Wl/tmT0swM97SWa8tlg0wMcC783Axr/XJTVz3islGyRhsb0hAXVmTX/4KfsHn5DUfwNQSwMECgAAAAgALWdKUl//nirRBgAAoBUAABwACQBjdXJsLW1hc3Rlci9saWIvdmF1dGgvbnRsbS5oVVQFAAG2SCRgvVhtc5tGEP7uX7HjfGicKpKlxI7TyXRKZWwzkZErUFJ1MsOc4CSuBo5yh2118uO7eyBblrDlvDT4BQF3u8++PbvomZhl
*/