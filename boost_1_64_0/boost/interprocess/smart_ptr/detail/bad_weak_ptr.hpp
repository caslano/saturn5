//////////////////////////////////////////////////////////////////////////////
//
// This file is the adaptation for Interprocess of boost/detail/bad_weak_ptr.hpp
//
// (C) Copyright Peter Dimov and Multi Media Ltd. 2001, 2002, 2003
// (C) Copyright Ion Gaztanaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED
#define BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <exception>
#endif

namespace boost{
namespace interprocess{

class bad_weak_ptr
   :  public std::exception
{
   public:

   virtual char const * what() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return "boost::interprocess::bad_weak_ptr"; }
};

} // namespace interprocess
} // namespace boost

#include <boost/interprocess/detail/config_end.hpp>

#endif  // #ifndef BOOST_INTERPROCESS_BAD_WEAK_PTR_HPP_INCLUDED

/* bad_weak_ptr.hpp
/LUXJZJ1S/LH0XbyHNcvnzvJ59rSOeu9THhF4iaPXBjXHmQt6yxYJplkrsS672zeXxt+VMaGYZreQrtC72Gu37hwG9tuF3Lm8WCrnXe+D19NcYzQ6vK+2xl03CssFtbxaqHeLtFXms9Wzf384LC3Up5+wt6uTxrxmWl15b3P+X4zW+4pnkjxXxU2RCvQWuldzDUmaeRfFCbXkOTPQJ8z8gV2pPNfoT1HIGe52gCU11eek8yyzp6TbzyW+H6MmEn+L3qBNpfzSXKT8oukbf1CkknTB2qLIWPct7KpbFmaWIuyCc++zbG8FkXPdMREOnTXPkcMurV6r3EOczDW/17jkMMJjjvWtVqu5bLKNKrhjsv1hLd4+kLmfCFT88bllfcj749j0bc+xX9H4T6D+5zZ2ePe+EUiUd7XeO/xa+F6wD3D97cEP2tgirYZ97QZBcYx6pPvcf7fX1R7kjsjzDUxIjxdg7j+bPe9k+SvuO/BX1yT8v5pfd9xeLG5P76semv0xpedvjV67nVrEV5s7jvLqm9z31kWnM19Z1nVbXoEa3P/eLx6baKrrHprE11lga9NdJX9tmsTQza8revFnqNx5PQa5zxcEbfvyyeO/Xjq6h5f9f7t14uFbHhXfT1XsyBseP8bzuX+RgbXsi3feL42NF6bFMb7oNfjtUbn8dqkNrwmKYtteg/gtUljeW3SZbxf+ixwANvgHQjeB+bwvueDeDz4eBh/n/F3b4yxXklzq/QPg1w6OJJt+o5im82jwQd57dQrbAv8Dd5fvYL3V/8P74+eijgngmeDBSJ/4CS20T0ZXAhOAR8Gp4IbeH/0l3h/9L28L/r34EzwF/AKMAN5nAW2AYvAC8E5YBfwSrA7eBU4ApwLXgVeDV4PXivqBZwn6gO8HnwOnA++CN4IfgguAA+Bi8CIcMOWeAx4MxgP3gKeAy4FG4P3gf3BO8Ax4HJwBngX6ARXgCvAEnALeI9ID1wJ7gEfAI+Bq8Hj4IPgKXANqEcYtq8jwUdEucEXwa7gy2BvsBQcAr4CjgQfB68Et4A3gM+By8DnwXvAF8C14FbwMfBJ8AVwo8gX+DfwMPg0GIbraDNYE3wGTAa3g83BV8HO4GtgHvgGOAV8E3SBZeCt4E7wbrACXAV+DD4OHhLtDr4j2h3cA5aCe8FPwX1gDPrnfrAG+D7YGPwAHAAeBS8GPxPlBj8HLwWPgRPAI+Bk8Evu90t0/uahbzaj37fC7+tY1+YbtpX/A9ga/BFsy8cd+DgX/Imvu1MgPc90ww5EFHgHGA2uAB3gE2A8+A6YCH4MJoGHwNrg12AKWEs34j8XPBvHLcEG4IVgQ3AA2AgcAzYB88AY8BowFiwBa4BrwfPA9WBzcCN4PlgKXgC+AbYW+QEzwffAtuARMBWMRr3UAWPBn5GfRuCvYDaowb8PWB+cBLYHZ4AddOM66wQuATuDy8Au4HKwG/gQmAWuA7uDpr2OssBsqjsDlHP5kmNb5Es/DwvIHnkwc2Cne81laL3l6V1vuWVXyCa5wiY55uRC6yx/D+ss136OOoA7CHcCrvYXqOcv/hjze6G/0F/oL/T3P5//n3H69v9rmobv375C/7lPdk72kO4D84YO7zFsSHa2XAJg7hO4meRyul+crdol0ND9/yZRM3XK1yl0/7/CQcVTNP5XKUEa9aR5kGNJXvUyETYonXLLHoGI12YjIN2bvr86j1AP95+eW6+8pK93W/xLFXr+V6aJwXRlulAtD1i3v39l+wAJPAAbrRttEQ7ORVrpRlq2Bs2fMikfYxjUFvmJoi3mmvMzF1CYE9qnWoSqfRCnHJttTuO4YlRY7jfWi86/p+3WIhXjtTK8nA8=
*/