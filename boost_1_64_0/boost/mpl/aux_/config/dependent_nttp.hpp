
#ifndef BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// GCC and EDG-based compilers incorrectly reject the following code:
//   template< typename T, T n > struct a;
//   template< typename T > struct b;
//   template< typename T, T n > struct b< a<T,n> > {};

#if    !defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__EDG_VERSION__, BOOST_TESTED_AT(300)) \
        || BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302)) \
        )

#   define BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC

#endif

#endif // BOOST_MPL_AUX_CONFIG_DEPENDENT_NTTP_HPP_INCLUDED

/* dependent_nttp.hpp
yY9mPinbt/rQfeXVA0KUzBWT67alvRbUnaYVPxRMX/uy+RzQCF4/f7WDeT9lnzyDU29Wl98PnxF8+k6ByqvxkT4hK5e6mLye0nzqZNU5lfDLrkmD/jpn1eJqH5azNlTlYahmRx6Tl9/21bfbNPNHz+740QWvd1JgVPR+/6nJE9+O8pqVl9RrWuCntAPZB8ZsMG8stU6lF7/ukX+W0aaVsO9uzJKUFDXa+2z1ecMd4zX9LtXs+50f2PeCzkk1DVk5wrJy93YX45U3lhVlXnWNrs0NWRu5fKBd3IGa2hzrEpPWBfNLK2rsnl9cr9foAq8UvSvbH/GGyPg4rTlZkdrUn3NG+1LJFnpq3tEdC/0LzS6wCt9nKRhNc/MfTb3b/2jWgshTU48tobrplboDqRfx47d909+QicvXaNOm5VFTX36QWn8+v7S7/v2Cv0r5Dufbm4QIjYiW6sNjLE6f/R4RYKi7KDnRpuH50jlfxhrrGQ6tP9E0fvcop8gvTbR0/Z6po4LCzw6zyRpxpMJpI5hX9PxQdcoV0qU/+Yd9T+ReqXmejmPYghGqxtqxN+4tLNwsN2ntw0WfU8tL2iJ2vhi15yprsP466V2l/r0mequOuF8oM2Jyxc3NjtppX8Zee2ZvtVBO+cAeLeZTW02Lm2FVh3hWLLtefbL0941KndZkLq91MHfWxaWbPJ8O9NRg/3zXr2RWcF5QM6+Exxl+8dgm78r84RYem7Irtn+5FddfqpLgy/Xv626onPSIrj65fefulZsl8fs3sh8eZrNW2stUJjfqqn/p/VbjZp+tnvKHTtA/LJ6ZsSzywFOnq9ptVmscvGe39o8zvOz+dcXikrKZ+ofvpEkLGj73tw1aenP8eK+UPh4a9uVX+gyOPEUd5FLl2R2/se9Z7fk+qWrruz0nbcMUsjbOXcZjj/midUeHokdRdhsylO0fP2tKz9gfo4wnvfsSa2yf1Fb/PS2wVOfRNFbDBA+nT8ZHHuDvT9xLObN6nor+tObaq1FXHqm2LZU7uuTm/uOXUyddHuXhZvQjvajgeLVu7dNTWmdtnPxPrb9qGhKQ+tXi3MPzP9d+dRnUnzbk0tl4Z2WDt38FTBsSUGYkw1wr5l/MUuuk7Udou5qzNBTnrHUL2i1pef4gF4SNop03vu+9ozVsN39cr7iiMytfny8wcteOfJ5Oam0YKbP95euxpdfqi/jDlA/aMGjuBVsdzicVnByZuHV5kKFyjyaDbNYcc+sL0bOTh9W6ONmnMk8erba+rguG7H35aar2pdPdLY8eWp5bM1wplid9imrHJsy4SaphtGRe2/WlqU+jz4rjbxJWvtH7cbvfgQ+HDHVtn/YKyiwu/Dr3yuvb0ePHHNu220L58+vEh2FqioXz2/Y0rfgUu2fWAsXDfvJzV238edLh1j61BXYRizm14+3NVwccXn/F5FFlhrN1OmfG4fzMAx92OZ5KXf/d//4xv0Unz//1/MyLj6TRNxTkU4/WL9QYQd6ZXUYuWNbHuk62b/+f1wOd3wwu32u3cvjseN0Zco5tb/vGzHm1pywhPi8/suyWn/MNpuFftV2UY+fRzH7bDdwMy94tCG5YsDxwqtOFlX3/2fJ3U2/47s+0GqvXGndmHrrhWpVAUZb1VPuYejMlPC2vefaxna5XjxxubRpmLu2/YmrDd1LBxe9etrPcs0hK6ebye8ksn56XU2sSIq4oc9rMJn0Zvk39rV9osU2SrpvtmbCYqsakE8av38l7B28pjN/nsHPLuo0a9erqG0qcqYU3z0lafuzvw5Ye15iz3SpaT2k6J9X3hf2TAUYxPd8GBB3ud+Ch2uyivlr5t3brZw0ZFLPQFSibyL0=
*/