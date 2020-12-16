/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_process_name.hpp
 * \author Andrey Semashev
 * \date   29.07.2012
 *
 * The header contains implementation of a current process name attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The function returns the current process name
BOOST_LOG_API std::string get_process_name();

} // namespace aux

namespace attributes {

/*!
 * \brief A class of an attribute that holds the current process name
 */
class current_process_name :
    public constant< std::string >
{
    typedef constant< std::string > base_type;

public:
    /*!
     * Constructor. Initializes the attribute with the current process name.
     */
    current_process_name() : base_type(boost::log::aux::get_process_name()) {}
    /*!
     * Constructor for casting support
     */
    explicit current_process_name(cast_source const& source) :
        base_type(source)
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_NAME_HPP_INCLUDED_

/* current_process_name.hpp
q6qIfo5y/2DAHUZ50uQpmxmTmG5JfbWGPyl9vJxMUUXivka5nxtQ1xXvMvXGVfPoTSGWhWXYTqWxmvLzPO58tb2FKn4NOTM+WMZTT5oaWO9puTsqPH9nrnKzJrAwniTZssc3Cr6owm/iUtfaz4aGd9pU1nq158Hu9pyFhb7/lDrsKUtunwvnAk8ofzs7xF325lGGxE6XxzkV9/scyyOksD3o/HbXw/qBO4ybA7bTjzSRfuQdxOxHvo12j/era6u9lVDtBdZzgBHVvOWeym7ej95tZNQy+ADyBmUzBXeLkFPVTPcQ96u57hCpzuhQ7tbUdnMtTIzyDmtTOPGRuXOD6+w7/mstve/YZ/92zkf/dlbfI6t+Q5kV6D5PtSXpB8W91G/8VHWROouZrrOYW8dyXS/0Pfpg0w+pE2He9+he9yinq8l5V0iIvPeNa8l/tb37Vj4bmEIo6k6FeOlxyWVrGwOVu7uNEc7fnsFf73HeRV2T2Ou5fZjSiUY/SObIHneNLPcIdr+kfUxJN/3S7aPQblzW+NRxuVnTDR1OB+W+GTENNRz6Ba33sNJrwEgdrPvQx5RZgFPb1O5aK51qzKLRk3RUUWaHSFm4Ph/xG0udX12FcTbC/FvOkPPjGx1mOURKOUR5zS113trqi84nm75H2/v5SJuaslfDRdnARvCQeZZqnaJ1JDsjYzrV3l4/nOqCuHfp+wmXjP1O9/qiq8dml22uUw0eVjpjHe8HrWHJ+EnvW9j3nlD2t+rnibXqqjqo9KuFq/51Zupkr/FGj11mmg3L89VE5dd3lrBSzQFJ14uRyr4Fs61w/VzQ6XxG21ii++Mmyn2Yy2ffb+nHddwk7Lp19R5xNS5Zx2Cr3pI6lm816fwI8vo2ZLYl7x9R+rXlWvSp+3KWIn2++37vwdpqHGBOrp+/6HMV12F3kry+m3x4iL/vhNPkLMWI6/TNpEv6Zqd24XCfI31oKPQ1H6XcMVflLs85pf1IedrOXnTsewlD5bM6n8JSHtY+eICcef4SCagAX4AvmueP1y3avtxvylIyp47PcuqDVV3+QLnLcrVwvrcQf132ebI+i+FRZb/HaIL2ZMTxvVVdx/ak688X9Uz7urr+NK7PNfEpnD+nq4yQemiv/yr/HeZ60qfL3Jo51CRSbu0DBqtwc+RawnWel6ny3KPS8aiaF3ao7PEzM3sisfO0t2zl50GZo4sOVcja5pOUTkWX7f5Kt0nHeZ/E+ahym2GPs36GwrxHtZ31cv+1AT4gZqtRuJkIVI/B5+rMR2Q+ZJ33ML9hnuNfO2pS3792ZJ33YEYZyvxCyjVM2pC1bVyzzW2kvfi87xsh586/jQQgbyGvmWew1Jd2QVa6JyTx0r+Sx0GqPWQrAx/PmHGv6+5n4W59GrlTPde60qeq+UqK9BM1POdVKZ2TRj/u/x4kppuMqk5jkPbLdsafbjOX63t/Xzemgfp2kf17vHqu9TulP5BxOlTXnRm4waX1vF5z7q/d1Ff2vY0bLeds3KvMgvR3aOibrd/EU3PmjWZ9i/T/rCvPd2hyVZ3Q5aHrD/mOucp33Q9LHyn56z0HOSgP0QdIIDeZQubvCbHXBfPRS1Y6gfn1jBr3tnNRsqnAjnMQdO1zV1SlLTuVt+jb76vQkffZyr4No2YZ/b7mYWnjvw33/3m+/dmiPudE0hJlfb8ncbbn71b5poCnf6iKDCJ/wysUyV/uX8hfP99T4N527o/v/BVd/U5jYwne7ROPInlwVeeBd1qjGxQ9B7kj7uOKpFXe5vu55sPt3mXLF8e0omuvS5lT0/kymGNdsvl9o/JbdcdO7zPQ/WnWlEg+WvLWXpckzpb3xTcqXeJmq18=
*/