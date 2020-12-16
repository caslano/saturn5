# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_REMOVE_PARENS_HPP
#define BOOST_PREPROCESSOR_REMOVE_PARENS_HPP

#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define BOOST_PP_REMOVE_PARENS(param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_PP_REMOVE_PARENS_DO, \
      BOOST_PP_IDENTITY \
      ) \
    (param)() \
/**/

#define BOOST_PP_REMOVE_PARENS_DO(param) \
  BOOST_PP_IDENTITY(BOOST_PP_TUPLE_ENUM(param)) \
/**/

#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_REMOVE_PARENS_HPP */

/* remove_parens.hpp
608vzF0VuCZwHeAGwK2BexTFPblU9yjc34b7z67OXo/Lcte9YVH86ra4J/4+w/srof08z9fx/CLPLwFfBb4JfAf4HvAD4OvAt4DvAt8Hfgg0CGdhfaNr+y5GXEYnKavXAx8HfgQUhPtk4FrQv4nPXwC3vJLFe/d9cP8I2bm3+g/pLR2h99/Djsc1YrniSLt345of9USbqQDen0o4MnshRfv4Ymt1pFhnoOvbWr1CBsBVmYmWV/TZXG0eDfxnaa6dYTu/WlICmdtYennbFWmGFO/tuLMyomjF0Z4Nd8XA0ZEjw+ri9Na+qzGkFhbt3ceUFK9tP45NVTyhH/g4FfHWrn3MinjauIW/JeqilzSwNB7afc2dQFN37UepO4Gn7t63GPTtm3RUbsRdvYd4kH/pbLZbeg/+wdrPYh6T8bd6Jzp9P0/FrtfWNuN6O3FhnceqanGliqOef93S6XStOF+7V9iJHnTgcrpE/3+OyynZK9mrr3GYcRrcS5bWuw3dqq6sx+YfMj2++KCxswsipGP7hztaz9p2Pe1hmmclGzQFh/OjON8lywJE78yhLsnu91B2PP7oGSdzc50rrbU1lnC+oxGe4lIRVi5SB1XdV/OTPdc9nB72cro91luUiWVfSqaUNgDRUqezpMqkNlutNgdj3d7+8mIrMrO/qivYFMlSHNn3chHtX+kycmW9xQpbB5aw7AjLkHzFoasNXXbgoDsYl7vL7l66GRkbmEI5isZ3OeNj4eTNpF81XeGDIbSmA1zXSXHxspHeLKiWVhTrJejS8Kkbd09XcCtL7cDFy/vKYFmyFXFsdaIFX5ysR/t7xV3mhkfZD47ekf/sMzVNfAdR7zKQSUCH4p60kffDGGPE94jT7OUQ58iBcSpZFqX26Z55nNgvj8Rz9KB43GMtkol98hXxveI5dol43KtH5OOORyHfvXMH/oD8XXFAvOo1z2EJUTbmZbEdmM/jl44vz6n335hV/c7NhLpzRQ+Dm1FBHbtBo44KWg82SMdd90nHgKUD7612ve2ETdmo0sJOb2j/I09nTBbykPV2GNJLNuoPDw0NqTIX45TAJAkMFDemazfQlTEYfhIeiSrueNdV8yXhn9Zk8qr8/KPyUt5xeJh0PcboeYu4UumGT3S1xvlZccqbYI50A+IIqSds+tGu/l/jPxjdp5R3PLYrFcIUcGLw+Fr6GF6zvw38Ht3jd/Uy/d7x6NBlpu/YnjhC+KXOPWZ0mFCPEYU88pgKjavV1uKlTjVYwr3ioHDX82AJ6aA9fLtJVa5IuBML1JTW16qON6qT4I7Os6M1bPMwNWQ6/jJfFuZv1mqZ/3W/lZ1RDjE8HPXFPt6mndtKezbfVV5WIc/GPh31bdBPp8sUz64/nUdj28x/1hZHjnUL//3uXvq49wtttf7sT937SjxSsBVaOT97P+bB3W5myEH1DW3K+URTaP09iA2bjnuda1EO6IHICZLfLVGhPMNHe3D6mVr06LYf0w0iu3Vb2oSkOgG3zc8APD5lVq26/Uxc65LTB7aHxyytaHvQwETgrW5bV9FBHCvTze1LCCXJ7LijC732fbpabC6ImPESnndEpHxTRlxbK/G3G2S1WU/BPt7dXGIY6rRLNViwoVmL8t3QiWMmYWHlzDlRMbYKX86WQWy9aqSFWWV1267EnQWlxVvJxGog7L1Q7yh1qE/FKeu9ngCTz1ZXMnN+2/iteuun0uST68PhrCEmrRCvgVUredgIosGCCh5Z8qo/oZTxPcrZlXS4VMYP7UG6p3x8kPfzj07rcXZuSiqFzk6RtHDbHDpoaVy4ND+w0w5HYw/U+3zKAS9LTddJTYOEs+hZS1BCIaL0AXU+PKc=
*/