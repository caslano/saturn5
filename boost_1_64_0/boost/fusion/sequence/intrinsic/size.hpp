/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_05052005_0214)
#define FUSION_SIZE_05052005_0214

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_size.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct size_impl
        {
            template<typename Sequence>
            struct unsegmented_size : Sequence::size {};

            template <typename Sequence>
            struct apply
              : mpl::if_<
                    traits::is_segmented<Sequence>
                  , detail::segmented_size<Sequence>
                  , unsegmented_size<Sequence>
                >::type
            {};
        };

        template <>
        struct size_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::template size<Sequence> {};
        };

        template <>
        struct size_impl<boost_tuple_tag>;

        template <>
        struct size_impl<boost_array_tag>;

        template <>
        struct size_impl<mpl_sequence_tag>;

        template <>
        struct size_impl<std_pair_tag>;
    }

    namespace result_of
    {
        template <typename Sequence>
        struct size
            : mpl::int_<
                  extension::size_impl<typename detail::tag_of<Sequence>::type>
                      ::template apply<Sequence>::type::value
              > {};
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::size<Sequence>::type
    size(Sequence const&)
    {
        typedef typename result_of::size<Sequence>::type result;
        return result();
    }
}}

#endif

/* size.hpp
ydpsHJaZBeGcuFp7XIOM2trP6vsT32+9u5PzMIk4g8FmiKmDHUnmOcW7D3jJuE3iqIAOLHjRA5c6u8+p78RM3pIFHAZ86lUMoiC1P+2GKo+36urGKby1E2nfMTjCiA+MS7yu62KrrkHixUkSVpoXojIsK68bWtczJm/FQicMCp55ilV6stI+f46U5zAvyJ0yjwLW7YKK+5gLrXfM4iTM4yRr/P5EDySs5Ht8ivAGrAorsY1xGt76Uq9vcNO+CLxkjFZRBR3KY2LbVbtaNB0LWtiaf662eEvPi/MiTzSvNPjtU1/hTz1ilPj6+mkUeFkUMdibLq4tSEcZdI+y1vPxH5DvUuWVEweZW7ucWQ7bxpy9G/jIWlUESZQxmKLFh4HOK0tuHghu7Su6n/CWTJzOgiINwO9QNRHMf9KrZ6tPnNFlPUZx/qX196vQSeIUJKlK1CaOrT0iKT+B+UYc33nOiLsUmXSseABnWzLKMIiT2KEiequWCFXvCyZ/yWLXcaPY91l/cW1LDKGNHm6yca279APq/5aEHJaasiBOyHCnDuz6dCLDCCzOMR3zntSds5IHqReEWXcskz5xI5MNMYpz3w9be50qDYrETbR/CA461YYnVBts35LeJ8Hk5QZhrlnBFqy9V9hHyvNZVeTiZO4gE7rUTynmE4qXtepaZIWTBL6LvHISAk6sK8Z/eJQ5ziKRfyAr/Ij6QmpPI2u8HCdleyyPIr/KCvb4DRhd6BRE2onhfsHkzVmVFGGSFpKX8hwRuQF+eAj+9hL4SI3tUp2cYmu1sTEQ9O/fA4S/jNBhieoT2+/fwc8dRoKjR5szowLCTNTHfrT+TaNeYcgKx/Fg3SuZf+S6xihLOt9qA60FMMJFMy3Rj5SsK6asoIS5Pkvissz+F1nsW2a9fBaHFcz+3P9fZF0ksiIWl7Efl57738jC+xR6LxnFWRz5TsVEmD0vODoz6ydH5Ydcxzu0b9P9W5ZWhW+whEkeKB7T1+r28u4XPUXkLSP4jBH7iNsPD8bCOqVtk/49Di4FTiP2ajcW7yzMmNXHR/49thZs5kDsxOPxD6pCc0bfjtpBQFdelkr/PspcH27h+qZk8OjtG/lSvkltM4sgCN3A/6/zK5t6t9uiLqk5zMp4qqh7WB6mmBUjL/sPCQ3txJD30SOCjhcQghl5r7ZoYo9r6rnOjdr02bVlYhecjyGmVgDQN9D1fPIOipP6dZTDdiK90wb9Vsr+C3FNO9wXdWT4XKyAhvUk+KehBaVhVzhO8MQgD/OzXx8xnfbp25ROnSrM2O0EZ/lvoN+Txtj+G5cJvdt/44E3RIxln435TxFjt4/yccJxsWswVnUW9IW7EWKN9xMSNeaL3RghSds13rgTg10PdWCIw/fEArFP3cTCoDCSF9vG0ULRH0zo1QCr7Z517Mr6udH5Z08gbfumQBsQW/SHSLPjg/KbIQ1jdZbqbv8brfg4ucvLOM3/n3noNiNUsSC1ithO+4ZtzKCYl3tGbOygmJe3GP232E1TF75rjGKpBkXL/PpAHOZkR5kzOwZhxdZK464gzlK+kLJ/uHMQTpd9R5y3JJYo0nSZ/ngX3baH2H/9TpytY75BFw6bWdty3FDjiKePmcPaxOA3wDL13L+L4qQglPM3i05eEXEXb0Rx9BV13bdvTHDE6wbz4woM+rPOPIzLgMroh3oTiy6MbtCm5oc2XQxQEotzeUJiaFewYnv+rhtn5RJcvmknrjNm55e7scSXNr9ZJ0aZNyHu6904fGH0Uf0ajW3pl56b5k7x385JmEP+a/Ruws0yr/BJKATYhB+y7jT2fJXGD3BS7pYuOzLV/PGhkxK+o2pvB3xE3+rHTlU=
*/