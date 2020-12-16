//  abi_sufffix header  -------------------------------------------------------//

// (c) Copyright John Maddock 2003
   
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).

// This header should be #included AFTER code that was preceded by a #include
// <boost/config/abi_prefix.hpp>.

#ifndef BOOST_CONFIG_ABI_PREFIX_HPP
# error Header boost/config/abi_suffix.hpp must only be used after boost/config/abi_prefix.hpp
#else
# undef BOOST_CONFIG_ABI_PREFIX_HPP
#endif

// the suffix header occurs after all of our code:
#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#if defined( __BORLANDC__ )
#pragma nopushoptwarn
#endif



/* abi_suffix.hpp
q3j++4h3NPjpjvPXT4G8xs8gzs92z51n+uFsFucWe9Sc7HstxuY45zR2GkGyv7+2wc4gRs9iAYN8NXoBw70BjaEsYo/YABgrD7RRdWwjYDDKHQc+2rr4HpRRRzgvH9cYCwdt1GkMw8H7EwffwvfEKhm5RVG57RxbZp7yqeX5+2C6zV80kLscs0xPItIqScO08Fo9x+55aP/+vR1KxA5Tz0CHSjMxCp8arP/WBjtDQJx/vo3vZ+YxPMkOVu2vydRPnFdRfVIEuRu6VSQg4h1m/scOGbkrVK4SgetkkS/LRrDuibkcjn+Wzf5CBjJz0lrOPlrFsYzKlKKQVenDlYu+iSB0+fu4zJ6387mNB5cBK187K2Mi2DcKKnNAVkWWu74j6i1SW39MubmI/Sj2VC0QOHyh9javj72dz2dkGCUycn2h9mFrM6KHJsA/Hori+xsm54o4qII8TlMipz3lYZj7TZqeRmUnZFBGkZ9n9Y0hw37kXU2dpNyDSe7kYSRxbEDli6mpi5TvhSLLJAz+gajNqikXp/CE955YSnpAUm3L+GRQ2blD+0noaA9jGutqD2z9dAn7uGYzFPfY1jAMzzHRnuJawKFPmpntw3fcg66/z9o+E/6uv1tHyIhfXg+45a0A5eH+OsF7C4jfGt8EIc4WCvrdEO6tIcdaEWhdaF8XePZRNuPcQHM6jrLRPs8NgWNNuKkt/hsxfOgsedeNGT50ljx/E413+YfYrjF+7Ir4lZsRvMNHgn8LjesqaPsweN4tDY7H2Igt7ySYDhr3IW5DMMtvwtbbIQYdzZDvgmO317i9R2bqWI2Tmf0YWevfETAY2+r6ijJvvBN8h/Gu2f+YJu8RP31nguHepL4TcRfEdPnwt4z/uhvBYY/LuoP/3TE/ODJ5Zvr4NNZmZnf7O4Dr+TIYYdyrinhAfRetHeYoSj232b5VzTVeBe1+cWYGIldb1m32qB5zG4WdA+wxvamTk6C1/l7B3tWr676ipxrHyeNkHj+m+oJvQ1h6Eq2EUCvuRSNHGVU2qsfI/GatwUF6oBTNINZfpzFolNbee7zewpo4KGnynmuDzVlZ0Czk7B6nHJ4vqKfmQK8ws/iYSZZenBufOwrz30nIJOyDbqD82ZyE/BsLSu/wg+VRsOmqvp2qv3muN8b3rL7F5Hm9+GYdxyX1HH/xFARs49+ocWWuVZkLPjlYOWXjX6/xPqlXHL9Y44uPPI4wx79m8AP7kUHXal+t8d5Mbx8nAY42i+8OefTI+vvk8cWZuh6YvdqXQB0DHUdkbfygxq4D9a8D4/n2FUsn1NvL16jx75UgN72oDmWn5peb7w+8Dfi1aL6fntwLzjBxLflL2I+FcHQR4D3ENeb7IzFN6L/3lWS83h9VmQQjgmJ+ceHE0FzlDOXeo6qqpHJKV6gyN06VBmhr0i6/LzX5O03LB+f1aw2+2AcTAwNL9otGdh8Ks/z7AuBmcN1H3sKsAwzLldUdtLN2Lc0x0N1b7GnXs7C9gOEbJo7tI2+7bmSwhZH19fNNOY2sr5/T+Kj6+llMFyfRdn92g83rjstngMOyh+fvpw2um2Zq9mxezG1FhJGXOqUs2jUPrjXUjb696qeYeqz6y56732PIFsazqC5PihwuBAbqL/WGrJoEL8AkcanXX1LGLafnjoNRD4BmDu1R9/mnal2410d15cILI7eqwkj0lUGSRy4unQJNOgIzqWm/VCYsRRpUSZbFnqhkUKq0+MlhPUv1/EP79HJqcWVpuqf/Ltq0iJcQXVEqXCeJY1eCRbcoKYMjq9GFaaG6KqUhq9xUpaW2vzF1WlkoAVPBTWqgf5hQ/YOo0zI99Eb28/C0aUwXDtxJHqg=
*/