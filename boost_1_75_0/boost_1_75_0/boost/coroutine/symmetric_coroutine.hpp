
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_SYMMETRIC_COROUTINE_H
#define BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

#include <boost/config.hpp>

#include <boost/coroutine/detail/symmetric_coroutine_call.hpp>
#include <boost/coroutine/detail/symmetric_coroutine_yield.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {

template< typename T >
struct symmetric_coroutine
{
    typedef detail::symmetric_coroutine_call< T >   call_type;
    typedef detail::symmetric_coroutine_yield< T >  yield_type;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_SYMMETRIC_COROUTINE_H

/* symmetric_coroutine.hpp
vfz/jc48xndtHy5ffNr+G63Cs0Zo1a52dHJHlm6yRpCqs/8R5+fLNEdl/sG9TDP87uAIKAB4cUMg2n5vEPN66V9I2WxQNHUGOKoPesH05rkjhwJ7VS/DSxleMNnVP5IroH0wGM/7R04z5PUTuwbX/yBN/0Fq0Ri+BJJ88QCbdO9Wzh0JDz15ieKzf5yw/Jzswt7eej4WoGvXBXgoaNZgWCsKtsnB0LSZbWbf40WvUbEcoOF6e2DrxyyhyA9T/KtzfzPXxNEbKjZyTimRtUn/B4bN/vHHRA5odHLcMWKTOIRgKY/CkOlm4Dzzu3L3Y0kA8pNv5PM6w6KHxuFEcwsRP0ai8sdV89Y/cXKMrX21vef+m+CVv/rfRGAThzD98QkJxa5T+IsAmyyENkQNfd9A9SIBmfbxAb/i89JdbY2XxPA6O+FbS/aQn2F1KxM26GHuzZhCcWnIHFYY5LOioZmoYYfLEVJWJ6TfNW0UW17jbV+hcgC2lrChasCgc9botFw7r7msq+SuYSOg6fjbZ0OaARNdhlYsCDLYNoxCMZCCg0StO/BMKsmhnO32mLZVuna+qJ9DfNtkUOlGSYs0NiI5yVcjugVtZiTc0Duecq2PdGjqqzF9l0ygTzw2s76gFERWwGZRd6tDWDw+7z5lOPPQqijF2Pl9LNxtaPuGzSOqcflukMAhFs8AUY94EIdQf8d5vpG1OW+REYHY07ZZ
*/