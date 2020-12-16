// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/group_handle.hpp>
#include <boost/process/detail/posix/handler.hpp>
#include <unistd.h>


namespace boost { namespace process {

namespace detail { namespace posix {



struct group_ref : handler_base_ext
{
    group_handle & grp;


    explicit group_ref(group_handle & g) :
                grp(g)
    {}

    template <class Executor>
    void on_exec_setup(Executor&) const
    {
        if (grp.grp == -1)
            ::setpgid(0, 0);
        else
            ::setpgid(0, grp.grp);
    }

    template <class Executor>
    void on_success(Executor& exec) const
    {
        if (grp.grp == -1)
            grp.grp = exec.pid;

    }

};

}}}}


#endif /* BOOST_PROCESS_DETAIL_POSIX_GROUP_REF_HPP_ */

/* group_ref.hpp
BP5zfNevxEwm0Tsd9VNQVBk4E6wAJ7Oe/a3EY5jjyIuzv1qrexccwHiUX+Gyc1Ao/hO7/+0cdPz9la3r3u/sFfcXrCv4fxOhu/U7+0TnUqZELjBz42fIWDVJ1zfafcVjmEMpQXNY+Rnmc8wXGO1PfnSMG5oju3SwPUeWOGvNY56ALHLu69nIIue+noYscu5rN1tmwmuGLHLua31kzrmvnsHhc18PDzJzX0+onwuNI/o1rN1/PB643w53tI8Cu+/YnSJrgU39DB/+g30H4fxw37Fw+DH7Dvz+cN8xZ/gx+w78Hn/fgW5Y3/Fd4t/Xd1A25KTkH+47QnXTS/4nfA/PMrAeDPQd6x11Uz6ncD5OrvfczaL3nfPsRbRlvyO6IftM2mR7fVphCeeGVTjKuCZT16HoGOPCTLu+Pg/b26OcAwvLXNZGSZxFdG7m+SQiPdN4vEch6H5Ew3xN1pHxRFw1y6TlyeHBtJxGPdXH/iXl/RXm6UbUkT6fKDG17ehLXQJ+7nvOpOnZsXINRZQX660kz1KHpqx0Da6RSzmI7sGwcMiihn/EIXfm31n3/mSdz4bx6DX9GNfllky77gMrBhCbMRXXVpVzTLVTdMe6vzPAjX/OdmPGcfeJ2wXHtWfPscZaXwSf3cw6zs56P+rUJKg8iYDbKLkf8R1S8iW3ooj7kBnfPjQyeN52ipXuyIv65Z/m0/XetPevtCttR7+VcJqgx1m7xv9EXyhMW+Yx4zrnvUvO/pcwVloDaY+sJjTr061ReoY1Yb9GnHkSzsk+t7Npk+Adop9otdVwc0S/t+9dnnxaegZyrtTJnKnZ1vOY12vOgHxG/IzgDthT0rdR0mf3b28Sr12v9jrWePGX4In1eF3S6/6+4XLJZxVl3sjqa3XRdIf8NXHe22XtbajvuVD8LSFu7EZ/BWcCJzv3JTL3kSni3oHni8Ymn4kim4tsTq33HAc0jxq3fWaplF8nk46oQBjEmaphHhD3VpZXWmWSa/oCedqRGn7++LfEZ9fhDJYtV5nrrIH4jfWIPRQWrqm8Y0lMps031ncsMReP9sfVq/UuJqSXi94RZL6Lm8TU80c3C623/hrZN6o7G1kzZH/F/i2mEX3fd/B7zFEMxSfXqQfOx80LfRgo8qbJYuTvG9VENbbP+gwUYjT2P+i13ilQvse5b9KKrNAeSX364Bwp6xsa06QiC56TefzPZsikXW9sqTK979IOzHsidKSedqSas8DlXcPDUufkLTlobzgy3H77yPB3SY1HBe2zEoP2Tmp/SdfKZkS491T7VLUPiHAfrPaOLXQfhqyg/bmm4c8KKboHwY1BWOswzxDnyiztG+cU5k0v41jgmXlyrdnryqvMdbRGdFtzvUaZa2CHyE527iFi2u4r4paLPbTundN2Hf3Tnr+xdybgURRZAO6ZSUKAEDIhCRBDOBWUG8KtCHKq4RCQWyAkAQIhCUm4VlAQUFRUVFS88QTxwhNcUKOi4MGKNyoq3uiiIqLigew/b95U90w6Cq7uuvtl4H1/+tWr6qrq6uruOsW9unkWbEMZQ/lYeRjPgkBarzjZ5HXY862Zzj0vUA/TkRdJa5vguoyByja4GJZprzV1p6nPCsS2tRUbNm8/z7yrtBP35riZus3kyWJxS5F7tA6BvYBUIV1xNVvG+fx2G3Rsst6jarcfqRqwqzI8zlctZAfV7rfXtOviH6HzUz6sZ++zOsFX0TylI5/H5T5/rKJ5a0c+76iieWs3FQT01nnF+889bu4p61unZba/K6N7xfPi3OeJHfk8NPd5XBXPd3Kff1XRPKgjn7fWrFNAH9/49pZXV//Ec36HBt4pGQ8/XvF8thlin9B+9Qk=
*/