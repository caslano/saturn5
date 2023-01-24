//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP
#define BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost{
namespace interprocess{
namespace ipcdetail{

class interprocess_tester
{
   public:
   template<class T>
   static void dont_close_on_destruction(T &t)
   {  t.dont_close_on_destruction(); }
};

}  //namespace ipcdetail{
}  //namespace interprocess{
}  //namespace boost{

#endif   //#ifndef BOOST_INTERPROCESS_DETAIL_INTERPROCESS_TESTER_HPP


/* interprocess_tester.hpp
5ztxXl5bOh13UNXgDnZyNFJk6zudrxfuZLAqR9hQyN1OROTWStxtpRVy0IwbtxF367RIRgpxX0V2e831APNFImWv9mcP2f31rMDPAiypVs8nuNaNm22O9c39bxODcS2yEU3qlXXCsbJdG6o717pXpjeFFUEZuBz1dAeLnKvNF0gKPm9c7SEj7xUYPpwzehLB+o9zCljWW/9sUwpvrY6EOSh6ZXfZ3sdSbHIFbRYJ3ewZU84HOSlNqadBHgU+8X+0ifa1vtCFfRWDaWLfxiNbiLwHwQxYGstOWfQMqLMpCKcqkud3HjyHZZC94x5z2OTfl+7CXhZriNRInNuo4RejatIsrAjkVgrdQ6mCjiJNK2QvFC1UlMfVuxZnvnuWxXrDTouzdudSvViH7X3tF4bdjtz/mv3E8mUs6ntjDxzwgb7XQjXO2AOn2vd19Eeb3QsyeIR5TcDGILf33W4CDF3LSoPGzs7lrSZs+TdsaWfJCrlbKYNlLj9afcL/2KOHSXormyxxkZXg8VXxe+uRgUl2cusYPccLXUiu7mUT/+0Yuv+64qTXTKXyYPd6jal9K7/bIdewEbxmmyeHQxpAek3Oyus+KHvGd0F2jWk/f9FbQ/qR+vMJiPmDTeFIv2qWl3cDDX3xfJlug/JHfX+NRuW4YCkXTW1JCzKdOySg5MDDFP1aMVoEe1r/2Nqp8wz7Ajl57tGaMGaqtNac9hLP
*/