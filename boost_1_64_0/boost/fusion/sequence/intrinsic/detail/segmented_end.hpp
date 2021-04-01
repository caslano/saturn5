/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/iterator/segmented_iterator.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end( seq )
    //{
    //    return make_segmented_iterator( segmented_end_impl( seq ) );
    //}

    template <typename Sequence, typename Nil_ = fusion::nil_>
    struct segmented_end
    {
        typedef
            segmented_iterator<
                typename segmented_end_impl<Sequence, Nil_>::type
            >
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq)
        {
            return type(
                segmented_end_impl<Sequence, Nil_>::call(seq, Nil_()));
        }
    };

}}}

#endif

/* segmented_end.hpp
+7Q7yOgkmnipJIkuwNBMZIrZKFRjV8XYwNCtOGUw6CB7pGWfW3OWn+jesuSgRdWv8Q6HYoUoKMtvVTht7DliBXE+2DHZCQmRsKY/WcQlSunTa+fcihxtDaKuKBypDSjo65KX9Zu5PNlXLRqUlPazeu/SI90LUXi91OiSnA7Ks7kBbvtQprwAaRjGvqHIVM33uoWGOZlNPj1GcPBftB7+rEGetmxjZmG73MI9ZlzMTvuiNIcgSSzFuUVJGfPClkjGD9rkRpBjqUFh5r6+RA/byssO2V9GRkvKv2lb5oyiXJAIDJmgKFxUfw3FrinlaQxnsEfGFV10n0tfi9oukTdk0lCe6aZZMawPsDzKFEWkQfvAHk+Y7x9NQDB+Hn+Y2ylPAjWFCsvdsipxaShY/CfB24Gc8L5U73xoQYQOiCXvSwH1JFY5RmNgrSW+piQ+2y/9uk1Ti7qrOurgqx5zMNfB+iqYtfpKHaulbHQo8nO104vc1up9eh4+xeAo+PFmCll2/1g6maIWULiE2+58gKKrWfQbBjgpwVWwkFyRgqKzJMEB0PjY940GJgxZgQ==
*/