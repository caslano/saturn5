//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP
#define BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP

#include <opencv2/highgui/highgui.hpp>

#include <boost/compute/interop/opencv/core.hpp>

namespace boost {
namespace compute {

inline void opencv_imshow(const std::string &winname,
                          const image2d &image,
                          command_queue &queue = system::default_queue())
{
    const cv::Mat mat = opencv_create_mat_with_image2d(image, queue);

    cv::imshow(winname, mat);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENCV_HIGHGUI_HPP

/* highgui.hpp
BkY0A3nIzvUGnZpATC+DJqqufZVN+oDZXPS1OGdf3cgwzd/JlE2Um9pxqmzieyMwZtyBE5sZjkc/MrKn1O1dewBhuPzC+K0wdoTZKjE1Xa3jSw8EXf8NVL3lgySmybdqm3JtG8f1F2miqn3Z92D2/RVsTAd1Z9h/Kn15CGG4jGV0X16/XWLa++LtAH1kX8YfKjGr9+WmwC1XEajwfedO8b0yzIJc5MYj6Luwj8ZlUbHPCB9Z019BN4eOQru7GzS8JsTY0V7DaINeVes0r1YGAESugMcKDErXfJ3aR7RVdJ53GP0edJ4/ejxwI+U6n3+CwNRD2qqH3fnEBk7j6etNeitPH9jfxJk2NgtPamJMu3PryQyzev6KmwxzD/krrj+lBSe4gi38AWBG5rhYeKrAGImXBFvQk48/rR2nsFb/1qOwZuzipxOOyef43K+/Xz8svou5jzzdu3TZAamv46Kg1yBztI2CyKU3LPejjfwp06/yvFr2WO47QeGEwm183pAVXVKxqRVmOQko4shiCWq4LnCg49+m44mFkjxjExFagWnjdX31zrNrlHtKHMUl3VOgudXr/oDGt++7Nl3TOXi2PyDfCfP9+/kKD11haYd2HvAC7A22uDSclznMpxD/Xi1zNPVZkOHEsfq8v3OGzEfFltRFujeFqSf6+rzn22ndX7wLd2lv3SgJvCC0KlYo54jswj7k4dP4yUiQkJPyn/z3+sxlVa+780j9t3Jzr7Q9kt1OkcKiOBW5vs7/uIrPrdCPysyzu5aafNnU5+9Vyxx3ySic+WqKDiwu4V4s8RManvqaMmGTVbEz6QfmPdoSeOhD3K7nRbZ9v+9A2Iup9T0zo5XR9dPAInNv6qWRd/WywOL9EJEXXdb1xdIw9d/If/g+tdyhJGGRjln6/nLKmL/675PaXphGMc/DkCtzsYf5q/8+vp3S2nCsnggkwp3CTdne1x+py7qJmZRu/+IHyrX87shF/0hdLuAE1Eyam27oanydw8hPqJelnytw47yoy9IoKJ7rWKKy/C1jzLOsTJIgjeoKqhekGCA8PgI553frsmk3LGw/9mOlvMya+zy5ZSkdOYg3qFZPYBVuHpRx0VXeb+qqMHt0UM6F8W+pfp1p4vlZSEtQrgu85S21vcLygzAPQzWQYPVTVY2A31oeW+7WZYxhN/XKlBWP2NGvZKzoDGL5vtX62LWiMHQ9O1MECIhR0x5xgN7sOBfUuo4lXpHTL+darhFLcFby+zYVz0JWk+amCFwrZ8oDvdQRyN4eqPYxz4qwSMOk5tbgbSjH9gNaP13SpcRJHgZKP/MlZTrIKqBDvcv9KVoOUjX/j4w38nCGrU83+Y7cI+q6zunVBkL5u2dWFoawI3ka3d1uonx9YpDN+lnKIoT38ZmdJgbtgI8bHFPv9CbdegSjY9uV5M4T6G17h2L0yBtK1cq0Z5+y4Vcrc1Lekjkxbc+pxONV+X+NKg9f2wq39lmtOH5lUn1yf6m0I3OD/ofaUAvmhedL2l3Q6ko1G1B6o/tjLb8nbxk40o8C1/jdtZiPo3B4Q8O2lnAY84adxXd1OuwsqhhbGk2zs7jKafWcU97myJWk0tW3+ecNmvkGHt8AujYfNZlHEwMekKtxo46RfEDe0aSDF9ipbGKYek6b/fyIQVf7Ob5Zp5l2CJc43ZxRCNtZx+bYQjjdnhl+yj5/n7fMA4XHD2yVOPyW4PF9D5S0+vdQx/nKg0DXxgljxDDbJKbuq9rPd44Tnb+9V+fzpQ+WuCaf+x4iae18/gb00Xx+fbvAGHwiX96Oir48zRS0tF/i7coeCYxW3WBUmQx8tx/F6XR9nqYbaF3uI49m36u9F+XQJtM=
*/