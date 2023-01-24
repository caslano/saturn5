/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   contains.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string contains a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c contains functor
struct contains_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_iterator left_iterator;
        typedef typename U::const_iterator right_iterator;

        typename U::size_type const right_size = right.size();
        if (left.size() >= right_size)
        {
            const left_iterator search_end = left.end() - right_size + 1;
            const right_iterator right_end = right.end();
            for (left_iterator it = left.begin(); it != search_end; ++it)
            {
                left_iterator left_it = it;
                right_iterator right_it = right.begin();
                for (; right_it != right_end; ++left_it, ++right_it)
                {
                    if (*left_it != *right_it)
                        break;
                }
                if (right_it == right_end)
                    return true;
            }
        }

        return false;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_CONTAINS_HPP_INCLUDED_

/* contains.hpp
eCdPa+vvjs/nIsfrWjPdialtAktXYTbGwGBnaGAdPP/4SnUaQfMGoJnE2VkCbxD1HdgtU0XvKXXzeN8vsYjX+bpkA9dMqLlHLrQ7tk8CmsRpWnmiaJaP0GluzjgjDqtXlR3OWOxsuEewSPBEg+vx3D7HhlJ0rXEtqCRq4aemi/0XTRuQqt/Ma21Jj8d5NA77uyANJUfv3GPA9iKg4f5VRtN26wTU3ka7g/7oZZXPnlP2BhnL3PHFFwkA8RaNVztTcAE/QsYjuGgbq6pLeGRFGtPDxzN09V6wuDHVAYfAh3rfT0JgJyyg40q6agPNFPAAxlpzsH29CyMRr3euITJy37mlb7pxIAWIv8QbYhVMa5b4YqR9eSvrtZIbKSNjmW8SSHn2l6VWDZiN8e7NRX8rosJSo1VUpfN1r1iFBGRob3fuUDZb4372cy0xQRvzPTmdDp64e3BNfrHVr4DP4LcHXAHonSS8dH85LmbjmjybQA/rm+yIhXvMsZsfhs7GOQKaIF4aiQjECX1pcXXp8NfIFxSTUtPsT2gBisv9A7PQZH5/9WePOG8q+ohuzA58VZ14Jm1wS6EtV2zm727u6CdiqMXU7hx7QdgKm2102rTFgoZkouYvz/hweInfqL/RecPzXi8pwqz1jh+PWJhD7t2O/PKZ0h9w9pwW10Zv66LXscB+s1cjzn+2WZFHyFhsQpNzUZIK3jBeqOQG56/v
*/