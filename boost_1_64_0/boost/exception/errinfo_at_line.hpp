//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593
#define BOOST_EXCEPTION_E7255CE26C1211DE85800C9155D89593

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Use with parsing errors exceptions, for example in a XML file parser.
    typedef error_info<struct errinfo_at_line_,int> errinfo_at_line;
    }

#endif

/* errinfo_at_line.hpp
m+ioBNetxDQjQ1W/XBQkxswQjjrH2hG1gtSHCwdZdi/nbn5dkc0ZhDtTgQpMsVGHnJd5TbASU3YYbJScGQ1NJ7xCdJkixOlHnxjXOyxZJo+/TMe58TFn3w+ObRAYhinqz62mYhenQ1nda+eTMBtMmqKBBv07tUXVi1JESllnUIG9XYOXWGbc9IoIUc98OSEAJE895wlvq6gvgNB+rdEC5LadIZzEhTa3bSa7ftJZPzPAt9/3LDkZefEHmZ0PHS7qgS5sUb12MHdVaWlSilR+3NbD1BKDo+NRMbQGY6SUVQMDnZjFMkw6cQl5YGbC0d0ODWVHgdt6RAlhA7ImveLIx+jAZCydZXMvp0G7SVDRLPtN9Tyu4/ogAeUtn3/c2QpoR0i0VcED7aOO5+P40Al9NP/R1xVogp+Jku1WAi4lODk4ejEdSIIKAKhZ2nLfJlThlIVobnbfDa3XgtsaS5vQ9afBOzCMCYY3EKJpAaMZtOMtP0FBAuhEFIo8PYtTj7yc37hoLc44cZf/09NUo1ABbiUIgn5p440juA81qhVV/sIQklwjb2I3F5JWtQ==
*/