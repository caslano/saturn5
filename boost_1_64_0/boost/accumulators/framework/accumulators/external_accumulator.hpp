///////////////////////////////////////////////////////////////////////////////
// external_accumulator.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_EXTERNAL_ACCUMULATOR_HPP_EAN_01_12_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_EXTERNAL_ACCUMULATOR_HPP_EAN_01_12_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/parameter/keyword.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp> // for feature_tag
#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/accumulators/reference_accumulator.hpp>

namespace boost { namespace accumulators { namespace impl
{

    //////////////////////////////////////////////////////////////////////////
    // external_impl
    /// INTERNAL ONLY
    ///
    template<typename Accumulator, typename Tag>
    struct external_impl
      : accumulator_base
    {
        typedef typename Accumulator::result_type result_type;
        typedef typename detail::feature_tag<Accumulator>::type feature_tag;

        external_impl(dont_care) {}

        template<typename Args>
        result_type result(Args const &args) const
        {
            return this->extract_(args, args[parameter::keyword<Tag>::instance | 0]);
        }

    private:

        template<typename Args>
        static result_type extract_(Args const &args, int)
        {
            // No named parameter passed to the extractor. Maybe the external
            // feature is held by reference<>.
            extractor<feature_tag> extract;
            return extract(accumulators::reference_tag<Tag>(args));
        }

        template<typename Args, typename AccumulatorSet>
        static result_type extract_(Args const &, AccumulatorSet const &acc)
        {
            // OK, a named parameter for this external feature was passed to the
            // extractor, so use that.
            extractor<feature_tag> extract;
            return extract(acc);
        }
    };

} // namespace impl

namespace tag
{
    //////////////////////////////////////////////////////////////////////////
    // external
    template<typename Feature, typename Tag, typename AccumulatorSet>
    struct external
      : depends_on<reference<AccumulatorSet, Tag> >
    {
        typedef
            accumulators::impl::external_impl<
                detail::to_accumulator<Feature, mpl::_1, mpl::_2>
              , Tag
            >
        impl;
    };

    template<typename Feature, typename Tag>
    struct external<Feature, Tag, void>
      : depends_on<>
    {
        typedef
            accumulators::impl::external_impl<
                detail::to_accumulator<Feature, mpl::_1, mpl::_2>
              , Tag
            >
        impl;
    };
}

// for the purposes of feature-based dependency resolution,
// external_accumulator<Feature, Tag> provides the same feature as Feature
template<typename Feature, typename Tag, typename AccumulatorSet>
struct feature_of<tag::external<Feature, Tag, AccumulatorSet> >
  : feature_of<Feature>
{
};

// Note: Usually, the extractor is pulled into the accumulators namespace with
// a using directive, not the tag. But the external<> feature doesn't have an
// extractor, so we can put the external tag in the accumulators namespace
// without fear of a name conflict.
using tag::external;

}} // namespace boost::accumulators

#endif

/* external_accumulator.hpp
pYIJsxJjXvYzhgCLvmpu/FoCT/T3aQk80X7mfp4BttrSu3VdcqWSfharJbbjIoX5qbBG+5h3TbCNoa6QN0EMpphEKUuB9ryyANljkuTpfbxXvRGSaw4HWwLl2dMsHImNXH9zCH4IXNOC2URuBtJOgHj2HikgnuqIBcUVOM/dpTL1tn2LpxNlhHJYIRiV/duYVLw+5+hUvL5Dwn/NZfxXSQnNVfhOYbxwT7DwjWAhKmQbXyN4noIUXpp4sHGt2Di64Fudg6fZvNVH4H8Pah/B+aELIrqX3ClfHrkhYu6rFB0W7RLflW8P2s38mzqkhNB7Nc3UU6jdqnCbjRfP5/n1wmG8xo4hezVkohJ8ABGFYdobw/90+OfTCtTHjFVaHY12uy2su9sogc2qodyFvkmTflCTFWEE/25iY2laXU7TpBUH0y/8vVri1h0fv4i9EYxEyXpCYbNK+jqBjv4iZDS3b/7zV/PHVfJAAo/xp+HOeIx+xmMEBqJ/nAJjXHgd7P1ooBclAzGOrjR/fxajMJIw/XhPSq13scJPPONkZdfw6CVKLfmgfHjNn8lHrrlSPvLNW/Ch1d4qtg8j33Dz4E371qEZGHXFZ6qkGF8GP9GThJ/o7RY/8crRlgprxX0WEGCdl4EAF993CPiJgyU+alvn8ViB0xeb/4qu+X1Yloyf+CNf9/iJm8qS8L6OjOkkHn/wN1wQ7HtUCn7idtBIwAqy2dRVltnUPWd3wU/0O1hu5pPGkZMs8MR7VfxwavzLz6ZmLJdmnP83acbiSV3BEyf9wqqz5UdznV0IAjKoMPCC3ZpdvRSAIl/gWozB2QUDcR4srirbgWfnZcYqqTMKbuKOi9TjcVacy604QerDqrMaOvJ5rxewE6XbrikX7ETVzQu6YidOt7ATr5JT3bt20KnuL8zpZ4l0XH/CfwB2Iq+vap5u1C3bYlcaOgRZIIT4mb98ttMwHUH4Y3mDefieQBfoxGmoWFyXOgRrry72c2X6F8FPbCvpjJ/4Ysm/ED/x/gsSTH5EqyJ4TcZP9PJBCL7BTha+vYylGGcsxXMES/Ec5m+6K4GcOLjERk5kitfsL6U6XNiJCj/x+HuP6fL+36jU+WTH4K74iV3tq+8ZZUtxNl5ikYWXyBP85qEIoZ5sREEQ7IKCL4qUqPjVef6TnNlc+7pSxkvEKMsjLcTtzVA4xgGeSMZ5uc6Gwi3AULRep6vgHba5E0IbK0Vi2RiVmtsMh3mx0A/OQvf4i7cF1bWg0CR7GSTwxRFjPhf4Yqf5+Pxg0nycLhhsd77ihhDVy7asuobxF8+RSXMhPD8DfxFuP9x+uCvgRmu4zSs9B0ZhLJFUT3lFpuLfodbWLFTWKefJPNYHfrEyA0qDBvOegsOAwpiMv3h+IAmDrrfgL975V5Q/D5xotUOEve//VdhzTziUBR+dVT8I/iIa5sB4jYbm7xy+oFP4yu7xFrtfn0l0OAjeo/cz8RoHjEzgNZqC1zj3ZXcaeos5vm8yXuOxjNfoh38l/EkQndr3IHiNx0sN578sNfzbSnSARaoD5EkHyKK8yr6PDlBv3n36YcFr1A+E1zi0tAteY+wl0t6FWBLtY1v3EuD/nJcSQsYautRsiRkdp3WL2DiSU6pg67/xXxyxMYHH2D3+ZAJ+0fYv6BS+8sD4jOyu6OR2HQQf0ivu7tczdbSqavgZv2W8bts/wbozNgXK5x3Ycbxs3jma9zrmCv6lax6w+EHy6slL67bqdx3WbdVZ8uXFWT++zMuOTGy9JxJh9Gjug+ZI/PJTr8U+95JSK8ViCtLDbW2x5UEy8J3PF53DOL+hF+lxUEWi3jDIYhQmA2H4Wc1vDk9F0i3ZteA=
*/