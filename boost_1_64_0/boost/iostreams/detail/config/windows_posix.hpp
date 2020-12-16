// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2004-2007 Jonathan Turkanis
// (C) Copyright 2002, 2003 Beman Dawes   Boost.Filesystem
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

//------------------From boost/libs/filesystem/src/path_posix_windows.cpp-----//

// BOOST_IOSTREAMS_POSIX or BOOST_IOSTREAMS_WINDOWS specify which API to use.
#if !defined( BOOST_IOSTREAMS_WINDOWS ) && !defined( BOOST_IOSTREAMS_POSIX )
# if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && \
     !defined(__CYGWIN__) \
     /**/
#  define BOOST_IOSTREAMS_WINDOWS
# else
#  define BOOST_IOSTREAMS_POSIX
# endif
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_WINDOWS_POSIX_HPP_INCLUDED

/* windows_posix.hpp
KD1NEjmEfm2Unp4Ma8AOSn9OgZ1hR6W3nZTedIbnwi5wIDwNpsHuSl97Kj3qpfSoN1wEu8LrYDe4Wl0/DIvCc1NwiXq+REy+er5hdr0Az4fN4HDYBWbBXnAk7AMnwDPhKNgPjoaz4Fh4MRwH58EL4GLlf1OM58YVevzGxMG/H78z5OKzvJ8jFx+suu9NdA8en29OfAidZ8vl7OI5g8f3jDnn9ydWBY/NWXPbgj/f8+Y2bE+wdmPexli/5XsUmDRMDmY5ZhMmgDmI+RKT+GCC1RGTirngweqz6qp/1b/qX/Wv+lf9+7n9jtP5f/buMvsAwJ98/t8DjvP/Z6rz/7LV+s+LMOs6MZ4Zqdf/XdC7e1/ZsSe7LjyuA+V+vR7jQIq872f63rgOFL+GMy/Ma0Dxazj7zL2WzxC/e01n21HR13S+K/dmVXpe39JGP31NJ8/FNeSiriUaznFIqngumd5zebC2Jb8rE5g3Ufwz92aNMuWb2i1jWr+pzni5fJTaV6DWpywQe27CTdZZ8aFrPsYwckYIjzPfb8hz4jbmuT735SpxH5Fg0AHurfzck2XifmFCeM3nLLEb90QTVvRzT34pbkMTGqpwVoh9lNWBfyY9cj7XIkv0aMoSx1r8s8fKnhi1Z5PdnONsOyfFMFuz0eri1j+9RmiOhJtt9SHezmqN031y7fn41pTsQb4ETqxJ5t1DA+aNuliv+TdZS+OG+cLr454Vv0kJCcxKD4lb4/shPl6db+azlsozjfDH86b1MOF09reRdZq7Sf9Wua9LQopVw5GmAnsDnt6rMnIMfniLWZ83CL9gNlDlvwr3F75brQbIlnvd501I2Mvj61qT4sPlrFTu6afkFdahunpP9z5xTzN+M2Ov4ZsZ+38w7BdX5+zcJvGfLfsu7g2d/jDLudd3s8RVQ6/jWhzKg4TmcdcZnket21Lr5Noq2dSS528Yn+mrz/u5RCvF34HSsIk54FfUuTPRz6QJVDiThqWf8xboZ1s2XsqWsodlXUeft2qpsz47hM+kkOcYznRzb2so5jFMB19fawv5/Zpvk3Wq7U/Le0/8RouxK/nW1ncWJzn1sXz+TDSkA3OUS3x3xbdxnGtaUOCUWRvRZ7/VSunoIQmvtz+Br9IWYsp4GzXV94pRRxpX0MdJ/nX4svXRdS6Pp/OAGvJ9/Xx7zrQm71GbUc4TRlh1qJt9+PlbkiXfwA/72YKf7bafOlckhv0ccvnZF/ZT78oRbj+tlB+7YlrUCD++K/on1opL9LVMrMVlvV4vmIRxhduee35rh1v7ivnhcL90+cnAz2I73JpXZIX9HFZ+pmJvovZpP0g4d2Ae0iZ0bYcyej+N46yiKzHFyu4+1+gS4qzRINRmpXk+wyihQUiHrNDOdrV++ZKx3tYvx9rGGc4fEj/7Xd+UUecRVVgbHYhyRtE+1xlFxrOP1L7yB8fp79JUaG9L66m+np/6EX6Mp432eWoTDO2t3jFhbm8P2Wduyn0BtSeOdkjsj/imIf0XrYWGPpWKi3/h+s3nqN+awnXifrvP1L46793QqeJ5m8lwkbg/7TO0p9wb/bzNT0hLibjv9rVSbWq22K/3DaQWuoX0PMUTvGz9Sp/n9v3E0BlEJ1g1TW0u8ZnO1TTu3cGvsd+AH/ocPNsqcd/l+w2rYpqrdabT5drVvn6sfN/Fs+2VZ8PN9WzGM9UmmPsWR4irVNx26HPe5oi9t/lMNdzMe47UGaXi/rDPvV9DzhWVZ0zQ+1++Er+cMarajm/EvQ3xNhE5BHm2HeKn1NfUOs3d1uo+8Z91OOwxcd7DExvOs9Tt/hbx1xVdaaqfIXRvOyuJf40lL5zhzWMtXTsr6nmX+vk=
*/