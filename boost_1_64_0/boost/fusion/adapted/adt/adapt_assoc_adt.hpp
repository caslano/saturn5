/*=============================================================================
    Copyright (c) 2001-2009 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2010-2011 Christopher Schmidt
    Copyright (c) 2013-2014 Damien Buhl

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_HPP
#define BOOST_FUSION_ADAPTED_ADT_ADAPT_ASSOC_ADT_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/control/if.hpp>

#include <boost/fusion/adapted/struct/detail/extension.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_base.hpp>
#include <boost/fusion/adapted/struct/detail/at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/is_view_impl.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>
#include <boost/fusion/adapted/struct/detail/is_sequence_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_at_impl.hpp>
#include <boost/fusion/adapted/struct/detail/category_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/size_impl.hpp>
#include <boost/fusion/adapted/struct/detail/begin_impl.hpp>
#include <boost/fusion/adapted/struct/detail/end_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_impl.hpp>
#include <boost/fusion/adapted/struct/detail/deref_data_impl.hpp>
#include <boost/fusion/adapted/struct/detail/key_of_impl.hpp>
#include <boost/fusion/adapted/struct/detail/value_of_data_impl.hpp>
#include <boost/fusion/adapted/adt/detail/extension.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base.hpp>
#include <boost/fusion/adapted/adt/detail/adapt_base_assoc_attr_filler.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_ADT_C(                                         \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, IS_VIEW, I, ATTRIBUTE)                       \
                                                                                \
        BOOST_FUSION_ADAPT_ADT_C_BASE(                                          \
            TEMPLATE_PARAMS_SEQ,                                                \
            NAME_SEQ,                                                           \
            I,                                                                  \
            BOOST_PP_IIF(IS_VIEW, BOOST_FUSION_PROXY_PREFIX, BOOST_PP_EMPTY),   \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR(ATTRIBUTE),                      \
            BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE),                 \
            BOOST_PP_LESS(                                                      \
                BOOST_FUSION_ADAPT_ADT_WRAPPEDATTR_SIZE(ATTRIBUTE), 5))         \
                                                                                \
    template<                                                                   \
        BOOST_FUSION_ADAPT_STRUCT_UNPACK_TEMPLATE_PARAMS(TEMPLATE_PARAMS_SEQ)   \
    >                                                                           \
    struct struct_assoc_key<BOOST_FUSION_ADAPT_STRUCT_UNPACK_NAME(NAME_SEQ), I> \
    {                                                                           \
        typedef BOOST_FUSION_ADAPT_ASSOC_ADT_WRAPPEDATTR_GET_KEY(ATTRIBUTE) type;\
    };

#define BOOST_FUSION_ADAPT_ASSOC_TPL_ADT(                                       \
    TEMPLATE_PARAMS_SEQ, NAME_SEQ, ATTRIBUTES)                                  \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (1)TEMPLATE_PARAMS_SEQ,                                                 \
        (1)NAME_SEQ,                                                            \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#define BOOST_FUSION_ADAPT_ASSOC_ADT(NAME, ATTRIBUTES)                          \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        0,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#define BOOST_FUSION_ADAPT_ASSOC_ADT_AS_VIEW(NAME, ATTRIBUTES)                  \
    BOOST_FUSION_ADAPT_STRUCT_BASE(                                             \
        (0),                                                                    \
        (0)(NAME),                                                              \
        assoc_struct_tag,                                                       \
        1,                                                                      \
        BOOST_PP_CAT(                                                           \
            BOOST_FUSION_ADAPT_ASSOC_ADT_FILLER_0(0,0,0,0,0)ATTRIBUTES,_END),   \
        BOOST_FUSION_ADAPT_ASSOC_ADT_C)

#endif

/* adapt_assoc_adt.hpp
iPkgJmFMopgPYz6KSRyTJObjmKQxn8R8GvNZzOcxX/yfsasAbyPHwjm+G8EcMzNfk8J2j9MkbXPbJtkk7bZHPsd2Um8d22vZhT1mZmZmZmZmZmZm5vs90uiJJnvf18Z6/xM8PT09wWg02TWza2XXzq6TXTe7Xnb97AbZDbMbZTfObpLdNLtZdvPsFtkts1tl27LJbCrbnu3Idma7sjOy3dmZ2a2z22S3zW6X3T67Q3bHbDrbk81ks9lctjfbl+3P5rM7ZWdlB7KD2UK2mC1lZ2fL2Uq2mh3KDmfnZEeyo9mds7tkd83ult09q2X3yOrZWtbImlkrW882smNZOzs3O551ss2sm/WyfnZeNshUNsxG2YnsZHYqO52dn90zu1d27+w+2X2z+2X3zx6QPTB7UPbg7CHZQ7OHZQ/PHpE9MntU9ujsMdljs8dlj8+ekD0xe1L25Owp2VOzp2VPz56RPTN7Vvbs7DnZc7PnZc/PXpC9MHtR9uLsJdlLs5dlL89ekb0ye1X26uw12Wuz12Wvz96QvTF7U/bm7C3ZW7O3ZW/P3pG9M3tX9u7sPdl7s/dl788+kH0w+1D24ewj2Uezj2Ufzz6RfTL7VPbp7DPZZ7PPZZ/PvpB9MftS9uXsK9lXs69lX8++kX0z+1b27ew72Xez72Xfz36Q/TD7Ufbj7CfZT7OfZT/PfpH9MvtV9uvsN9lvs99lv8/+kP0x+1P25+wv2V+zv2V/z/6R/TP7V/bv7D/Zf7HVeyF2YXYRdlF2MXZxdgl2SXYpljHGOBNMspxdml2GXZZdjl2eXYFdkV2JXZldhV2VXY1dnV2DXZNdi12bXYddl12PXZ/dgN2Q3YjdmN2E3ZTdjN2c3YLdkt2KbWOTbIptZzvYTraLncF2szPZrdlt2G3Z7djt2R3YHdk028Nm2CybY3vZPrafzbM7sbPYAXaQLbBFtsTOZstsha2yQ+wwO4cdYUfZndld2F3Z3djdWY3dg9XZGmuwJmuxdbbBjrE2O5cdZx22ybqsx/rsPDZgig3ZiJ1gJ9kpdpqdz+7J7sXuze7D7svux+7PHsAeyB7EHswewh7KHsYezh7BHskexR7NHsMeyx7HHs+ewJ7InsSezJ7Cnsqexp7OnsGeyZ7Fns2ew57Lnseez17AXshexF7MXsJeyl7GXs5ewV7JXsVezV7DXstex17P3sDeyN7E3szewt7K3sbezt7B3snexd7N3sPey97H3s8+wD7IPsQ+zD7CPso+xj7OPsE+yT7FPs0+wz7LPsc+z77Avsi+xL7MvsK+yr7Gvs6+wb7JvsW+zb7Dvsu+x77PfsB+yH7Efsx+wn7KfsZ+zn7Bfsl+xX7NfsN+y37Hfs/+wP7I/sT+zP7C/sr+xv7O/sH+yf7F/s3+w/6Ljf4L8Qvzi/CL8ovxi/NL8EvyS/GMM8654JLn/NL8Mvyy/HL88vwK/Ir8SvzK/Cr8qvxq/Or8Gvya/Fr82vw6/Lr8evz6/Ab8hvxG/Mb8Jvym/Gb85vwW/Jb8Vnwbn+RTfDvfwXfyXfwMvpufyW/Nb8Nvy2/Hb8/vwO/Ip/kePsNn+Rzfy/fx/Xye34mfxQ/wg3yBL/IlfjZf5it8lR/ih/k5/Ag/yu/M78Lvyu/G785r/B68ztd4gzd5i6/zDX6Mt/m5/Djv8E3e5T3e5+fxAVd8yEf8BD/JT/HT/Hx+T34vfm9+H35ffj9+f/4A/kD+IP5g/hD+UP4w/nD+CP5I/ij+aP4Y/lj+OP54/gT+RP4k/mT+FP5U/jT+dP4M/kz+LP5s/hz+XP48/nz+Av5C/iL+Yv4S/lL+Mv5y/gr+Sv4q/mr+Gv5a/jr+ev4G/kb+Jv4=
*/