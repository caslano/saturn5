/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find;
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq);

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq);
}}

#endif

/* find_fwd.hpp
bdb2jv9Esjb+v9oz/m00/l+j9PFvo/FXG8a/jcZfLcePp8PjhGS+sFW+ZgLFZjNvKYe6d9+RIFqSF3Aql0VlkgU/c2Z6i8x09TwVMmUHS3U7TJzSUagMhBouaDgW6rokFDlplSQa9Mr4XDsJn87GxVi0FUZ7DBfjKPCwI6kBUVkqG6yW6M5o9kKJB2TrtsrpGFrTELEMS4GbPXRRlxtcX3xF1oUTvM25ooRZrqzjS21lk7fKlUUV9LZW9rR4ubIlx9uxsk810soO1nFYbSMdXiVsmVoGv8k3Ejs4uqfRanCcJIqM0YuEQMSljUaICNksZzQaNgs1fFajPLVD/CbpKm7SyumxR9tl5fRhUyLFVWnCA+R1eGxWX6LHs5x5mTjq1bXeI0GR9hCnnQNpb1DafZzWRaTVqEu8pB0efwirNEOiKHRVUyT+R7OLjnVrZxLNhEYJ1oozqRamtO/ndCZl6mZRmajKXcuix5IQMEPloRqjEpqTAiL5UVnrty3aAtE1VSHqHRnVfXdgR64lvTWH2nXPEbJsFV8v3WKVpti6kXMRN9rX3MYZ6ZXtyq88rHZ6xCQFqGQf7QH76KJw++hdek09ZE1FDGKHN4d0CqOahtlHJ6IqJwTwI/voTJjYTzazHpIY2MbNRrhN4mnV7aMLdY10o310NYNd74fbtI/O+5kgJZufP/yHnvv4eS6nb/lPYsQ4o0BY7ssxEpYH
*/