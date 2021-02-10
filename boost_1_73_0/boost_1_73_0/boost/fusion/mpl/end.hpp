/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_10022005_1619)
#define FUSION_END_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/detail/end_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct end_impl;

    template <>
    struct end_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::end<Sequence>::type> type;
        };
    };
}}

#endif

/* end.hpp
XkxSoZP2Shs8Kou6UoHmaUqykE9w7dTmMPLwtGkb5KixMPSjZabpqEUiZ2sbEUeSEhcqw4MQB9wUSYS5DUUWcWU3W8vLIzymFuCdrlnpG4HMUBl42hvBYPQUJkwL3YZPg/HfZxdj+NQ7P+8Nx5dw9g56w0sS9s9geIyuF3iYAn6VK67xcAVilqeCR/7Mn/d0G41nIgvTIuLwlLwXaG6KvJM8ra1Hy2xSxOtrdm+uRGY8IY54DG8vBqfHCFBwOnjbvzg/3WSY8ZlUS8vAM/R2jY6kiE+KKREbz1CYyDh8GAyDd4Pz0TjonZ6e9eH3wxXt+HI4GA7GcHA14fyP3yIG3T1Q6Hr0cs4M+i0Dsq9rvTTIMBgYOFMAHVSEhtDsNuZSRNAn7ZAYCNzXdORy8x66TIvvPKCAlRMxbTV+NACOT95evO+NRifn46ZuHW2s+J20rPffoBgFr2F4cXrqV1KeTXHlwH+yNA1rn44bF9zLUYmvPcGC7PaRtrjLQ3FUonpTWh0rzm3gogIxRhQlhuL7lo2WM6wAWjO1xIjmaaQ7MECzJdfZCzK2CBPaRpJeEM8Lt82KMUmhXbXwskMM9AkVlUK7VGJRBBEzzL5Pmci24U0a3sJ7F8CWS7OYOy6Ha2sd0TUwKyBGRireZXmO
*/