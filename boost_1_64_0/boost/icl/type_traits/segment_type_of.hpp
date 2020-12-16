/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902
#define BOOST_ICL_TYPE_TRAITS_SEGMENT_TYPE_OF_HPP_JOFA_100902

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/icl/type_traits/no_type.hpp>

namespace boost{ namespace icl
{
    namespace detail
    {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(segment_type)
    }

    template <class Type>
    struct has_segment_type 
      : mpl::bool_<detail::has_segment_type<Type>::value>
    {};

    template <class Type, bool has_segment_type> 
    struct get_segment_type;

    template <class Type>
    struct get_segment_type<Type, false>
    {
        typedef no_type type;
    };

    template <class Type>
    struct get_segment_type<Type, true>
    {
        typedef typename Type::segment_type type;
    };

    template <class Type>
    struct segment_type_of
    {
        typedef typename 
            get_segment_type<Type, has_segment_type<Type>::value>::type type;
    };

}} // namespace boost icl

#endif



/* segment_type_of.hpp
bHJD5PjLHKStW+zRfIyPb/CTafzJKEY4Zlxxi4RppilM9saLfogHq4fM9exfiHDrR0KsjkLtRQnHZ7zkMlC+xJJFCcn+ZIOgdeHjRiH7nV3uC4rMxj4rlrU0R6yMpLyK+lUkhGKDVS3yI/nBuEe1TY51LtEyHZ5IWaVQt5b9qGJQxUtiULU5yW1DzK1kM75pzvwsYwkyA2OhsWI4zvjCgmzzfUpRrmuyTXa7EQSLmJM4FNPS3c6i9Lwid1ZGLuMoehq7WNz5hGC3EpeKF4ZNGA9nViG/Z0NhiIYfhc4sjHjE6INpec50RJA1SXyc8Xn5rlzjMgQTV4B0k1dsd6UBVxvvylXxeibZPQnDnzQRH4oU5ZPtSqPrYZzZeRkiXHaWC3pPEtnAT85KdxUVYuDopi/w3QcRn7CtXc6dOdMMU/pY9fFLVh+ZBlYjHou5NbgpEknY6tM5T4nO9SICbpUmndRx0FCqIC4imtJvBsvQuISdXaivQuhdwG2NglGcHvhQw+kOGqrw5QYCr4wFtChWPa1hykQ/XBrBkpg3UCOYPa4fZN7BCXfQRqPij+a20mcYz8tPemER1tin0L1L2SitDMYEgjokQAqoiSEBHEC6T0LzyGZXiwOhYkeFpwzOWP+u9v1srJO3ZmWaGpeFFmnAt+BPT281ZYSTreJZujJZtuMZqqjwCKkoyR3JlmnQT1SVHjbYQMEf2TTtbH9wQKqUCGoBBNP05Qk0QocrNwNSgP3vxG/5DbAVhh+tx+wiHN7340frVLvJ08pEux0/WsPag99QvGfiR/S9+M3Ae0DQX8DvfrxvwI/ie5Hiw/trgv4Sfp/g/TsRfh9+yTcm2kfgR/SX8QvgfR5+FP4V/FbhfZ2gv0r+b4JeE37kfg2/FXhfix/F9zrFifcDRI+rD+K3ldgitpBNw6/UFrU5bC5b0FZu89iCoPhsXmAKsI7qBCQcuZ3w4wZMQ8ga2E2NImwZ3j14L6cYQcvXY62Cy4tYIg36XkPideA9xQaLNLZ/5xOgtQbpFrFsuMkqsdUUuD/IIoIfoz3qIY1wulsfuOEkbLgyaonADOf1FVeWFQV8Vb6A6XbobkevlJE6Q2PBMnUkNgxxolAJR1JIcpeRjCIcRKDwS0spbKuadI/pfbgjZaRT73VdU9IynbkZLkcvcXdMb3yKaNR7iQm3WjZaWJPLBWv45AYa6wfGwNbtixLaUVyDgvJigUHQKVUyndxJ/GkDBRmJuUWpIUFZeZRzzfFwfjgeuOV40PsaI4OxdMRVTb/ZAcVwjhhOT5Jm8W8MknQcf1MPI/BUSVol5FykJil1JPdBImsDR5KqsXFbJbggyTF0ZL4rx2AIuFIGj5wyZUqSY0DqSHipYnvQ1C+pR0dVPmO5T+mhQNb+wEhUsTFupBrldBnJGjDSmmH1Yzprx2pLuTOEaCJ7XOBdc6Z2tYYlE/hCD7xWWJ0GFnSMdGj6yXEDf7R1ZmNgoU2ntd2w1VqsW/TuZtowkhUaChLd+LJO8iaoYeV2xz5UutG24sfN9w1xYGvfA5Y0u2qFll6LhvtBbXqfPDK5WndXVts8frReZ6AMKCM82h6aij68RJ9eRCOUXnwPL7zkZqWTV/ZHZab7I0aji9DILz+ivx2pxuuFf2+Io+a0TbG5xNqN1zfSQd/g/lZfxaLhlc4eRtsfyYUR308Ew6JIUNjXH0lbM1SIHEgOpzfG2KAzRnZWYVZFUyldEIkzW7h2ycFxOeAClmU51ZUpAihQ7KtgSOt3M0JROlNu+qexjuQnzdKK6IvkAYnnvOPNYDprhlwYavki1CLAU8Mh8yhRs0ORmZ4IzSLZJ+dDd9MFro58ISWkK3QdJlI=
*/