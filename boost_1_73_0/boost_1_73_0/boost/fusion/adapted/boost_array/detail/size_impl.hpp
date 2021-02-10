/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SIZE_IMPL_27122005_1251)
#define BOOST_FUSION_SIZE_IMPL_27122005_1251

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct size_impl;

        template<>
        struct size_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::int_<Sequence::static_size> {};
        };
    }
}}

#endif

/* size_impl.hpp
ErFDhY78Y4eVrObxIgkT7xdR57IrOL20xns2Vq89ZydX2P/Wpz17Qo8q8ESCLvf6A2JWrKVHoKHZ/90ZfDtLpstwkYbx3FswFIMNMuCrErUR9SfrK6O6k/LAskbUzBbf0gBnlZKFkwGNLKylVB+q932kVmiIFjyva0zQ6850ypsOP2tOelsbhsOcSbn1ctWixc2YwH2ogWbGUVfV3HJno0DN3maf3cE35JpjHDhv1yiAktD1PQ8N+6uUIDs6yukW3GAAIPS16swOSfZW6n6SIJsvPO/+4aC1PBiq68aD57mu6TliewbSLa+N3NpE2LbB02XFa1dDK7DuhNwND4obXidJhCThjfg8iQhan8LSDT7bh522KWdoxrLkFpqswprlnzlislI5GtO0W2TAuBLuOHY7TdpmpYdyQ2BgDKAGvmRRmKRDHL6NCvOqQZ/mzEVWKEDUyvRDGN5/5rxxUAM3WKswcIiVxpocPLHp9HaYPQNPgvMo9ebnUTR2GQDteFszicKUrJPGiS2WcRpP4yjxAhTPxoOBg2w2rTIKtdUv6DRNF+D4ifsNzwK7LOLFMZbkDJu4k/Le5uxjcLaIZp5fl17fN64Ur251laiF2UOTiHLPbu7T3x5933R246bZsIxptCMJv2KYatzP1WYy
*/