//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IOTA_HPP
#define BOOST_COMPUTE_ALGORITHM_IOTA_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p last) with sequential values starting at
/// \p value.
///
/// For example, the following code:
/// \snippet test/test_iota.cpp iota
///
/// Will fill \c vec with the values (\c 0, \c 1, \c 2, \c ...).
///
/// Space complexity: \Omega(1)
template<class BufferIterator, class T>
inline void iota(BufferIterator first,
                 BufferIterator last,
                 const T &value,
                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    T count = static_cast<T>(detail::iterator_range_size(first, last));

    copy(
        ::boost::compute::make_counting_iterator(value),
        ::boost::compute::make_counting_iterator(value + count),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_IOTA_HPP

/* iota.hpp
esyhsBU8D7aFw2AnmA67qntPOBz2gefCfupu1uXpO2oz0R/hXJd3s5brVjgVbofT4Q64SN23wtvgR/AOTTfF0vdTHVdJV/5OMusa7XB1Gi4mSLjWJhx+jUivCPORhpsQ5D7drfW2U+vtO1pv92i93Qu7qntPeJ/W2y44Ct4PM9Tf6LW4PrReiw56vY6wJewEW6v9Y0mXPzT+do2fqH+LHi9dz1oBE9SepPahsBKeBy+HGeo+HlbBKXAFnK3+C+EVMBeuhIvVXgFXwSp4FbwCroHXw3XwRnFXXfmWzrlhH20vrTH7NL8ZWs4JMFntHdQ+Ck6CmfACzc90mAMz4UpYDNfDxXATXAI3wxJ4O5wLvwvnw4fgQvgbmAV/B3PgP2C+6q0ogHGwECbBEng2nAg7q13XGzNvPXN6PSSwzrWKAvWV6PrVRPhNjX817KL6dobDrXA0vA6er/YpsBbOUD08c9X9EngDzIZbYK66a79hXnXqfiP9qxHh0iydK+g8oxYTgemm4ZLd3nppAxNga/hDd+PO/v5/W6e7+97wWt2vaq3u+pfRj4GpxxzBWL9CfwYmHTMPU4nZhtmHeR1zAtPmlVhr8Cvh9bzhX/j3v/6LxJR+6fJ/vmGVFud7VwB8sTUAHvnKNTycjzzC85fvbzm5JQXyTQv3LrBSnsuLSspyEbwszalYon7XeuIwcWRUzy3JIl5pfs6yfEvWFIxPsMy+9hiVLd+kz/l1mFriHvyG/X131uyZF0w7P2v2mLFTPGsLSMV/bzMFtb+1Ek/1+ZpvP+jNrOCTsIZpacKkWImqZ/QjsV/Gu0u0f7ycaoln66//QMJVM9d06bckTYvZtn2+nVSCxEnC/gfxLyHtWIlTbOK094tTWJKzqMJ8t5z0TdGvTxoTEqYTPtXk2SWyg2wtf78Er3yXubrZ13xcwpUxt2xvZO0TCbegEbpS9fuVrh+QehUZ5CTzTcvUpcomjbvWla0Hv4u6Uxfilm3cpKyOb/y7tQ0M17nrYMwufGq/GaIN5NH0S6vKtR3QPk09mO9MOyVud5GxxJH+Rswk0oxr0jYuKlm/izdCtudrpxlR+k6v8/a1mOs9bTxUHtEHcZJ2qvF6Yje6evOr1V/kmhvNvm3sfC8We3MJny85KizN99dbTznrKGN1pPfjbVzPi803wMkqB/CF2U6YKZ4wZ51rwkwNCFMfaWEjTLM+Jsx0DZNszZI6/+x2TwbMmGDqvonktYW0t3mnkKdP8pOnZzvbnvkGSHlxk/I62s0uvScq3sWH7zL47NjY4J5wN7LyCwpz0CIio9QpdXH43/sYles+pe8suzH3Uv66BtcRCWLu5VnTLuDdOKgsifrReCP0jNSA79fGf7RZI/Wh2FfYbYnwfF02epKPiv9VZkwivp6xYocvLFu21H+N05sS5jqxF5s4AwLbq2MMIowZg8qdY1Au77fmrIC/SLiLyYFDL4HKbsbKuPEbCbPNcp7Hap/b0P9q7zkszLi5tts+g1XGV7sfRUi4nkYWfgGRf02dvtII3eeJOobZMip7/OK+mO/6zrYpdS/jX5Fx0/rVsOWB7dgpA6UenO14Z0zDdnyfp31dHax9OduxeYY460XjNjnl+gmRfTnHa8nbRM1bkurnH6Py13PgLvJWf+q8ZeVU5JnzFFg/pe1f4zJL6KSy1FfF3sM1lv/XYp7CfIgJuOcSXvrmtzzhP8c/ne86w2jFXVl51MeMlfHi7/aTpRbI2OGTlb3nvb7LI0vdReF3N0XHPAnHRddsjIvOiIvuExc9wtJnRCP1U3hlh+VGdsJ1set1kVu8KddEn7Cu1zmh9odUjnGuylY66GtgL30WdsNsJUz2t6U=
*/