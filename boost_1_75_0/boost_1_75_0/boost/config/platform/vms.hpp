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
7H/lPCrrubFRIWV92wH/0zYK+6cj8PJoft/pJqdvwg/hTpkdJ8pEdo7/WZVoATnjDjuGlZ2QccJxzYWVCWP05uUuGzuD/kkQUrzFv+Ywzy4ZlRV3Je3FFH4+MlrnSPjp5YtrBh/bB6IuUoxrW0TCyfZRL+lH//4xlOD52CnYQdAuJWns/VulX1QQjTotLx5/je1pf+KjzBlQT6PxU4TSZ733xmY72U/7+RuNOzVsXr143/uxw7+U+ynv3x+bGnW8yWJ/0o89RDiBuCKvdGlDaC9v2sOLwpWu137/p7b2hMuRNYk/o6/LUMf2hJY11lKK7ty8u3eawjHpEKV7fC0F/nyKh1Yf+ytMEWCiQVFtNuYFOlrzH5rz+7A3J7oZGVUhdeIREt+DnxUZkWbUnzffy8E+PBIScmb0f6AUdbNeoZ3DC0eICInPAt+DX3Crmu5Kf733grDFVyv49278Sqe4/dXBQB92TJ5XWS9n5z67vVaLTOc5HO3VXpTDVlDWTzjmtJ8vQTtPcO3HR+HMrzxqHEnN79Wf7Ru/bBF52g/qvuBk/i8uOzGcZp7H+Xf/Hwm1T5Fn7W1j9545IMttOtkk7m/SmpZbif9wCuRgjbeMLxvMl3NqeySf6HVSYkv89Fd35J58Bm4tCnU4UInPhX9N7E+scbLY98znzZ8aC4ZO/8gcwBcnuX9PfJGo2I3aTrSv5w2vFPM6v0bryiQM
*/