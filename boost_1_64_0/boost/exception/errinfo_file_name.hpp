//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593
#define BOOST_EXCEPTION_FEE5120A6C1211DE94E8BC9155D89593

#include <string>

namespace
boost
    {
    template <class Tag,class T> class error_info;

    //Usage hint:
    //FILE * f=fopen(name,mode);
    //if( !f )
    //    BOOST_THROW_EXCEPTION(
    //        file_open_error() <<
    //        errinfo_file_name(name) <<
    //        errinfo_file_open_mode(mode) );
    typedef error_info<struct errinfo_file_name_,std::string> errinfo_file_name;
    }

#endif

/* errinfo_file_name.hpp
dxxkWuiuja1Z9+Uyg1K7IbUbvgBCjPibEovZ6QpXHGLXrKsQMZAZP2FFbKGv1jdBJAmLJN5Oc/LC3nnFUHAxagFIY9ew2F6jXzYrf+1V6gidpz76LrBltQfMzSBbpUScSDcJN403wANEcTOM9n6cRTUkHqWZwc1BMFCIdvjyQ1ZDFcIwIcLhjBXBMFG3em/SDmJphkQB6V5aGQaszA9XWC4waLsY0D0aIoRSXVmNSXpkfwqd4lryXqExxQMQ93oQ4hr9Mg7PDRMv8ZFyA+RMbzoGzk4vUk22jQtQQnMJWIZTEwBADwI4o9xAXQh2cO2khN+SCcPmeRW0b+8tZn2bPX7nP1Sr+YPYap7kCggWF7d5RkAIIP7aOED8z2XUbjjaVf4JQ/aWiwpcDhSFoB0Y9GswI4gpyuL3QdAjGHRtmUhVQal+hEHXVKKh2nMbvMODr2vkaypAalLlckz3tXJjaLcGO+qHzJ+v/V117ZiSaU3ECrzzFjWjIGDbXSKwffNowKLBW0BrOJV3g6W8EMD7PsI7pwwnAbjhoyERcQni3H5UgE4/SViY3r88Tqb9iUgbxC2E+zoAN+R/s6wPUl8EsTBzrodAdo+WQ5GxuCaX5+JE3N++eAzmDrJ1GPqIry8NbqapJxsSswgz91GKO38KxtpByVDwY1PCPvGKIJXCVig01OfvE5+nLjqKJErbayxRbiQ2bVESpRY/pERp4Satw1BB0m6SAscDJPMNGMbs5wA0iq7e2eE22iZCKMylx1ud/8qFSnyUNNdGAnQvZQV/p4pSt+4v/Yr65ow9qm8uOhJFlFwuO2tdMcZ+GIgGTXSBF1uq8vgy3N1YgvXynAmp1xVhmvdCGsg+VWQfxgzIUXW+a7dC74UjsHmChNdDgLU5q0xgsgkiCJPvQCikfBACqGVvwhHBc/Z9o4RCEffMgDcgtudU+IV2+iIkNMeT0Akj+7Lq6zkCUqCp2N+Nt5RSoWfuQUPVp0imnjVWDSMfl8NIhJAIQiqyoZBB7kKyOx09lg1yl6gty+YzzwuD3F/VwRRA48f/jtC86vPDx/gMHIUIg01IDbLsV/5yLCD/LIBBFpH1h2hhD2s/DUu+lEq+c4xDyZ98HutyGdXlWkhBs8uTPGJ8+FRyN1i6oKCpUNA8LOgHkEtUUk4E6IBaGv94KjCCA1sQZwxt1UNbcajEacX+YuFhPTbVov5vitMuGaP4536I0JUIvo8+jKHYubHLo9h9H+Qx/+WyzM3bLgNg48eogf9ITPLTErlrSA38QTHwGxg3q1TGqYE/SAN/kAf+NLXXjtEBSmheBzZj6rDuVNE+neqVeeymwgl/JYLw9uh42TRv+yh1+4XAMCy+4Bj+Asx8dvvGtr8w/AgJSpvBIk7ajXCZiXmRCGbjOHnJfwH2qoUZ+CE0UbHZCevRVoRuORB4UcSNYQid7CcrqvowIh5xp3sxBowIhemzdvqlUrJ8vr/khE0QgoQqKP99WflHPSnzFyQ/BZD5BEQeGMWQNn5/16BnH2lQggSF8j6/g/PmSr/7z1r6FT8fNH2vnv6uP3D6vPSJ/9lOn61bhkLfWVn5f/1g/vycNaDju+3NwvB9Pmkvr/5P+cqzZb+Nsmdyf/SnMvfg7ddMeRsSnyCV68bDlcrVmGYg+dqf8st5UlFqUuep51WBXLvaTzMiY5rnTPhur6bPgDoE0mvu/MngjJbL/mmKQnn0ADkQNyYIYwOZPltAvG4+HMXrGSBCfw5vZpNL2klBvJ4gcgrxegfG/YXi0I5+Dl3LTXLVixDJRgBRMRp6BfJPj/UZGFmoBmN9tKoM7FJjyyiB7zTAqRJxutvI4FubwXfPYRBXj/gymgE=
*/