/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_20061024_2021)
#define FUSION_ADVANCE_IMPL_20061024_2021

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        template<typename N>
        struct poly_advance
        {
            template<typename Sig>
            struct result;

            template<typename N1, typename It>
            struct result<poly_advance<N1>(It)>
            {
                typedef typename remove_reference<It>::type it;
                typedef typename result_of::advance<it,N>::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_advance(It)>::type
            operator()(const It& it) const
            {
                return fusion::advance<N>(it);
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<zip_view_iterator_tag>
        {
            template<typename It, typename N>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename It::iterators, detail::poly_advance<N> >::type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_advance<N>()));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
W7kjJ5AsTLEnvyzg632YMufRfVUGc9YwazFu7baZtcjiYZbCEva2uECWCKssbFvPcXvIMpX1QrruGMRZw+i1qRfMbcWiVmQ668I5S8NaNXjQgSwIRuPKwMpbf69CFgfTCbs2o+MksiRY13wLzrdfIn7LJrO2MaP3CPm2o3jPk7wXWBFhZxbp+5HpYZS1N8w34+XvZD4wvTDPJXvvcw2wqsLG1v+4mWtQrNfhbcP47MKo9rKw8HuT/0uWK8aVhx1+breF92JbaBVgd873MiMLE+YDa7/r1okC22qWCKOfWfY12Wo2YNDBNLIkMa4iLK/Tn9FkWWJcJWXcbWF+imWLOSvDJlXUTpPp7QrHVVHGuQurqpgXjM6EP8zE/Uo8WQDMTtjlKl0mkQUr42bGvDMjC4fZCLOdf3kzWQxML+fMnBXEecLchDV9U+QtWRqshLCS01o84zxhJYVZ/uk5jSxP2UvTH/3syMx1xmbxodoRzhMm91LJvdJyzgUm97Jl5IpBZKEwd2H7RlqWIYtT5sxJW9SQLAkmc3lyqiRnnQ6TfbD73qwz1w6zFXavdTNfshylvs5FTBM4F8UW63tN51zsjddz7u05lswLZi/s+7uyczgXmE7Yp6DtrmTBMFmf76m//ckMMGdhAdXjUsgSYE7CDq7oGkuWrKxnUbr2Xc4MJnOZsffvJWSZMGthrTr77CfLVsbplm1/SZYLk5n121LmK5nmYDyuV3oW70UHk+stXzKiPucJk1mPqRkzhfOEyfVcKvs+JAuC0Wcs/7f1DxaW5Kxh5vKcve1RlyxM2efOe9/ecR+UfW5wvBJNFgcrKtarfKXIY7J4WHFhtZYlzeH+Kbb54eAIvt5hVmK9WladfLm3Sg2jD1/mvexSah/e5bgr912pIcp//W/cd8VqT9/blfuuWJnsCYO470pmZ0p3rkemORrXdzt8/Dkyc5isz7dkamMyvTJu7IK6zci8YLL24YEn+5D5KeN6Nd/5L1mAMu7kdMu5ZEGK/T0quR9ZqGL/4+rO42LeuziAT4pq2qbVlJZByJ492UIYCmMfQrmk7GXNeseefezZxx5C9uzZQ8iePcsl15Ylsjw85+E5pzPnv/t6vV/n+/2ez/n+ZuPeWwVuGlqssDVVqurQEoSdSHC5h5YIZstsxPXWVWnuwhI27+iHtkH0V/6IZSO0VLHf/ut3ntHcwZTMlkz5+yXNXcyh1AXL5TR3YQkNVSE0d7Hmi1mrQ9EUbvDIM/M8+9yaZgvmzOxHVjWaQyUwfncvKX750vzAnPjd9VlZG00HVpbZkdBpH9AMYGpmwfO+0oxMYs1+85OXoqWB1WRm+ma7Dq0AjPe+6uvdoWg27uZn8dnz4ir1AGbJ+pv7sO9CtBAwPveAy4mvqT8wvl9SuGklWhSYPTP//i9bosWBuXNr06ommhEM51AdbKNm2mK0VDDd//9MsQZYrWmb2qOpPOh95be1nmvfEC0ArAIzTdlVVeicYFWZbfna5wZaElg9Zi+0C46h5YDVYfbt3SA17VfcUhHE7OfNAzuodzBPfpbLEbWpd1HXaMjTi2jZYP7Mon9M20W9qwtzqQmm8Z3YhvZTU++/bcbGkoMoT1ZXC0xZ5fJIWtOT7uBv67Y47AxaIBjW1Rb7GT3pvvy27u9n0NxNYOWZHV9sEUv9gdVi5lvtK91rtVfhmnXA6h/raoPm70Xvcb+thnNJH7RKwsI+lii882A2bM3V+0LLo4WCWbG6W3N3fUTTCtvatNVPNB2YA1vT7dOxemhR4iyR6wNWoMUKmxq95CTNT5xzZLWCnmgGMHtmRYOb+tIchI35WZV6MIk8bVp2aI2WKno4lmdfDC1dWPw=
*/