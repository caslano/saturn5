/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : access::struct_member<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* value_of_impl.hpp
6XEP93AP93CPf++xlvz/lU2dvPr+/wyd1gJDf/MjY1uReG/eQMC3Lfl+Mt/nXGN8X1VdUF5UUFnkJUOVX79/2708IX2UmXq/PIC0NWkIqZjfNu3sfxcdNeRA72R01ipRHeL38esNFfr3Ro8sPlbfZcNvO5m6O5tF6KMY+/jSk4myA1hg/J50PanEaNMufrny6MlxfQxX5F5DTyZ+uQI+2YymROr+LtDjyadaH3ifdBJ503a1qc9bUDa1oCqmHlOkz7PyqUXe6grTX1v49yWVFdPM/Xj2vSVjdHx7VMaNr6NkT5VtwYHqq6xgX/Wwk90YI7H1RSPrVSzBqHprVK+Rr73WQTqRf6Gl3sKy4oLy6T5P7HrDx0Cp/OXPVbsuJU0xxqal/KLeieiV7bFZZP8iT5SuQZQOGXmlQubpoHPUKlKHjN1+5ZMmjrH/f+hugfWcM7oFPs/S59KMqLGudg5WOzNIU/mrfrfodk4prk5grJvtlL54+JiLOpe3tjavt021Xn8EMqT2tJHBy+8lx+IYctRH1SldR80FlbRHOhehc1AtWSP0Uky7k866DqLGyjLp1q9sgczwR1hmdOTu4fIz/nt5iSEQj11N603r9zD1VIJ2Njl7htnZ2LTNB1uG+XJUfEflK6ycWm3q7G3v/66krGBKleM5yw7/blpgvKWHj0u6J8x/oL5H4sKKomLzOqYu5fdWIGJkDIhc2QWoCz2tSWd3MhYYo/rOG34v4Y431dCsiW17ERF3RDr5s3SeToLlRgyQiLoYY3Fe00G9xoHp5nnJs5wXzcMbRp6DUn0XHGNdIvRyywrQB62o0u/Tws6Dnb2U5hHlKamYXm50UqR+7NKNTf22NsG1a6Of0/xtN05O4TRf7P406qYoXUMF/s8p5v01Qp/Mt4n2pXVfG0hKJ/PCiDq9Q8ZkDR49NNs79OAc7/4jE5hjNkzxy+AN0/fWd5O94f0k2aSDa8oerhvbKFkHaR406v+MfJ5eAVn1gBO3jZHOW/Q939RrbGPV+/MZ981eQV27sGnv4Kzc7FHDvCWYbSSiZ1lgo2/3iYPu3/I2Vv3HSuPaaEYeNC1jyhKcA77311vI4yNPqKE5QLYyba19UW3cg5qpG5encZwLp/4w56zPO0X7PDXPUad29ufI07sZudDOTFYm+3NkyjOvnVU/cwa/z3SWx6+hmYhf2KPj0NEMjpnd21vleXNv5pQIecJiUxVhAFEdv77oZ11NWTpEyhLRL3PaW3WEG5Gj3kGOkIpwHP0S3t52HazXSH06dTnUk6gu+sB0ex3hyzpYx+GxxrtXH/t6/YMwgXrp5+hzzr3Efp7o39GMkbSVYiQdb8xbTrJUFVcn0gcWWWyfxZzlW9rROiYfo19rHeRLVHd/YHrs68P1Vez6Kv436c5+ne6X//RtFp26cuFhHx2599Ztrux0ZHK6s4iq9Rlj3SbgS7SlrjO9j4fiSw8JfJaujtZP9J43O0pXZ0vpJG4t3c5tpOO6LSyAqfBouB28Am4vXdYdFf95J9Uzw6N1E/ip6mkHy1TPFdItvRruAa+Bh8A6mAevk67g9bAOzoMkv67JPXC+dBcXSIfhJvg+vDmko6i1D62JzI7SUbxQ7bwI7i5dmoHSpcmULk0WvNRfnuL0qbw0ldcK8luOgG/d9vB2mArvkO7jQv2+lNSk38/V79vAifr9E5LnOdgDPq9+eQFmSGf4IOkMT4ANsFg6w6dKZ/hS+Krqy/Ro7QAOVn2tYbrqO0v1nSNd0XNhH3ie6jtf5dSSUntGjpeOcBbJI53OTaXTuRU8XropM9WOE2A6PBHmwJN0fmsUP/xkWCadVZ90Vk+Tzuo50lmthadrHJw=
*/