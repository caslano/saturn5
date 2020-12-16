
#ifndef BOOST_MPL_PARTITION_HPP_INCLUDED
#define BOOST_MPL_PARTITION_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/stable_partition.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {
 
template <
      typename Sequence
    , typename Pred
    , typename In1
    , typename In2
    >
struct partition_impl
    : stable_partition_impl<Sequence,Pred,In1,In2>
{
};

template <
      typename Sequence
    , typename Pred
    , typename In1
    , typename In2
    >
struct reverse_partition_impl
    : reverse_stable_partition_impl<Sequence,Pred,In1,In2>
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, partition)

}}

#endif // BOOST_MPL_PARTITION_HPP_INCLUDED

/* partition.hpp
hOfMU5/gc7QRi23ahtIKT17Ui3rPNSb8Z7ZTiR8yXnN2ZdWO77MByV4ruXEfJffcQBu8je+58zZtsXJ27TMzlr3JaQ0Ast1VO73nBh5/NuPZWA6TSLmMd546+kb6xGdUet9wdjS4gXI2TjNKbMbwlfXsIPkZmnF3nQXLMQoXI6Xe/ppVaoqUon3z2Ej20PGiFHnJVmQoTbPisoZyzsQcbKAbVkPVBKSazW98yOcnfHiLPXTD/5CpHK4Xx19VDx+F46/j9IM9I1s05sNfUMfzJeMnsxnHQKdI6flUtcY+n/ggxqATwOeqq0jVdxuXR3le0dEGr2Pqg4G6ILlnCtDO6pfMGdVABN7VRFOoeDt52RoV9C0dFB4dqoX8CX1FmKCxTi2TT8Uee0N0fG/HqLLnqgYRS6LoYlX0IV30zw4981hL3Zrt5UHGRF1PICgpOtlLL5hNAbjJ2EDd541X0t97fcs8FMAZ8ZdlQhfzxkTDrn3FjdTHcq63AaN9YAhGW0oU8xHLhq3jHe0Oi6gbXNTBoK+YppixySxNNXnL35j6Bfstn6G80X0tekVEQYXPfhmTzeS+ykHhT0qnx6pOr6tVnf4bdrjZeq2BWl0/ldinGO08U27co4zqiX+fx1HeRsW/G0GWjVJ6VMVGOitgD9sb8za50Ud6cJY0ohsbax2x19EE9ZZbAW810GW/F8uNQboJcmiQDv7G0oqGqoH1DHlytxfrK9ZbsNcL7F+Gb5HOVzxDIQiWoOfK4dMc5KAzoyWnZLNwUOlDJ56Dju2n+S+gJ13KGe4T4MHCTu8Lvoj7z6uS5HnNzHb5bauZQf/HmW1NRD/NNZ/AkG7jCRxm0tZAEbNnWWFdWVF9kPYOXntA2LPm81SeV8VLu/P69i64GBkMm2B/aYVvSV49SkQnZzlHBf00sb7nQl7xGk7my75rZtMDdkpl8Gr4vdx4YLXMaaCG/VJkw3XZQjMPyFb/GMhHelT/GLhXBmCGqDjgYeGAx2tkp2qKNM/cjNoUvfJscJv+OCDZVeYnTqUdY8nUYgKZeZs8tEXD57mgQIiS6tcAlS3UnQn8ik7XRzkxOt1BqdP5vayovD7K3Ztaj4RpUg4fBor9p06L6LKKk4disTkUsbz6NYtN8HioR1YpKlcV1Ue5SVd0MVDrJZlgn5JXpGLt5D4vxn4kzXMdWhe/OE0ITSkRTjFqHrKaH3JkzXP9quH10enJzTM8l4mEm1FAgiCSE/seT+lCdmYVXcINs2jlb4yx+WnrlJUvpCpU13CxaQKWIhp9EUNPMWRcIH8ByE+DgAl9A1BWdeuA0yHRz4uu5fnhECroTpCTBKd4oqkpp5QOfaJdDqc59uMx9jMEw8VCT0bi3V0F0XLQ9S9UFHN1BopyZu4azqqjZwaNFACy96X545hAIU4GxDo8Qy1Be+jOZC6EjhTX8HMdmJs+0aVRfqg6O/RnzQrzFCusvgcjbQmC2OD6NTMtIrsASlT04kLM/9hpoVYN6A4FaJIACv1DZclQTzM2L5JTjndUhuK1pyWjHk2LYH7ywY+aYO4iP1mvlfCKvBfRuRN7XZz3kd5U0FhuDEgpllq+0RhU8nLx9vpGlErNL8DhDE3voDdXl9H5dv1wB09S2QXS36Mi7H/V2/zz7BXToXjSrUkf9sCbq+TaZNaYrKylA0nnM3j2fS4coqm38y59W7IEEt0nZiPirO7ZCqUwDQyPlWo3odrDVrU2p9XSXaolD7V0vgnM+FyV8ltArU+wg5lmgfk+gTHyZsTarVuUtygTjrvFsAyGLF+6RrnakkC76nW/wvn9JSk2ixzh5Gq0i/2fqqip5cVTbukMCFcIfmOB33eXysfuD7A=
*/