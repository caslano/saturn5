/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_ITERATOR_FWD)
#define FUSION_ZIP_VIEW_ITERATOR_FWD

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>

namespace boost { namespace fusion {

    template<
        typename IteratorSequence, 
        typename Traversal = typename detail::strictest_traversal<IteratorSequence>::type>
    struct zip_view_iterator;

}}

#endif

/* zip_view_iterator_fwd.hpp
/xd9EBYx99wUMi+YjbDotV94PX+YhbCg4C+tyAJh1sKmjx93lSxYsUE7vZy4dpijsO1VKliSxcCoBgtYYCeTmWSpsEo/zQp2OtvtM/cB5vfTrGF/Nxk3met7V2g2sJbDvY6QhcJoTluYe9yBV2QJMLoX2MHmHRk6mPcCcxPmWLQ+9z0T5iTsi0vxbbxPmK+wRq47A3mf79EHYT4JmTynP0wn7Pri9K1kQYp96/H0MGetWHP3eb04a5i1sIcd1pcgi4fRd6L+b5WTH3bkXGDFhC3cFVGGz65i9U9+XkeWBDMX6x2N31mT84RZCctKOaIjS1fmzAxofoizhtF3m3SwsfcnnuT1PvJZyre3gzJ3kmXDaJy9Mi71E4/Lt8bn7M9y/2DUPxfYibkn33D/PhfOWUKZM/cLz5lvn8ZM/Xn9pZj5fzXVkn+O05ukmMXuSnEm8/vOfcg32/oLbpMFfOfnlXx7WPLkJ7JQWEVh8ZOsl5IlwNyEfQkbfJIsFaYXtuNxhA1ZprJepTV2p8hyYSWElatUwZdM96Pwc0U32I2/P64iC4JZFhoy23+Ra1BswKPbbmThMBthEft2PSOLgZkLG/9i0HiyeMUG5K3gPP/4wd+JyrfIEMNLskSYhRjXOLTeG7J1sKJi3NWEXw6QbYEVE/YuvE5Nsl3KuPY35jUhS4c5ivViXzx6QZal1PBJZ+BccpR9rnSyXUeWp4wbo9vQkcxcM9Oq/DR3WMt6NS6QBcLofYAH7J8i7c6SGWBawdnNt78mze9OlmxiptUU41y8DY14nzBLYf5J8/vwPmGNhDkOfMhnoqmpGX2/Lt/a1u/1nCwI5iPGrWxuu50sDtYm3wr2WbdFy/5k2TALMW5d1+LNyXJhbcW4cHwZgCzYzEwzF+M8V47gcWGw6sJ+RGkOZEmwqsK2hZg14N7CKgtzXzL9DzJdEeP1nOOyQ8m8YNbCegdkRZL5w+ha8YRVaHnpNPcW5izsj959qnMNyrgWy7xdue/KuKxFd5uRJcCshEWsH7eEa1fmLDp9eRmyVJirsMTi7YeRZcKshQ37Z2N77h9MJ6xU6LN0PkuwEsLWeq+yINMXNdNshb2cc2cbmQ/MQdj07S+ecGaKmfXXtSYLhdkL27jxU0fODCb3OfjVrdtk8YodOeFXjjODuQmbEL7UnCwdJvuQ8qq6I+eizHnr4md7zgUm8/y+49YeMvNixuMWPZ01lMwL5ihs9sQ2J8kCYHphOfOa/c65wGQfFn6pnUoWA3MXtnNV+9VcO0yepZWranKPUmEyl9IbPI6TZcJkb+8N91rGuSjj9IZFsWRaceNxVodf8no6mMzF06wzX9M+MBdhyxwD+pMFwWTtMYknPpKFK+tZPGsSyLko61V46X6KLAEm+552N6IT56KsV/G66UPOBWYnrPKmA9XIcmCuMrOTi++QmZsb9929e1Ou3QvmJKyX7cnC1ygwuZfltTdVJguFycwan7lrx7XDPIQ1enOOxyXBrIU9Si3Zn2uHyTyHrEttRJaurLcuaiw/P2TDSsoaPrRxJ9MsjM/LFl+H/Vw7TPZhkbUnXyuBMDnn9/JhN8nClDnXthq4jywOJmuo771mMffdQrmOPBq959phsg+fr/zjRpYBs5fnJbttSa4dJntrs3cR7zNPsSPzTXuS6SyNz1JK8cu7yXxgOmFfOnRrzrnArGRmutAVZMGWSg1bNkaShcMshPW9ndCMLAYm6/u22/ItZwazEeZ34fpKsiSlhoeuLe6TpcFkbw2/j9GRZSn2Pnn2Ac4M5iVs2y/3NDIvK+N75LgB0f5k9WH0c/OlYO9bPSzGmSk21XfFY7KmsKLCAmYOmc95WvFrhnw=
*/