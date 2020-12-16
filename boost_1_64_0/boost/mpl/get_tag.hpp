
#ifndef BOOST_MPL_GET_TAG_HPP_INCLUDED
#define BOOST_MPL_GET_TAG_HPP_INCLUDED

// Copyright Sergey Krivonos 2017
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$


#define BOOST_MPL_GET_TAG_DEF(TAG) \
    namespace boost { namespace mpl { \
        template<typename T> \
        struct get_##TAG { \
            typedef typename T::TAG type; \
        }; \
    }}

#endif

/* get_tag.hpp
L9yNw/9F4jHX/cMG4zHX0Gfo8yF/jPhm97nTzk/nV0zG65hQQF5d88NI3V39IrQ6dM79vts4lt/o5iOvH2+d9T/cjdMWQh1slKfuTTHSrm4iv8XktLh6lysa3hQt35wGfhKBENoW4de48OZXCalr/dC9rC2s3mke4bcwsC0AVgdgW+RRbsEU1ilt0eZ9lvHiJ5h4EvwyPdTk+NmVOVuLT0vL+SPlRCmZcqu3Z5OD5NjP+BGnvvEt+LIQE53RJJxmECalevM/unpqEjXvcW/2oDd78YyYtbszyvRrCaAnMfI9JtH55+nfdhkkmsU5rNdb+0OQpzNONjdSkoxshSS5WIqS8z2DKUp4/Cdh/Hu6es4jpQspRCWhdVyMdseOrinXoTGJQ2OiR0Nx0iFVN2STigmaGuX2dB6BENq2mnC8JNy2YAFrVPSS8t3zvksajMKH6Vcqmo/wt24EwqC0EQ172ROHT2M99AjSi0AMd4vyDXtY/eGjKqSjpuI06lDVUl5WQ3uQqvjcDDPLgNn5NWj5dOHWPQ7hTmpPHfwSB7/o0fI48FYq+ccOdqlx2kxfPdRYKEWlS8qDxFOEnV4SCsybpKyV0ureZNatpK+EzPgWoUe+v5u5SIstVfWIUWgGsY7wBagOy8gRClVBNoEiCKeZwE4AIuNK2Ue8fr4ApcaFnSfp1F2iMk0M0oZFw3GBbuHNx7kxbYByYfUR9AsMLFHQWw50pU/jPxwwmtxygJEpqgm4OSp8sIx1aqXkRTLBo5pIG+koiiaK34GW80YTxlz66gETHUrhBlgKpbOoilCMUpGSUOuCaUTycHtJuGXe5zBdyzuo0fZSPSDw44uHiW41lTtKWe+mp7qZ9mOiE7P4kqI+m69XblZNGA69C/8FOnZuo8lnMHm5l9jNjqRpPb67m7FsipY3g7ebC2/+AQQU+LupsJrN+gVGcWpLL9MvowpwCJEFE4OkcKNPrLvCOgGScLDvkKM55gTtcjrPINb/f9cMGvrAp97rSvNf0JzuyKLaVGH/3a2cWfhdwtJoR3XVDqG4/gvn0RVHFtkhqdwm2FHMIBWzTKivCdWXhJqqyFNXfTTcVF3V5Fp0Of3Nr/LWlrcSy8SKImx0GFkL462mhnYCdx1xM7TkzdVVza7KzzSGWpSH/xaIOdLjtxBrsYf/FmKpHdzk48DBW8OZzeQ+JLZr3UZYqrwtLty4adUtjf4SaLZz+phoHB4Wrqoo1Ge92SXV+THhCYOQ7nSL6Th/D/CC4pyvAAy8CA3wWQu1XhJuKqy9GRzI0o4QGJcrrzW3CuSqz7zFVfm1Gi7dTNtomPtNNn7CzzvKkcMUck5MYNL9J6iCsAtU/uVJZmxFUczIp9qBaOclEPjoc2249Qy6sjo8MkF1mFqYoe8XXeI9PVbYt//VNYgr7MA+RnzmgpQN/+Jq8II8xXfVVfXsH/dCMHA9M8jofAsLgwt3MBeG6OaIufArii7ET3SEJ7dy7zlwIZEZC3ELDUVJaEfVaBouon09z4RJ+Q5cePXz4EIHVt5RWMv2HWhouDHCdNkYO03Wf/0fqG9p6in01cuTroDLUBCA5w1OrySLgSa4Jy4Rc4Sy13gUH1KeYLMmIozKr4FnEj9Sy/xsWhnsPA8mmq1nhJhz5pgUai7Tt70qOKdcY2TmCMITHHHVLbjp5+/+J7nJsDd9+e0uYV392WGSBVKGU7mUMJ+5Cm+hRtKuiVnlH6LcGSH/wqzYFBBFZFwAyzZlpcqOrGBt7F15sabB2libS99gMeBfTN+kEzs5hlc82/VBgjQY/rIrR8qYfUd5DTy5E4cBU5F1scC0X/4AtyW7lD0uyDQyV5EJ9MFDglMxkVI=
*/