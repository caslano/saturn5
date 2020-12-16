/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_AT_10022005_1616)
#define FUSION_AT_10022005_1616

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/at.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { 
namespace fusion
{
    struct fusion_sequence_tag;
}

namespace mpl
{
    template <typename Tag>
    struct at_impl;

    template <>
    struct at_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence, typename N>
        struct apply : fusion::result_of::value_at<Sequence, N> {};
    };
}}

#endif


/* at.hpp
kDVW9TxzcOBRI0/fUBxq+x5g4JBCC/MZ6r69XLCIARMDzfvaagQwJZscmNxYUM07xpjXFqvhM9L7yntJhsy8wXuAcx0+8KPsYFwvdT13rtC/pYxJh8182uPEKTtEtROBlzR0xzovF07gNOCpWC6cgGnC47lwAqWG897yXDgB0oCLB3Lh9W0ttfrcwDPIgbcA1HwVX8v90vrPugTRpmSSC7OZpe/lvdTZOfXzZ3q9mIRlW/dGb22XeZ1DE3MPHzqw1kBbXdDOX105U1UBOP/jcVahc0uJI2/WvY6PjOv8j5t0HvkfCdO6rnVI9JIwt59NdHFdd+Uq0f9k+Wb2Y5ScTRgdxDVZprcoWr5V8Agg1zNWnu8dmJMDaT/rM2A6sOp54wqucyTFm70a5gQvpTfd5D6xZTMn9s7aR17Hjrmu+1i91PXcuRJqHaoBI4+O8y779ut8I6v9yewyHkwsWzSzomyO/q5lLg5PcZYdU7ZImL2NTj0dHNO1LVK5+BxJM/0H6Ioom3fua6OQMa4n5jr4bMb0sZ0l/srqpraAnY7oWBhzYKsaI8tyziC8XSTMTgIIMKbOWN52vi2ZWzm/bH7Os+dpF6whHDS+4+WdkgvLPirtqpOmmThoo/a7vGM4BwZdwtCbmAPHOGTAW638w53AxOyZiytcT87qZ/rWO3D3k7OumPmog+M8Patp89zmwFxPz2o5vODAFWzNWOWbFCzY0drRDx0c9ZRsrdJjnpEFph+ShWeqVkqNFcDKFlWUzy2fjZr6F84rn11eJp9Q1v3+DvGYT2g8zwsd4SEPrd/Es2IB3vyZs+2GjHolQJniZQ6c6lqfYx9kwtzPsqbdMDJ9rzyZa39KXvuJg114EGf0WDRsbmMLDtQ4300eomDlnD9pvSxV15dkG+l6Pu80BeOZwzYyPaMXGM/CFlfOxsrp+Zdz4tW+Jf2cVeaIQjgsLjROsuA8bMuQdaYQjgxeMEfXXXsdvLKsogXq5nCWppRazSd6F8JT6nmA4xOPLTgfikpeiKaCUqfWXqRwSUqbgqEsrvNgy5oD1Fmxg7coUBtoDEUWZR/hlIhec05xVmFcqeLeSY7/6AAvq0U4SD64zmKO7ADfPJc8uwMcRCOoS0odG79U46GvjUhHMev4wJrKWs6oZG+qi0Nv4sfvyZLdWKfr7sV5+LYG5MnVV1EQT8nVWd+7pCBedt0Qgs2anML3xwrjL68ONyoiDPzUZT+Cby/CI40NBn7s8v+BL+lxeJ78n/jBcGMDHDR5fuX/uAcTX04uo+R6Vcf4zvS5chVX/8g9rQ5zRcjBjxaWA6a1nBscLdD44qQfwVf0aPxUR/gR0JViavyqpR3ia7nR83J45D/5f+HzVTq6gpCmfIr4eeF7bPZIn9Ko9rulY1zyx9bWbG4XduZO/NjcISYHV9n3KQVx5eNn+vzaUr5i8bLqcKDOMahgnVH3/0PhsF/p+HjKwXXu7sYJ2/NoGeheQ6IAnua9fiben+oIrxk9wFwMvoRycPONXePGOsS1ZVkdoZYQit8d4mq5T1L5RQFcO5A4uDYvzHy8ID5/Gr0zsS0fx/lGpdr7qx3hsPFsNBWKpxscXHJzb+VsKGqsb6wlLM1eFuTbKAQRheu9ycRFiVYGQaQCtRfIouvvJt/swmWnRq9soxvGM2Tan5/igoUdRZV2EnRoSW3pAE/biH5PyNkG7uSc4GbUUMmNJp6bZusWE+amOXO6CdO0OPJVefubBp6jBMb7K8R7BjzbBOMEp5l2G197NObx7zTwNEKjmmeXCx6h8q4Oa0Qto84yJ0IrmkOke/QlVW2mYHVYtq6zovBBXyflNPpT8dtMmJ1yGt/D76Lm0yk=
*/