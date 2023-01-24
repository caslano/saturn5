/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0940)
#define BOOST_FUSION_CLEAR_10172012_0940

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/std_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail
{
  template <typename Tag>
  struct clear;

  template <>
  struct clear<std_tuple_tag> : mpl::identity<std::tuple<> > {};

}}}

#endif

/* clear.hpp
B0afwoHqUE85kv9g/rXd/GtdTxp4HnLiODTSST+H0c/BdMniuy766aTL9XTp4US0tyu4TAJfO9BtB/+0U+Fm/PNsaj0+qODaZX9DxQyseybftVPdiOLkGTSwwTmwHhv+4WUKSt4nlykoeZVDZaDr0+6moeR9ekGDEIJ91WpuUqv54C5ZTdsmVnMzVVMaTqSNSxXStZcqpD8dKEkvcTWN9O8diTQkXBOkfSrpcpX0rAGS9L1NJD0FSXvuDYAQLO7YFAjBZj/HmE5csSaEIAnstSkoOd3pkkiXC1Pq9/kFmdn9WuMyc6pDwzLTLgSb5fFLlGZ58hKlWa4wO/OWm5vWLE91IJnxKDLzIHWsrlbTSq0mfLCs5uebmlZNa6oGA8wF6S8TFNILEhTSLbIk6dImkq44n0hHE+k7VdJDVdLPZErSXZtI+m4mXUHiePZihbRNJZ1/qyS9Lb1ppEOQtCc3QBz/ad8UcXyiumFxfP9aFMCZdHmdLlPp4r02CBPDzASe/oo5WZ+GYzwjY4h1bDslYqRbayViJD4Mz0kXfY7npEUUMfLyczJi5N04M2JkZ1szYuTLf+046c7FmTh8cov2NPnPtSb/uU4ZkbXIxlP9xbRC1ouX2Mw5fzOg4aEtQhjoPlY3iAs12kaiKQCd/PsdX52HcA3NgJk8HjzpGbrS7cSgLJzbj7LhXCSv4B49lqhBx6diumHEQYaeB1/Z
*/