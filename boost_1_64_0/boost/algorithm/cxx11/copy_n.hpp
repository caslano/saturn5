/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  copy_n.hpp
/// \brief Copy n items from one sequence to another
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_COPY_N_HPP
#define BOOST_ALGORITHM_COPY_N_HPP

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn copy_n ( InputIterator first, Size n, OutputIterator result )
/// \brief Copies exactly n (n > 0) elements from the range starting at first to
///     the range starting at result.
/// \return         The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param n        The number of elements to copy
/// \param result   An output iterator to write the results into
/// \note           This function is part of the C++2011 standard library.
template <typename InputIterator, typename Size, typename OutputIterator>
BOOST_CXX14_CONSTEXPR OutputIterator copy_n ( InputIterator first, Size n, OutputIterator result )
{
    for ( ; n > 0; --n, ++first, ++result )
        *result = *first;
    return result;
}
}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_COPY_IF_HPP

/* copy_n.hpp
8l+J/c3H/GJ/R9iF1hgNFZG73XSUvCBS6aJfTwQYwa8jUonDWJAH/myVfBvZnRFvlQUc7hDPvNX3RyUMaGwELEFafb9mWptNrhECcYff6nTPfSRDIAAQMQ4mACqVzo59k2EL6e/SriVtWfbs2qcLbw/4SE5W0IjioBzoy2oIzudGg86NHb6pdPvaGqNebOcGTvTAtbiiNA4zW6lKZrYtxKkURJ9jGlPM1bi4tAq7I8S+sD0ivkL0vIFpZ6X/t22bpN83dmmKAXxztMUAZgsGQNMdIpoFarfpDi0IF6zwpL/cmvRjDzfpp/ea9EPye036P4lJP8UF0zRiGr6QnPT8TpOeHyC3lBD+9wVw0ZNUY5W+Ctbx5Iy3F6vGyzzll0EsmpXAQd0Bj8N5T9nSpvxvThTsSEx5zdxnUeccElP/e92mvtq1lYxR8e2Y8g005bFhk6I3mtyiZswMrjyvHxEyryhqxJW4pkd+M1S2OfWcNudlKqXXV0SmEEmrcxronSi7XlA2fsUkIrr9kW45q2xTSeRcpeoHrb6wW6a+Eo0nvuPhhnnTNa1V43vcO2k79nqSLWLr5zCthby7xRQEjhG/BGNuTcFHSCAY9cnyhyks1rP6WmMZ7aRd0H0Cns6u15sx13gC/qn7BJyemoDy1ZiB+Mwz8HXMwNSH/8gpSOthy9/gtFGHF687zPmmWuL1vSOI1w+smfZ2+kwTPh20nq3oMdNe8vScaQF9STf5GkDpwwvYINjw6JvnEyl8XqZF0Sox0YK0QcquL3DahU7XIGOZZFVT3dKRi4LueWXpErYMYKQC1Can2TpTppT0mGsrsJeKuRYX4hX0jAlH26NCBmFlmO4vLcRo+nmrZSbNwgx+LAIK/SEJFYSEqmcJxYcFLAn1nBZ7gOAQ0zzZozP74IVlrXveXazgCfACusCDCijCmzqZbbrn/opSwoew2zbP6jI8pCwJ27N3n3oPesDGB7c0bmQSfDKoPxoOy493CfnLDPbyjy1/QSqgCfIYA7k4PeQ2Nox4spj/fE4U8Q2jSwQDMEmXPL2FfwLpVviaJoFF+ifSuT7Lf93l78ERxy5/9+K0I3OFWyyucO2xyd/fuj6B/A0SeXj1VRY/kEtZ7MqRHIhiX6CH8G0TwndJuvAdyoRGQildCCe5wq+OKnzTZ4sP6jsLOkvYroMXArZzSc6KNpMiixoH7YqZrNdDYnaXX4lLclOAsUROCmqWwo+aUljMp6Q0prlCxixxLg8AQPoyRAIQafvhgIDEtiCAVAYQkLxJOJY72DUjKYmvPF5JnM4f9VUsj/MHm9NxRCR/OM3H/1V53CO+GwgwZWm478vm7LvDx9bRW8vI2BDfKtFEjL8jhRcBD6Dq3PAinj10K+AlcIeMVyQuy+W7WWFvmoJjyeOHwet6mYLwZYqzBY8rMYNK+TBPfDMl4dWfejw39Xhe6vGLqcfzU4/DcQgIPxdQZeKxPPV4YerxS6nHi1KPX1aGja/giSiSlGFjFJ6T33dw5L1CHD6pwG8JflkOnET+FTP7aWJpC4Ntok/WTqNDAh2IqCrJKHSgpH+KfeLY4vPVfyl1KcFruC5zYYTpuT1R+WMyLcN29uKdzIMuAzP8yWx+DI0zcH9Y8ApKDOABJ75C4/jEI8ZNc9Yg6crU41Wpx6tTj9ekHq9NPX419XgJIz74FapXPI5PPV6aerws9Tgh9Xi5+ahFgxOVKKCLhSb1wLu49v3XGL9XPpW/XqG8brvQuh9Z3I3ccZcrYxGhV144K5ucaG3JyDtEJyIkVeJ0307jY91TLOIH7S7nRuVFc9AE7i+dgUYXU6McUWiif6dxFP9eruUPopagfw8dl40Oo1g=
*/