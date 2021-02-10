/*
Copyright 2015 NumScale SAS
Copyright 2015 LRI UMR 8623 CNRS/University Paris Sud XI

Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ASSUME_ALIGNED_MSVC_HPP

#include <cstddef>

#define BOOST_ALIGN_ASSUME_ALIGNED(ptr, alignment) \
__assume((reinterpret_cast<std::size_t>(ptr) & ((alignment) - 1)) == 0)

#endif

/* assume_aligned_msvc.hpp
HBoAhi4j6aeL/E6H7he1YV1LZqLWrIozD6KVF9CO4FzewGZt98eybEKOotY9Mr1naFUZYmOa0DCbooPaVwJZSWof6iGRr0ZT1qygU0oTbaBC5J4Zcp9O7JHShnoKNLilBpJSzRBzSG0PUJnrmiW2cDyKzAYuJGkU2v5wsg6q703R2+OiFgLiZT7ujx3P3qtWAO7vLmIV2UWBLLiyXQzUagE2k8836mQoWtAGGptOPBvtP/EMEqExvVRpY5rK5rzKKtWFx48ehTBajc87Uj48Eo7JdMOQKnqV7WrE/V60dKl3sJer6reACOz21SItWmr+dOvp7GX4rL9TeZWUuwtqI/j0Bufv15OOLWvoMaF8F0MLRAvfphE9CGDbanTcjTUVEYQNX/NeSDPd0hxdpc/qf9EItX5Ik1XfQjm2UPcyGTeXkfe3tFXinmVfZhacSiXXj97s3BbSHBIRrCKUSKhCZ7q04zv8mX6iZtDU3ttWNMYcdrg9YA2NmdJzPVMUd5/1hFf1G0CkBY8zFQ4KDHxAHEd+rDdCrzUVKjW8a1gMI9S1LypjWBvrd64r1p4YSZWVHrpOc++ooJOZpJd7vJ/xtn6K9GYGGI9qo9SeqhW9wF4bC6kS9LcsNZgC9McCZNuogDoK8ur8o2jQTHW+
*/