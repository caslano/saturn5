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
smkRZvf260E2YNb7mf3Hewt184pMU1w73GuZWf6Oi3Axv3Ok0x5Y+LkZX7cQ7+nEaQANwpphtXJaH1mabRpN63lJl32zPtLkO+xQq40lfD9isxyr1keKVdoGFMOaTQynCqE2x2rjSXMsQa2fNFnPB0iDbbAx0nC/QauniUr7YcSoHCGcoUzL9fS6Lwr7dEE4edK9X+t072Fiee6dgD7X6tw7AX2ep/NeVYf7emr981mn3gbm5QKlF9zY9xGSBc+JIx2Di+AeR7FGAWE4R7POLYbCOUayZZjmgtP8szSORX2we6jb1N7cEE6sQlZUjM8iGlGM3zMlYrPCUOnasuMyZGSJZq6POuoYd52okeJYYCcu9qBeiJ7QAeFXoox/dxyHHPd7orUU8nfgIsdxvwf5/KwKZt6JlkG448zCYKHsapYPDcwdxC9c8Bu3rvVCuZKWmpXxSq0I2QLhN6RPznyh8I/3udvfuyl1sY42lbroB7akLvqBbanbhQijxZIZ5YFyW6w59ZKNgdJwgvaYtRo8h3WJ5mlC46FLQwZbgsPTEu6/THEzQlZJcfYu3f/E0MNJgDA+qXm7uTiBumLD+FRHTwPCOCnO/TFA5SknY+KMlVMUT0ri1wjUm1NjnkXSRWdShj6o1dxf/HTIsUhwLFAx81I0y4fq45ViFfMXxwK1r27aHL0W00q2sWa9OQ7xOSP0QhFnnzUwXZ9VvNWseHdE35meb2ERti1L7PtjvF2lZ9FZ0kdNslCnfWslE3tCfz7UzXizKEZcp6w8uq58oaOnAWn4ouRuaFcWNubvl6K+oMDpnudIL5Yl9igpbedKrrKMxv08T6ra2nmK67R/JerhdnK+4rqdfDX08CMF1x+HPF7voB5c4Hup3tHYIDFz4Ax1/+DBB2V0kWLhF2SM68XK536QQnoviXP6EYRhfD3qgb4BhHFplPt9gcuUByo2pOVyzdJYWq6I+jgtV0Z4mJaroh5OyzfinNJCY4zssZ+sII3XCL1UrGGglP5rmfFwLrHrmKlxpOuZeXvm3cB69pYE742seXMqb2I9+MRE44zM6Q3ZrJsg8dzLkJluy+JgDOpm9oSTR4B/2+PYDrAF4D1ukVz9RKRxyMCT1EqUSzQOGfIl/C75XsDkdbcGTH4Pv41ZlpaukTb+7ruddTfn/Pus6Scz3euOwCPvdadg9VIrGyfFcclAz7Lf5vsPmYVPTBybZE49UdrHl3XVh73bZ4sh0cR+HLI6n3FzDzP/yUz8J5JH6sBPJe9QB+6VnkgduE/yoA7cHzB53QM+w+pP7MGAyfg85DPZNIA/HHJuFjDP52cdeaE4OlqpJSaXzJuyUjOB2jGXR/ga+gmL+fco6vL5O1pJqnRYAo1xoge/wsMyA9ozWOrZrqHwusI0PiZZpH//uOSif/9LqYv+/ROeXh6pkv9XUhf9/l9LHe6MefcbqUNyD20069lpiJXFXr7Bmx33onhSXaOzGToL5H/q//O7tvO09MOujZCRwJ6RzG4OTnX/WZ+lhWLLntbqnrG/DT31Gj5giD/n8exQL4osxe15yYP+5gs+a9syeVHq4jzgl6QOTyVO58seAz3b+w7YKzHWHgX2uwgzOQjs1Qgzd4V68JrH0v+rHvzev+Z/1oPX/z9/FjzE6Y3Q79aAJmV1D7rmzf//GrdfyB/UNa26qzhUL/4oPamsGDT+GvA2nYH2J9LpJVYpd2VfFpC97TOjG0jPxHeQ4S/ddqXaqlA9TfHaPwPv7TOfYIYXuAFLZO8qxt+E/qIY75P1HrD+GX39OXiqwVisr8GiVXnu8gfMcdYu5elfhV4aLxcq2QhaUmrDwc3ULv7GHvsJFc/1DPQsANs=
*/