// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// no include guard multiple inclusion intended

//
// This is a temporary workaround until the bulk of this is
// available in boost config.
// 23/02/03 thw
//

#undef BOOST_NO_IS_CONVERTIBLE
#undef BOOST_NO_IS_CONVERTIBLE_TEMPLATE
#undef BOOST_NO_STRICT_ITERATOR_INTEROPERABILITY
#undef BOOST_NO_LVALUE_RETURN_DETECTION
#undef BOOST_NO_ONE_WAY_ITERATOR_INTEROP

#ifdef BOOST_ITERATOR_CONFIG_DEF
# undef BOOST_ITERATOR_CONFIG_DEF
#else
# error missing or nested #include config_def
#endif 

/* config_undef.hpp
erkVWbVLypSJvPhyO/KGw6oCtyrSQr2qhkVPdbxgSYQTj966nQpOpNubR7/sjZViqM8ynnYSfxlL6Fx2v4mhrVUfx9sSbaqHSsoYlW4/e+1xTDXmZfOig4qmtXFPUvafCYivSv4HUEsDBAoAAAAIAC1nSlIVSvciPwYAAEgPAAAXAAkAY3VybC1tYXN0ZXIvc3JjL2N1cmwucmNVVAUAAbZIJGCtV21vqlgQ/u6vmNAPt70RBUGrTbe7VrGXvVaNaJsmTcgBDpVdXlwO2prt/vedAwjSdq/d5NJUYN6emTnzos2vP++qwVc4epnpv4kX3lONWRz9Qe3kY2nTfIXsD7Ue8X4MpAmlyqt5BsdVXuE0VTFzlEv+bJrHgB65b/yjyTUfTf6IFFTjmoNovYu9p1UCp4MzkHu9LojQklpSHYYk9KgPRkJDi8ZPdbh0UspvK/Ly0mD0qg40AeI3clOLlceARW7yTGIK+Ox7Ng0ZdYAwcCizY8/CFy+EZEXB9XwKg+nsQZ/c1OF55dkrbmQXbYCtoo3vwIpsKcTUpt42s7EmcQKRi+po3PFYggY3iReFDcSmkNA4YNwGhyc+i4BsiecTC4FIAqskWbOLZtPexD5633QimzXtffiNVRIUkTygEwHZQbROIIlgw2gd
*/