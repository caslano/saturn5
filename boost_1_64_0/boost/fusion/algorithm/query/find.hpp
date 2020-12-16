/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_05052005_1107)
#define FUSION_FIND_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find<Sequence, T>
              , detail::result_of_find_if<
                    Sequence,
                    is_same<
                        typename mpl::if_<
                            traits::is_associative<Sequence>
                          , key_of<mpl::_1>
                          , value_of<mpl::_1>
                        >::type
                      , T
                    >
                >
            >::type
        {};
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq)
    {
        typedef typename result_of::find<Sequence, T>::filter filter;
        return filter::call(seq);
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq)
    {
        typedef typename result_of::find<Sequence const, T>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find.hpp
Rz8kDpmDVCDbkQPI+8gppMstxCxBkm753577/n34/5WdvFsi/v8l4t+v/E71/0+Pn5aQkTA9LUXr41fSxXDhabBINyUhFV9qziIl6aWSLu6f+nRTpqclpEyPT1ITcvQg7WIcxlWutErBXMXKyM11zyngIqm+M6u1id1fuV78dAaFAlqvT/526/WjLdbTL4/lT5VFvrOVZfX+v0N93WK/5mqL/I50wp5W+QU4f+J1i9j7kTZ+9ioruwboa6/9zt6u5SFmX/sK7FppVc4A/O2emMqnbMpVI+e3apiOAMqWaW4z3vkvoeY6rIjFHsa8aS2BrB/fauFLPmKR132d+HO3Pq9A42VstWgrBTIXoATphRQiN1GuOENebod5dk6xH/mF6/IrXKT1c4hPkRN53/33beP5zhw34JjN3gV1Bv0CGRsONVLPMW3MbXiVMu/HkF8gcTw8544Wn/rI1tgaRsOblXkXmwzndrIGX+aLpDdWr/gHQjZ7Y/WHi492m8vvOlf1L+XBT911wVDs/s7p9bnMzSrJ4Vxuf4vTVRfzpM2oMcRdn0d490hwfY5R05eIT87zea6u3Iek3Hcj3ZANyK2KTTcbys1sE398Rh7f7ZELXX1H9ecmwq2Gcg6Q78Tvq/PZnJRGdV9r9IL3wjvwN1Xf696rv6RwWAYTQ7i2ZszLKiwq9Md/6vHPxKq+M6+PaoxGj466WOz50mfUePpF5hj7ucVFi3R+TfFbu/06zi2KzrSlzu7Pvzd8Lv+h/vNrhs/HvZ/1PlEL3/wape62anzzUn/+9AdPuzrShP0u1OtbO7NOtym+tm1GneRaE4AP9JWYwPXy2GprO7Nfdj16VW7z+GWbZqutnfyLc9KrvTn/O8i/Vs2/6XZ53YcOo6RPhYoP/Seiwx7krlj+3KfqoHRO6VC+xzjPvJONrrkcylYJ3r6dJ3po+1S0tk/pxqwCXOvea87aSPfv5HTq+Het63xLvHvCGOp6kpRztZSzj7SHXkgsfrx6Vznl4lKy0Ghwv2MnecaD2V1d41mOQ/K/WvJve55hHyHJP+z+xvNnZ4Zm6+AZPyvOM9tgI3ZNdutA7vGp04dlzIpPmsn1sozRy3c8GE+ed8h+EMY8Qzt6740i5N5oF2krrfJk1kBZAHtQaPM07wmkt39pR3NMnCqlr6l6pKbFT5iaMWOSqQo80XF86qVtb6c6mm29mfzq/civbJH/NtgUKzYwlLfqfOWvfg+QLaQN2+4zf0+T81sH+rppL5Axo3R7gehs0y/MrNtWzpHsh25lJXlN0kvah/QNZ2mxwV4Hwszt9D5+X+VbJ1erDaSvbIr13W49z1AjOlmPW3Wil2nECHAfF+whuuhjSG3vZO4v98fy5wHJ17ab+M5bW74u4eby5Y0mpW0+dI8AbP3dSOvy7Qo3t8EHlDZol28T9sjBtqZ+8atOun6hr+vOZp0eUtqgvU50h6bpI+2O+wTpD4Z6OSq6DEd6yr3Jw+hSZ6sLDwMB1ItOF9v93Oz1y+xi7q8LaDdhD4p+lt3U/zHtu5G++6jnHmpzV/Hzt5Z7TfiI0pYeVOeS6W6iFB3yfDwnVlbr93Rzmu8rRR/sLu0rUbVrTiGPQTklqh31cxNlXp3YltssJfky9z1VlOGZMd2hzueXZyXP79w/itCNtXJ/JvmO1d2P6W1WHSFrGlqRFh6Gis3iHjbYjBUDzL7zaTNl7t1bj7httihnkWI2S7uN8NNurnvTJthCsfUOC1vENGKLOZH84cDN4egDH4JpfFe93miL8gwelly2WOej/Xx9h/49Q5U6N5N+IDpttXheqtY+L8l3uyzmcNZ49yXLmi923K9+lzWvIKukxJO2Fjo=
*/