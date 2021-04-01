/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
States of comparison and inclusion relations as static constants
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214
#define  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214

namespace boost{namespace icl
{
    namespace comparison
    {
        static const int less    = -1;
        static const int equal   =  0;
        static const int greater =  1;
    }

    namespace inclusion
    {
        static const int unrelated =  0;
        static const int subset    =  1;
        static const int superset  =  2;
        static const int equal     =  3;
    }


}} // namespace icl boost

#endif // BOOST_ICL_RELATION_STATE_HPP_JOFA_090214



/* relation_state.hpp
5yvKRFnv7xru9hOFDRL2+gmXW7tGmwXf6lz0rXvWmJNsNy0ynm5MhRunooKeLbcbW9aGuG3QbqPKmcVCKgV2q0Ks4Hx3BHi8yzjCxbIAf4EXTjP4jnceYDOzNz4JNDto6o/FCS9INMTJyq5mA43GgUyNktGduoCIILihnm2liDA7tJ79TOYSA7XqjwdJah8EsBH9IFiVWb2nG22eq9Qki4BQVCC0OCfuikSo2EGDMLFldK0+SIaRk25b8dYkIyTPOe3qLF836mw19hGOkFe7/svfhgG0/5zHJ7wjOlCMmkXi681PjPeGKb53tWVlHjbwfk2Lvakk8/ZSmiFiDh7rFC+az7fCwDjB0DEVjrj66T084/mFcopXyVOxXI7LAEvore2dbbLrrItkg3tkdQtoEKzMFlQTEhNvwgQMh+JeCdf4KwrGIWHtKOqTydY+/Xa2W5vAseEg8ktSpfd+R/teFcXS1NdtQEZFKbJ30lEYPXjOCloC62sFuuxhBhoa08p3mh+LzxIDRcAewHTmIGjbNorHrAv7mUIoQPMzfsusCOQuL/S/1lKechMWAA==
*/