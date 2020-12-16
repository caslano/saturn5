
#ifndef BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/same_as.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Last >
struct fold_pred
{
    template<
          typename State
        , typename Iterator
        >
    struct apply
        : not_same_as<Last>::template apply<Iterator>
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

/* fold_pred.hpp
/k49zPlc/kX0fK6Pno/3COeT3dJ8YEAVcIFPaZchzvMcxoyapM8K5TDSCXLtG/XTg/tBL83Fx8kl5o4l/7S3OYbjgNUSr5etLRiDRPfJPGET5bBaK9qjTxb0DfuqJk5Bn7AvIrTCN08kVdoDNcX/JNqbDwyKvvmsOjCat1n9vjwwRifFKcGBAfGRmRqfK20r/iv1hzee1ML4M31Bz+epnoER8RwVXNfGRiM4l+u6a0bxVO3obEt3m7qlEIys2MZaGEIoIrRU6qEg2q4wndXR6BfcrptTwCBTPJvb0NjNVVLqUBcfxBvPd+7mvnb+g307SU32ciJXIKPzUWSqDDCO0nVfTccn/PQz+/6iVnhLXQjiQrs4cQt5qrmGGH28yTgliy4FuFcRb13zhdeVoIZVlgo/w4TZxNbkDfdyfZwbToxvJPZ/1PgoRB8/WXdjwY+n8dpjvFSWFlfyUn8paKFnEvjy4rfRw19Keml3afFuLrUT93JlVoEnoWB3WUEleXPHtV+JnVFZXrCbpreHLAwOSWhsLy3eLh4lV1MZAvz2iokplH2iyt5qbLS63E2eGt9Dl2K4QGtbSb2RamUXbCX93xPNma8JeO4sLd5JbQrO+vaEnK0itB81vTPfnLVdS76EsH5nONN4Szefs5vcEnHz5bk7yVkL6Gstwv/J53EC+jD/aH1EhB2vgj6eBsfoO6GnstLEPumPoxruHe6peUjrOtoLJOIuOD8e+/Kxf6OJQZG7e1A65nhLKV54AF6v4CbILGGYIyNidzWq5pD1aV8/DroVGZt3guB/spa1CsL9fjeMkCzrlBb9FcY7mhpiCzbzbLDetTF9d6AOfnx+003N8ASjUtUDjnv8XVSS5d57WeIFDz+gjkgtv3X65ttPNf8HAQYBM8iEAYe+Uhkm+SYR44Gj1GVPcAdFXnvO616YydLGdLpZUuV0lRPlAtoKfsGsG8RhvHLSC0mqlU6lU1UZ88tSFbm8PY1ETFUAr2RgaXEGGY4Zf3cpYGEh5IvRnPCO1KrLKHOGi8QuE/odZuTvOHsSzRfDZOei6PE1IACqHho664fOehsO60A1sKXg+2+jH2HA7DKcOlv09SWyvG3XDmn7n1ivocB/RLdrfYg9Uf62Km1MPOESJDIvEoEmQKqzsAeVGso+urqzD8HZF6f5wj+nTFfhFMrsRKmgjTJkhCax/Tmg1pBC4SyatAtJQFlW4EcT6IEUwcBQzbskzQeG6oxL6UtnxK5FH3Uz03wg3pLBGTzrOkW82TQ11/85WkP8gyY1PbAUXyWrS5kFUILmxkL08tkC5Jd3yS5IJXz6CkFETAXz70jPExhGVIXTMOeOxLSF2WiVuPprwVgmHct0G0Xmh/hE3GnQvdyGCGnpKjIt4WAIoDCyDkz0W1F5n0THlaTlTqAjSyocpvuQaFIRAC8Dp6jMCtwLTPj2LvnO2IPp4fG4h9zXfmHHLEVnI1PcRca7csPvxhXz992y+k5seE2Y+yE+CkRwORz6B6YSE2T3d/9BzzYL/5NSAI41HfEKhCkmuuevuG4EVs7O9QclaeIFNADjhfMUxukgMU64vdxzcR5my/+HifsHWxS9gbCUOOzqc3WIP0J2CBpJEoRxQh3Ql1BAv0QwosKheK0gUieShdwjiy+OBEo0Z1NriBDOLsmIglwB7lM7mhO1DPeZ0YoVH8JWzB/PRFqb396Pm4DvTZ0AX9uM72dRACw8cE/c4FqcE6FBCQbSoeSncyJy+L9Ofjo3kvx0waHsV4OTRHppw/iibpRIDKLp85IoJ1L6cgYxnSjvkMo7pPIOIQ/tieTsDVjcftQfeCkeWmHgCzE0POm8oUu+E5U0i/97gO8=
*/