// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_PARAMETERS_HPP
#define BOOST_CONVERT_PARAMETERS_HPP

#include <boost/parameter/name.hpp>

namespace boost { namespace cnv
{
    enum class   adjust { left, right, center };
    enum class     base { bin =2, oct =8, dec =10, hex =16 };
    enum class notation { fixed, scientific };

    namespace parameter
    {
        BOOST_PARAMETER_NAME((   adjust, type)    adjust)
        BOOST_PARAMETER_NAME((     base, type)      base)
        BOOST_PARAMETER_NAME((     fill, type)      fill)
        BOOST_PARAMETER_NAME((   locale, type)    locale)
        BOOST_PARAMETER_NAME(( notation, type)  notation)
        BOOST_PARAMETER_NAME((precision, type) precision)
        BOOST_PARAMETER_NAME((   skipws, type)    skipws)
        BOOST_PARAMETER_NAME((uppercase, type) uppercase)
        BOOST_PARAMETER_NAME((    width, type)     width)
    }
}}

#endif // BOOST_CONVERT_PARAMETERS_HPP

/* parameters.hpp
ja40KKh6RDCVBdrR3N6ejG+OLsgb0KvMHvdY/qdNkNIpvVxpocSvWcB8poS70wzge1pMb7pryZP08ien6O2b3zJeb1y5TL+59Dm9duk8vXbxMxa+xnDhM3r180/p1fPn6Feff0KvfPYJ/ercR/TKp2foZQhfQsA4N658QS+cOkGfmzGV5oaBDunpwmgWIt2erec/D/gvAn7FoRDqPDuoDVUN6EifX/wE/fbyBXr7u+v0+peXGI/fXOR4/gZ4/+aLz+l1DJf5vxDM5bqA5TkHZTlLr5z7mCsD1MGljz+klz46yd6/g3o4umcLVQ3yB77dgH8fmtfTmVb9h/wrgPesboQ+IRtNz71/nP4L+EZ+r35+ltUb45vnF+XjW6hHJiNffQmy8yWTH/y+ceUSlPsivX4Jz55Dm0A5voK2MJcB+L946gNog/dYnLf2bqZ5vdvRgghPmtfjP+Mf610eZE/nFyYzHr4FHr6Curt6geMd6/s6yjTAv//6Kyb3P9+9w87M//Yrd3b+15/v0fv3fqK//HSX/vzjj+xOgZ/+dZv+8O03UOYL0BZYho+4MpzBMrzHynAD+swzpRms3af8B/yj3E0OdaYViQMYnetfnIf6+pjJMsrBN19cgDJdgv76Lb3/8y+MT5Trtw/sontXzKX1NWqgn0kXKpLogoIkOh/CMyUZdD3A/7m2DvTSfnoT+vuPt26x/LEdvmBl+IBe
*/