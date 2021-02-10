/*=============================================================================
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE
#define BOOST_FUSION_IS_NATIVE_FUSION_SEQUENCE

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_complete.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Sequence>
    struct is_native_fusion_sequence
      : mpl::and_<
          is_complete<Sequence>
        , is_convertible<Sequence, detail::from_sequence_convertible_type>
      >
    {};
}}}

#endif

/* is_native_fusion_sequence.hpp
reD6Kh5eYSc36TzIr9L5ZBRchZ+jIIuGUfyZ+5iFWRGkY2gOnY/ivIAO50WcJlswdhQUUTbNsQ8cPpzkaRB+DuNJeAEDhUVwVRSzfH97ezjPJjD77VE6zLeHavlbV8VUr+Q9TGIa3gTprAiKNJjnUSvAN1vBNB3FY/wXNgS+nM0vJnF+1TKzgaGS0XaaBXk0mWBf0C6Ocp52FPRke1r4WjCDGccF/pOnSY5DXV+lU+dF2EfsZTzPEhgI9gFeGqWwza1gnoyijF6mlashZE9pg2uPxsx3FKQJTCZYP+gFnd56cBHmcd4K3nX6v52e94N3B93uwUn/fXD6Ojg4eY+d/d45OYKjj2GwLIi+zLIoh8GzIJ7OJnE0kjF/3M/22tq/xclwMh9FwTqe3iCPivls62odH4xhF8bB4Xn3eHDU6R28Om4PXvfP6Ak++O3gj/bgpN3vwJ9B52Twm+nreRIVMfzZjpOtq5dr/xYlcLZOu4Pu2cGAWtrNwmwWbmPDmlbn/d7Jwdu20ya/ybfnRZ6E06imFYxy9Mqf3uii/PZg8MfbnvWazN767MwMmwUNaAjfjxowCpxouxk8eBCo7waDk9M/2sfHg+POq8PBoNlc+7c5bWqcDMLRKBsUa//G75pvAPjy+BJaB5M0ubTG
*/