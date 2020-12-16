///////////////////////////////////////////////////////////////////////////////
/// \file rbegin.hpp
/// Proto callables for boost::rbegin()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_RBEGIN_HPP_EAN_27_08_2012

#include <boost/range/rbegin.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::rbegin()
    struct rbegin
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_reverse_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_reverse_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::rbegin(rng);
        }

        template<typename Rng>
        typename boost::range_reverse_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::rbegin(rng);
        }
    };

}}}

#endif

/* rbegin.hpp
FYAVghWBFYOVgJWC7QtWBlYOVgFWCVYFVg1WA1YLVgdWD9YA1gjWBNYM1gLWCtYG1g7WAdYJ1gXWDdYD1gvWB9YPNgA2CDYENgI2CjYGNg42ATYJNgU2DTYD5qmwLQrMC+YD84MlgCWBBcCCYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1grWBtYN1gHWCdYF1g/WA9YL1gfWDDYANgg2BjYCNgo2BjYNNgE2CTYFNg82AeQ63LQrMC+YD84MlgCWBBcCCYGlg6WAZYJlgWWDZYDlguWB5YPlgBWCFYEVgxWAlYKVg+4KVgZWDVYBVglWBVYPVgNWC1YHVgzWANYI1gTWDtYC1WqZHW9j0WlC2fnfHtctSZ+OC4TjHngWblAUN8x8xn2cFw9aRpRhWJLPmO1qWbFiDLM6wK2V+w26VJRrWK0swbEgWa9jbULv3yPk8PsMSZFaeaTIrl2xZvGFbyqxel8msfp4C810ss3rdCnFdkOdTkMsYxH0Fcf5K21aWWb1eX2btiUKw/WVWr2tlQatnsiTDumUBaw9CLp9A7d6jbEuVWfNtKLPWdnsYs1xm5XmKzFrbRpl1Vlog7g6ZtQ4DYJ/IrHWIPtqeL0lm7aV0WaLVT5nV611hzINk1l46C+wmsKegvhGZ1ZcpqMF/jH0tX1OWZthOEFcls3JpkCVbtYP1yqy+jMms9fsWxkyosvfZmmCFMiuXCpl13T1RZq3DZWB3y6waBmC+N2TWfpmEuO9l1r6OO9a+vqSCrSOzcsmXWfXtLbPWtgrsXJivBfLshDGfAhuVWes3A5Z03HyedMNyZVZfdj0Orj1gx8l8hp0OdoHM6tn1Muu8Pwi5PCuz+jl2HDyfgDGjj7d7FpRZeWbLrPOwuczKpRjsINkKhjXIUgy7VRaw9qAswTrvMqufUxDnrbYtILP6uU41nGkYswSsQmbVcLrM6ss1kGe3zOr1MMRNyax7XOIJ9j1gHZl1pveQWblUy6z5roT5HpRZ+/plmXWm3wb75AR4bnqive7JMqu+bJk15vYya93LYL7jZFbPmiGX+2DMfhjzExjTd5L9fClTZu3dApm1fvuCVcusa9ZZMqufLSfB/U9m1fcC5PIhzOepscdMkVm5rCmz1ihPtpphR8j8hp0is/Jskln9vL4G7nFQ3wjU8EmNsSf0iD05lEsw+KvXgpLCprj1IsZcQRZvWDbYlmAlMN9BEFctSzCsQZZo2PUwZhfEPQtxo2Cfy/yGzTvFtniZ1ZegzKo9S2blsjlYMcy3P+R5NNjpMGajLNawK2U+w24CuxvsEbBnwYbB3oPav4K4eafa65Ags8ZMk1n7c30Ys0Bm7ZdSmbVGh8KYNTJr/c6SWbVfDHEtUN/dsiRr/aC+t8G+gjHjau24VLB1ZFYNBWB7y6x1qAA7EXK5QGbtpWtkVu33yaz1e1xm7YkhsA9lKYZ5T7NzCYJlyxKsXoOVylINOwWsVbaCYU9B3ATExZ9u9yztdDjvMr91v5VZte8hs/p5NMxXD3leCfPdAXG9MN8w1PchjDkj81n77Ax7zCSZNebKMqu+DWVWP3cCO1Rm1V4Ldpks2bBOiHtKZp2/cYj7HnoWV2f3LCiz4jJlVj/zZAHr3MqstS2XWdfI4yDPesilBawTrE9mrdHbkMsUjOk907aAzBpzNYjbBGwnmVVDBdhZsiTrngN2n8xa95dhvkmZtXejz7ItILNqz5TFWecd4raHuFKZ3+qnLN66H0HcBbJYw5qh9jtkSdZ1AuJGofYpMO/Zdl8SZVYNQYhb7WzY12A7nQ0=
*/