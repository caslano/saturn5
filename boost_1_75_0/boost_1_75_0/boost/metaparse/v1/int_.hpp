#ifndef BOOST_METAPARSE_V1_INT__HPP
#define BOOST_METAPARSE_V1_INT__HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit_val.hpp>
#include <boost/metaparse/v1/foldl1.hpp>
#include <boost/metaparse/v1/impl/next_digit.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef foldl1<digit_val, boost::mpl::int_<0>, impl::next_digit> int_;
    }
  }
}

#endif


/* int_.hpp
iKHsDD+1P8ZhXGZZI3xhu+4sZ81k9yxrxHt+4dz4e378mh+/4MdPm816vMCgmbTEjEFzTGB3077cQXr0iGwDqi4Eamb4z5x9Fgli/U9QM+MuRIgftr8rYYAznH/mX4lFo/hNgWiTa5lD4QTrSWFCPy1C4bAO7/pNEREkfratcZCH6fBnSNwggj0z7h+VWSozu3zqIW/AVwFYCwH3Wq/6q0c9hPbZKQ0i1Kea3VfHdIRq3blhClBMwF/Jy2pzvRUJBTHOd/BIwRJcVnCyGk9iauAseVLDk5iF+wBofep37INlqk8rbGQLGArVsT/y5sB/AwuP2hzFK8DAW1hQHeMofg53zsxa1qIy7ac2RfkIATPnsNNoyZo61F3tKH6Q9tfNLwP3c69NUxH2OW8MRDz41mo/teJL1uJLXhYvwUttbDwbk43v9adgiavo0TIttw3Lmdfy1DB/D6xqzy7c1gbvnFjWdD+ULZ+KtDv4XuD+6MxJuhdNYsGeKWAe+myyXdZVzIQvROgUBQ6V0y47387oMK2fzRdReWOw6wj2BS3hfDsth7LJdo52XYY6BWsBa97zGbx5O1nPmu7DOz+4Bz7ONrWZGbCprboHzQW8AemThePWUbRLCWnAW72hAaP4969h77+avUJ7tjdvQ7/JCCVY9hFBHhUwwgEgADdUfszr5yncpnv0TWCU9viPMB24P5yORaPVr5PgySkNwv2R
*/