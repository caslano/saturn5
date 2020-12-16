//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP
#define BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/sync/windows/mutex.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

//Windows mutex is already recursive
class windows_recursive_mutex
   : public windows_mutex
{
   windows_recursive_mutex(const windows_recursive_mutex &);
   windows_recursive_mutex &operator=(const windows_recursive_mutex &);
   public:
   windows_recursive_mutex() : windows_mutex() {}
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {


#include <boost/interprocess/detail/config_end.hpp>

#endif   //BOOST_INTERPROCESS_DETAIL_WINDOWS_RECURSIVE_MUTEX_HPP

/* recursive_mutex.hpp
Y6ptXofjPc658cyvHHusBG7Ad8EvG+UAw3iWgRX2cW428/RuKb/AX44SMM+vfY9GmLZ8MfiAH5C/TfWPx69j/d1VHjdjLL14v7zvDGkYFcNXuSWShyDhNfl3n5XhDQBfXSbO0TxucP80My8Vf1iuMfM+W8bR1eD63CrlP+7P4Lydz8dqocwjbpQyH/GP8f3LiOfn8rtOIhzJvbVTPs/yW/peo9+aK+O9y+i3DjCdln6W4aNPkPLjmQbUBvk8Az7Gs44wrQrf8VdlmFf5h/kuwhm1exkX02rOWUh/5SvQ2CjxjZDhFyMs1Y5hxPcAwhov+9fXEcm8fjinJjnaBqamdE1NXnNpnP6Vfurg59uSC+hqs35YZPZD5mkhk1q32cb7RpnjkHlG8g591s4TTJnzkGH//25qZxAFd0vtAjbS7vHSl58b7f/XdLKmbwieRZ37DuL9Lt0NsH0TEH05+/XWeeUc3ttkGY/0AXfEzE8czrPv5SvDdyUHzL18fEeNvFs673OEH/d7+EoOuN/DV3Ig8T18c9uwz7G5v90282GboNU2XAOLvksF4qwLBj3YKOjBRsE22CiQ591G0feq8AC7jSoRXshiI75bSftsjHPXX8iDfUIe7BNqg302JnTXH++hutQnP29zDuQNuE25SM8eaR9Mx5Upi1iafpHt5pel/PO+Uljpq3Ba2+3RzS+bfdJcOa5M0dtyj8N8s+L/ISmTrbOv6p9jtUhX71Pe6XrJ+D+O+2q7a8fIDMPS75jjvQHS/xS8G3Q3uGDT5Hc3+HrhW8u7ntFf/T5ia+jZ1VcBJ+QuyZbhi75epuV1tI+CH/QsyvOLWAj4nmj/k/pI8vdomXmWd9lG5c5C7vtyHW16alIvQw4asd2nXM5AtPtCLuUaQ+YrHL/3pcyUgezvelSnJo3Tc1qrYVYPZF8HznntWJBrVw/BfRbuOc4rDfLYd3hZGxDfpxnjRjX/06V9hc2zpM0tvNBM1AAmpj/nSAMxdYRTpPY6Yqw/V0r5Prq6gbDczY8acrTpD1zMx7mZK1X73JZB9n3Td4h7gg6Y+6bZr7S6xth4wP1+6cYDie+X3u1yT/ixwXbdqqFbs0039pku9tI0e9CxuQ06Ig16HS193v4hdh2Xwm/YoiP7vFbnV8Me9Au3QT+kwVE/dQ6mZSh5b7hVYgvcNOiX9ojUD+9xK4NliyqDvjh1MVPK3q3Rl+FQX79ce0JgyjtCP/n7Wrv+it8Mpa0Pli1bWr1KefeSMh813rvvl89dzDVn6P1Yetv2N4h0ZzHd6v1Wswvsd/jcIso/bbe47MPFM4pnjZ8ur/EpVW4A834HmHHv2DB7nMWIs0Ufp+3ezqTsVu6WUmxemdn6nVotjyR+pxbSYrtTC3E63qlVdJld97miLup1lzdqudU7rJTTLfHvA4Rs4ndqGTor5WuLch+gyil7RqPvc/DvO6jT17y3clxmXF3hP/G73hA202+5v+9ye1p/iLSm6dPK+wrdpTftoPv7rNIOJn6f1bjM1u+ziuq7abhd35N9EKKhr+WoonLv7JpWymJ+G/IHYWvzZ/UIe3pfQ3oLndIrc8hdegs95E9hG/JnTXbr+ROtOwuvsOt7lVi7VfRVl0fBJMx9dnF1hX/1vSV+O0FZ813BQ9uIdFh0ZZ/O+NQ+IfdKu643QdcSva6LVpStWLa8xtznWBr/vlCG41fejdzrgbC19yA3a9I8GrIBXZqV/bSTpM0rsIUdu+SdOLMt6f2wC7tnM72TpI0ZviXNqwv1dg7q04wa786+wTbUdyf7LhypL/912rTKrtJV+a/zUP7rDibeT3op/5VX2XWdAV1DWl3l2gS2oZSJAYYrnUM=
*/