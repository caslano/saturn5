/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_VALUE_OF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/detail/cpp03/value_of_impl.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_data_impl;

    template <>
    struct value_of_data_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::second_type
            type;
        };
    };
}}}

#endif

/* value_of_data_impl.hpp
R3oZ9pOfZgY8AOfA36kdb8Db4Z/hNvgmvB++BffLL/Oy/C/H4YfwX/Aj+DX8WPbkNdI9ku6dsIecIaZfzSyfyZ7jsudz2fOF7PmH7CGvqmlPY7gNNoE/gU3hSzBa87VnwPfhmZB/m/PMLWCM/JMt4AjYEmbC1jAXtodFsANcDjvCu2AneB/sDvfBHvAV2BO+BvvAt2Bf2IS29YPN4EDYCg6Gw+EQmASHwskwEV4GRxv65O+8Go6Fd8jf+ZD8nX+Uv/N1OA1+A1NgE/rzUtgUpsKgX7nnyfMr5yGVqm+lw3duYzXv30nz/p1hEuwCp8I47ccL4ZUwHubDbrAYdodLYY+gPt0jQa+Dvt467vvADnAAHAYHyo8zSP7GwTpOh8BMOBTOg8PhQniR5Xunh6XvQofvnV6g71K2gW1hW9gZtoNxsL3q4RjWvQx/k/+9i9F+jfNROp+Mhr3hGDgQJsF0OBZmwHGwCE7SeSUZ3gynwIfgVPgUTIV7YZqOvxmwNboug51hOhwFr4SLYRbcDOfCbTAH/h7mwjdhHozC5gXwdJgP42EBnAS9hn5YDA9An6EXlkBjHC419MJSuB6ugA/D1fA38Gr4N3gN/BJeC/fBo+Un5iP4X/APnIhv4NvwC7j5ir9/c//1mfev75x/zC2MGSQN8SFbkYeRg8hXSOyt7ny+W9ziFre4xS1ucYtb3PLfKI2Rou/C/28u8eQsMYIATjAGwPDvr7F8ByBWcybAX/SO4uHOoe8oVpthvqVYh/eJq/P41d+v4ew3ieSPiDS/HcnPEmn+PJKfIpI/ov7+Amf/SyS/Sf3zB/bLM5bv3zZt/YL3DnXes3LmRM81Q7b55/m7IdqviH+++BTYDonS/JfBabDdKVG1zgG5+fm+n/n58tw5CLe4xS1ucYtb3OIWt3wPy3eV/y+7YN4J5/8zYv/fiydW4VEz9l+52ZbzWXi/omLF/pdaYv+HalKgl/LSdNXcQGwbaxx2loepgcKCeRmLCj0l+Tl1+HaeNT52q2L4PyU+oR18H36AnZltArGqMtDUMT+3pMgfU7w+Uv3Kf/dUe3/sKN9OMGM6y4PxxNUx3luCy8yEKuayCsOW841l9HpobjfleFJ8uJYZ3a6Y5eq4UTO2PDkYh+opNDOMKTdNpl+v4v5N3aGx6Cw37Qz9Hn8wV9IZpo05RtBrMA62ILis2BYPHK13BhbLnnzlQEvpGNLHppG177+Qbx/actmUS9d06ZqKxLZk3iFUl4aLstPVOR57ktlGWi07YiPYkaZY+f2KVX8W6c0/UmKd7TCbXod3CJRjzWaH3hUJGzeJ2k8sYydjrz22WLl4gvvN+Eij7djY1zg8X9O6lrShUyAv0JhpU8dlXDY6ecbY+uZqWtsymBPIpjOlSXguouv5R5mDzvrmIVrbsvY8RIExW9UkvO0fxrM8aIf/9FPfPFGcAx3bHXtaeA6uj1j3WIi++ubeCrSn/LTw9nxM/TGdQ+on91V99qOlPfZcd03D81t9wv8SQ/TVN68V+uz7UMef3l+x5YfbKhvGqM0jkU/Zvixgw3xvhqfQV+dj33r+1rGvZV7zvZmtmts891z325tuzP7Ji9n/b317M9+cy2/V95prPpk9KTZ+z+OfDjjlhdU1x/Kjwn9/Bnshu0JyfDylHCJPw64wkOOkG+tlajvuxcztLjHOUzBKMcPtYC8Yp9jgXrAvHAT7wZGwPxwHB8LZcBgsUQzwKjgC3g1Hwh2K0T0AL4HvKFb3C5gEG2PMFHgBnAp7wmkwEabAKTAVzoPT4VKYBq+CM+AaeJmhD86E98N0+Cy8HO6Hs+B7cDb8CM6Bn8Fs+HfoUYxuDmwN58H2MBc=
*/