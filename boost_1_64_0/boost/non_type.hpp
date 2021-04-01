// -------------------------------------
//
//           (C) Copyright Gennaro Prota 2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// ------------------------------------------------------

#ifndef BOOST_NON_TYPE_HPP_GP_20030417
#define BOOST_NON_TYPE_HPP_GP_20030417


namespace boost {

  // Just a simple "envelope" for non-type template parameters. Useful
  // to work around some MSVC deficiencies.

 template <typename T, T n>
 struct non_type { };


}


#endif // include guard

/* non_type.hpp
7JPd6MoqhCDeeV2GtVOkBHbh4gGCGlloJldXHtnNHIMUQuXf8zpGPbVltTImGUkKv5AQquZ73L3af0d0EK7uDqkux1gV4nyr96eCkjLHxpJykQJDo9VtzUTw9lEPqdBmoKf2ZmVjOXjDX9AZ0uN8RydzJ/rPBhc6HXAufG2h/T1rPhfeZfAmmPvqpx0hUq9EAkDffMBeuGl7Ibr/AJSAvr8q77PymvuPaPZkP7B8W0igFAbm6VuZJJbgCaFiwIQWI906CcxmFrsyFk8ZXcBpsB/TF5jK36m2GhHpcLgHBOx+63JyyNLl9H3xY+hUd0ndDIlmfeL/ITenVtgaTVJGeXsvWFeqZEOgXXyDZ795ybzn0+sI6wqJQOp69wyQeF+cgXGKFZV7C+3ywyb22T9TS6qLHhLVaCIApH5cTSOo74vrs4bm+OGUp91vsZZrj9qHPwtY7N/Sl8ZZmbt9Jtmt0L97lTll15U8gr04emoPKlcTgFF6eK4gmLrDjOlf6wuEbr+A3egQJn6UnMumJgHZ8hNhrSYqHIv+JdkmJ0TJl9q82edbAF7Vm5Oigg==
*/