/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403

#include <boost/mpl/if.hpp>
#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/continuous_interval.hpp>
#include <boost/icl/discrete_interval.hpp>
#include <boost/icl/right_open_interval.hpp>
#include <boost/icl/left_open_interval.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/icl/open_interval.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{

    template <class DomainT, ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)> 
    struct interval_type_default
    {
#ifdef BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
        typedef
            typename mpl::if_< is_discrete<DomainT>
#  ifdef BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT<DomainT,Compare>
#  else
                             , right_open_interval<DomainT,Compare>
#  endif

#  ifdef BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT<DomainT,Compare> 
#  else
                             , right_open_interval<DomainT,Compare>
#  endif
                             >::type type;
#else
        typedef
            typename mpl::if_< is_discrete<DomainT>
                             ,   discrete_interval<DomainT,Compare>
                             , continuous_interval<DomainT,Compare> >::type type;
#endif
    };

}} // namespace boost icl

#endif



/* interval_type_default.hpp
rLHyzfKglPkcOlr+rLwcs8bJf+23C7OO8f3cbxdmjff93G8XZh3r+7nvt5h1nO/nvt9i1gTfzy/X7cWsib6fy5sx63jfz+XbMesE38/luzHrRN/P5bGevH6mSb6fywdi1km+n8vHY9bJvp/LazHrk76fy+djVrXv5/JlmHWK7+fytZh1qu/nfnsx6zTfz+UtmDXZ93P5LsyK+34uD/Xi9S2d7vu5vBSzPuX7ubwKs2p8P5dPwqxP+34ur8esM/w4L1+KWWf6cd7vX8ya4sd5+UbMOsuP8/K/dtrKZa2z/fivy+/ArFo//svze3N8pnP8+O/3O2ad68d/+UTMmurHf3kdlsgfF/ImzJrmjwu/3zHrPH9cyFdh1nR/XPh2wKx6f1xckfQtmDXDHxfyVsw63x8X8j1YUZ+S2AX+uJCXY5U00x8X8lFYNc3ScWCwvB5roNny4fImbAnNkY+Rr8DWUYP8OHkLtp0ulH9SvgvbS3PlNfLiMu4Xmic/Rz4eq6FG+fnyzbcXx6yL5PPkq24ujlkXyxfKG1lHE10iv1a+7CvdYtZ8PODrz7tzWetSPIevb/L1Y+vpMjzC17fIt2OttADnf6Fb5TuwnbRQl7/NtwO2my7Ho3y9Ur4Xy+/L/L+uzx2+fbA+dKX8LnklNpqa5PfIJ2E1dJX8Pnkd1kBXy78pX4gtomvk35YvxaxF8ofky7HVdK22z8Py9VgzLdZ2bvb9GWuh6/BCvn7Ktw+2i5bIfybfNrVbzPpsOOvzcS5b3I/5f22353X54Zh1va5nq3wsNomW6vrs8P0cs27Q4+L38vnYMvq8/B35Osy6Uf6hfBNmLdP1yblStxfbQV+Q58uDcu5HukneQT4cG083yztd+fHtsDxrO8zksgvpi9r+XXT5pZj1JX9/JF+JWbf4+yP5Rsxa4e+P5C2Ydas/b8pbMes2f96Ut2HW7f68KQ/tx/MRrfTnTXkMs77sz5vycsz6ij9vyqsw6w5/3pSPxaxVuv5T5ZOxWrrTjxvy+dgS+qofN+SjPuweW4Hf5ccN+RpsA63244Z8M7aN7pZ/Xr4T20Nfk98iX8j68/dn/l++Sl6KDaQ18nv9+mAT6V75t+Q1WD19Xf6wvJn1z8fvk2+SL8FW0Fr5j/12YRvofvkv/HZhrfQN7Ycvyvdixf2Z/9d2fsnvF6ya1slfkzdiy+gBeZt8LWZ9S8fJ9+TrMevb+r175Bswa73W84Hvt5j1oPaHSJMej5j1Hd2uQvl2zHpI3k2+B7M2yPvIiyp4PqXvygfI+2DW93S8OlhehVkPy0fJqzFro3ycvBazHpFPkjdg1vflp8sXYtaj8lr5Esxqlp8vX4ZZP5A3yldj1mPyK+QbMOtx+RLfnlgi+U2+PTHrCflKeRtmPSn/mm/PAWxP+qF8nbwCszbLv+fbE7Oekm+ST8Qm0Y/kz8gnY9bT8m2+PbH5tEX+knzviB4x68fyXb49uaz1jPxd+UrM+ok8dJX2Z8xqSTjJ12PWs/JieTNm/VTeV74Zs34mHyjfiiWSD5Pvwqyfy0fL92LWL+THyWMHcLylX8qr5RWYtU1+hnwUZv1KXievxqxfy2fLp2DWc/L58pmYtV1+tbwJs56XL5Uvx6wX5F+Sr8KsF+Wr5Bsxq1X+dd+emPUb+Xrfnpj1kvz78lbMelm+Wd6GWTvkP5UHB/L+ml6Rb5eXYtZv5b+VV2HWq/I2+VjM2il/37cnZr0mD67W8xdm/U7eSb4Ms16Xl8rXYtYu+f7yjZj1e3mlfBtmvSEfId+JWX+Qj5Xvwaw2+QlyJk9i1pvyyfJKzHpL/hn5RMx6W14vr8Ws3fK58gbMeke+0LcPZr0rX+w=
*/