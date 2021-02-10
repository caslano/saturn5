//  (C) Copyright Artyom Beilis 2010.  
//  Use, modification and distribution are subject to the  
//  Boost Software License, Version 1.0. (See accompanying file  
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 

#ifndef BOOST_CONFIG_PLATFORM_VMS_HPP 
#define BOOST_CONFIG_PLATFORM_VMS_HPP 

#define BOOST_PLATFORM "OpenVMS" 

#undef  BOOST_HAS_STDINT_H 
#define BOOST_HAS_UNISTD_H 
#define BOOST_HAS_NL_TYPES_H 
#define BOOST_HAS_GETTIMEOFDAY 
#define BOOST_HAS_DIRENT_H 
#define BOOST_HAS_PTHREADS 
#define BOOST_HAS_NANOSLEEP 
#define BOOST_HAS_CLOCK_GETTIME 
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define BOOST_HAS_LOG1P 
#define BOOST_HAS_EXPM1 
#define BOOST_HAS_THREADS 
#undef  BOOST_HAS_SCHED_YIELD 

#endif 

/* vms.hpp
s7GWPRj+ssewVDh49Yn0X4QPrp2TX/F/aCxfdoiie2g+6LjE9Q1QI9h73UcDeJPXPfS1V9Rinav3KHoD3FIlqb5GynkZqVfcaTxb/zEv7yq2ziT0xwM4/vTpD3gPH46Oz0y4IAWjOQSSFitarU04T/TOXxnZ7SxBv5pAJZDcOggYZkyA4Km8JRUFfM9ZTAtBEyACEiriiq3wBytAZhRSllMYe/7CcX+YcJuxOGvj3PEaRMbrPIGMbClUNKZs24QpSSWBpxgB4ydMSIxZS8YLC+EpSFptRBtGJUFywYFsCcvJCuGIhEzKUvw5GsV1lWMlo4THYhR3VFiZ3DypaoHZbMgd8FKC5FALaoKyN2HDE5aqFSnCzbJe5Uxk5j4tBCySEa9A0Dxvw6Ero6IpgULQsmUqSygxeybVInghFNptxjcHhkhrGyitqwLhkBa0SzgSb0JdJLTS9pqIDqVlWVP+Ssv2uSfAC8wKenYATtCDFRFMmHDjhJfePIQbezaz3XAB3new3UUb78pxL1AbDFEroLuyogKzqIBtypzR5AD8l066YYWXMJ7Ppo773Yv8mXNthxM4gd4xBLRUsv7Yg17OVqrvcGadnlpHuKF+RZSIu2hNJStSrtqMahIYMLgE1/45MZ5FXb4HtNbMlhXb
*/