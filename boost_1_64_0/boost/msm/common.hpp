// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_H
#define BOOST_MSM_COMMON_H

namespace boost { namespace msm
{
// wrapper for mpl::for_each as showed in the C++ Template Metaprogramming ch. 9
template <class T>
struct wrap{};

// tag to use in grammars where states are seen (init_<<, states_<<...)
struct state_tag{};

} } // boost::msm
#endif //BOOST_MSM_COMMON_H


/* common.hpp
MGWdGY9D7rc38Uv3QmKZfq+PkbB8zn38F8bcN+lk9WP0/XLEZ+tpnxFEHPeH/e6jrX7VOcdSHpN59ynUjuKo4xBtGLc/a7VMzXqpM421tzoHF8dF10dWiHueZg+Nl7v+brsx9/ZrZ/cH9IfHEfeFm9/jnFs8xsRwkhYxCnKzTbxWxHH6Zn3f4hqB7Yz2+x8A/bDf+j3N7fuu194hdVHvAZ/jzTru3qOcHoosuB4T0Zcz6rpT3YP+ayV9ilhr86THnh73DmfE80jzOSOskPB6w+ur+mb+VOPI7yAEv2dQkOdt+nfF/fSr3eLm/SnxLL5MfhvDe0lToPr5hHuMOQb+xfZQ+NKmEF65yfHC1pB0b9PuL9p/3bE15N6y2f+VbghdFK4z/n64w/2O5bG/05bP+l+f2BcToTzn+7zfdgy6si0ULtjqnJgvbHVuuil0HxkLhS3b/E94PJTi7nnxm+2h+0y6N/tuxTr3394eKn8yZptl3LctlH66JYSvJdzffFvo/uY638dXv8s2++3O9SG27B4Gfe6def4239XfGrp9R7BeD7a/OdR/bayfm/Adrw3uS2GdUx3DKiem3/rGEiF92KaQuykWcq9a53ev1KcuFiu+B/vqre55timUI9tC9dvxkH1kW6g/zfr3yN0p27xbrj1Nzm+Lh6TvgfX5rdzM9xIh9/2tPq9t3hfJce45iRB7IBaSvu+Q+fl2/2e5MZTkRvl6+fnQdve6a/4/kvq3ef0J631L3Y7gaHU6VhntO0LfZzaE9J/1S/P+BadvDekHxUW9k47nsupeXfHZh/gUPE/ftz30nbHBfYHU8dp4KL/JPWp/tcn3KqxTTjgv2eCcTL7evSM8dM+OUF/cETKW7xvYEHKPrwvhjeu0wTHSO7aHknvzZdzrsN4eC7Gd60P1BvPMHQf5fvbm0G2dqvr31fVLTH9/Ybt7KZoTzlofkupQOGd9qNt+7sRNPpPfELqvs83fY9nuJ7eFDcqv/te9Ur6yLWRP1ZYRffbh9SH9s+2hfFvCb9Z5/K64i2X9/ea+BfuzCWP8cvf1v1vZv98Rku/bHPr0QfqHiRDkVtev5foj2/1uxyb3qBffYY/nbQpdW/XL6druO6IF96oPvs/Zd5HY/lzdL9wS+tzjo882MuNrHFOpS8r5zOcPss84wLmO/2O6Vb17nGvdYjxetM05gj5vi4WSe6WXLjGnn3GQ+7h7b0Z/nGIb1o/doF63W85YyT7hvVn3kHX8XHDNpOtryr1YH/mf1ez6zX7LokVuKfce/fzwdnnivbsSoZDfrE22+ahyLtvmO8LrQ9fshhBzv/PygvYdLke2aNv5m0KfcVe4Vr0/sT50J2PuB74ulP0Pa9dV6vIry8r/Ln3V9eN1oaqMst9u7rreuazfXy5Pim38AOV4/dWb/v8ZTE79q8ZL/UyvN8dEvzaqQ67NGDJ+qtPr/EbaulDaoO8vl3ufMe4fsK9+p/sWrZHT/9BHb7PMEfHQ1ayHbSd/aqw9KRbP2xFiZ2qTPuz+1saQLrtniHt4VJq/+aoeyResC7FDxN/fLio65pN7+rP6unUhd8A69yeR8+eZQz5tLvmLMq2buV2e2F7ol3dl+4ResT38YP3mf6bu1de/NL+IV/KQTaFirCTlQe57+l1u9hmX2R+bU27WTrmVvNLf35DLF2tLh3Kf6Xd4nPvV/yN/frQlZF4oxk/aLz/uGOgL6vERufvCdaEvHlN3/4um/tnvr3fvzvWhYp4qXLItlI9Sr7TXzR1dS5tDZt4Y79IfL9OH5vnMoxtD5TXmJPcpydXMY85VYhTWqcPJm0Pp9TzPnHq7erju3H2K9q43Lt9g/ntYW+wvyk8=
*/