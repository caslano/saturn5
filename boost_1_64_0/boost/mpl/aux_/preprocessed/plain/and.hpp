
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< bool C_, typename T1, typename T2, typename T3, typename T4 >
struct and_impl
    : false_
{
};

template< typename T1, typename T2, typename T3, typename T4 >
struct and_impl< true,T1,T2,T3,T4 >
    : and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4
        , true_
        >
{
};

template<>
struct and_impl<
          true
        , true_, true_, true_, true_
        >
    : true_
{
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        , T2, T3, T4, T5
        >

{
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
lte1k8XrFZW/vvnvoxtkhZd9xsd5lz1+JbL8sXr9aDQV+8zXU7r2Smp2dNC5QId0t+Kp4Rfeos3N3J796b17d14+P+/clIc9nF/LHVKr+q4rVfUeoI/Nz3Mq1/OpoO1jS3POrnhj2gqP1bTV2Jjq0/fcPfN8Scudexd0dgs8GvWW9etEr5ufP//Z5+MftKvxe6ekyJfGfh05nGNukqn+dMTw+8cmHZ/T9XLvDhOcG7Ot+pufp/TQO/ZP3J+T1+3Az8NTh/gVm6/1UF/SqbfbRP+5uW+6xM51KP6dCx4vm7dDs7ezc0t9Bm2dNbnH2pmb1+wyGES7nfjeN58HaE+0bLdzFXN6NkeKMjZFC7wV22AStsXRaMQsDMY9GCLGmgzFMAzDOAzH7hiBgzASR2EUTsFoTGEdYnActsMcjMWF2B5zatBOjg9hZ8zDeHwMu+Ay7IovYjdcjQn4GnbHjdgXf8L++CsOENeFBmIrvBWH4W14Hw7HaTgCZ2ESLsRkXIIj8WVMwU04CnfhaHyD4yUV38GxuAPH4ceYjgdwPB7GCfgNZuBJzMQSzMYAjpf7MRinYnfMweE4DR/HGbgec/F9fAQP4FzczfEzD4swD7/EBXgSF2IfPmeLcD0+imfwMbH/BkXbGh6gFFCOUZxow0ugZFJWUWKp094Hto6yh1JMOUcJpE0vjjKUkiba+fZRfGnfC6MMoCRTMim5lELR9meg7a8+JV60AS7GHZQiygWKvWgPzKWsoKyjbKcUU2rH8dyUeEo2JZeyhLKKUps2QzdKFCWBMogynbKY4tuJf0eJpwyipFGWUvZQiinnxL1sQymzKYspKylFlBOUC5Rs2cYoQ4YMGf+p+Dvy/4iw6rv/v9SJ5yjvcyh+27Xk90Qd9MEvQ/lDgKNByf/F1P/asf25xnrVsf2P/sl+cUqOdJV+cWJef33OJPIhy/ynRJv/aPvNib/nocXY+ft0+c/v5X+fJPrB6vKhc/+SOf37mfOId7cO2Vq3xRJjB5tThTVKntklxtSzEftdHA952IaSrZnTvw46YyN0QVd0w1bYHEPRHRPRAweiJxagF76F3thU9MfxR1+MQT9MwBZ4K7bELeiPH2IrDBT9dWIwEG/FIByNbTAD2+JUNOJ0DMY5GILLMRRXYRjWEtf5G2MEjsNIvB+jMA+j8RmMwdXYTlz/j8Xm2B6nYQfMwzhchh1xFXbCDdgZd2M8HsQuWIzd0JXtnYA+2B15b9c8h9sS+btShgwZMmTIkCFDhoy/Lf6m/D95ZDXl/7+b7ikQ+X+gyP9DRf7fFg+b7jls6GjQ3Otu2QhwndoAqvU+bE3bgP9V2gbOXee2gRLLtgGl7WWHuCfavy45tfAI7y2uaYVtX77l/1T/i4SWlv0r/HWP7XWPT7RQ+18s8+PPuj4Us0Sdtg/F3aJO24eiv1/FPhSxfhX7UHgrdeHKtX17tS6qvO6Mr1IXqfxbr4r9KhzVOuU1znpW7FfxpVqnvMYOtU55jQLPiv0qFqt14eV1D6p1yrZ6yK1iX4t0tU55jYFqnfIasWqd8hp+ap06LoNbxb4WP7pW7GuxX61TtlWqWqdsq76uFftaRKt1yvvwVeuU91FPrVPexy/NKva1OKzWKe/jA7UutDr7X4jvEYvvFTfd94qn7nvF1/J7Rf89otxDO7u+Zb+MXbp+GXt47K35rjl2lX4Y+3T9MAqv0g/jkK7fRfFV+l285G7Z76KvT2X9LqreblnV/gZV7f9Q1f4VlbeXWu8vUXk/k6q3r84wt6/ufr/U36bBL7FPe5f82qOo/gGr/VVEu6s434rzcJSNZburs2h3bYqNsBm6oju2Qg8MRU9MRC8ciN4=
*/