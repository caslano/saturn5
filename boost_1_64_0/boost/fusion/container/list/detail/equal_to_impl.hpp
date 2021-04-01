/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_IMPL_09172005_1120)
#define FUSION_EQUAL_TO_IMPL_09172005_1120

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion
{
    struct cons_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct equal_to_impl;

        template <>
        struct equal_to_impl<cons_iterator_tag>
        {
            template <typename I1, typename I2>
            struct apply
                : is_same<
                    typename I1::identity
                  , typename I2::identity
                >
            {
            };
        };
    }
}}

#endif


/* equal_to_impl.hpp
KBnRsFHCsJuzvjiNbSOD0ZJN4hLCav1KDT8elMhRCRchRX82LIRP7jCo5A4+bkolnPfaD0nfLooNBYx5xgPbK/Hc08JQINOV3dTWEHqCQIbq0SciPaQVSQ6YgcHvK164aAxBs1DWPqt/8ylwfBXIP62BlQv7e3cYa9ixVQCPi8LzyFOzkGgej9GyXSbApa2K38qjln6l6HWg8ogAiC77rTymn0YWR12VVMUKBm9vx90Fxm/s2lEbA4rG/hhJFwaRDMUydbaNvn5NRNBJwDXeKVwgviJtBQ0BtmkiANGIIWTbHMpZeE/SfCjgfhy/np4sDnMxxF/DVWa64GsQtKUZ4tnZJSUU9kOkJpHGFiW5FcOcym1zbotLKAp/I0W8caw9f/RBfmdYEBMyflLPNlxGZkOwSPUOve0q9rDzqeIQk/acIQlBilCP+veWMpU00uxXMXsjtQnIM55XPT+QU3ehYYHN9GIwnVVrWyqd1zqJpfEak1n04B/OMbPNTwpcQk9Q6rW8rTXb83eMCUuIevMMriknH9yklr9PYNUh5WHAbu6G8nJ1hl3whS71TA==
*/