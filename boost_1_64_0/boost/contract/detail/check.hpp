
#ifndef BOOST_CONTRACT_DETAIL_CHECK_HPP_
#define BOOST_CONTRACT_DETAIL_CHECK_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/config.hpp> 
#ifndef BOOST_CONTRACT_NO_CHECKS
    #include <boost/contract/core/exception.hpp>

    /* PRIVATE */

    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #include <boost/contract/detail/checking.hpp>
        #include <boost/contract/detail/name.hpp>

        #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
            if(!boost::contract::detail::checking::already())
        #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) \
            /* this name somewhat unique to min var shadow warnings */ \
            boost::contract::detail::checking BOOST_CONTRACT_DETAIL_NAME2( \
                    guard, __LINE__);
    #else
        #define BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ /* nothing */
        #define BOOST_CONTRACT_CHECK_CHECKING_VAR_(guard) /* nothing */
    #endif
    
    /* PUBLIC */
    
    #define BOOST_CONTRACT_DETAIL_CHECK(assertion) \
        { \
            try { \
                BOOST_CONTRACT_CHECK_IF_NOT_CHECKING_ALREADY_ \
                { \
                    BOOST_CONTRACT_CHECK_CHECKING_VAR_(k) \
                    { assertion; } \
                } \
            } catch(...) { boost::contract::check_failure(); } \
        }
#else
    #define BOOST_CONTRACT_DETAIL_CHECK(assertion) {}
#endif

#endif // #include guard


/* check.hpp
UWgSTOQhOg98p0Aj0C5uMfUE2cUnm3F3JNghQjfQLm6ryLWLjzR28ZEgr5SRVyfUqWmdL0jL9TmmCwEf4Z+Ybm3ciNy9CbZxT604uPhDTj+dVpF9//0WqYvvJsH6XjybbZlU5jyHs2HAXpnC347QJuEzEnw3yJ2QkDzee5V58C1K6lqkeaHMHSHW21V63kvtF/O9stl9rwz58Rj0XtB7K3K/TUq4Ali9IWek87ljKMfntCtyfUMhSlvf2TodqwLX+YxjdT2sKRB7i+Oeo83aC3gEJzxeGzg2OuL1ER7aJdY/069w4AnhZ1bAWiPxKRW/NsDfNgj0eC4aGcSBbxoXeleG6SDfmyrwLSsfXjfD9w/aeOBJqNONBetnScva9ATs0baYtWmrma/blKbAXD6u2e8z+HdNBznzvkbnr/gFDY9W1+8AuTw9dWSddLZZ621bP6zrgdhZ+G7GuVD2oYCy5xEc99khaSP9z/CPQ9rYpIyLducnzbjScTdXdP0FBm7Xj09rO2R8I+3PmrJufGBM2c+ZeSZ3UOVtAolLbGhoHfQ/0/gCjL8dskb00/9rC+RsJ4y/LwKt6FL/3DGe3b7MwN+7NBf+FW0rw03sBCgbEdoop69B2Ygp+3WQg7QBeWM5fEPpC46l/03p14i1y2Ve6rnuQsG/hvCHaO0YX+xq7WnpDrW1tzV6e1x6HKc7OttXd3TTOsB54zlvTWNnS9OpmjeB8+ra21sba9s8Py+P8/iwEacncrqxs7O9k/T2JD534Hi+tsLVSu6AhPuc794mSzqdfUq5ySS1vcfphKeOyeqE6yvGdO6JKMHJFMw2Z1K+I/SGZC29gdIexID5bgWvpcxV0sPzlHxZihc8jdVSEhCrpVTWZS1XJnFQ5ss5jO9V4DmMdEx9SvyXrFuNx+WuWydSuqjYvI1FdBzuzRXoH2Fce76ex9Qtgv9Dwb/RC46ZdCO3n7iJD0eH6ChbEs6r/IBgBQ62hY7qRqXrCKblShysbyDNZxcFv9TluSOoiv5KFr/MwciVkYxmKmLYrRUiG3KQUKl0JEWuDjohnpI4eJNIAD8COVYRrkSyUXFChp5vQjuNHATOTTMYI+fEWVG8C52XgYW3KgztORpUfC+6Us4E3XaQNp3GuPG/P4UjKXbfRJMRD+uJbwxF+sOJpCd5bM+FybYa0Hyt/w6ov2QM9S/R8+qunIxzHMN3cv76eHwgGh4SP497i5DGYf5PXB+P4S3CzVLHdRXZtwihbemUjAWQO98JGyaIP3soX8ZmifYHSV3xf8rjKuRp2SqZc5Uyx34GMqmhsSHVwdiQDBkbOM9sLIqfV0i8AYATjNqGbzMH+Vfe4v2iQu6njFyW8Wlu8/2UX4ledzrI6nWXZ3XAvRUSPwHo40/rwPgJ95n22DKWP2zP/ZSPspoAdhD73Y1PhfjaozpHY7c8fYx+R9W1nGlpfHGmecsRuWv5H2A9deVxPf0jwVBG04tzv+s8RnkYK2VaseBDvfg9+HG/Ll4ndA160tilTxk782nlQWCUD/1K8U4oD+O3NMi97hugn1U2mka5Pg71aRu0PNJz/YZw0rEqI07fatKkn60MWb5ULjfeiYHfauCvGvgPDPzv0H83CIxkz3W/Tmld82iMyJrGf2s/Kh6sccHxeN4w41Prov+Zj/8oDVhTrU90XGUWh7+7MK7xm1b643zvEQznEOx9ObFVhyTQ3csQW3WohQL/kbe9nhU450ts1fpUYuCU8MZoeng1xTfzMmUOc7A4XW+JD5wc3dZFX52i3hqJj5dfmXOXqL69rYtMs1BnY22D/O3yujvbW1nnjYbAOnBNkH31f6Dr+nNyJdgz0m/2bschhOM=
*/