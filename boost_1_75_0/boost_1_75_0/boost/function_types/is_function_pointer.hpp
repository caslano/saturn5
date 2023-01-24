
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::pointer_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function_pointer,(T,Tag))
    };
  }
}

#endif

/* is_function_pointer.hpp
fLZX30bYMUYIrb+lu4vAMjOLG3GiaefLG06K/MwMxvGwg0GmY51uzgCVDVrCQ6axAv9RIYXHGw5jbp7wAUjSh63RfABQNurUB4Pq5ZB7m7ZatzwpTB5TniTw1Lk1n4B4nU3zX/UqeFIyUMr0dXKNyPPxvkCQzNdB4lYNEvHyvO9O6pJIxrJhZwADjybvAIA8tcwQRVEAADuVxrfFCSKqN1k1F3lZNdtn07QPzDHacGp48fd+/3hx1CHUG0a8CBnvgxczchkQ0AUeTEUqkcqXcGvBHfLaUBO/PBpeABAaqseViet9cWWaP1wpUit11uNKYxgI1+5wA87kjGsLzvx8uX+c6TRL4Ey7WQS8d54m4KmxJQhllu/To8zRDLpI98Ga7WN9sQYA9gbQfkQHeVE7BFEWQ6ICHyS6bZ0vElXpkGhcG5Bo4Ni2IFF1IkIkzeiEfnYGQeGNpwL4+3y+t1tr/j7b7w/o7zMz2+S6DdiwIebyQfl57jCo/8r9bRnrRYmBvH4GzxDrlz5D7/Ni0Y/5zB5tzOZynzF3b33Mt+S5J+ej39t9bRlrQS8RGtB7rG9NN8T9hJGN3aOH5knyTNI8K0ru8+OkOSbblSqdhuJR97XFC3P/ZX4c7LuoYyHfeFCxxqvxjDfvVoeVi/q3L0djwHnQvlXeo4tJdFUoKoSyZFQIjWpAhdBlW2I5+3zNCDUm0YOj1ZhEA2+JFtGF
*/