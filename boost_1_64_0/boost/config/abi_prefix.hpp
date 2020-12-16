//  abi_prefix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# define BOOST_CONFIG_ABI_PREFIX_HPP
#else
# error double inclusion of header boost/config/abi_prefix.hpp is an error
#endif

#include <boost/config.hpp>

// this must occur after all other includes and before any code appears:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif


/* abi_prefix.hpp
IZylP029k/XjxqbjS+q/66N0egYObQUQ2OI0GUPwo2sIbhJD8CsM1xGge9j0LNFLRObneZi6qz/PmlU/ls3wX6jwrD0pDO/M+/keXiy93JfV/xpcu7f1fr4/lQeF50s3ETOz7ZFybYYaFmR8HL9IZXPhFbC94lUguvTIaeXjbj8/+/6pFZas8iCsYoeFhQ7K6RsVKEi+3ow9J0xzHk9452dFdfqA6R+YvCt8sE7tZxmTX0ZD2D3VR2N5/LzugxVRx42OLS9ZCziMWUDAo3Xsix+xjuFwtI7YD9czjNmSyscphkfriK+/NsVneqqTZuMOjJmIW2e5/nUJRvaScVy6HsE77lLE713D3nWX4Cm0ylb9xllXQnaG+zNoY3iEy89wEdPjHJ5nraUYP8LFMxjksONbXNefWcdw+6gPeVvX2zz9WBryj53fIo8d8fLzW+SwI160LWrj/FwA999nN47kNd0Htc+6yebWdQLz+SWI49EqpukD4xQbdObz8zZbnLvzfH7PtRg+Mp/PXpvxRubz/BbG687n63COnc/rr8vwkfn8U867aj5//nqcq/MZ28521nYSkWRBmnjl/9yBw37GU9SYt5ufecbmyArfWEH8IT5oL0/XnTX6Oz/uRLk7r9W4ZWPXX6e/syNNcl+F4XU2InZpvcbwSJPcs9iAmH20h2E/a6Pm8ONM1C83EbzZJMT0/FRjumqjjBhvv9vhfXqzxvj0HGVffi3Eh9J6+doU42mV10FsZFovI8dKK94Z0DhWa8DwnFRjmA+I9bcSzKor56/fYHrJgDL+DfT39mgTZcZvqDF9rInnXmx/2BNFFGe550hyxyo+NFHQK1bYRi6/h7eRMgT3vnLVdj91G1Fx3FLPC8fq/WE1lC0qAZKuL6ufn0DcdZxo37FrjcZY90NsYqwdxlVvMKNuebd97nrN4d0KjtGvrXFUwLCxTYDNzJJuEvYE0FY2YLrLw+9v1N91l4O69lwLvvNI4F6TldeVk1eVm6z+zWHHWP5jSHPmh+CCa/9esvbcANjMrLY0CYYmzcIS03BuC3AGJ+f69WYJxrNvxTOSWeI52er3xOp48v38H7GyYUfXGOftaxUP4qzPaoFvOv295hzjneyMJ6lCeOSQCVKyporjntyld1r3R1N4Ni1DMTT153PoK0wuFF6WVakrc9EVRevN3NZ38TcVReEGXhkIbo+Uh7f7Xdb7BhnD841YDBsXHTqjE0w2FmlS5J6Kc7fNUeuO/bssW71xVWSho7LHPpIeWzAyfS7jhlngysQXZFaDMnifgMXRE9KJK6cKEhSyjqTRZwuVq5SYmwVFEoCYfRy9C9+tsbAcEUu39IuoXYOMOK+8wMvNLdwsdAMfxOxTTpS5xGVKJ1P/+QHK9BaGZa7wNMVFnsiqgugNHSmjzNi7mUzuOIkTpqWWwWB4PaQyhfCDMFRZkQvYAZ1l1zdamZ1UphSR56ZFlXmC9mp2vu2hMlLkKpg4DaXgqyaeBzGX8dIkqO9C8NWSVVd5HoSFWwZVnDdnvNZ6Fu+jvJu3q1KmUZqWHjl7bSxMT2DC6vOv56u9uf7++jwzpsedMB/8rBrrzk8ghkeddNy6AutOctYZ41En7xt/MKJv1HNE5H0feNqzGc5d1tLvw3Pk5fUM1+eY7RnqftrHHUjgdCAoRDORsf0yxZR7j9ivvCKvEng5sjD0PuwY5VYic0rpeoWoN0pnT7MuE89o59kZref6QQTPLB+leVNoL4TFI83zuArLTGitPB5PBi5rZ3FU+pWOyJl77t+r/sAy13Ztnzmu/eJo1thYhPYpnzWufeIghjbUz76Tr9XDNPLjLFy1r2k9buL56sXaRrkfW8c=
*/