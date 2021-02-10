/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::it_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
asH2BCXzPFbjwkyovfiN0onOMsjSEIyeoYU///YM/qRX9vtcTS6KNqbaXsbeRpdndB/RZRzTXcleDOgglngJmg31s1b1DV3TLSFOqFvHHarf3XnnhXjwnurHjt/B4+8E69ogvLayFm4uM067ZY7uoaOo/GRkKfzCWd+wkXvw726jy+Po/O355fV91Rz9bLAhtovsdGuyNULGZ5QK3M2JpanmmrcHZ9YsD059slcfU3cQek7Zgkw3JJxIj5flnvfjzDaIFzzHrc5ehdZc9En6/1BLAwQKAAAACAAtZ0pSgAor/9AFAABCDwAAGgAJAGN1cmwtbWFzdGVyL2xpYi9ob3N0YXN5bi5jVVQFAAG2SCRgrVdtb9s2EP6uX3FNv9iGYq3DPqxNU8xz3MVoage20yJAAYGWKIurTAokFddo+993R8qylZemHaJUskTe+x2fu0a9p7sC6MGjV+zuGC/8dRyXWv3LE3s/dRx/A/+HXJ/w9zElEexZvsVdeJzlG3QcS1xreU3vcfyYok9kGz0i4vwU0yuuIBtxDlW51WKVW+gMu/Di5cs/4Rh+/+33FyGcMSl4AXPL5ZLrVQivU7fyV86+fOkb/iYEboEV/VrUIhcGjMrshmkO+F6IhEvDU2AGUm4SLZb4ISTYnEMm
*/