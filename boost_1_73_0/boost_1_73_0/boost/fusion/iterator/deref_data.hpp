/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ITERATOR_DEREF_DATA_HPP
#define BOOST_FUSION_ITERATOR_DEREF_DATA_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    struct iterator_facade_tag;

    namespace extension
    {
        template <typename>
        struct deref_data_impl;

        template <>
        struct deref_data_impl<iterator_facade_tag>
        {
            template <typename It>
            struct apply
              : It::template deref_data<It>
            {};
       };
    }

    namespace result_of
    {
        template <typename It>
        struct deref_data
          : extension::deref_data_impl<typename traits::tag_of<It>::type>::
                template apply<It>
        {};
    }

    template <typename It>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref_data<It>::type
    deref_data(It const& it)
    {
        return result_of::deref_data<It>::call(it);
    }
}}

#endif

/* deref_data.hpp
zLxt4id3FRvOYmOQzzhfbBwprt8fKPMZO4shtBm+xilJxRRAeJnDazjyZuYHx3swTbl46pbLl7crqBUbH/qNArpuyFbcUJLkN1Tz6iFvP1+DN/owLH9DhjdvT/BnxQ2Dihuc4VZv7ZeKs2FpOBymW13dW/ADbGWH8a6ZG5A2MuhCE64yNOGqwCu35I6UqDtg8SzPyE18f1Ro2oo5XHiX01Y4zJZctdLxmke31vnO1scVeRXZTxQ5/JU/0RNYfJg=
*/