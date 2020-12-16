/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_JOINT_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<joint_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::first_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
BdhhGhY//7H19NwXHuupYdNuLXqHxlbAOmtYyQlH30fvFrCViO0I3zd0PXsSyec6wWvC9j38mREkL4At0rAOhXvcQn3lS49dqmHTWpWcSeMgXBT8qIbdes8uPvWVrwRfCOu538A3iB5gp+C41B62ePu822M8YXAJxx4siT148eW/0Byw0WNvaVjtBSNoTO70LYwHgSTWou+wfjRO/CDeO2H8vRPPADtfw/7aciFTWNGPog2E6fPDQsBmBpPY9NjFheodxX7z2FWoR+4E30PfDA+SvHg+uy6QxPodWded5v50n2VjmTvDvBlb+eizCivK8dkcP4m9dnTna6kNO/gsgvXcBbBr293XivjSwsS+fnGXh6kNgMF0RVjBTX3up3G3JdDTnsu44bcvaJxo5bNO2nMP1by9hcbPNj47Q3vu+Mue2kCyBFhIw2L3/Ubvr7itSS/v9duHUhva+axIw64unfgyyRlgmzXMW7PGp/bt6LMOGjao76yfSc5SsIx16fNJziD4Ug+9zPpohOoJWJ2G3f1AehrxDLD+Gtanoe9XJEs7+SysYQ+1P3Mm8QWwnTTsvZ/mhahMwFpo2KpuZe9SPXeGaEga9uOb1TRPxwA7RsN02V0L2O5JzJhX8ncx2iDmAJqPALtFwx7YfM4R9N47+DDHEWbOmx0Meua8uRVs1VbKzN+1+eeKANtHw2hO5bZjwIoR4+8/cNSvK2gO0LBd4fP7FReNoHF3N59FNaxt7akf0nOAjdCwyr9+OENhxR35eyDMmB+WAjbES2JvdX1/A9Hb3WfLg0lsn4cW7UDY3j6DrkRY7djTviC9vJvPHtToXTP6jm9pTgWsS0YSu+CJIek0H/X02QbtOe/MB06nMnv7bJ5Wl1O77dSNnuvrs9e150asvOJAoneIz77U2vfja3830HjWz2c74nPdhTNk90nxHgUHHjRW3j4yll8wM7ZMXrC5f7T8VOi9Y8VdJSJGtfwzHuleXheOVHY/cP8D9y+owhIIq+/Tq3scXLJCldtHQcmIsW6FT7Vuhd1Cv2uW/CuWw0CPCgQ1M4a1GkZFuF+rTNBIMOKDuU5lov9J9AR/kC//ygzA+sAVHyoSIctsIAokC8a6mtG6Gk6j+WsFDyBP0B0P+GaQXR4QBeKBaQdgZAeAVbh/Zpr869d0WAc74gH3jrDKAiJAfaFZuwV4WPklrbAvwGCxqysegKdKvV0mKArEA3Ptz2jtD9ET/RU58q+CTHd9QTgmVNpmAidhyoK5Fma0FgYPCH9cFo4JGe7mB77lb5ULRIB4kLLWZLTWBBdI/3Ns9Zg0hzyYErPMAyBg8iB1HcvUOhY8F30eU0Ptxe/siAd1iYpEtVUmEAXigbnWZbTWZewYn+uo0rfG3ZjAbym3zAIgYMqBuW5nYt0u0WJ/UUD+tSnN3fwI7sDhqilWuaBIGHww7RCM7BDg+ukvao0Z8wB3w4dquMQIfHDLbTLCoLHVNab4GemPgQzqnFeuGz7AL/DFsrqIIhKGPDS1npboCH8aRuPq2tJZv5D34VrVHImEwYfi/j7tp3DDY4dZ2V9KdLi/tAWOD3nO5gn4ZbtbEAmDD0XH+Ow45AO335f5Xz4j0aP8aThfFmY7myvEXf1l1vuFIGHKQxXY8ZAPnfjZl/u2HCHRYf7a3eVf+TCAdnTFh9JqyxokkTD4sOo6n+2HfODN3u3Uk/eT6JH+TGx5sbt5k1cyanc9QSQMPnS6KcmHzgYfhvqJNOf6A68k3P0Xsc0IRYP4MG6ezybjuorvAZ19xIIlsqVH+O1Rl2xwZ2+COsYgCKFlNhAJbV0xH/YYcI9oT35utmgBrq2G+Evy5F/rs0CVcsKHcvA=
*/