/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    using.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_USING_HPP
#define BOOST_HOF_GUARD_USING_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_TEMPLATE_ALIAS
#define BOOST_HOF_USING(name, ...) using name = __VA_ARGS__
#define BOOST_HOF_USING_TYPENAME(name, ...) using name = typename __VA_ARGS__
#else
#define BOOST_HOF_USING(name, ...) struct name : std::enable_if<true, __VA_ARGS__>::type {}
#define BOOST_HOF_USING_TYPENAME(name, ...) struct name : __VA_ARGS__ {}
#endif

#endif

/* using.hpp
/nau0zSQ1g6xaaKTXonui79JHLB4VdBJPNP1GvuGROGMflPA/mC/b74Fi0juwML+aLfU36IvKuDHVsb6PNQwhqGHb71Wkn4AMrpujPCpnoRSR/XEaZbHW12KKH7k+VJxbedRfWRRZDpu9GONRiifDlByma3154XyVOHjSC8jubpZ5k+DtlHSwJk6sXVzrx92sCmGRSnxVHTFsKb6vllXff3UPtwdiRjd7kUnDmMSmGpbDZDf44+HT1dKi2L0wTeaV43aKPSO0WDSC83f2O9IHIjiSXJdUWzuQ6wUVfZNxbTlfiw0n3tqsmSjLsSxrjwLjittV9CNTB8lBzuOh9rRdI2GJPnXR6/aLDprpc878FiZRfhahif7meFayoiLCooUPgO+/EWZZCLHrpwvVe9qxE09DLcIVgr4iqevIxmv8GFLAQwhKeiFDzBkJbmk91B868RH7Xy5961YTEfoqqebHJ9Gu7naS2W6d2gK7fNeSHvJ26WoXTHt4m52n6ljBe7Quv5WWtf/Cq2P30rr41totT2eDku/yXfO0OEp/Jb1HMLQ7fvdhnZppwNqA9h7ztq8nl20nPzAwxfPv1nH6TBdrFf49daxL5W2r54sSLxRU4fV2BOPfVeuVaT3kxD+AlBLAwQKAAAACAAtZ0pS
*/