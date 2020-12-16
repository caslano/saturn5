// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace json_parser
{

    //! Json parser error
    class json_parser_error: public file_parser_error
    {
    public:
        json_parser_error(const std::string &message, 
                          const std::string &filename, 
                          unsigned long line): 
            file_parser_error(message, filename, line)
        { 
        }
    };

} } }

#endif

/* error.hpp
0b71i+s6zAyCqOdQws9srCw1bISzEuYnsz0oKyzipmzVjnOAl6ib1Kgow2WBJDO5e+CLe0lqHXqsGQdRJ1rZpDw8AbCmPmWDSW19oj2WeXBc0n6q6htItpeUlcypNe7G+Nm+Wy9oyGw70VazwHsWaIiKUX0b49A/Pt6dLQ9U9X0BYKP0QF32Xgw8cekIdYrJbIXcQn8bWTJeED0KsuxrKxzUsuA6yazxiseb8EFXxFveQAgUxgP6Gd/rtiIY6Pk+tOd7O0Vb63bGq7V9fNc5jCiqL7+/2x6H2fFEysD7mMzVpqMtIyW6vRphGgDSbR+W5W2WtX55CGgUUlng1jimEsnfp0yfyh0vK4d+g82A8YRQ9nsS//Ocl1ZShs8XtUwhyAX1VHX8OuPj9lD99lwvqOmt79XnD4NfzPuBJoiQqZ9dQCfW2+GTErZosX3NH+s675gse6mLBW4lq1U9b4nfS6ZgIaHCk4o+lfhI3Yk1KC5mqM/+Afy6TYDKWXYZyJFDVfbXv0bIWX0v8Rfg1Bquy++5+uj+5jbjRSNxaDyp36KLldzMgif2Sihj9ov23NgLWGN+1sb4usDhtosBS/iNAVfzD/re2C9k6+8DfJf9OAgZOdwPvLIyZvvwovYCsiVR3rbt6oVF2eNosxHCapmrvo+jLJMPH/NXytYesZZU0gU8rL/A07pFio3cW/H+TqNiRjdNwgM9d8hfA+88eRKrus+gfNN2tMdgbmT7bJvl7sBp2nC2zjkJHGZnGSYk4zdT8+nQBOQC+x3g1xU7UADDWMj5ghU4K6Hb1LSp+ur7mIeqQdyO3jL8+T5Ut+GM3Rd1dwrmFdY94PBFcz++PQXfaus+FK+oV6U0IDA9eLekbnkGcEf5Wup9cWP8nKP9yjVp/2JvRNiaWhRip4U2Yu0E/XKEoabWqG+i33AgomYKvKNu1a7nXR38IBfSJmqRjYlvpHMEzguAYwRN9ulLG3PLXiMvtQf1OVYkPs2VV5v2w0I4VnTRV/W1+rVXVzKLygcpmo36kC8Npz/rG/1t6TfA78dZH72elasuytP3t+I7rd+W3f+uq9fWndrc+QDgtp1u79ceQT4H5paW/rTRY2w6hmT4X9zuQx9wOfsYaGijneT30w35tfXY5wDfxWdBxA1fo29tu3gJNIyeamk7J0YHzKW9agy/vMtc531zK+DUnI5MlzTv7XOb9xvAqdsuXB/ta9IwjbiAT0zZDd9uymBtbJo2tJpztzBtaIINFbQDeqium2vr1o8A576Pus/i6mRfQh3id+ZrqdvPRilXdf/DVdk8QDeiizCUKMP90aQ0VJ/8FMwa/pDaur1NukbJ+S+uPtofrIvReP663g+1PczlATdbGNpbN8eosTf6U2M+2L6prxvfHC6VyzL/NGVs3zXxveTe5p6+vvfZA5wSe5tsVpsBo/btTRvCsjcPHeAydcW9u/SlaXTDVkrjapmBewFnjiQvKocKVGSFn+FjQyE05cerzF/6Hly9ZrP6su/27q3renv9vNbeug+Ai/TI/coM7B17vh1LZhOzG6noXn/vKNk0HUP+tbpO4F2n/cxYp0EackfnBnNAJtdl9e3GZFeUJOdqDUvlIoaxAs7e0XvOuh7bt7du71BnkbzsB7xh29Z8A3cwOA35H99b32eZsqAP33TT3q/PzUN762ucvR5cFXCtoFrGLthBapGNrW3QAB/7vMUvYHv0hVSy/othd6YgAJqw80iPiT9Ujzvvre+RbV/9byyfizEMRNn23rp/xfTUfsEPZev+aPwmdlepNpRo/H+MthiDQI6BD/oNhwiNYQxY00duz4scOM0zOHvtnpM4dddJwzZyrq78fL0gg9Q=
*/