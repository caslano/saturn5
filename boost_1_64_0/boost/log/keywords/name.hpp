/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/name.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_NAME_HPP_INCLUDED_

/* name.hpp
tBHN+m0NthPd0DWWollfiTXkzmiNpRHI6bFJVua4JGscUoHsQo4g1vgkKwcpQnYgB5ETSOqEJGsoUoxsQfYgR5HEiazZhCxC7kSeRl5DWuSzLhNSgKxBdiNHEOuyJOszyBRkFbLnspit69gW22JbbIttsS22xbbYFttiW2z7X9/Om/3/+efG/v+iLMvYnylSm/Yval6OIGX2eOsFvAf12/+XhKj9GWZN9RH7e5Hn7/xEwm6wuvF/htXIfRz2Ah3TG7SOgPuYXvWrNpHrtquHX3e7eq72RI1/Mwe1NGROEGsKUNoNn7cYPufYubaAsVuGHeT67ZY57QVl6wnnavqLkBvtseILzbwcU1+jy8uqGSOvs60sMw/d45iH3gY+KWEnUgZxbnWlcXvc1nww8yIfEz8z+DbicatD4oi+DvEbqQ7NXMqnxU+ezHt2q1eNw8yLukvrM9q5hfF2/Wk5pTvrz+S94XXot9P8vhrj/KbXZ6//DriZOsxZFLEOjdknl3o07S5fwq/3zuQrYqG3pWtdcg5n2bJVayID80dXXaM2dHU+VZbsZ8tcrJexHXCVL51eOx2pYr+KacBal0dwN7ZTyH9JhXQWEvY4bhUSdqk3YC+gotRpJ2x7qe0eb859u+w3kfDHCD9L82iHH9BSzo2t5IDNzBJxX+K9hPSP9bYIsyfVSc/zjOTpXnqnNhzrKSuKrLA6mvnOixaLfR/qMEnO/RrnXiJxL/MmGVtY88TtDdw2ittMr/ZnbNrO9XxHfPnmm15/SdMmCU/WtdxOEIeWidZJwIbCVAl7g3cqsc3ytjJ5SrS4JDjKbtIinWeHKRiPKvUiOdZS0nmUc1TLfqlX45A0UPsmjjIp75Sw8v887Sgb99UkaE6ary8sgDdmBGwa1dr9pe4fbs84arUN+TC/n6Ny1jtsO6xTfxtgAmE3QmyN8NvEKfJCax9r9dg9rcQfErC9lROlPRzbPsRVi419CNe2zjHR4dQOHFO95pjUD3XGMeospE8+lKjjQyyl2nA7siS0Pddvw82tzRKP6Tsn49cKqfefi3snM+el8AzXePHPb7H+h+e3XPOoh+OHN179wPWbKrafXnhHs20r930Qef6D+7yX/7/5LZ+WeSznar6KjnvR+0Puj13GvezX8dGPwXR4AHaCT8K+8CAcqONsJ8MfwsvhC3AafBoWwmfgIvhjuE7d18Nn4Rfgj+B39PjD8PvwMHwcHtHjp2CF/74HztX0JiPFmt77Nb3fgG11PFVvuAcOgI9oeh+CeXAvHAe/DfPhd+CV8GFYJP51XG2c3lfoPc1ROEHGuZvxLWZ8zRjYA86An4Gz4QWwHH4V1sB7Nf8Xwbthb3gPzIG7YD/4Ndgf3g8vgU/BEfAoHAV/DQfC9+EgeBoOhi1I5BDYBubBjnAs7A/Hw5FwAsyDE+EceBmcD6fDGjgDroIz4TZ4JbwNzoL3wdlwD5wMn4RT4MvwcvgLWABPwSJ4Gs6F/4DzYVwc9QXjYQlsBhfC1nAx7ACXwt6wEg6AK+E4eB28HF4PZ8JVsACuhdfDG+HtcD28C1bBb8EauA9uhI/Cm+CTcBN8Ct4MfwVvgb+FW+BJuBUmUt/bYQq8DabC22FHuANmwy/Ai+FdMBfeDafAnXAm/BKsgl+GNXAX/By8F26BX4F36P4pqWe9JsJuqueNRC/YdHy6zSOwMXxR2+fPVA9fggWNoh/Hw3gKGQPRD5mCrLTF/sYN+QZ9Tsb4/C+P76l7XM/5G9PjMp6n3rE8n+Q4nrrG8Oj4nbrG7oSO2Tnv43XCx+q4jtM552N0dHzOGY3N+STG5ZzNuu0fx3icMxmLM2US42CQ3ciRSbGxMLEttsU=
*/