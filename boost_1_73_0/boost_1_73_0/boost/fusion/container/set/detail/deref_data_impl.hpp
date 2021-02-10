/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/deref_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<set_iterator_tag>
      : deref_impl<set_iterator_tag>
    {};
}}}

#endif

/* deref_data_impl.hpp
MAO1kf69NPYhCip+sjlbc38FTc6sSiES/jqR739+++0smK/PsmR5ohqYPD/emHCISO8rm6KnGsSbEGae4Fnkk1on1PEciGDxVO3TSqSCzTf3DPqhFBDPAyklLWGLw9JzrJpBbtxCxruaXdv61LJd9vsLxk44qHOQ5YcigT5bc4g8cbkbjBD7zy+Ng9J4/7yNy+UmDFnEy1OcO6ZauVAbdg/2eIeFq6GPIpV4LpOCm2dROTI7a8OO4WMx9iCtNKPz7Gp2N9vHMHqr2w7W404KJvfGQc0kgMSKEUtBAvE633ewTOFTRT+x4m1NKkcKC5aKM3qpyDZptD1GltfMYApHixCYZa++BlH2Es9rf32Mg8XL1xVebd11jGsMXxjebelx86xeWfCuABXh7e6EHlDtRpPs4hQ358PwX5JxL95fsldLcMwiYz++7mH3Axn2A3tVz/FycBer08GfClIJ8hTFjptI1FH6+bO6G1cLiI7xm26NcGsku2yixMuldxSONRp5LvtXE0kp9zFIzg0ahYsWsW0x1R6YIyDVdpg23uDDcd3EX+39VFt/jsJSwUmJ1eUmNdMx2GDfwVV3V0P8NfDyl5R0LDj5PGKSL0X4zPKNg2DD42xVTU5Q0cuYt0JDMYubPrYpSmMfCRKpnfbl
*/