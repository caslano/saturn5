/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   functional.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header includes all functional helpers.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/utility/functional/logical.hpp>
#include <boost/log/utility/functional/in_range.hpp>
#include <boost/log/utility/functional/begins_with.hpp>
#include <boost/log/utility/functional/ends_with.hpp>
#include <boost/log/utility/functional/contains.hpp>
#include <boost/log/utility/functional/matches.hpp>

#include <boost/log/utility/functional/nop.hpp>
#include <boost/log/utility/functional/bind_assign.hpp>
#include <boost/log/utility/functional/bind_output.hpp>
#include <boost/log/utility/functional/bind_to_log.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/functional/fun_ref.hpp>
#include <boost/log/utility/functional/as_action.hpp>
#include <boost/log/utility/functional/save_result.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_HPP_INCLUDED_

/* functional.hpp
jdA1/jrqcW1NV45Puk7sklelNOUcoTQ1Ik1ziNOhuyqkSeJCekw55cTZyynfm56OnXO7hMupc8cuVS2n/COUplA53UC8tofLSeKj5aTxcacrKd6ermKfdIXudahquoqPYLpubck81qIK6ZL4eNO1N0q65vmkq2POiblVTde8I5iuX3clXXdXSJfEx5uuFQn2dC3zSRe1usr1cNkRTNdc4pW1uGK6iE+Fejgv0Z6ucp90denQqcr9YPkRTNeNoXTdVyFdEh9vuibUsKfrgE+68jp0rXI9PHAE03VTKF0PVkyXxsesU61B2dd5qr9eVGNHAPNh7+y/qndmt1XlO87eduyO2/Kqv+5R3ftPZG4wPD5q+ZzmmRvM1bnFfjATnmrmFFHqro7FXaa6awFrw5Yud/k+4Q1Rd5M1vCkud8U+7i5RdwvV3SKXu3k+7paou53qbpfL3TIfd39Wd8cFcAfbwrC7ch93XXSu9U51t8Dl7oCPuwfVXesg7mAbeDmU7+RW8n1c77dxr/F8D9d8C9czz3c983HLUNtRzovM5aHyUdNRi1+MzdXFntgTe2LPz+H5SX7/j5k0cUrhkfn9P8B1/j9bfyezhmz2Ctwa2je7L/x+2PvM0wf2PX1g/9AMxK+KSmRvafi98PC3zabvi/odQPUrIO6at5D3SbP3qp/IxrH2H7Dtp8Kt7Zt51jO2xm5TPUfwGgkqI5CUQGJy3NEpp6a0SUxLbZSe2Dg1Kzu8x/QM8uJg6IVJ9+JXdb+ivLuSfvQSZ9KFfow5G2/2KXvmJT7V3/E36rf656JexW151PwuKMIPa563/iBqnqt/AZe7EuMuWdzVsuZ3uU9ZvS2y60J13Zr/5daysp9tdtstcyqeHdgp8it5983Gjn6TTOLdyJH7DrTsHqin5ed/nmBA1LIz+hLRp3rKMs2nLLvX0L00AcKC18LGLYnLBxXLsqRIrtAYXTJ6sjtvzTfkrhU3VwX4BhxxVD/weZFzn7tc1TzgOs9eZPav7xTZYFu54s5bHybbyhB71jI0YbT7MCS/zVqmuDVn3K/V340Fk6cWUoOL3XtDA+JHivUMuzv8q3+IZwExMG5TxW269Ry7cav5665T9eC9Ih8bCFKKme56V3IJjW3alLKiEq1rtE+xWxZw1c9fSRq0fI6VeOyXvuZAHH0PjXkBgcTN7JNSmNIqpXXoP46IpJH5jaiviLmTI1LVqnv4DNDx2EnGzpnU6aVpKLXzGZXjhUbsXWkmlHr+XmZV9sMnpL/wobnbQ+u+qdta98Nn9ItEn2rawmRr3W+gZ++vFbPIssW+5NvVIpMy09/5ugff5F/X9HslXuKP7uelPbkabG8di3qhvia+xX/2tic5nOVqRyVmX/c0sdvdPhcoskCl5eG/19ublyWuPgH3mgaB7kteEJpHqpAGmXgJHUwodbR/n99V2owt7rivdM90xPiEX1LO7rNG2cnm3Js83XWs31sxbhN1qLeOO+kfRd3bjV+W8UPd7RNZezlrZemjcFv1sT5stwHtbzGOX2Pz2MWhsd6h0WWlJCamZh6j+6VpMzJGeMcak576kp54aYdVzd9/d/x/XvfW91NP+6LewG3OR9Yy0OHfXg4To5cD/nnHiRLzbdBOIkuxlgHuvOVny3/sVX2sV7tR8/8izX9PeVV6PiBaWVxWzfH8VC2b4lQzf8aDHdTruJ1nKZvSAk7klRRNKSsom8DYLtt5TZ7Z2zD+RJ59a0WH2Tqr8vlSb9/t7jPTannOamicl1WM86SpYy+sNI64izz7kv6fxW/7UY48+7RPfx91R6g/rBA/Od3oqq+9TP045WPsIrH2iyZPjbuJ7neN4erWVteNW9M=
*/