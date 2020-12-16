/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_09162005_0343)
#define FUSION_FRONT_09162005_0343

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct front
            : result_of::deref<typename result_of::begin<Sequence>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }
}}

#endif

/* front.hpp
bNzNt9sLQhPYfoo2Xa/Kys3QTDyTrVlr3S7YTGufmF9t0Lnj06ROgQEj327B9KG2B58/+PU3bc/rhN8zsjA3s1xrTth/IetBUfatStmZ32IuZClmHsIOdb7TK47JtJ8P/IbOP5CgKUpzmMhFPmDoT3PL0AwoD26YQOhCe5n08ykiJwHD7iCKYzevykF1Siv4wqzirCKnS+TkhuvmWcvPW0ZR7Fpv7u3QFgsrbTEhd5bnl9YW2tp4+RyRA20KDZq4pj7sYPLR9hLKeLn5G7o+OX7L9MIWyFmE6iyxDiK2ktDTaFRJ3mdh40/HbhjBiIEIgw+tU7mGkj47QWRZUC8HjkV5vT7AryjF5BhCp9O/rcxvqZc5ZuDIgbgM1TheHY3MNicoVjND6nSRyGoZVpB5rhfAmFxdWYcaPnBoGgMnPDEOKjr5YdiC64Hkoe0EoTY6faVP/06RA9/cDWDXlnm50EdWCEXNLUEoeGi8CXXPlv+usjYHVpLFeSTbqFzBWI06PWhlZQdoKHvaD6tyHM8IMzsKXCd9VDmvFGuAKseCvV8et3InNI1l6Mz8rRdYi6tZviJOCt5bhNc1PN9z0gQa2QGLjzZ7FxHdDWx0KmvhfeAle2k/d9LYN41T6jyJ/QzWnraaUw3ljP9ebQcHbM08r+XbxknPPjH58le84jib5Xora6vzYrqESafX5gu9gWPyjCrHYj6zoRPBpGt026vnO33QpuBkVhSwKHZWIGc5jklLfBMiI4Z507J9108h+RnrVA8SIeeYSn2iDGzR3NQ32CW62tF7bPZd7pxfO88nwfNz64qcO7+nY9qPA69lwz/muuybFkXz1Z3/F26nydlp9A9UThoGnmWaEV3PUDkchcwRXP1OU0ROZiRR5kWmH1A5rM9iB5ZC1bmcyHEML8tD33b8h8rpvWe5r8zBn1blWBELNuZlkeOxvbWYXQr+om2Ip+LyS8Xcoso4nsERJY7NzMgL5nhlpVviO7gPJrp7oLuZejFs7Kfh7QRUtE68XD/Olr0fKqPM/Xerc6Md5NBLiBysPh7U2ITH8hTRuf8u7bMezEa+lZr1slwbRhW8eb5LjEMD57W7tG4+HGltJ7fq5JAzXJE5SdbtApETGJFpe5ASsKXI4RrQWRZ6L/vo7BMPCVlXKu0UpVHm2E6lveeWQU6hErRzfuL4y6eOnph8dwe+IVuPcK4j7WQbVmSGbhjB5gYe48oeRjdD0CSvFXPd3cr+1EzdNElsw2W+IlCFMhFbVcIU7o3/SOdZ2/Ty2Id5JcgbmfH7Et7MyHLPyXPTNlKY3wt8B7bikw6odGJyJp6Gtbm8ze1ROaeJnMSww7zlukEKmynaZ1k/47v8d7fnxJWOvNOpyHFTM7atoAWV2pCcz/2R7n/iyMxgDxWCHNK9yohZvJvBRz3PZCrzyU0iJzRgEGcRm28D3lfr75f6fO+D/Xb0T3TfH/gtOCqHgRHwbSARU74jKbMKGZNTqiwH7r1cv5XnGXx4VcbM6txyrzAGnIeGgux1a51y7jawrf9E95lJKwgcL3bFngW339B/a5YkA9v6T7StkzxLgyhPYM59Ynnl3csPaSNDvS9/btXmgFuj8MwOAzi3/pz4XIZp1gpDaFdmYQySYb9NY0feVfGpkcEeP2rlsTF94nASJNBHC78syjPwC3IPACxWkoNfZ8abZRq6EfftxLuDUZUnN2DtyZIwCwwWtK/YanRXIAoBftNBUdYhlS+FXhqGZhY6gg++XlskqTYEz5TKExu2BxOOnTnGDBulquMptDHmRyV3nTBOo9AJwmjDbxzM9vwLr4A59OMyzrUwsGG0y0C7XtD6cCcAG5A5sLTm+U+/CLQ=
*/